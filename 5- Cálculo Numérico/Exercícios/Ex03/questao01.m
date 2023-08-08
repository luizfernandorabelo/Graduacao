% Definição do vetor x (chute/solução):
x = ones(3, 1);

% Definição da função vetorial f:
function y = f(x)
    y = [
        x(1)^2 + x(2)^2 + x(3)^2 - 1 ;
        sin(x(1)) + x(2)^3 + x(3) ;
        x(1)^2 - 2*x(2) + x(3)
    ];
end

% Definição da função jacobiana com derivadas parciais de f:
function y = jac(x)
    y = [
        2*x(1) 2*x(2) 2*x(3)
        cos(x(1)) 3*x(2)^2 1
        2*x(1) -2 1
    ];
end

% Definição da função de resolução do sistema usando o método de newton:
function y = nonlin_newton(f, jac, x, erro, max_iteracoes)
    k = 0;
    xk = x;
    xk1 = xk - inv(jac(xk)) * f(xk);
    delta_x = xk1 - xk;
    while (norm(delta_x) > erro && k < max_iteracoes)
        xk1 = xk - inv(jac(xk)) * f(xk);
        delta_x = xk1 - xk;
        xk = xk1;
        k += 1;
    end
    y = xk1;
end

% Determinação do resultado com a função do matlab:
s_matlab = fsolve(@f, x)

% Cállculo do resíduo da solução:
residuo_matlab = norm(f(s_matlab))

fprintf('\n');

% Determinação do resultado com a função própria:
s_propria = nonlin_newton(@f, @jac, x, 1e-8, 1000)

% Cállculo do resíduo da solução:
residuo_propria = norm(f(s_propria))
