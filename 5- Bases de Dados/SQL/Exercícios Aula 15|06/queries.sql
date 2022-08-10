SELECT t.nome,
       t.estado
FROM   time t
       JOIN uniforme u
         ON t.nome = u.time
WHERE  u.cor_principal IS NULL;

SELECT jdr.nome,
       jdr.data_nasc,
       jdr.time,
       p.data,
       p.local,
       j.classico
FROM   joga j
       JOIN partida p
         ON j.time1 = p.time1
            AND j.time2 = p.time2
       JOIN jogador jdr
         ON jdr.time = j.time1
            OR jdr.time = j.time2;

SELECT t.nome,
       t.estado,
       d.nome
FROM   time t
       LEFT JOIN diretor d
              ON t.nome = d.time;

SELECT Count (*) qtd_classicos_ferias_verao
FROM   joga j
       JOIN partida p
         ON j.time1 = p.time1
            AND j.time2 = p.time2
WHERE  j.classico = 'S'
       AND EXTRACT(month FROM p.data) BETWEEN 1 AND 2;

SELECT Count (*) qtd_regulares_ferias_verao
FROM   joga j
       JOIN partida p
         ON j.time1 = p.time1
            AND j.time2 = p.time2
WHERE  j.classico = 'N'
       AND EXTRACT(month FROM p.data) BETWEEN 1 AND 2;

SELECT EXTRACT (month FROM p.data) mes,
       Count(*)                    classicos
FROM   partida p
       JOIN joga j
         ON p.time1 = j.time1
            AND p.time2 = j.time2
WHERE  EXTRACT (year FROM p.data) = 2018
       AND j.classico = 'S'
GROUP  BY EXTRACT (month FROM p.data)
ORDER  BY EXTRACT (month FROM p.data);  

SELECT t.nome,
       t.estado,
       t.saldo_gols,
       EXTRACT (year FROM p.data),
       SUM (CASE
              WHEN j.classico = 'S' THEN 1
              ELSE 0
            END) AS classicos
FROM   TIME t,
       joga j
       join partida p
         ON p.time1 = j.time1
            AND p.time2 = j.time2
WHERE  t.nome = j.time1
        OR t.nome = j.time2
GROUP  BY t.nome,
          t.estado,
          t.saldo_gols,
          EXTRACT (year FROM p.data)
ORDER  BY EXTRACT (year FROM P.data);  

SELECT T.nome,
       Count(*) jogos
FROM   time T
       JOIN partida P
            JOIN joga J
              ON P.time1 = J.time1
                 AND P.time2 = J.time2
         ON ( T.nome = J.time1
               OR T.nome = J.time2 )
WHERE  J.classico = 'S'
       AND T.tipo = 'PROFISSIONAL'
       AND ( ( T.nome = P.time1
               AND SUBSTR(P.placar, 1, 1) = 0 )
              OR ( T.nome = P.time2
                   AND SUBSTR(P.placar, 3, 3) = 0 ) )
GROUP  BY T.nome
HAVING ( ( Count(SUBSTR(P.placar, 1, 1)) >= 2 )
          OR ( Count(SUBSTR(P.placar, 3, 3)) >= 2 ) );

SELECT t.estado,
       t.tipo,
       Count(*)          times,
       Avg(t.saldo_gols) media_saldo
FROM   time t
GROUP  BY t.estado,
          t.tipo
ORDER  BY t.estado;

SELECT p.time1,
       p.time2,
       Count(*)
FROM   joga j
       LEFT JOIN partida p
              ON p.time1 = j.time1
                 AND p.time2 = j.time2
WHERE  j.classico = 'S'
GROUP  BY p.time1,
          p.time2;

-- TODO: Q10

SELECT t.estado,
       t.nome,
       Min(saldo_gols)
FROM   time t
GROUP  BY t.estado,
          t.nome
ORDER  BY t.estado,
          t.nome;  