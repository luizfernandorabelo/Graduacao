%% Exemplo 1: 2x+y=11, 5x+7y=13 => S = {64/9,-29/9}
% A = [2 1 ; 5 7];
% b = [11 ; 13];
% n = 2;

%% Exemplo 2: 4x+2y-3z=0, x-3y-z=7, 3x-y+4z=5 => S={1,-2,0}
% A = [4 2 -3 ; 1 -3 -1 ; 3 -1 4];
% b = [0 ; 7 ; 5];
% n = 3;

% Exemplo 3: 10a-b+2c=6, -a+11b-c+3d=25, 2a-b+10c-d=-11, 3b-c+8d=15 => S = {1,2,-1,1}
A = [10 -1 2 0 ; -1 11 -1 3 ; 2 -1 10 -1 ; 0 3 -1 8];
b = [6 ; 25 ; -11 ; 15];
n = 4;

% Definição da matriz diagonal:
D = diag(diag(A));

% Cálculo do raio espectral p(D⁻¹(L+U)):
raio_espectral = max(abs(eig(inv(D) * (A - D))));

if raio_espectral < 1
    % Definição do vetor x_k e x_{k+1}:
    xk = ones(n,1);
    xk1 = ones(n,1);

    % Inicialização de variáveis:
    k = 0;
    max_iteracoes = 1000;
    erro_permitido = 1e-10;
    erro_computado = Inf;

    % Cômputo do resultado:
    while erro_computado >= erro_permitido && k < max_iteracoes
        for i = 1:n
            soma = 0;
            for j = 1:n
                if i ~= j
                    soma += A(i,j) * xk1(j);
                end
            end
            xk1(i) = (b(i) - soma) / A(i,i);
        end
        erro_iteracao = max(abs(xk1 - xk));
        erro_solucao = max(abs(A*xk1-b));
        erro_computado = max(erro_iteracao, erro_solucao);
        xk = xk1;
        k += 1;
    end

    % Exibição da solução:
    if erro_solucao < erro_permitido
        xk1
        fprintf('Solução encontrada em %d iterações\n', k);
    else
        xk1
        erro_solucao
        fprintf('\nSolução com aproximação além do erro máximo permitido :(\n');
        fprintf('\nSugestão: Tente executar novamente com um número maior de iterações\n');
    end
else
    fprintf('Sistema não convergente!\nRaio espectral = %f\n', raio_espectral);
end
