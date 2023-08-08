% Limpeza do workspace e fechamento de figuras:
clear;
close all;
clc;

% Definição dos vetores de pontos x e y:
x = [1975 1980 1985 1990];
y = [72.8 74.2 75.2 76.4];

% Determinação do número de pontos:
n = length(x) - 1;

% Preenchimento da Matriz de Vandermonde:
A = ones(n+1, n+1);
for i = 2:n+1
    A(:,i) = A(:,i-1).*x';
end

% Resolução do sistema de equações por inversa:
a = inv(A) * y';

% Plot do resultado:
l1 = linspace(1970, 1995, 500);
l2 = 0;
for i=1:n+1
    l2 = a(i) * l1.^(i-1) + l2;
end
plot(x, y, "k*", l1, l2, "r-");

waitfor(gcf);
