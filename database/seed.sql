INSERT INTO courses (code, name, description, duration_years, tuition_note, featured)
VALUES
('BSCRIM', 'Bachelor of Science in Criminology',
 'A college program focused on criminology, criminal justice, law enforcement, investigation and community safety.',
 4, 'Contact the admissions office for current tuition and miscellaneous fees.', TRUE),
('BSTM', 'Bachelor of Science in Tourism Management',
 'A tourism and hospitality program covering destination management, travel operations, events and customer service.',
 4, 'Contact the admissions office for current tuition and miscellaneous fees.', TRUE),
('BSIS', 'Bachelor of Science in Information Systems',
 'A technology program focused on business processes, systems analysis, databases, software and information management.',
 4, 'Contact the admissions office for current tuition and miscellaneous fees.', TRUE),
('BSAIS', 'Bachelor of Science in Accounting Information Systems',
 'A business technology program combining accounting fundamentals with information systems and data management.',
 4, 'Contact the admissions office for current tuition and miscellaneous fees.', FALSE),
('BSA', 'Bachelor of Science in Accountancy',
 'An accountancy program covering financial reporting, auditing, taxation, management accounting and professional preparation.',
 4, 'Contact the admissions office for current tuition and miscellaneous fees.', TRUE),
('BTVTED', 'Bachelor of Technical-Vocational Teacher Education',
 'A teacher education program designed for technical-vocational instruction, pedagogy and skills-based education.',
 4, 'Contact the admissions office for current tuition and miscellaneous fees.', FALSE)
ON CONFLICT (code) DO UPDATE SET
name = EXCLUDED.name,
description = EXCLUDED.description,
duration_years = EXCLUDED.duration_years,
tuition_note = EXCLUDED.tuition_note,
featured = EXCLUDED.featured;
