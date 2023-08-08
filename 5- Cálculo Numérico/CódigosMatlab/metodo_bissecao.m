%{
    - Função considerada: f(x)=x³-x²-13x+5cos(x)
    - Raízes: (-2.9024012197493, 0), (0.3544655346387, 0), (4.2167155494677, 0)
%}

% Leitura do intervalo:
inicio = input('Início do intervalo: ');
fim = input('Fim do intervalo: ');

% Inicialização de variáveis:
x = (inicio + fim) / 2;
k = 0;
erro_permitido = 1e-10;
maximo_iteracoes = 1000;

% Definição de f:
function y = f(x)
    y = x^3 - x^2 - 13 * x + 5 * cos(x);
end

% Ajuste de intervalo:
if f(inicio) < f(fim)
    temp = fim;
    fim = inicio;
    inicio = temp;
end

% Cômputo de f(x):
fx = f(x);

% Iteração:
while k < maximo_iteracoes && abs(fx) > erro_permitido
    if fx > 0
        inicio = x;
    end
    if fx < 0
        fim = x;
    end
    x = (inicio + fim) / 2;
    fx = f(x);
    k += 1;
end

% Verificação do resultado:
if abs(fx) < erro_permitido
    fprintf('\nNesse intervalo, f tem raiz em x = %f (valor encontrado com %d iterações)\n', x, k);
else
    fprintf('\nNão foi possível determinar raiz no intervalo especificado!\n')
end
