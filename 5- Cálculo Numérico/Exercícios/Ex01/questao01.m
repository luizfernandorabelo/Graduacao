% Geração do vetor aleatório:
vetor_aleatorio = rand(1, 100);

% Abertura dos arquivos:
arquivo_texto = fopen('arquivo_texto.txt', 'w');
arquivo_binario = fopen('arquivo_binario.bin', 'wb');

% Escrita dos arquivos:
fprintf(arquivo_texto, '%.16f\n', vetor_aleatorio);
fwrite(arquivo_binario, vetor_aleatorio, 'double');

% Fechamento dos arquivos:
fclose(arquivo_texto);
fclose(arquivo_binario);

% O arquivo de texto ocupou 1,9K bytes.
% O arquivo binário ocupou 800 bytes.

% A diferença nos tamanhos ocorrem em virtude
% de o arquivo de texto armazenar 1 byte para 
% cada caractere. Como existem 19 caracteres
% por número, (1 dígito significativo, 1 ponto,
% 16 na mantissa e 1 quebra de linha) o tamanho
% do arquivo de texto foi de 19 * 100 = 1900 bytes.

% Já o arquivo binário armazena o conteúdo em "mais
% baixo nível", guardando a própria representação
% do número em binário. Como o tipo double usa 8 bytes,
% o tamanho do arquivo binário foi de 8 * 100 = 800 bytes.
