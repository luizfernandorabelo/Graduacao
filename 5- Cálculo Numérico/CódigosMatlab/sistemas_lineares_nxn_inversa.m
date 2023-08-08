% Ax = b tem solução única <=> det(A) != 0 <=> A tem inversa
% A⁻¹Ax = A⁻¹b => x = A⁻¹b

% Encontrar a inversa é uma opearação custosa computacionalmente
% e é inviável para sistemas grandes (escala com tempo grande)

%% Exemplo 1: x-2y=1, 2x+3y=9 => S = {3,1}

% A = [1 -2 ; 2 3];
% b = [1 ; 9];

%% Exemplo 2: x+y+z=6, x+2y+2z=9, 2x+y+3z=11 => S={3,2,1}

% A = [1 1 1 ; 1 2 2 ; 2 1 3];
% b = [6 ; 9 ; 11];

% Exemplo 3: 2a+3b+c+d=2, 4a+7b+4c+3d=1, 6a+9b+9c+8d=3, 4a+7b+6c+4d=2 => S = {-7.5,-4,2,-3}

A = [2 3 1 1 ; 4 7 4 3 ; 6 9 9 8 ; 4 7 6 4];
b = [2 ; 1 ; 3 ; 2];

solucao = inv(A) * b
