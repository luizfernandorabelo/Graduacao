%% Exemplo 1: x-2y=1, 2x+3y=9 => S = {3,1}
% A = [1 -2 ; 2 3];
% b = [1 ; 9];
% n = 2;

%% Exemplo 2: x+y+z=6, x+2y+2z=9, 2x+y+3z=11 => S={3,2,1}
% A = [1 1 1 ; 1 2 2 ; 2 1 3];
% b = [6 ; 9 ; 11];
% n = 3;

% Exemplo 3: 2a+3b+c+d=2, 4a+7b+4c+3d=1, 6a+9b+9c+8d=3, 4a+7b+6c+4d=2 => S = {-7.5,-4,2,-3}
A = [2 3 1 1 ; 4 7 4 3 ; 6 9 9 8 ; 4 7 6 4];
b = [2 ; 1 ; 3 ; 2];
n = 4;

% Escalonamento:
for r = 1:n-1
    for i = r+1:n
        c = -1 * A(i,r) / A(r,r);
        for j = r:n
            A(i,j) += A(r,j) * c;
        end
        b(i) += b(r) * c;
    end
end

% Substituição inversa:
solucao = zeros(n,1);
solucao(n,1) = b(n) / A(n,n);
for i = n:-1:1
    soma = b(i);
    for j = i+1:n
        soma -= A(i,j) * solucao(j);
    end
    solucao(i,1) = soma / A(i,i);
end

solucao
