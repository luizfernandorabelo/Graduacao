% Definição da matriz a ser decomposta:
A = [2 3 1 1 ; 4 7 4 3 ; 6 9 9 8 ; 4 7 6 4];
n = 4;

% Inicialização de L e U:
L = eye(n);
U = A(:,:);

% Decomposição L U:
for r = 1:n-1
    for i = r+1:n
        c = -1 * U(i,r) / U(r,r);
        for j = r:n
            U(i,j) += U(r,j) * c;
        end
        L(i,r) = -c;
    end
end

L, U, LU = L * U
