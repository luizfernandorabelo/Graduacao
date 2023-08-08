% { INFO: Tempo médio de 5 execuções: 0.0004450321 }

% Definição da matriz A e vetor b:
A = [8 1 -1 ; 2 1 9 ; 1 -7 2 ];
b = [5 ; 25 ; -10];

% Definição da matriz A aumentada:
A_grande = cat(2, A, b);

% Definição das dimensões da matriz A aumentada:
m = 3;  % linhas
n = 4;  % colunas

% Início da contabilização do tempo:
tic

% Escalonamento com pivoteamento:
linha_pivo = 1; coluna_pivo = 1;
while linha_pivo <= m && coluna_pivo <= n
    linha_max = linha_pivo;
    for i = linha_pivo+1:m
        if abs(A_grande(i,coluna_pivo)) > abs(A_grande(linha_max,coluna_pivo))
            linha_max = i;
        end
    end
    if abs(A_grande(linha_max,coluna_pivo)) <= 1e-10
        coluna_pivo += 1;
    else
        A_grande([linha_max linha_pivo],:) = A_grande([linha_pivo linha_max],:);
        for i = linha_pivo+1:m
            c = -A_grande(i,coluna_pivo) / A_grande(linha_pivo,coluna_pivo);
            for j = coluna_pivo:n
                A_grande(i,j) += A_grande(linha_pivo,j) * c;
            end
        end
        linha_pivo += 1;
        coluna_pivo += 1;
    end
end

% Substituição inversa:
solucao = zeros(m,1);
solucao(m,1) = A_grande(m,n) / A_grande(m,n-1);
for i = m:-1:1
    soma = A_grande(i,n);
    for j = i+1:n-1
        soma -= A_grande(i,j) * solucao(j);
    end
    solucao(i,1) = soma / A_grande(i,i);
end

% Final da contabilização do tempo:
toc

% Exibição da solução:
fprintf('\n');
solucao

% Teste se o resultado da solução está correto (Ax = b?):
erro = A * solucao - b;
correto = true;
for i = 1:length(b)
    correto = correto && abs(erro) <= 1e-10;
end
if correto
    fprintf('Resultado da solução correto! (considerando erro de 1e-10)\n');
else
    fprintf('Resultado da solução incorreto :(\n');
end
