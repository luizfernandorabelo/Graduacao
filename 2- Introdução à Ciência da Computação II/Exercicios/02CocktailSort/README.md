# Cocktail Sort

## Descrição

O ​Cocktail sort​, também conhecido como ​bubble sort bidirecional​, é uma variante do bubble sort.A diferença entre eles é que o ​Cocktail sort ordena em ambas as direções a cada iteração sobre a lista. Esse algoritmo de ordenação é levemente mais difícil de implementar que o ​bubble sort​ e possui performance levemente superior. O ​objetivo do exercício é ordenar em ordem alfabética listas de nomes de pessoas notáveis da cidade de São Carlos e região e buscar se determinadas pessoas são ou não de São Carlos. Dado como entrada um inteiro​ *N* que corresponde à quantidade de nomes,os ​*N* nomes e cidades de cada pessoa, um número inteiro *​K* ​de buscas e os ​*K* nomes a serem buscados.A saída deve mostrar os nomes em ordem alfabética e responder para cada pessoa buscada com o inteiro ​1​ se for de São Carlos e ​0​, se não.

### Exemplo de caso de teste:  

#### Entrada:
10  
Joao Octavio Dagnone de Melo. Sao Carlos.  
Neurivaldo Jose de Guzzi. Sao Carlos.  
Rubens Massucio. Sao Carlos.  
Newton Lima Neto. Sao Carlos.  
Oswaldo Baptista Duarte Filho. Sao Carlos.  
Paulo Roberto Altomani. Sao Carlos.  
Airton Garcia Ferreira. Sao Carlos.  
Edinho Silva. Araraquara.  
Marcelo Barbieri. Araraquara.  
Waldemar de Santi. Araraquara.  
2
Edinho Silva.  
Airton Garcia Ferreira.  

#### Saída esperada:  
Airton Garcia Ferreira.  
Edinho Silva.  
Joao Octavio Dagnone de Melo.  
Marcelo Barbieri.  
Neurivaldo Jose de Guzzi.  
Newton Lima Neto.  
Oswaldo Baptista Duarte Filho.  
Paulo Roberto Altomani.  
Rubens Massucio.  
Waldemar de Santi.  
0  
1  
  