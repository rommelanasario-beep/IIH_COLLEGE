const API = 'http://localhost:5000/api';
let courses = [];
let authMode = 'login';

const $ = (selector) => document.querySelector(selector);

async function api(path, options = {}) {
  const token = localStorage.getItem('iih_token');
  const headers = { 'Content-Type': 'application/json', ...(options.headers || {}) };
  if (token) headers.Authorization = `Bearer ${token}`;

  const res = await fetch(API + path, { ...options, headers });
  const data = await res.json().catch(() => ({}));
  if (!res.ok) throw new Error(data.error || 'Request failed');
  return data;
}

async function loadCourses() {
  try {
    courses = await api('/courses');
    renderCourses();
    $('#enrollCourse').innerHTML = courses.map(c =>
      `<option value="${c.code}">${c.code} — ${c.name}</option>`
    ).join('');
  } catch (error) {
    $('#courseGrid').innerHTML = `<p class="muted">Unable to load courses. Start the backend server first.</p>`;
  }
}

function renderCourses() {
  const query = ($('#courseSearch').value || '').toLowerCase();
  const filtered = courses.filter(c =>
    `${c.code} ${c.name} ${c.description}`.toLowerCase().includes(query)
  );

  $('#courseGrid').innerHTML = filtered.map(c => `
    <article class="course-card">
      <span class="course-code">${c.code}</span>
      <h3>${c.name}</h3>
      <p>${c.description}</p>
      <p class="muted">${c.duration_years}-year program</p>
      <button class="btn btn-primary enroll-course" data-code="${c.code}">Choose this course</button>
    </article>
  `).join('') || '<p>No matching course found.</p>';

  document.querySelectorAll('.enroll-course').forEach(btn => {
    btn.addEventListener('click', () => {
      $('#enrollCourse').value = btn.dataset.code;
      location.hash = 'admissions';
    });
  });
}

async function loadDashboard() {
  const token = localStorage.getItem('iih_token');
  if (!token) {
    $('#dashboardContent').innerHTML = 'Log in to view your student dashboard.';
    return;
  }

  try {
    const data = await api('/dashboard');
    $('#dashboardContent').innerHTML = `
      <div class="dashboard">
        <div class="metric"><span>Student</span><strong>${escapeHtml(data.user.full_name)}</strong><small>${escapeHtml(data.user.email)}</small></div>
        <div class="metric"><span>Enrollments</span><strong>${data.enrollmentCount}</strong><small>Submitted records</small></div>
        <div class="metric"><span>School Year</span><strong>2026–27</strong><small>Current intake</small></div>
      </div>
      <div class="enroll-list">
        <div class="enroll-row"><strong>Recent enrollment</strong><strong>Status</strong></div>
        ${data.recentEnrollments.length ? data.recentEnrollments.map(e => `
          <div class="enroll-row"><span>${e.code} — ${escapeHtml(e.name)}</span><span class="badge">${e.status}</span></div>
        `).join('') : '<div class="enroll-row"><span>No enrollment yet.</span></div>'}
      </div>
      <button class="btn btn-primary" id="logoutBtn" style="margin-top:18px">Log out</button>
    `;
    $('#logoutBtn').onclick = () => {
      localStorage.removeItem('iih_token');
      loadDashboard();
      updateLoginButton();
    };
  } catch {
    localStorage.removeItem('iih_token');
    $('#dashboardContent').innerHTML = 'Your session expired. Please log in again.';
    updateLoginButton();
  }
}

function escapeHtml(value) {
  return String(value).replace(/[&<>"']/g, ch => ({
    '&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#039;'
  }[ch]));
}

function updateLoginButton() {
  $('#loginBtn').textContent = localStorage.getItem('iih_token') ? 'Dashboard' : 'Student Login';
  $('#loginBtn').onclick = () => {
    if (localStorage.getItem('iih_token')) {
      location.hash = 'dashboard';
    } else {
      $('#authDialog').showModal();
    }
  };
}

$('#courseSearch').addEventListener('input', renderCourses);
$('#navToggle').onclick = () => $('#navLinks').classList.toggle('open');
$('#closeAuth').onclick = () => $('#authDialog').close();

document.querySelectorAll('.auth-tabs button').forEach(button => {
  button.onclick = () => {
    authMode = button.dataset.mode;
    document.querySelectorAll('.auth-tabs button').forEach(b => b.classList.remove('active'));
    button.classList.add('active');
    $('#authTitle').textContent = authMode === 'login' ? 'Student Login' : 'Create Student Account';
    $('#authSubmit').textContent = authMode === 'login' ? 'Login' : 'Register';
    $('#nameField').classList.toggle('hidden', authMode === 'login');
    $('#fullName').required = authMode === 'register';
    $('#authMessage').textContent = '';
  };
});

$('#authForm').addEventListener('submit', async (event) => {
  event.preventDefault();
  const payload = {
    fullName: $('#fullName').value,
    email: $('#email').value,
    password: $('#password').value
  };

  try {
    const data = await api(authMode === 'login' ? '/auth/login' : '/auth/register', {
      method: 'POST',
      body: JSON.stringify(payload)
    });
    localStorage.setItem('iih_token', data.token);
    $('#authDialog').close();
    $('#authForm').reset();
    updateLoginButton();
    await loadDashboard();
    location.hash = 'dashboard';
  } catch (error) {
    $('#authMessage').textContent = error.message;
  }
});

$('#enrollForm').addEventListener('submit', async (event) => {
  event.preventDefault();
  if (!localStorage.getItem('iih_token')) {
    $('#authDialog').showModal();
    $('#enrollMessage').textContent = 'Please log in first.';
    return;
  }

  try {
    await api('/enrollments', {
      method: 'POST',
      body: JSON.stringify({ courseCode: $('#enrollCourse').value })
    });
    $('#enrollMessage').textContent = 'Enrollment submitted successfully.';
    await loadDashboard();
  } catch (error) {
    $('#enrollMessage').textContent = error.message;
  }
});

$('#contactForm').addEventListener('submit', async (event) => {
  event.preventDefault();
  const form = new FormData(event.target);
  try {
    await api('/contact', {
      method: 'POST',
      body: JSON.stringify(Object.fromEntries(form.entries()))
    });
    event.target.reset();
    $('#contactMessage').textContent = 'Thank you. Your message has been received.';
  } catch (error) {
    $('#contactMessage').textContent = error.message;
  }
});

loadCourses();
loadDashboard();
updateLoginButton();
