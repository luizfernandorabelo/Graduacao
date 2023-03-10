# Lista 02 - Arquitetura de Computadores Paralelos

## 1) São características de uma arquitetura Pipeline:

Capacidade de executar mais de uma instrução no mesmo ciclo de clock.

## 2) São características de uma arquitetura Superescalar:

Capacidade de entregar os resultados de diferentes instruções em um mesmo ciclo de clock (desde que as instruções sejam de tipos distintos, e.g. Integer, Floating Point, Load, Store).

## 3) Considerando a taxonomia de Flynn, o modelo arquitetural mais adequado/eficiente para paralelismo de dados no nível de instrução é:

SIMD.

## 4) São exemplos de computadores SISD:

Computadores escalares contendo um único núcleo.

## 5) São exemplos de arquiteturas com características SIMD:

GPUs e Processadores Vetoriais.

## 6) São exemplos de computadores MIMD:

Clusters e computadores multi-core.

## 7) São características de computadores paralelos conhecidos como multiprocessadores:

CPUs com múltiplas unidades de controle e unidades funcionais, usando memória com um único espaço de endereçamento.

## 8) São características de computadores paralelos conhecidos como multicomputadores:

CPUs com múltiplas unidades de controle e unidades funcionais, usando memória
com espaços de endereçamento distintos para cada processador;

## 9) Uma GPU é um processador baseado em máquinas:

SIMD.

## 10) O protocolo Snoopy em coerência de cache:

Mantém monitoração no barramento.

## 11) São características de máquinas MIMD:

Memória compartilhada, com o mesmo tempo de acesso a todas as posições de memória endereçáveis.

## 12) São vantagens de memória compartilhada:

Programação mais próxima à sequencial; Comunicação mais rápida quando comparada à comunicação com passagem de mensagens;

## 13) O _falso compartilhamento_ ocorre quando:

Dados distintos de um mesmo bloco comparado são atualizados por processos executando em processadores diferentes e que possuem coerência de cache.

## 14) Clusters são máquinas _assíncronas_:

Verdadeiro.

## 15) MPPs são máquinas _SIMDs_:

Falso. MPPs são máquinas _MIMD_ com memória distribuída.

## 16) Arquitetura SIMD:

São síncronas e permitem a execução de uma mesma instrução com dados distintos.

## 17) GPUs são arquiteturas paralelas que podem ser classificadas como:

Inspiradas em máquinas SIMD, porém, que permitem a execução simultânea e síncrona de uma mesma instrução por múltiplas threads (paradigma SIMT).

## 18) Em GPUs, _warps_ representam threads que:

Executam sincronamente, mas que podem seguir caminhos diferentes durante a execução, perdendo desempenho.

## 19) Associe elementos de processamento _fortemente_ e _fracamente_ acoplados:

**Fortemente Acoplados:** processadores fisicamente próximos, compartilham memória, possuem alta largura de banda e baixa latência de comunicação;

**Fracamente Acoplados:** processadores fisicamente distribuídos, utilizam memória distribuída e apresentam alta latência de comunicação.

## 20) Quanto ao impacto das Redes de Conexão no projeto e desempenho das aplicações:

Os diferentes tipos de redes de conexão impactam no desempenho de aplicações tanto em sistemas com memória compartilhada e quanto com memória distribuída.

## 21) Exemplo de rede estática:

Hipercubo. Tanto Barramento, quanto Ômega, quanto Crossbar são dinâmicas.

## 22) (Colméia) Certa manhã, a abelha rainha de uma determinada colmeia chama todas as suas abelhas operárias e as informa que a atribuição de hoje é coletar néctar de girassol. Os trabalhadores então voam em diferentes direções procurando girassóis. Do ponto de vista de arquitetura de computadores, a máquina para executar este sistema pode ser considera como:

MIMD. São múltiplas instruções pois cada abelha coletará néctar de forma distinta.

## 23) Alguns amigos que fazem computação estão com um grande trabalho prático para fazer no fim do semestre. Para dar conta do prazo que têm, eles resolvem fazê-lo de maneira paralela. Cada um ficou responsável por uma parte de trabalho (uma funcionalidade diferente), as quais serão feitas durante a semana santa, isoladamente. As partes que cada um fizer serão unificadas posteriormente antes da data de entrega, gerando o produto final esperado para o trabalho prático. Este sistema pode ser visto como uma máquina:

MIMD com memória distribuída.

## 24) Alguns amigos que fazem computação estão com um grande trabalho para fazer no fim do semestre. Para dar conta do prazo que têm, eles resolvem fazê-lo de maneira paralela e remotamente durante a Semana Santa. Cada um ficou responsável por uma parte de trabalho, o qual ficou hospedado na nuvem (Google Drive). Quando eles voltarem para São Carlos, o trabalho deve estar testado e pronto para ser entregue (e seja o que Deus quiser)! Este sistema pode ser visto como uma máquina:

MIMD com memória compartilhada.

## 25) Quatro atletas do nado sincronizado entram na piscina juntas e desenvolvem vários exercícios magistralmente, com movimentos perfeitos e idênticos. A apresentação do quarteto foi aplaudido de pé pela competência, habilidade e sincronia do começo ao fim da apresentação. Fazendo uma analogia, este cenário representaria uma arquitetura SIMD ou MIMD?

SIMD. É instrução única pois os movimentos são idênticos.
