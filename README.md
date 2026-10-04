# IIH College Full-Stack Website

A complete starter website for **IIH College** based on the school information visible in the supplied reference image.

## Stack

- Frontend: HTML5, CSS3, vanilla JavaScript
- Backend: Node.js + Express + JWT authentication
- Database: PostgreSQL
- Algorithms: C++17
- Optional local development: Docker Compose for PostgreSQL

## Project structure

```text
iih-college-website/
├── frontend/          # Public website + student dashboard UI
├── backend/           # REST API + authentication
├── database/          # PostgreSQL schema and seed data
├── cpp/               # 3 C++ algorithms
├── reference/         # Supplied Facebook-page reference image
├── docker-compose.yml
└── README.md
```

## School information used

- Name: IIH College
- Location: Dela Rama Bldg., Buenamar St., Brgy. Nova Proper, Novaliches, Quezon City, Philippines
- Phone: 0975 810 5308
- Email: iihcolleges@gmail.com
- Enrollment: SY 2026–2027
- College enrollment fee shown in the reference: ₱500
- Senior High School cash allowance shown in the reference: ₱2,000

> Verify these details with the school before production deployment.

## Courses

- BSCRIM — Bachelor of Science in Criminology
- BSTM — Bachelor of Science in Tourism Management
- BSIS — Bachelor of Science in Information Systems
- BSAIS — Bachelor of Science in Accounting Information Systems
- BSA — Bachelor of Science in Accountancy
- BTVTED — Bachelor of Technical-Vocational Teacher Education

## Run locally

### 1. Start PostgreSQL

```bash
docker compose up -d db
```

Or create a PostgreSQL database manually and run:

```bash
psql -U postgres -d iih_college -f database/schema.sql
psql -U postgres -d iih_college -f database/seed.sql
```

### 2. Start backend

```bash
cd backend
npm install
copy .env.example .env
npm run dev
```

Linux/macOS:

```bash
cp .env.example .env
```

Backend runs on `http://localhost:5000`.

### 3. Start frontend

The frontend is static. You can serve it with any static server, for example:

```bash
cd frontend
python -m http.server 5173
```

Open `http://localhost:5173`.

### 4. Build C++ algorithms

Requirements: C++17 and CMake.

```bash
cd cpp
cmake -S . -B build
cmake --build build
```

The three programs are:

- `course_recommender`
- `student_ranker`
- `enrollment_allocator`

They are intentionally kept in their own folder so the academic/algorithm code is separate from the web application.

## Demo account

The seed file creates a demo student account:

- Email: `student@iihcollege.edu.ph`
- Password: `Student@123`

For production, change/remove this account and use a secure password policy.

## API

### Public

- `GET /api/health`
- `GET /api/courses`
- `GET /api/courses/:code`
- `POST /api/contact`
- `POST /api/enrollments`

### Authentication

- `POST /api/auth/register`
- `POST /api/auth/login`
- `GET /api/auth/me`

### Student

Requires `Authorization: Bearer <token>`:

- `GET /api/dashboard`
- `GET /api/my-enrollments`
- `POST /api/enrollments`

## Production notes

Before deploying:

1. Use HTTPS.
2. Replace JWT secret.
3. Use a managed PostgreSQL database.
4. Add email verification and password reset.
5. Add CSRF/rate limiting and stronger validation.
6. Move uploads to object storage.
7. Add a real admin role and audit logs.
8. Verify all school contact details, tuition, schedules and accreditation claims.
