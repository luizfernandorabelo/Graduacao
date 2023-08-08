% { INFO: Tempo médio de 5 execuções: 0.0006504536 }

% Definição da matriz A e vetor b:
A = [8 1 -1 ; 2 1 9 ; 1 -7 2 ];
b = [5 ; 25 ; -10];

% Definição da dimensão da matriz A:
m = 3;

% Inicialização de P, L e U:
P = eye(m);
L = zeros(m);
U = A(:,:);

% Início da contabilização do tempo:
tic

% Decomposição com pivoteamento:
linha_pivo = 1; coluna_pivo = 1;
while linha_pivo <= m && coluna_pivo <= m
    linha_max = linha_pivo;
    for i = linha_pivo+1:m
        if abs(U(i,coluna_pivo)) > abs(U(linha_max,coluna_pivo))
            linha_max = i;
        end
    end
    if abs(U(linha_max,coluna_pivo)) <= 1e-10
        coluna_pivo += 1;
    else
        U([linha_max linha_pivo],:) = U([linha_pivo linha_max],:);
        P([linha_max linha_pivo],:) = P([linha_pivo linha_max], :);
        L([linha_max linha_pivo],:) = L([linha_pivo linha_max], :);
        for i = linha_pivo+1:m
            c = -1 * U(i,coluna_pivo) / U(linha_pivo,coluna_pivo);
            for j = coluna_pivo:m
                U(i,j) += U(linha_pivo,j) * c;
            end
            L(i,linha_pivo) = -c;
        end
        linha_pivo += 1;
        coluna_pivo += 1;
    end
end
L += eye(m);

% Atualização do valor de b (após as permutações da decomposição):
b = P * b;

% Substituição direta (Ly = b):
y = zeros(m,1);
y(1,1) = b(1,1);
for i = 2:m
    soma = b(i,1);
    for j = 1:i-1
        soma -= L(i,j) * y(j,1);
    end
    y(i) = soma;
end

% Substituição inversa (Ux = y):
solucao = zeros(m,1);
solucao(m,1) = y(m,1) / U(m,m);
for i = m:-1:1
    soma = y(i,1);
    for j = i+1:m
        soma -= U(i,j) * solucao(j,1);
    end
    solucao(i,1) = soma / U(i,i);
end

% Final da contabilização do tempo:
toc

% Exibição das matrizes P, A, L e U:
fprintf('\n');
P
A
L
U

% Teste se o resultado da decomposição está correto (PA = LU?):
erro = P * A - L * U;
correto = true;
for i = 1:length(b)
    correto = correto && abs(erro) <= 1e-10;
end
if correto
    fprintf('Resultado da decomposição correto! (considerando erro de 1e-10)\n');
else
    fprintf('Resultado da decomposição incorreto :(\n');
end

% Exibição da solução:
fprintf('\n');
solucao

% Teste se o resultado da solução está correto (Ax = b?):
erro = P * A * solucao - b;
correto = true;
for i = 1:length(b)
    correto = correto && abs(erro) <= 1e-10;
end
if correto
    fprintf('Resultado da solução correto! (considerando erro de 1e-10)\n');
else
    fprintf('Resultado da solução incorreto :(\n');
end
