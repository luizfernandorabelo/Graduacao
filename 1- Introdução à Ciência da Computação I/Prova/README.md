# Prova 1

## Descrição dada pelo professor:

Implemente um programa em linguagem C que atenda aos seguintes critérios:

- Ele deve utilizar apenas memória heap quando manipular cadeias de
  caracteres), inclusive para a leitura das strings passadas como argumentos
- Ele deve receber os seguintes parâmetros (na ordem que segue):

	* Um nome de arquivo para ser aberto e manipulado
		- O arquivo conterá palavras em cada uma de suas linhas
	* Um padrão P1 na forma de uma cadeia de caracteres
	* Um prefixo irá compor o segundo padrão P2, na forma de uma cadeia de caracteres
	* Um terceiro padrão P3 na forma de uma cadeia de caracteres
	* Uma palavra W (sem espaços)

- Considerando cada palavra contida nesse arquivo:

	* Imprima o número total de palavras contidas nesse arquivo
	* Imprima a palavra mais curta contida nesse arquivo
	* Imprima a palavra mais longa contida nesse arquivo
	* Conte o número de ocorrências para o padrão P1, considerando todas
	  as palavras contidas no arquivo (número de palavras que respeitam
	  tal padrão)
	* Imprima o número de palíndromos contidos no arquivo de palavras
	* Imprima a palavra mais longa que seja formada pelo prefixo definido
	  no segundo padrão, i.e., P2
	* Imprima, em ordem crescente, todas as palavras que seguem o padrão P3
	* Considerando todas as palavras contidas no arquivo, imprima a mais
	  próxima de W, sabendo que W poderá ter alguns caracteres distintos.
	  Por exemplo, considere W = "automóvel" e considere que o arquivo
	  contenha as palavras: automóvil, auto e automotivo. Nesse caso, a
	  palavra mais próxima será automóvil, pois apresenta apenas 1
	  caracter de diferença.