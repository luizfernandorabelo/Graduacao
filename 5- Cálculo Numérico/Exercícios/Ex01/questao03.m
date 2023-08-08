% a) Criação das variáveis:
a = 1.0e+308;
b = 1.1e+308;
c = -1.001e+308;

% a) Cálculo dos resultados:
disp(a + (b + c));  % 1.0990e+308
disp((a + b) + c);  % Inf

% a) Comparação entre os resultados:
disp((a + (b + c)) == ((a + b) + c));  % 0 (falso)


% b) Criação da variável:
x = 1e-15;

% b) Cálculo do resultado:
disp(((1 + x) - 1) / x);  % 1.1102 (diferente de 1)
