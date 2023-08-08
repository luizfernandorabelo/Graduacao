%% Exemplo 1: x-2y=1, 2x+3y=9 => S = {3,1}
% A = [1 -2 1 ; 2 3 9];
% m = 2;  % linhas da matriz aumentada
% n = 3;  % colunas da matriz aumentada

%% Exemplo 2: x+y+z=6, x+2y+2z=9, 2x+y+3z=11 => S={3,2,1}
% A = [1 1 1 6 ; 1 2 2 9 ; 2 1 3 11];
% m = 3;  % linhas da matriz aumentada
% n = 4;  % colunas da matriz aumentada

% Exemplo 3: 2a+3b+c+d=2, 4a+7b+4c+3d=1, 6a+9b+9c+8d=3, 4a+7b+6c+4d=2 => S = {-7.5,-4,2,-3}
A = [2 3 1 1 2 ; 4 7 4 3 1 ; 6 9 9 8 3 ; 4 7 6 4 2];  % matriz aumentada
m = 4;  % linhas da matriz aumentada
n = 5;  % colunas da matriz aumentada

% Escalonamento com pivoteamento:
linha_pivo = 1; coluna_pivo = 1;
while linha_pivo <= m && coluna_pivo <= n
    linha_max = linha_pivo;
    for i = linha_pivo+1:m
        if abs(A(i,coluna_pivo)) > abs(A(linha_max,coluna_pivo))
            linha_max = i;
        end
    end
    if abs(A(linha_max,coluna_pivo)) <= 1e-10
        coluna_pivo += 1;
    else
        A([linha_max linha_pivo],:) = A([linha_pivo linha_max],:);
        for i = linha_pivo+1:m
            c = -A(i,coluna_pivo) / A(linha_pivo,coluna_pivo);
            for j = coluna_pivo:n
                A(i,j) += A(linha_pivo,j) * c;
            end
        end
        linha_pivo += 1;
        coluna_pivo += 1;
    end
end

% Substituição inversa:
solucao = zeros(m,1);
solucao(m,1) = A(m,n) / A(m,n-1);
for i = m:-1:1
    soma = A(i,n);
    for j = i+1:n-1
        soma -= A(i,j) * solucao(j);
    end
    solucao(i,1) = soma / A(i,i);
end

solucao
