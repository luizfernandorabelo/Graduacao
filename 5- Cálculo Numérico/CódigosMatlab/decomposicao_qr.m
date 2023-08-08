% Definição da matriz A:
A = [ 1 2 3 4 ; 5 6 7 8 ; 0 9 1 2 ; 0 0 3 4 ];

% Definição da dimensão de A:
n = length(A);

% Inicialização das matrizes Q e R:
Q = zeros(n, n);
R = zeros(n, n);

% Decomposição QR - primeiro termo:
R(1,1) = norm(A(:,1));
Q(:,1) = A(:,1) / R(1,1);

% Decomposição QR - demais termos:
for i = 2:n
    a_i = A(:,i);
    v_i = a_i;
    for j = 1:i
        R(j,i) = Q(:,j)' * a_i;
        v_i -= R(j,i) * Q(:,j);
    end
    R(i,i) = norm(v_i);
    Q(:,i) = v_i / R(i,i);
end

% Exibição do resultado:
Q, R
QR = Q * R

% Cálculo do erro:
erro = norm(A - QR)
