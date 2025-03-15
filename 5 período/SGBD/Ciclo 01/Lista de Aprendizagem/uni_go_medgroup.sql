CREATE TABLE clinic (
    id INT IDENTITY(1,1) NOT NULL,
    costume_name VARCHAR(100) NOT NULL,
    address VARCHAR(200) NOT NULL,
    number INT(15) NOT NULL,
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
    user_tp INT(50) NOT NULL,
    PRIMARY KEY (id),
);

CREATE TABLE patient (
    id INT IDENTITY(1,1) NOT NULL,
    user_id INT NOT NULL,
    name VARCHAR(100) NOT NULL,
    cep VARCHAR(11) NOT NULL,
    rg VARCHAR(50) NOT NULL,
    phone VARCHAR(15) NOT NULL,
    birth_date VARCHAR(8) NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (user_id) REFERENCES "dbo"."users" (user_id),
);