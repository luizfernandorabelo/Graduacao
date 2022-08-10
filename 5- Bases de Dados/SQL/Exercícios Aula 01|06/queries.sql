CREATE TABLE times (
    nome VARCHAR2 (20) NOT NULL,
    estado CHAR (2) NOT NULL,
    tipo VARCHAR2 (12) NOT NULL,
    saldo_gols NUMBER DEFAULT 0,

    CONSTRAINT pk_times PRIMARY KEY (nome),
    CONSTRAINT ck_tipo_times CHECK (UPPER(tipo) IN ('PROFISSIONAL', 'AMADOR'))
);

CREATE TABLE jogos (
    time1 VARCHAR2 (20) NOT NULL,
    time2 VARCHAR2 (20) NOT NULL,
    classico NUMBER (1),

    CONSTRAINT pk_jogos PRIMARY KEY (time1, time2),
    CONSTRAINT fk_time1_jogos FOREIGN KEY (time1)
        REFERENCES times (nome),
    CONSTRAINT fk_time2_jogos FOREIGN KEY (time2)
        REFERENCES times (nome),
    CONSTRAINT ck_classico_jogos CHECK (classico BETWEEN 0 AND 1)
);

CREATE TABLE partidas (
    time1 VARCHAR2 (20) NOT NULL,
    time2 VARCHAR2 (20) NOT NULL,
    data DATE NOT NULL,
    placar VARCHAR2 (3) DEFAULT '0x0',
    local_p VARCHAR2 (20),

    CONSTRAINT pk_partidas PRIMARY KEY (time1, time2, data),
    CONSTRAINT fk_jogos_partidas FOREIGN KEY (time1, time2)
        REFERENCES jogos (time1, time2),
    CONSTRAINT ck_placar_partidas CHECK (REGEXP_LIKE(placar, '[:digit:]x[:digit:]'))
);

CREATE TABLE jogadores (
    cpf CHAR (14) NOT NULL,
    rg VARCHAR2 (15) NOT NULL,
    nome VARCHAR2 (30) NOT NULL,
    data_nasc DATE,
    naturalidade VARCHAR2 (30),
    time VARCHAR2 (20) NOT NULL,

    CONSTRAINT pk_jogadores PRIMARY KEY (cpf),
    CONSTRAINT unique_rg_nome UNIQUE (rg, nome),
    CONSTRAINT fk_times_jogadores FOREIGN KEY (time)
        REFERENCES times (nome)
);

CREATE TABLE posicoes_jogadores (
    jogador CHAR (14) NOT NULL,
    posicao VARCHAR2 (15) NOT NULL,

    CONSTRAINT pk_posicoes_jogadores PRIMARY KEY (jogador, posicao),
    CONSTRAINT fk_jogadores FOREIGN KEY (jogador)
        REFERENCES jogadores (cpf)
);

CREATE TABLE diretores (
    time VARCHAR2 (20) NOT NULL,
    nome VARCHAR2 (30) NOT NULL,

    CONSTRAINT pk_diretores PRIMARY KEY (time, nome),
    CONSTRAINT fk_times_diretores FOREIGN KEY (time)
        REFERENCES times (nome)
);

CREATE TABLE uniformes (
    time VARCHAR2 (20) NOT NULL,
    tipo CHAR (7) NOT NULL,
    cor_principal VARCHAR2 (15),

    CONSTRAINT pk_uniformes PRIMARY KEY (time, tipo),
    CONSTRAINT fk_times_uniformes FOREIGN KEY (time)
        REFERENCES times (nome),
    CONSTRAINT ck_tipo_uniformes CHECK (UPPER(tipo) IN ('TITULAR', 'RESERVA'))
);

INSERT INTO times
    VALUES ('Corinthians', 'São Paulo', 'profissional', 100); -- ERRO: estado inválido

INSERT INTO times
    VALUES ('Corinthians', 'SP', 'profissional', 100); -- inserção válida

INSERT INTO times
    VALUES ('Flamengo', 'RJ', 'prof', 50); -- ERRO: tipo inválido

INSERT INTO times
    VALUES ('Flamengo', 'RJ', 'profissional', 50); -- inserção válida

INSERT INTO times
    VALUES ('Corinthians', 'SP', 'amador', 100); -- ERRO: chave primária já existente

INSERT INTO jogadores
    VALUES ('123.456.789-10', 'SP 10203040', 'Cássio', TO_DATE('06/04/1987', 'dd-mm-yyyy'), 'Veranópolis, RS', 'Curinthia');  -- ERRO: chave estrangeira com restrição n.n. não encontada

INSERT INTO jogadores
    VALUES ('123.456.789-10', 'SP 10203040', 'Cássio', TO_DATE('06/04/1987', 'dd-mm-yyyy'), 'Veranópolis, RS', 'Corinthians');  -- inserção válida

INSERT INTO jogadores
    VALUES ('123.456.789-10', 'RJ 1234567888', 'Gabigol', TO_DATE('30/08/1996', 'dd-mm-yyyy'), 'São Bernardo do Campo, SP', 'Flamengo'); -- ERRO: chave primária já existente

INSERT INTO jogadores
    VALUES ('111.222.333-44', 'RJ 1234567888', 'Gabigol', TO_DATE('30/08/1996', 'dd-mm-yyyy'), 'São Bernardo do Campo, SP', 'Flamengo'); -- inserção válida

INSERT INTO jogos
    VALUES ('Corinthians', 'Flamengo', 2); -- ERRO: clássico inválido

INSERT INTO jogos
    VALUES ('Corinthians', 'Flamengo', 0); -- inserção válida

DELETE FROM times
    WHERE estado  = 'SP'; -- ERRO: jogos tem referência p/ time de SP

ALTER TABLE jogadores
    ADD endereco VARCHAR2(30); -- alteração válida (as tuplas já existentes receberam null na coluna endereço)

ALTER TABLE jogadores
    ADD assistencias NUMBER DEFAULT 0; -- alteração válida (as tuplas já existente receberam o default na coluna assistências)

ALTER TABLE times
    ADD CONSTRAINT ck_saldo_gols CHECK (saldo_gols < 50); -- ERRO: a alteração viola saldos já existentes

ALTER TABLE times
    ADD CONSTRAINT ck_saldo_gols CHECK (saldo_gols < 50)
    ENABLE NOVALIDATE; -- alteração válida

INSERT INTO posicoes_jogadores
    VALUES ('123.456.789-10', 'GOLEIRO');  -- inserção válida

INSERT INTO posicoes_jogadores
    VALUES ('111.222.333-44', 'ATACANTE'); -- inserção válida

ALTER TABLE jogadores
    DROP COLUMN cpf; -- ERRO: não é possível apagar coluna pai
