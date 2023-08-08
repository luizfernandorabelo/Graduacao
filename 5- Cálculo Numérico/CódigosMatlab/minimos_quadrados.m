% Limpeza do workspace e fechamento de figuras:
clear;
close all;
clc;

% Definição da matriz de pontos reais:
D = [
    65 -3.1;
    55 -3.22;
    45 -3.3;
    35 -3.32;
    25 -3.17;
    15 -3.07;
    5 -3.02;
    -5 -3.02;
    -15 -3.12;
    -25 -3.2;
    -35 -3.35;
    -45 -3.37;
    -55 -3.25 
];

% Definição da ordem do polinômio aproximador:
p = 4;

% Cálculo do número de pontos reais:
m = rows(D);

% Preenchimento da Matriz de Vandermonde:
A = zeros(m, p+1);
for i = 1:m
    for j = 1:p+1
        A(i,j) = D(i,1) ^ (j-1);
    end
end

% Inicialização dos vetores x (solução) e b (ys reais):
x = zeros(p+1,1);
b = D(:,2);

% O Sistema de Equações Lineares pode ser
% resolvido utilizando-se equações normais
% ou pseudoinversa

% Exibição da resolução utilizando-se sistema de equações normais:
[Q,R] = qr(A);
Qtb = Q'*b;
x = R \ Qtb

% Exibição da resolução utilizando-se pseudoinversa:
x = pinv(A) * b

% Plot do resultado:
l1 = linspace(min(D(:,1)), max(D(:,1)), 500);
l2 = 0;
for i=1:p+1
    l2 = x(i) * l1.^(i-1) + l2;
end

plot(D(:,1), D(:,2), "k*", l1, l2, "r-");

waitfor(gcf);
