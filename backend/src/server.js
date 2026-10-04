import 'dotenv/config';
import express from 'express';
import cors from 'cors';
import bcrypt from 'bcryptjs';
import jwt from 'jsonwebtoken';
import pg from 'pg';

const { Pool } = pg;
const app = express();

const PORT = Number(process.env.PORT || 5000);
const JWT_SECRET = process.env.JWT_SECRET || 'dev-only-change-me';

const pool = new Pool({
  connectionString: process.env.DATABASE_URL
});

app.use(cors({
  origin: process.env.FRONTEND_ORIGIN || true
}));
app.use(express.json());

function signToken(user) {
  return jwt.sign(
    { id: user.id, email: user.email, role: user.role, fullName: user.full_name },
    JWT_SECRET,
    { expiresIn: '2h' }
  );
}

async function auth(req, res, next) {
  const header = req.headers.authorization || '';
  const token = header.startsWith('Bearer ') ? header.slice(7) : null;

  if (!token) return res.status(401).json({ error: 'Authentication required.' });

  try {
    req.user = jwt.verify(token, JWT_SECRET);
    next();
  } catch {
    return res.status(401).json({ error: 'Invalid or expired token.' });
  }
}

app.get('/api/health', async (_req, res) => {
  try {
    await pool.query('SELECT 1');
    res.json({ ok: true, service: 'IIH College API' });
  } catch {
    res.status(503).json({ ok: false, error: 'Database unavailable' });
  }
});

app.get('/api/courses', async (_req, res) => {
  const { rows } = await pool.query(
    `SELECT id, code, name, degree_level, description, duration_years, tuition_note, featured
     FROM courses ORDER BY featured DESC, code`
  );
  res.json(rows);
});

app.get('/api/courses/:code', async (req, res) => {
  const { rows } = await pool.query(
    'SELECT * FROM courses WHERE code = $1',
    [req.params.code.toUpperCase()]
  );
  if (!rows[0]) return res.status(404).json({ error: 'Course not found.' });
  res.json(rows[0]);
});

app.post('/api/contact', async (req, res) => {
  const { name, email, phone = '', message } = req.body;
  if (!name || !email || !message) {
    return res.status(400).json({ error: 'Name, email and message are required.' });
  }

  await pool.query(
    'INSERT INTO contacts (name, email, phone, message) VALUES ($1, $2, $3, $4)',
    [name, email, phone, message]
  );
  res.status(201).json({ message: 'Your message has been received.' });
});

app.post('/api/auth/register', async (req, res) => {
  const { fullName, email, password } = req.body;

  if (!fullName || !email || !password || password.length < 8) {
    return res.status(400).json({ error: 'Full name, email and an 8+ character password are required.' });
  }

  const exists = await pool.query('SELECT id FROM users WHERE email = $1', [email.toLowerCase()]);
  if (exists.rows[0]) return res.status(409).json({ error: 'Email is already registered.' });

  const hash = await bcrypt.hash(password, 12);
  const { rows } = await pool.query(
    `INSERT INTO users (full_name, email, password_hash)
     VALUES ($1, $2, $3)
     RETURNING id, full_name, email, role`,
    [fullName.trim(), email.toLowerCase(), hash]
  );

  const user = rows[0];
  res.status(201).json({ user, token: signToken(user) });
});

app.post('/api/auth/login', async (req, res) => {
  const { email, password } = req.body;

  const { rows } = await pool.query(
    'SELECT * FROM users WHERE email = $1',
    [(email || '').toLowerCase()]
  );

  const user = rows[0];
  if (!user || !(await bcrypt.compare(password || '', user.password_hash))) {
    return res.status(401).json({ error: 'Invalid email or password.' });
  }

  res.json({
    user: {
      id: user.id,
      fullName: user.full_name,
      email: user.email,
      role: user.role
    },
    token: signToken(user)
  });
});

app.get('/api/auth/me', auth, async (req, res) => {
  const { rows } = await pool.query(
    'SELECT id, full_name, email, role, created_at FROM users WHERE id = $1',
    [req.user.id]
  );
  if (!rows[0]) return res.status(404).json({ error: 'User not found.' });
  res.json(rows[0]);
});

app.post('/api/enrollments', auth, async (req, res) => {
  const { courseCode } = req.body;
  if (!courseCode) return res.status(400).json({ error: 'courseCode is required.' });

  const course = await pool.query('SELECT id FROM courses WHERE code = $1', [courseCode.toUpperCase()]);
  if (!course.rows[0]) return res.status(404).json({ error: 'Course not found.' });

  const duplicate = await pool.query(
    `SELECT id FROM enrollments
     WHERE user_id = $1 AND course_id = $2 AND school_year = '2026-2027'`,
    [req.user.id, course.rows[0].id]
  );

  if (duplicate.rows[0]) {
    return res.status(409).json({ error: 'You already submitted an enrollment for this course.' });
  }

  const { rows } = await pool.query(
    `INSERT INTO enrollments (user_id, course_id)
     VALUES ($1, $2)
     RETURNING id, school_year, status, submitted_at`,
    [req.user.id, course.rows[0].id]
  );

  res.status(201).json(rows[0]);
});

app.get('/api/my-enrollments', auth, async (req, res) => {
  const { rows } = await pool.query(
    `SELECT e.id, e.school_year, e.status, e.submitted_at,
            c.code, c.name
     FROM enrollments e
     JOIN courses c ON c.id = e.course_id
     WHERE e.user_id = $1
     ORDER BY e.submitted_at DESC`,
    [req.user.id]
  );
  res.json(rows);
});

app.get('/api/dashboard', auth, async (req, res) => {
  const [user, enrollmentCount, recent] = await Promise.all([
    pool.query(
      'SELECT id, full_name, email, role, created_at FROM users WHERE id = $1',
      [req.user.id]
    ),
    pool.query('SELECT COUNT(*)::int AS count FROM enrollments WHERE user_id = $1', [req.user.id]),
    pool.query(
      `SELECT e.id, e.status, e.school_year, c.code, c.name
       FROM enrollments e JOIN courses c ON c.id = e.course_id
       WHERE e.user_id = $1 ORDER BY e.submitted_at DESC LIMIT 5`,
      [req.user.id]
    )
  ]);

  res.json({
    user: user.rows[0],
    enrollmentCount: enrollmentCount.rows[0].count,
    recentEnrollments: recent.rows
  });
});

app.use((err, _req, res, _next) => {
  console.error(err);
  res.status(500).json({ error: 'Unexpected server error.' });
});

app.listen(PORT, () => {
  console.log(`IIH College API running on http://localhost:${PORT}`);
});
