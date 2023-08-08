%{
    - Função considerada: f(x)=x³-x²-13x+5cos(x)
    - Derivada: 3x²-2x-13-5sen(x)
    - Raízes: (-2.9024012197493, 0), (0.3544655346387, 0), (4.2167155494677, 0)
%}

% Leitura do chute inicial:
x = input('Chute inicial: ');

% Inicialização de variáveis:
k = 0;
erro_permitido = 1e-10;
maximo_iteracoes = 1000;

% Definição de f:
function y = f(x)
    y = x^3 - x^2 - 13 * x + 5 * cos(x);
end

% Definição de f':
function y = f1(x)
    y = 3*x^2 - 2*x - 13 - 5*sin(x);
end

% Cômputo de f(x):
fx = f(x);

% Iteração:
while k < maximo_iteracoes && abs(fx) > erro_permitido
    x = x - fx / f1(x);
    fx = f(x);
    k += 1;
end

% Verificação do resultado:
if abs(fx) < erro_permitido
    fprintf('\nPróximo ao chute inicial, f tem raiz em x = %f (valor encontrado com %d iterações)\n', x, k);
else
    fprintf('\nNão foi possível determinar raiz próxima ao chute inicial especificado!\n')
end

