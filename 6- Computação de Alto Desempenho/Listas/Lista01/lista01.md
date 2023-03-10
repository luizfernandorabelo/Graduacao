# Lista 01 - Conceitos Introdutórios

## 1) Defina processo e o diferencie de um programa

Um processo é um programa em execução. Enquanto o programa (o código fonte) pode ser enxergado como "abstração", um processo é mais concreto (contendo pilha, dados, registradores, proprietário, tempos, etc).

## 2) Explique o que são processos paralelos e processos concorrentes, ressaltando a diferença entre os 2

2 ou mais processos são concorrentes, se ambos iniciaram mas não finalizaram sua execução. Dessa forma, estes processos "concorrem" por recursos computacionais.

Já processos paralelos, são processos que, além de serem concorrentes, são executados ao mesmo tempo em elementos de processamento distintos (paralelismo real).

## 3) Defina Speedup e Eficiência

Speedup: métrica para identificação do ganho de desempenho. É dado pela razão entre os tempos de resposta sequencial e paralelo.

Eficiência: métrica para identificação de eficiência, de acordo com o número de processadores. É dada pela razão do Speedup pelo número de processadores.

## 4) Diferencie Tempo de Execução de Tempo de Resposta

Tempo de execução é o tempo de processamento de todas as instruções do programa (de usuŕaio e de sistema), enquanto tempo de resposta é o tempo real gasto entre o início e o fim da execução do processo (incluindo tempos ociosos de espera e bloqueado, além do próprio tempo de execução).

## 5) Como a Computação Paralela impacta nos tempos de Execução e de Resposta?

A Computação Paralela tende a aumentar o Tempo de Execução, uma vez que o gerenciamento de recursos em paralelo é mais custoso. No entanto o Tempo de Resposta tende a diminuir, pois mais de uma instrução é executada ao mesmo tempo.

## 6) Explique o que é Granulação

Granulação refere-se à quantidade de recursos processados frente à interação. Quanto mais recursos processados por interação, maior a granulação.

## 7) O que é Programação Paralela ou Concorrente?

Programação em linguagem de programação em que, além de determinar-se como, determina-se quando as tarefas devem ser feitas, de forma a executá-las ao mesmo tempo (lógico), seja em 1 ou mais processadores.

## 8) A execução de um algoritmo de ordenação sequencial tem um tempo de resposta de 240s para ordenar 10 milhões de elementos inteiros. A ordenação dessa mesma quantidade de elementos em um algoritmo paralelo de ordenação têm tempos de resposta de 44s, 36s e 33,6s, para respectivamente 6, 8 e 10 processadores. Quais foram os speedups e as eficiências dessas execuções paralelas?

- Primeira Execução:
  - Speedup: 240 / 44 = 5.45;
  - Eficiência: 5.45 / 6 = 90.9%;
- Segunda Execução:
  - Speedup: 240 / 36 = 6.66;
  - Eficiência = 6.66 / 8 = 83.33%;
- Terceira Execução:
  - Speedup: 240 / 33.6 = 7.14;
  - Eficiência: 7.14 / 10 = 71.4%;

## 9) Qual conclusão tiramos com os Speedups e Eficiências do item anterior?

Podemos concluir que o speedup é sub-linear (caso mais comum). Quanto mais elementos são usados para uma carga de trabalho, maior é a sobrecarga na paralelização, o que diminui a eficiência do algorigmo.

## 10) Por que desenvolver Código Paralelo é mais difícil que escrever Código Sequencial?

Pois, de forma geral, temos que lidar com mais questões na programação, como sincronização, comunicação, protegimento de regiões críticas compartilhadas, identificação de paralelismos, etc.

## 11) De que forma Processos Concorrentes interagem? Qual é a diferença de interação entre Processos Concorrentes e Paralelos?

Por meio da troca de dados ou sincronização. Não existe diferença de interação entre Processos Concorrentes e Paralelos, o que garante "responsividade" entre arquiteturas.

## 12) Qual é a diferença entre Computação de Alto Desempenho e Computação Paralela?

A Computação de Alto Desempenho é mais abrangente. Ela envolve o estudo de métricas de análise de desempenho (tempo, espaço, interações, etc) e de formas de melhora (seja por hardware ou por software), de acordo com essas métricas. Já a Computação Paralela se refere ao uso de Programação Paralela com o intuito de mitigar o tempo de resposta de uma aplicação, ou seja, a Computação Paralela é uma das formas de se buscar a Computação de Alto Desempenho.
