% Definição da matriz A aleatória:
n = 3;
A = rand(n,n);
A_copia = A;

% Trasformação da matriz A em AtA:
A = A' * A;

% Inicialização das matrizes Q, R e V:
Q = zeros(n, n);
R = zeros(n, n);
V = eye(n);

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

% Cálculo dos autovalores e autovetores pelo método QR:
k = 0;
erro_computado = Inf;
Ak1 = A(:,:);
while (erro_computado > erro_permitido && k < max_iteracoes)
    Ak = Ak1(:,:);
    [Q,R] = QR_proprio(Ak);
    Ak1 = R * Q;
    V *= Q;
    erro_computado = norm(Ak1 - Ak);
    k += 1;
end

% Restauração da matriz A para seu valor original:
A = A_copia;

% Determinação das matrizes SVD próprias:
Vt_propria = V';                    % V transposta
S_propria = Ak1;                    % sigma
U_propria = A * V * inv(S_propria); % U

% Determinação das matrizes SVD do matlab:
[U_matlab, S_matlab, V_matlab] = svd(A);
Vt_matlab = V_matlab';

% Exibição dos resultados matriz a matriz:
U_matlab, U_propria
S_matlab, S_propria
Vt_matlab, Vt_propria

% Comparação da diferença entre as decomposições:
erro = norm(U_propria * S_propria * Vt_propria - U_matlab * S_matlab * Vt_matlab)
