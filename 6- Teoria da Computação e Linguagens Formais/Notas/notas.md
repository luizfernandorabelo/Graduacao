# Teoria da Computação e Linguagens Formais

## Conceitos Introdutórios

- **Decidibilidade**: um algoritmo é decidível se ele finaliza na conclusão de um problema;
- **Computabilidade**: um poblema é computável se pode ser processado por um computador, sendo ele decidível ou não;
- **Problemas Determinísticos**: mesmas entradas => mesmas saídas. Cada passo do algoritmo é bem reconhecido. Complexidade _P_.
- **Problemas não Determinísticos**: mesmas entradas podem gerar saídas diferentes. Cada passo do algoritmo é desconhecido (várias ramificações). Complexidade _nP_.
- **P vs nP**: _P_ => problemas que podem ser resolvidos em _tempo polinomial_ e _nP_ => em _tempo polinomial em máquinas não determinísticas_;

## Visão Geral de Linguagens Formais

### Características

- Foco na _sintaxe_ (estruturação);
- Desenvolvida na década 1950 (Chomsky como nome importante)

### Reflexões

- _Linguagem Humana_ != _Linguagem Animal_, pela existência de 2 fatores: _hierarquias de maior complexidade_ e _recursividade_. Linguagens formais se aproximam mais da linguagem humana por esses mesmos 2 fatores;
- Formalmente, em linguagens, como alternativa ao termo _"errado"_, a expressão _"não pertencente à linguagem"_ se tornou mais adequada;
- Todo problema de Computação pode ser vislumbrado como um problema de Linguagem.

### Tipos de Formalismos

- **Operacional**: envolve _máquinas_;
- **Axiomático**: envolve _gramáticas_;
- **Denotacional**: envolve _expressões regulares_.

### Conceitos relacionados

- **Alfabeto**: Conjunto finito de símbolos (ou caracteres). Geralmente é denotado por Σ;
- **Palavra**: Sequência finita de símbolos do alfabeto justapostos (pode ser vazia - denotada por ε);
- **Fecho Estrela Σ\***: Conjunto de todas as palavras possíveis sobre um alfabeto, incluindo ε. É infinito;
- **Fecho Positivo Σ\+**: Fecho Estrela - ε. É infinito;
- **Comprimento**: Quantidade de símbolos de uma palavra. É denotado por módulo;
- **Linguagem**: Dado um alfabeto Σ, uma linguagem L é tal que L ⊆ Σ\*, ou seja, é um conjunto finito ou infinito de palavras.

## Gramática

### Definição Informal

- Maneira finita de listar uma linguagem (que pode ser finita ou infinita);
- Possui um conjunto de regras que, quando aplicadas, geram palavras / cadeias;

### Definição Formal

_G = (V, T, P, S)_, em que:

- _V_: Conjunto finito de variáveis (símbolos não terminais);
- _T_: Conjunto finito de terminais (disjunto de _V_);
- _P_: Conjunto finito de regras de produção;
- _S_: Símbolo inicial da gramática, _S_ ∊ _V_.

### Derivação

Processo de aplicação das regras de produção _P_ para _derivar_ (construir) uma palavra da linguagem.

## Linguagens Regulares

- Linguagem mais simples, eficientes, de baixa complexidade. Porém, são limitadas;

### Autômatos Finitos

- Sistemas de estados finitos;
- Entradas e saídas discretas;
- O estado corrente é resultado de ações do passado;

### Autômatos Finitos Determinísticos (AFDs)

Contidos por:

- Fita: cadeia a ser processada. Dividida em células, com cada célula um símbolo do alfabeto de entrada;
- Unidade de Controle: estado corrente da máquina. Possui uma unidade (cabeça) de leitura. Acessa as células individualmente e sequencialmente;
- Função de Transição: comanda as leituras, determinando as transições, com base no estado atual;

Formalmente, definimos um AFD como:

_M = (Σ, Q, δ, q0, F)_, em que:

- Σ: alfabeto de símbolos de entrada;
- Q: conjunto finito de estados possíveis;
- δ: função de transição;
- q0: estado inicial, q0 ∊ Q;
- F: conjunto de estados finais, F ⊂ Q.

### Linguagem de AFD

- Uma linguagem é dita _regular_ se existe pelo menos um AFD que a aceita\*;
- Se 2 AFDs _M1_ e _M2_ forem tais que _L(M1) = L(M2)_, então _M1_ e _M2_ são ditos equivalentes;

\* Uma entrada é _aceita_, quando toda a cadeia é consumida e se chega em um estado final pertencente ao conjunto F. Caso contrário, a cadeia é _rejeitada_.

### Autômatos Finitos não Determinísticos (AFNs)

- Nesse tipo de autômato, caminhos alternativos são possíveis, criando-se uma árvore de opções.
- A cadeia é aceita se pelo menos um desses caminhos aceitar a entrada;
- Qualquer AFN pode ser simulado por um AFD;

### Autômatos Finitos não Determinísticos com Movimentos Vazios (AFNεs)

- Generalização do mecanismo de não determinismo, adicionando a possibilidade de transição sem leitura da entrada;
- Possuem transições vazias, denotadas por δε, de forma que δε(q) = q U δ(q, ε) U (Up pertencente a δ(q, ε) δε(p));
- Qualquer AFNε pode ser simulado por um AFN.

### Expressões Regulares

- Todo problema regular pode ser descrito por uma Expressão Regular;
- Uma Expressão Regular é definida por:
  - Conjunto de símbolos;
  - Operações de concatenação e união;
- Exemplos de Expressões Regulares:
  - Ø: denota linguagem vazia;
  - ε: denota a linguagem {ε};
  - x, ∀ x ∊ Σ: denota a linguagem {x};
- Expressões Regulares podem ser convertidas em AFNεs p/ AFNs p/ AFDs. Começando em AFNεs:
  - Para união (r = r1 + r2), constrói-se M1 e M2 e partindo de q0, liga-se os q01 e q02 de cada máquina com transição vazia (em paralelo). Depois liga-se qf1 e qf2 com qf também com transição vazia;
  - Para concatenação (r = r1r2), constrói-se M1 e M2 e, considera-se q0 como q01. Liga-se qf1 com q02 por transição vazia e considera-se qf2 como qf;
  - Para concatenação sucessiva (r = r1\*), constrói-se M1 com transição vazia de qf1 para q01 e, partindo de q0, liga-se q01 e qf por transição vazia (em paralelo). Por fim, liga-se qf1 com qf também com transição vazia;

### Gramáticas Regulares

Como são uma especialização de gramáticas no geral, as gramáticas regulares podem ser definidas também pela quádrupla _G = (V, T, P, S)_. São subdividadas em:

- Gramática Linear à Direita (GLD): A -> w ou A -> wB;
- Gramática Linear à Esquerda (GLE): A -> w ou A -> Bw;
- Gramática Linear Unitária à Direita (GLUD): A -> w ou A -> wB, |w| <= 1;
- Gramática Linear Unitária à Esquerda (GLUE): A -> w ou A -> Bw, |w| <= 1;

OBS: Uma linguagem é dita _regular_ se ela é gerada por uma GLD, GLE, GLUD ou GLUE.

Se uma gramática regular do tipo GLUD produz uma linguagem regular, então é possível construir um Autômato Finito com Movimentos Vazios AFNε que reconheça a mesma linguagem. Formalmente:

- A -> ε => δ(A, ε) = qf;
- A -> a => δ(A, a) = qf;
- A -> B => δ(A, ε) = B;
- A -> aB => δ(A, a) = B.

Com o AFNε podemos escrever o AFD correspondente. O inverso também é possível (converter AFD em GLUD). Para isso, formalmente:

- S -> q0;
- qf -> ε;
- δ(qi, a) = qj => qi -> aqj;

### Lema do Bombeamento

Se uma linguagem L é LR, então:

- ∃ k tal que ∀ _w_ ∊ L, com |_w_| >= k, w pode ser definida como: w = xyz
  - |_xy_| <= k;
  - |_y_| >= 1;
- E, ∀ i >= 0, xy^{i}z ∊ L.

Se uma linguagem não passa no teste ela não é regular. Se ela passa, nada podemos afirmar.

### Operações Sobre Linguagens Regulares

Linguagens Regulares são fechadas para:

- União;
- Concatenação;
- Complemento;
- Intersecção.

### Linguagens Regulares Infinitas, Finitas e Vazias

Seja _L_ uma Linguagem Regular aceita por um autômato finito _M_ com _n_ estados. Então:

- L é _vazia_ se e somente se _M_ não aceita qualquer palavra _w_ tal que |w| < n;
- L é _finita_ se e somente se _M_ não aceita qualquer palavra _w_ tal que n <= |w| < 2n;
- L é _infinita_ se e somente se _M_ aceita qualquer palavra _w_ tal que n <= |w| < 2n.

### Simplificação de AFDs

Se um AFD possui função de transição total, com todos estados alcançáveis, é possível simplificá-lo seguindo os passos:

- Construção de tabela que relaciona estados distintos;
- Marcação de estados trivialmente não equivalentes (finais e não finais);
- Marcação dos demais estados não equivalentes, de forma que:

  - Para um par {qu, qv} não marcado e ∀ a ∊ Σ, tendo-se δ(qu,a) = pu e δ(qv,a) = pv temos:
    - Se pu = pv: não marcar o par {qu, qv};
    - Se pu != pv e {pu, pv} não está marcado: incluir o par {qu, qv} na lista de {pu, pv};
    - Se pu != pv e {pu, pv} está marcado: {qu, qv} é marcado, bem como os pares de sua lista, e assim recursivamente.

- Unificação dos estados que permanecem equivalentes após o processo (não marcados);
- Exclusão de estados inúteis e suas transições.

## Linguagens Livres de Contexto

- Linguagens um pouco mais abrangentes que as regulares;
- Ainda são relativamente simples e eficientes;
- Resolve também problemas como balanceamento de parênteses e construção de blocos;

### Gramáticas Livres de Contexto

- Ainda definidas pela quádrupla _G = (V, T, P, S)_;
- As regras de _P_ devem estar na forma: A -> α, em que A é variável de V e α é palavra de (V U T).

#### BNF: Backus Naur Form

- Notação usual para GLCs;
- Variáveis são definidas entre colchetes angulares <>;
- Setas são representadas por ::=;
- O restante do comportamento é usual ao que já foi estudado.

#### Simplificação de GLCs

- Simplificações são úteis para otimizações e construção de sistemas;
- Pode ser feita sistematicamente;
- Exclusão de transições vazias:
  - Passo 1: Elencam-se variáveis que geram a cadeia vazia direta ou indiretamente;
  - Passo 2: Considerando-se as produções não vazias, para as produções em que há símbolos à direita que geram a cadeia vazia, geram-se produções adicionais sem esses símbolos;
  - Passo 3: Se a cadeia pertence à linguagem, adiciona-se produção direta para isso a partir do símbolo inicial;
- Exclusão de produções de substituição de variáveis:
  - Passo 1: cálculo do fecho transitivo de cada variável;
  - Passo 2: alteração de produções que substituem variáveis.
- Exclusão de símbolos inúteis:
  - Passo 1 (a partir dos terminais): V1 = {}; repita V1 = V1 U {A | A -> α ∊ P e α ∊ (T U V1)\*}; até que a cardinalidade de V1 não aumente;
  - Passo 2 (a partir do símbolo inicial): T2 = {}; V2 = {S}; repita V2 = V2 U {A | X -> αAβ ∊ P1, X ∊ V2} e T2 = T2 U {a | X -> αaβ ∊ P1, X ∊ V2}; até que as cardinalidades de T2 e V2 não aumentem.

#### Forma Normal de Chomsky

- Dada uma GLC, todas as produções são da forma _A -> BC_, com _B_ e _C_ variáveis ou _A -> a_, com _a_ terminal;
- A palavra vazia não pertence à FNC;
- Vantagem de uso: a árvore de derivação passa a ser binária;

#### Forma Normal de Greibach

- Dada uma GLC, todas as produções são da forma _A -> aα_, em que _a_ é um terminal de T e _α_ é uma palavra de V\*;
- A palavra vazia não pertence à FNG;
- Vantagem do uso: de fácil conversão para autômato e a cada aplicação de regra, um símbolo é consumido, poupando passos desnecessários na rejeição de cadeias, por exemplo;

### Autômatos com Pilha

- Similares a AFDS;
- Podem ter não determinismo;
- Possuem memória auxiliar (Pilha);
- Qualquer LLC pode ser reconhecida por um AP;
- Definido pela sêxtupla _M = (Σ, Q, δ, q0, F, V)_, em que o elemento adicional _V_ é o alfabeto auxiliar (alfabeto de pilha).
- A função de transição delta é da forma _δ(p, x, y) = {(q, v)}_, em que:
  - p: estado origem;
  - x: símbolo lido da fita;
  - y: símbolo lido da pilha;
  - q: estado destino;
  - v: símbolo empilhado;

### Conversão GLC -> AP

- Pode ser feita em 3 passos, desde que a GLC esteja na FNG:
  - Passo 1: adiciona-se transição inicial empilhando símbolo inicial;
  - Passo 2: adicionam-se as transições para cada regra _A -> aα_, sendo cada regra mapeada em estado intermediário;
  - Passo 3: adiciona-se transição para o estado final;

### Propriedades das LLCs

Para saber se uma linguagem é LC, basta:

- construir uma GLC que a reconheça; ou
- construir um AP que a reconheça.

Quanto às operações, as GLCS são:

- União: fechada;
- Concatenação: fechada;
- Intersecção: aberta;
- Complemento: aberta;

### Lema do Bombeamento para LLCs

Se uma linguagem for Livre de Contexto, então:

- ∃ k tal que ∀ _w_ ∊ L, com |_w_| >= k, w pode ser definida como: w = uxvyz, com:
  - |_xvy_| <= k;
  - |_xy_| >= 1;
- E, ∀ i >= 0, ux^{i}vy^{i}z ∊ L.

Se uma linguagem não passa no teste ela não é livre de contexto. Se ela passa, nada podemos afirmar.

## Linguagens Recursivamente Enumeráveis e Sensíveis ao Contexto

- Classe de linguagens bem mais ampla;
- Muitas vezes possuem propósitos teóricos, mostrando o que pode ser computado ou não;
- Possui os formalismos:
  - _Operacional_: Máquina de Turing;
  - _Axiomático_: Gramáticas sensíveis ao contexto e irrestritas.

### Máquina de Turing

- Formalismo simples e universalmente conhecido;
- Resultado do interesse de definir um modelo computacional genérico, que define o que é computável;
- É constituída de 3 partes:
  - Fita: usada como entrada, saída e memória;
  - Unidade de Controle: indica o estado corrente da fita. Possui cabeça de fita para acessar uma célula de cada vez. Pode mover para a esquerda ou para a direita.
  - Função de Transição: além de determinar o estado da máquina, determina o sentido de movimentação.

Formalmente, uma Máquina de Turing é definida pela óctupla _M = (Σ, Q, δ, q0, F, V, ß, ☉)_, em que, além dos elementos "tradicionais":

- _V_: alfabeto auxiliar (pode ser vazio);
- ß: símbolo inicial para espaços em branco;
- ☉: símbolo de marcação de início de fita.

Dada uma cadeia de entrada, a cadeia é aceita se o processamento para em um estado de aceitação, ou é rejeitada caso pare em um estado de não aceitação (ou fique processando indefinidamente em um ciclo).

Além do cenário de aceitação / rejeição de cadeias, a Máquina de Turing pode ser utilizada para resolver problemas, codificando a resposta na fita e funcionando como uma "processadora de funções".

#### Variações da MT

A Máquina de Turing pode apresentar variações que consideram, por exemplo:

- Fita infinita à esquerda e à direita;
- Fita sem símbolo inicial;
- Não determinismo;
- Múltiplas fitas;
- Várias cabeças de leitura;
- Cabeça de leitura que pode ficar estacionária.

Qualquer uma das variações apresentadas não aumenta o poder computacional da MT tradicional, ou seja, qualquer variação pode ser mapeada para a versão tradicional. Entretanto, existe diferença na complexidade de tempo entre as versões variadas e tradicional.

#### Linguagens de uma MT

- Máquinas de Turing descrevem _Linguagens Recursivamente Enumeráveis_ (_LRE_);
- Como MTs são o dispositivo computacional mais geral existente, a classe _LRE_ contém todas as linguagens que podem ser reconhecidas mecanicamente. São representadas por _Gramáticas Irrestritas (tipo 0)_;
- _Linguagens Recursivas_ (_LRec_) são subtipo de _LRE_, para as quais as MTs correspondentes **sempre param**, aceitando ou rejeitando as cadeias de entrada;
- _Linguagens Sensíveis ao Contexto_ (_LSC_) são subtipo de _LRec_, para as quais MTs com **fita limitada em função do tamanho da cadeia** bastam. São representadas por _Gramáticas Sensíveis ao Contexto (tipo 1)_;

#### Indecibilidade

- Estudo do que os computadores podem / não podem fazer;
- Problemas _não computáveis_, são problemas que:
  - ou: não existe um algoritmo;
  - ou: a linguagem não tem decisor (Máquina de Turing que sempre para);
