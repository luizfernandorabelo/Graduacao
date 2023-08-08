% Criação da matriz A a ser decomposta:
A = [
    1 1 1 0 0 ;
    3 3 3 0 0 ;
    4 4 4 0 0 ;
    0 2 0 4 4 ;
    0 0 0 5 5 ;
    0 1 0 2 2
];

% Determinação das dimensões da matriz A:
n = 6; m = 5;

% Determinação da matriz ATA (simétrica):
S1 = A' * A;
S2 = A * A';

% Inicialização dos erros:
erro_computado = inf;
erro_permitido = 1e-10;

% Inicialização das matrizes auxiliares:
Ak = S1(:,:);
Ak1 = S1(:,:);
V = eye(m);

% Decomposição SVD usando QR:
while erro_computado > erro_permitido
    Ak = Ak1(:,:);
    [Q,R] = qr(Ak);
    Ak1 = R * Q;
    V *= Q;
    erro_computado = norm(Ak1 - Ak);
end

% Determinação das matrizes SVD:
Vt = V';              % V transposta
S = Ak1;              % sigma
U = A * V * inv(S);   % U

% Exibição dos resultados:
A
U, S, Vt
U * S * Vt
