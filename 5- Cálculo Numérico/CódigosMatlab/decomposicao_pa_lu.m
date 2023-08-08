A = [0 1 1 ; 1 2 1 ; 2 7 9];
m = 3;

% Inicialização de P, L e U:
P = eye(m);
L = zeros(m);
U = A(:,:);

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

P, A, L, U, P * A, L * U
