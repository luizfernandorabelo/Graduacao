% Duas matrizes são similares se possuem o mesmo
% terminante. Nesse sentido, para mostrar que as
% matrizes Ak são similares à matriz A, foram
% impressos os determinantes de Ak a cada iteração,
% evidenciando sua igualdade.

% Definição da matriz A:
A = [1 1 -1 ; 1 2 0 ; -1 0 5];
n = 3;
det(A)

% Inicialização das matrizes Q e R:
Q = zeros(n, n);
R = zeros(n, n);

% Função própria para decomposição QR:
function [Q, R] = QR_proprio(A)
    n = length(A);
    Q = zeros(n, n);
    R = zeros(n, n);
    R(1,1) = norm(A(:,1));
    Q(:,1) = A(:,1) / R(1,1);
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
end

% Definição do erro aceitável e número máximo de iterações:
erro_permitido = 1e-8;
max_iteracoes = 1000;

% Cálculo dos autovalores pelo método QR:
k = 0;
erro_computado = Inf;
Ak1 = A(:,:);
while (erro_computado > erro_permitido && k < max_iteracoes)
    Ak = Ak1(:,:);
    [Q,R] = QR_proprio(Ak);
    Ak1 = R * Q;
    det(Ak1)
    erro_computado = norm(Ak1 - Ak);
    k += 1;
end
