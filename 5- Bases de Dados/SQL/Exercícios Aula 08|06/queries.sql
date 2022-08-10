SELECT time1,
       time2,
       data
FROM   partida
WHERE  UPPER(local) = 'SANTOS';

SELECT data,
       local
FROM   partida
WHERE  time1 = 'PALMEIRAS'
        OR time2 = 'PALMEIRAS';

SELECT TO_CHAR(data),
       local
FROM   partida
WHERE  time1 = 'PALMEIRAS'
        OR time2 = 'PALMEIRAS';

SELECT j.cpf,
       j.nome,
       j.data_nasc,
       t.nome,
       t.estado
FROM   jogador j
       JOIN time t
         ON j.time = t.nome;

SELECT j.cpf,
       j.nome,
       j.data_nasc,
       t.nome
FROM   jogador j,
       time t
WHERE  j.time = t.nome
       AND t.estado = 'SP';

SELECT j.cpf,
       j.nome,
       j.data_nasc,
       t.nome
FROM   jogador j
       JOIN time t
         ON j.time = t.nome
WHERE  t.estado = 'SP'

SELECT p.time1,
       p.time2,
       p.data,
       p.placar,
       j.classico
FROM   partida p
       JOIN joga j
         ON p.time1 = j.time1
            AND p.time2 = j.time2
WHERE  p.local = 'SANTOS';

SELECT t.nome,
       t.estado,
       t2.nome,
       t2.estado
FROM   (time t
        JOIN joga j
          ON t.nome = j.time1)
       JOIN time t2
         ON t2.nome = j.time2
WHERE  j.classico = 'S';

SELECT t.nome,
       u.cor_principal
FROM   time t
       JOIN uniforme u
         ON t.nome = u.time
WHERE  t.tipo = 'PROFISSIONAL'
       AND t.estado = 'MG';
