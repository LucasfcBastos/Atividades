
-------------------------------------------------------------------------------------------------
-- SEGUNDA QUERY / CRIAÇÃO DE TABELA

CREATE TABLE clinic (
    id INT IDENTITY(1,1) NOT NULL,
    costume_name VARCHAR(100) NOT NULL,
    address VARCHAR(200) NOT NULL,
    number INT NOT NULL,
    cep VARCHAR(11) NOT NULL,
    corporate_reason VARCHAR(100) NOT NULL,
    PRIMARY KEY (id),
);

CREATE TABLE specialty (
    id INT IDENTITY(1,1) NOT NULL,
    name VARCHAR(100) NOT NULL,
    PRIMARY KEY (id),
);

CREATE TABLE users (
    id INT IDENTITY(1,1) NOT NULL,
    email VARCHAR(200) NOT NULL,
    password VARCHAR(100) NOT NULL,
    user_type INT NOT NULL,
    PRIMARY KEY (id),
);

CREATE TABLE doctor (
    id INT IDENTITY(1,1) NOT NULL,
    user_id INT NOT NULL,
    name VARCHAR(150) NOT NULL,
    crm VARCHAR(15) NOT NULL,
    clinic_id INT NOT NULL,
    specialty_id INT NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (user_id) REFERENCES "dbo"."users" (id),
    FOREIGN KEY (clinic_id) REFERENCES "dbo"."clinic" (id),
    FOREIGN KEY (specialty_id) REFERENCES "dbo"."specialty" (id),
);

CREATE TABLE patient (
    id INT IDENTITY(1,1) NOT NULL,
    user_id INT NOT NULL,
    name VARCHAR(100) NOT NULL,
    cep VARCHAR(15) NOT NULL,
    rg VARCHAR(50) NOT NULL,
    phone VARCHAR(15) NOT NULL,
    birth_date VARCHAR(10) NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (user_id) REFERENCES "dbo"."users" (id),
);

CREATE TABLE medical_consultation (
    id INT IDENTITY(1,1) NOT NULL,
    doctor_id INT NOT NULL,
    patient_id INT NOT NULL,
    data_consultation VARCHAR(20) NOT NULL,
    text VARCHAR(250) NULL,
    status INT NOT NULL,
    price DECIMAL(10,2) NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (doctor_id) REFERENCES "dbo"."doctor" (id),
    FOREIGN KEY (patient_id) REFERENCES "dbo"."patient" (id),
);

-------------------------------------------------------------------------------------------------
-- TERCEIRA QUERY / IMPLEMENTAÇÃO

INSERT INTO specialty (name) VALUES
    ('Acupuntura'),
    ('Anestesiologia'),
    ('Angiologia'),
    ('Cardiologia'),
    ('Cirurgia Cardiovascular'),
    ('Cirurgia da Mão'),
    ('Cirurgia do Aparelho Digestivo'),
    ('Cirurgia Geral'),
    ('Cirurgia Pediátrica'),
    ('Cirurgia Plástica'),
    ('Cirurgia Torácica'),
    ('Cirurgia Vascular'),
    ('Dermatologia'),
    ('Radioterapia'),
    ('Urologia'),
    ('Pediatria'),
    ('Psiquiatria');

INSERT INTO clinic (costume_name, address, number, cep, corporate_reason) VALUES
    ('Clinica A', 'Av.Universitaria', 5520, '75083-515', 'UNI Medical Group');

INSERT INTO users (email, password, user_type) VALUES
    ('ligia@gmail.com', '1234566', 1),
    ('alexandre@gmail.com', '123R72RA', 1),
    ('fernando@gmail.com', 'WDFU82FS', 1),
    ('henrique@gmail.com', 'NUFsfg93', 1),
    ('joao@hotmail.com', 'MFI98ed8F', 1),
    ('bruno@gmail.com', 'mIRU3j9', 1),
    ('mariana@outlook.com', 'mifU3IJF9', 1),
    ('ricardo.lemos@spmedicalgroup.com.br', 'MVIV3f9J', 2),
    ('roberto.possarle@spmedicalgroup.com.br', 'sdfsgd747', 2),
    ('helena.souza@spmedicalgroup.com.br', 'fMFIOu3d', 2);

INSERT INTO patient (user_id, name, cep, rg, phone, birth_date) VALUES
    (1, 'Ligia', '94839859000', '435225435', '1134567654', '13/10/1983'),
    (2, 'Alexandre', '73556944057', '326543457', '11987656543', '23/07/2001'),
    (3, 'Fernando', '16839338002', '546365253', '1197204453', '10/10/1978'),
    (4, 'Henrique', '14332654765', '543663625', '1134566543', '13/10/1985'),
    (5, 'João', '91305348010', '325444441', '1176566377', '27/08/1975'),
    (6, 'Bruno', '79799299004', '545662667', '11954368769', '21/03/1972'),
    (7, 'Mariana', '13771913039', '545662668', '11969584932', '05/03/2018');

INSERT INTO doctor (user_id, name, crm, clinic_id, specialty_id) VALUES
    (8, 'Ricardo Lemos', '54356SP', 1, 2),
    (9, 'Roberto Possarle', '53452SP', 1, 17),
    (10, 'Helena Strada', '65463SP', 1, 16);

INSERT INTO medical_consultation (doctor_id, patient_id, data_consultation, status, price) VALUES
    (3, 7, '20/01/2019 15:00', 1, 400.00),
    (2, 2, '06/01/2018 10:00', 2, 400.00),
    (2, 3, '07/02/2019 11:00', 3, 400.00),
    (2, 2, '06/02/2018 10:00', 2, 400.00),
    (1, 4, '07/02/2019 11:00', 3, 400.00),
    (3, 7, '08/02/2019 15:00', 1, 400.00),
    (1, 4, '09/02/2019 11:00', 2, 400.00);

-------------------------------------------------------------------------------------------------
-- QUINTA QUERY / QUESTÕES

--1
SELECT *
FROM patient

--2
SELECT name
FROM patient
WHERE name LIKE 'João'

--3
SELECT tb.data_consultation
FROM medical_consultation tb
WHERE tb.data_consultation LIKE '%2019%'

--4
SELECT tb.name
FROM patient tb
WHERE tb.name LIKE 'A%'

--5
SELECT count(tb.name) as QtdPatient
FROM patient tb

--6
SELECT tb.patient_id, COUNT(tb.patient_id) as 'Qtd'
FROM medical_consultation tb
GROUP BY tb.patient_id
ORDER BY 2

--7
SELECT tb.doctor_id, COUNT(tb.doctor_id) as 'Qtd'
FROM medical_consultation tb
GROUP BY tb.doctor_id
ORDER BY COUNT(tb.doctor_id) desc

--8
SELECT MIN(tb.data_consultation)
FROM medical_consultation tb

--9
SELECT MAX(tb.data_consultation)
FROM medical_consultation tb

--10
SELECT tb.specialty_id, COUNT(tb.specialty_id) as 'Qtd'
FROM doctor tb
GROUP BY tb.specialty_id

--11
SELECT tb.name
FROM doctor tb

--12
SELECT tb.user_type
FROM users tb
WHERE tb.user_type LIKE 2

--13
SELECT tb.birth_date
FROM patient tb
WHERE CAST(RIGHT(tb.birth_date, 4) AS INT) < 1990;

--14
SELECT tb.doctor_id, COUNT(tb.patient_id) as 'Qtd'
FROM medical_consultation tb
GROUP BY tb.doctor_id

--15
SELECT COUNT(tb.doctor_id) as 'Qtd'
FROM medical_consultation tb
WHERE tb.doctor_id = 1

--16
