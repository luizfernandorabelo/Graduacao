# Machine Learning

MITCHELL (1997): Diz-se que um programa de computador aprende com experiência _E_ com relação a uma tarefa _T_ e alguma medida de desempenho _P_, se seu desempenho em _T_, conforme medido por _P_, melhora com a experiência _E_.

## Classificações de AM

- Aprendizado Supervisionado;
- Aprendizado Não Supervisionado;
- Aprendizado por Reforço;
- Outros (e.g. Sistemas de Recomendação...).

### Aprendizado Supervisionado

- É previamente sabido qual deve ser o resultado correto de uma saída para uma dada entrada;
- Os problemas são subdivididos em:
  - Regressão: tentam mapear entradas em alguma função contínua;
  - Classificação: tentam predizer a saída de forma discreta (mapeamento em rótulos).

### Apredizado Não Supervisionado

- O problema é tratado com pouca ou nenhuma ideia de quais resultados serão alcançados;
- Os problemas são subdivididos em:
  - Agrupamento: dados são agrupados segundo alguma característica identificada;
  - Associação: busca por padrões frequentes de associações entre os atributos de um conjunto de dados;
  - Sumarização: busca por uma descrição simples e compacta para um conjunto de dados.

### Aprendizado por Reforço

- Semelhante à maneira com que humanos e animais aprendem na realização de tarefas;
- Existe uma tarefa a ser realizada e um sistema de recompensas, que fornece alguma recompensa sempre que a realização de determinada etapa da tarefa é bem sucedida;
- Elementos normalmente definidos:
  - Environment;
  - Agent;
  - State;
  - Reward.

## Avaliação de Modelos Preditivos

Existem diversas medidas / ferramentas matemáticas para avaliar a capacidade de generalização de um modelo. Entre elas:

- _taxa de erro:_ razão entre classificações incorretas e total de classificações;
- _acurácia:_ 1 - taxa de erro;
- _precisão:_ razão entre classificações corretas de positivos e classificações positivas (incluindo incorretas);
- _sensibilidade (recall):_ razão entre classificações corretas de positivos e exemplos verdadeiramente positivos;
- _matriz de confusão:_ matriz em que linhas representam rótulos verdadeiros e em que colunas representam os rótulos preditos. A diagonal principal contém os acertos;

## Amostragem

Em modelos preditivos, o conjunto de dados é geralmente dividido em:

- Conjunto de dados de treinamento (maior parte dos dados, utilizados para compor o treinamento);
- Conjunto de dados de teste (menor parte dos dados, utilizados apenas para validação).

### Critérios de Divisão

- _Holdout:_ divisão em proporções $p$ para treinamento e $1-p$ para teste;
  - Para casos gerais, $p \approx \frac{2}{3}$;
  - Para conjuntos de dados muito grandes (utilizados em _big data_, por exemplo, o valor de $p$ é mais próximo de 1);
  - Técnica simples, mas não permite avaliação de desempenho para a variação na combinação dos dados de treinamento / teste.
- _Amostragem Aleatória:_ constrói vários conjuntos de dados distintos (sem repetição) para diferentes treinamento e faz a média das medidas de desempenhos;
  - Se o desvio padrão entre as medidas for alto, infere-se que o modelo é bastante sensível a variações no conjunto de dados.
- _Validação Cruzada:_ conjunto de dados subdividido em _r_ subconjuntos aproximadamente iguais e formadas combinações com _r-1_ subconjuntos par formar cada um dos conjuntos de treinamento. O subconjunto que não é utilizado em dada combinação é utilizado como conjunto de teste daquele conjunto de treinamento formado;
  - Bem como a _Amostragem Aleatória_, determina a média das medidas de desempenho;
  - Embora mais robusto que o _Holdout_, grande parte do conjunto de dados é compartilhado entre os diferentes conjuntos de treinamento.
- _Bootstrap:_ mesma ideia da _Amostragem Aleatória_, mas permite a repetição de exemplos dentro do conjunto de dados.
  - É utilizado em situações específicas com conjunto de dados pequeno.

## Modelos Probabilísticos

- Algoritmos bayesianos buscarão associar uma determinada classe a um objeto baseado em probabilidades (abordagem frequencial). São consideradas:
  - _Probabilidade a Priori (P(A))_: incerteza associada a um evento _A_ antes da realização do experimento (e.g. probabilidade de indivíduo ter uma doença);
  - _Probabilidade a Posteriori (P(hipótese|dados))_: probabilidade condicional atribuída à ocorrência de um evento (classe) depois que dados relevantes são observados (atributos) (e.g. probabilidade de indivíduo doente dado exame positivo);
  - _Verossimilhança (P(dados|hipótese))_: probabilidade condicional de se observar um dado (atributo) dada a ocorrência de um evento (classe) (e.g. probabilidade de teste ser positivo dado que a pessoa é doente);
- O Algoritmo _Naive Bayes_ possui uma bordagem simples, que assume independência entre atributos (o que nem sempre é aplicável na prática);

Matematicamente, tem-se que:

$$ P(y_i|X) = \frac{P(y_i)P(X|y_i)}{P(X)} \text{, com } P(X|y_i) = \frac{P(X\cap y_i)}{P(y_i)}$$

### Critério MAP

Os classificadores bayesianos irão calcular:

- Na etapa de aprendizado:
  - probabilidades à priori das classes $P(y_i)$
  - verossimilhanças $P(X|y_i)$
- Na etapa de inferêcia:
  - probabilidades à posterióri $P(y_i|X)$
  - $y_{MAP} = argmax (P(y_i|X))$

Nota: como $P(X)$ é constante dentro de uma classificação, a etapa de inferêcia pode ser simplificada com $Y_{MAP} = argmax (P(y_i) P (X|y_i))$.

## Modelos Baseados em Distância

- Algoritmos baseados em distância partem da premissa que dados similares tendem a estar concentrados em uma mesma região do espaço de entrada;
  - O Algoritmo _KNN_ (K- Nearest Neighbours) é o principal representante dessa classe;
  - Não existe, na realidade, etapa de treinamento. Os cálculos serão todos realizados na parte de inferência;
  - São definidas superfícies de decisão (qualquer objeto dentro da região de um polítopo estará mais próximo do objeto "centrado" nesse polítopo do que qualquer outro objeto);
- Abordagem simples, incremental e aplicável mesmo em problemas complexos, mas a etapa de inferência é custosa (requer processamento no cálculo de distâncias).

## Métodos Simbólicos

- Aprendizado organizado em estrutura simbólica que permite descrever os padrões extraídos do conjunto de dados em uma linguagem de fácil compreensão para humanos;
  - Árvores de Decisão são o principal exemplo: conhecimento organizado em uma hierarquia de decisões, que vão sendo tomadas sucessivamente até a obtenção da classificação final;
  - Existem diferentes critérios de pureza para indução de árvores de decisão. 2 dos mais famosos são entropia e Gini;
- Apesar de serem bastante interpretáveis e de execução com complexidade linear, são sensíveis à ausência de valores de atributos e instáveis (variações no conjunto de treinamento podem levar à construção de árvores diferentes).

## Métodos Conexionistas

- Buscam "imitar" o cérebro humano e suas características. Caracterizados por conterem unidades de processamento (neurônios), interconectados em uma arquitetura que apresenta váŕias camadas (layers), dando origem a redes neurais artificiais (RNAs);
  - Classificação Binária (Regressão Logística): caso mais simples. Rótulos da forma $y \in \{0,1\}$. Uma primeira tentativa seria estimar $\hat{y}$ através de regressão como $y \approx \hat {y} = wx_i + b, w = [w_1, w_2, \cdots, w_n], x_i = [x_1, x_2, \cdots, x_n]^\top$. Mas podemos limitar os valores de $\hat{y}$ ao interavlo $[0,1]$ através da função sigmoid (função logística) $\sigma(z) = \frac{1}{1+e^{-z}}$. São então construídas RNAs com várias camadas formando funções complexas a partir da interconexão de vários neurônios. \*A função ReLU é bastante utilizada como alternativa à sigmoid.
- Possuem boa capacidade de generalização e tolerância a ruídos, mas possuem baixa interpretabilidade (muitas vezes referidas como caixas pretas) e necessitam da definição de hiperparâmetros (número de layers, quantidade de neurônios por layer, função de ativação...).
