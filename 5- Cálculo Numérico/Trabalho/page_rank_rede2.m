% Definição do nome do arquivo da rede de entrada:
file = 'foldoc.txt';

% Leitura das adjacências do arquivo:
adjacencias = dlmread(file, '\t');

% Definição da matriz de adjacências:
P = zeros(max(adjacencias(:)));
for i = 1:size(adjacencias, 1)
    origem = adjacencias(i,1);
    destino = adjacencias(i,2);
    multiplicidade = adjacencias(i,3);
    P(origem,destino) += multiplicidade;
end

% Definição do número de páginas:
n = length(P);

% Definição da probabilidade alfa:
alfa = 0.15;

% Conversão para matriz de probabilidade de transição:
for i = 1:n
    s = sum(P(i,:));
    if s > 0
        P(i, :) /= s;
    else
        P(i, :) = ones(1,n) / n;
    end
end

% Determinação da Matriz Google:
G = (1 - alfa) * P + (alfa / n) * ones(n,n);

% Definição do erro tolerável e do máximo de iterações:
erro_toleravel = 1e-10;
max_iteracoes = 10000;

% Função para calcular a distribuição estacionária por força bruta (Monte Carlo):
function [V_estac] = dist_estac_forca_bruta(G, n, erro_toleravel, max_iteracoes)
    % Inicialização do contador de iterações:
    k = 0;
    % Inicialização do vetor v_k (número de visitas):
    V_k = zeros(1,n);
    % Inicialização do estado anterior:
    anterior = floor(rand() * (n-1) + 1);
    % Caminhada aleatória com max_iteracoes passos:
    while k < max_iteracoes
        P = cumsum(G(anterior,:));
        atual = find(P >= rand(), 1);
        V_k(atual) += 1;
        anterior = atual;
        k += 1;
    end
    % Normalização do resultado final:
    V_estac = V_k / sum(V_k);
end

% Função para calcular a distribuição estacionária por autovetor (Método das Potências):
function [V_estac] = dist_estac_autovetor_potencias(G, n, erro_toleravel, max_iteracoes)
    % Inicialização dos vetores v_k e v_k+1 (distribuição atual e próxima):
    V_k = ones(1,n) / n;
    V_k1 = V_k * G;
    % Inicialização do contador de iterações:
    k = 0;
    % Transições até equilíbrio:
    while norm(V_k - V_k1) > erro_toleravel && k <= max_iteracoes
        V_k = V_k1;
        V_k1 = V_k * G;
        k += 1;
    end
    % Normalização do resultado final (autovetor associado ao autovalor 1):
    V_estac = V_k / sum(V_k);
end

% Função própria para decomposição QR:
function [Q, R] = QR_proprio(G, n)
    % Inicialização das matrizes Q e R:
    Q = zeros(n, n);
    R = zeros(n, n);
    % Decomposição do primeiro termo:
    R(1,1) = norm(G(:,1));
    Q(:,1) = G(:,1) / R(1,1);
    % Decomposição dos demais termos:
    for i = 2:n
        a_i = G(:,i);
        v_i = a_i;
        for j = 1:i
            R(j,i) = Q(:,j)' * a_i;
            v_i -= R(j,i) * Q(:,j);
        end
        R(i,i) = norm(v_i);
        Q(:,i) = v_i / R(i,i);
    end
end

% Função para calcular a distribuição estacionária por autovetor (Método da Decomposição QR):
function [V_estac] = dist_estac_autovetores_qr(G, n, erro_toleravel, max_iteracoes)
    % Inicialização do contador de iterações:
    k = 0;
    % Inicialização das matrizes V, G_k e G_k+1:
    V = eye(n);
    G_k = ones(n,n);
    G_k1 = G(:,:);
    % Cômputo dos autovalores / autovetores:
    while (norm(G_k1 - G_k) > erro_toleravel && k < max_iteracoes)
        G_k = G_k1(:,:);
        [Q,R] = QR_proprio(G_k, n);
        G_k1 = R * Q;
        V *= Q;
        k += 1;
    end
    % Normalização do resultado final (autovetor associado ao autovalor 1):
    V_estac = V(:,1)' / sum(V(:,1));
end

% Determinação da Distribuição Estacionária por "Força Bruta":
tic
    V_estac1 = dist_estac_forca_bruta(G, n, erro_toleravel, max_iteracoes);
toc

fprintf('\n');

% Determinação da Distribuição Estacionária pelo Método das Potências:
tic
    V_estac2 = dist_estac_autovetor_potencias(G, n, erro_toleravel, max_iteracoes);
toc

fprintf('\n');

% Determinação da Distribuição Estacionária pela Decomposição QR:
tic
    V_estac3 = dist_estac_autovetores_qr(G', n, erro_toleravel, max_iteracoes);
toc
