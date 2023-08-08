% Limpeza do workspace e fechamento de figuras:
clear;
close all;
clc;

% Leitura da imagem de entrada:
A = imread('./lena_in.jpg');

% Determinação das dimensões da imagem:
nx = size(A,1);
ny = size(A,2);

% Cálculo do SVD:
[U,S,V] = svd(A, 'econ');

% Representação da imagem original:
subplot(3, 3, 1);
imagesc(A), colormap gray, axis off;
title('Original');

% Aproximação e representação de A com diferentes ranks (postos):
ordem_plot = 2;
for r = [5 10 15 20 30 50 100 200];
    Aaproximada = U(:,1:r) * S(1:r,1:r) * V(:,1:r)';
    subplot(3, 3, ordem_plot);
    imagesc(Aaproximada), colormap gray, axis off;
    title(['Aproximação r=', num2str(r, '%d'), ' (', num2str(100*r*(nx+ny)/(nx*ny),'%2.2f'), '%)']);
    ordem_plot = ordem_plot + 1;
end

% Armazenamento da figura:
saveas(gcf, 'lena_out.png', 'png');

waitfor(gcf);
