% { INFO: Tempo médio de 5 execuções: 0.0004090309 }

% Definição da matriz A e vetor b:
A = [8 1 -1 ; 2 1 9 ; 1 -7 2 ];
b = [5 ; 25 ; -10];

% Início da contabilização do tempo:
tic

% Cálculo  da solução:
solucao = A \ b;

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
