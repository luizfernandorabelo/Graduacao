import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
from queue import Queue, LifoQueue, PriorityQueue
import sys
import os
import time


def gera_rede_aleatoria_nx(n, p):
    G = nx.Graph()
    vertices, arestas = gera_rede_aleatoria(n, p)
    G.add_nodes_from(vertices)
    G.add_edges_from(arestas)
    return G


def gera_rede_aleatoria(n, p):
    lista_vertices = gera_vertices(n)
    lista_arestas = gera_arestas(lista_vertices, p)
    return lista_vertices, lista_arestas


def gera_vertices(n):
    vertices = []
    for i in range(n):
        x = np.random.randint(0, n+1)
        y = np.random.randint(0, n+1)
        vertices.append((i, {'x': x, 'y': y, 'ordem': -1, 'cor': 'blue'}))
    return vertices


def gera_arestas(lista_vertices, p):
    arestas = []
    for v1, coord1 in lista_vertices:
        for v2, coord2 in lista_vertices:
            if v1 != v2 and np.random.random() < p:
                peso = round(
                    np.sqrt((coord1['x'] - coord2['x'])**2 + (coord1['y'] - coord2['y'])**2), 2)
                arestas.append((v1, v2, {'peso': peso, 'cor': 'gray'}))
                arestas.append((v2, v1, {'peso': peso, 'cor': 'gray'}))
    return arestas


def gera_matriz_distancias(G):
    matriz = np.zeros((len(G), len(G)))
    for v1, dados1 in G.nodes(data=True):
        for v2, dados2 in G.nodes(data=True):
            matriz[v1][v2] = round(
                np.sqrt((dados1['x'] - dados2['x'])**2 + (dados1['y'] - dados2['y'])**2), 2)
    return matriz


def obtem_pares_origem_destino(G, total_buscas):
    pares = []
    while len(pares) < total_buscas:
        v1 = np.random.randint(0, len(G))
        v2 = np.random.randint(0, len(G))
        if v1 != v2 and nx.has_path(G, v1, v2):
            pares.append((v1, v2))
    return pares


def desenha_rede(G, pos, n, titulo, nome_arquivo):
    plt.figure(figsize=(25, 15))
    plt.title(titulo)
    cores_arestas = [(G[v1][v2]['cor'])for v1, v2 in G.edges()]
    cores_vertices = [dados_vertice['cor']
                      for _, dados_vertice in G.nodes(data=True)]
    nx.draw(G, pos=pos, with_labels=True, edge_color=cores_arestas)
    nx.draw_networkx_nodes(G, pos=pos, node_color=cores_vertices)
    # plt.savefig(f'{nome_arquivo}.svg', format='SVG')
    plt.savefig(f'{nome_arquivo}.png', format='PNG')
    plt.close()


def mostra_resultado_busca(G, pos, caminho, origem, destino, distancia, tempo, tipo_busca, id_experimento):
    # Informações textuais da busca;
    print('\n>', tipo_busca)
    print('\t-Caminho:', caminho)
    print('\t-Distância:', '%.4f' % distancia)
    print('\t-Tempo:', '%.8f' % tempo)
    # Desenho da Rede:
    if len(G) <= 100:
        # Destaque dos vértices visistados:
        muda_cores_vertices_visitados(G)
        titulo_grafico = f'{tipo_busca} de {origem} a {destino} - Vértices Visitados'
        nome_arquivo = os.path.join(
            id_experimento, f'{origem}-{destino}-visitados-{tipo_busca}')
        desenha_rede(G, pos, len(G), titulo_grafico, nome_arquivo)
        # Destaque do caminho escolhido:
        muda_cores_vertices_caminho(G, caminho)
        muda_cores_arestas_caminho(G, caminho)
        titulo_grafico = f'{tipo_busca} de {origem} a {destino} - Caminho Escolhido'
        nome_arquivo = os.path.join(
            id_experimento, f'{origem}-{destino}-caminho-{tipo_busca}')
        desenha_rede(G, pos, len(G), titulo_grafico, nome_arquivo)


def muda_cores_vertices_visitados(G):
    total_niveis = max([dados_vertice['ordem']
                       for _, dados_vertice in G.nodes(data=True)])
    for _, dados_vertice in G.nodes(data=True):
        if dados_vertice['ordem'] == -1:
            dados_vertice['cor'] = 'blue'
        else:
            dados_vertice['cor'] = '#' + hex(
                int(255 + (50 - 255) / total_niveis * dados_vertice['ordem']))[2:] + '0000'


def muda_cores_vertices_caminho(G, caminho):
    for vertice, dados_vertice in G.nodes(data=True):
        dados_vertice['cor'] = 'orange' if vertice in caminho else 'blue'


def muda_cores_arestas_caminho(G, caminho):
    ultimo = len(caminho) - 1
    for i in range(ultimo):
        G[caminho[i]][caminho[i+1]]['cor'] = '#cc5500'


def busca_profundidade(G, origem, destino):
    visitados = []
    fila = LifoQueue()
    fila.put(origem)
    antecessores = [-1] * len(G)
    ordem = 0  # ordem de visitação
    G.nodes[origem]['ordem'] = ordem
    while not fila.empty():
        vertice = fila.get()
        visitados.append(vertice)
        G.nodes[vertice]['ordem'] = ordem
        ordem += 1
        if vertice == destino:
            return constroi_caminho_e_distancia(G, origem, destino, antecessores)
        for vizinho in G[vertice]:
            if vizinho not in visitados:
                fila.put(vizinho)
                antecessores[vizinho] = vertice
    return None


def busca_largura(G, origem, destino):
    visitados = [origem]
    fila = Queue()
    fila.put(origem)
    antecessores = [-1] * len(G)
    ordem = 0  # ordem de visitação
    G.nodes[origem]['ordem'] = ordem
    while not fila.empty():
        vertice = fila.get()
        ordem += 1
        if vertice == destino:
            return constroi_caminho_e_distancia(G, origem, destino, antecessores)
        for vizinho in G[vertice]:
            if vizinho not in visitados:
                G.nodes[vizinho]['ordem'] = ordem
                visitados.append(vizinho)
                fila.put(vizinho)
                antecessores[vizinho] = vertice
    return None


def busca_best_first(G, origem, destino, dists_reais):
    visitados = [origem]
    fila = PriorityQueue()
    fila.put((0, origem))
    antecessores = [-1] * len(G)
    ordem = 0  # ordem de visitação
    while not fila.empty():
        _, vertice = fila.get()
        G.nodes[vertice]['ordem'] = ordem
        ordem += 1
        if vertice == destino:
            return constroi_caminho_e_distancia(G, origem, destino, antecessores)
        for vizinho in G[vertice]:
            if not vizinho in visitados:
                antecessores[vizinho] = vertice
                fila.put((dists_reais[vizinho][destino], vizinho))
                visitados.append(vizinho)
    return None


def busca_a_estrela(G, origem, destino, dists_reais):
    visitados = []
    fila = PriorityQueue()
    pontuacoes_g = {v: float('inf') for v in G.nodes}
    pontuacoes_g[origem] = 0
    pontuacoes_f = {v: float('inf') for v in G.nodes}
    pontuacoes_f[origem] = dists_reais[origem][destino]
    antecessores = [-1] * len(G)
    ordem = 0  # ordem de visitação
    fila.put((pontuacoes_f[origem], origem))
    while not fila.empty():
        _, vertice = fila.get()
        G.nodes[vertice]['ordem'] = ordem
        ordem += 1
        if vertice == destino:
            return constroi_caminho_e_distancia(G, origem, destino, antecessores)
        visitados.append(vertice)
        for vizinho in G[vertice]:
            pontuacao_g = pontuacoes_g[vertice] + dists_reais[vertice][vizinho]
            if pontuacao_g < pontuacoes_g[vizinho]:
                antecessores[vizinho] = vertice
                pontuacoes_g[vizinho] = pontuacao_g
                pontuacoes_f[vizinho] = pontuacao_g + \
                    dists_reais[vizinho][destino]
                if vizinho not in visitados:
                    fila.put((pontuacoes_f[vizinho], vizinho))
    return None


def busca_dijkstra(G, origem, destino):
    visitados = []
    fila = PriorityQueue()
    fila.put((0, origem))
    distancias = [float('inf')] * len(G)
    distancias[origem] = 0
    antecessores = [-1] * len(G)
    ordem = 0  # ordem de visitação
    while not fila.empty():
        peso, vertice = fila.get()
        G.nodes[vertice]['ordem'] = ordem
        ordem += 1
        if vertice == destino:
            return constroi_caminho(G, origem, destino, antecessores), distancias[vertice]
        if vertice in visitados:
            continue
        visitados.append(vertice)
        for vizinho in G[vertice]:
            dist_vizinho = peso + G[vertice][vizinho]['peso']
            if dist_vizinho < distancias[vizinho]:
                distancias[vizinho] = dist_vizinho
                antecessores[vizinho] = vertice
                fila.put((dist_vizinho, vizinho))
    return None


def constroi_caminho(G, origem, destino, antecessores):
    caminho = []
    atual = destino
    while atual != origem:
        caminho.append(atual)
        proximo = antecessores[atual]
        atual = proximo
    caminho.append(origem)
    caminho.reverse()
    return caminho


def calcula_distancia(G, origem, destino, antecessores):
    distancia = 0
    atual = destino
    while atual != origem:
        proximo = antecessores[atual]
        distancia += G[atual][proximo]['peso']
        atual = proximo
    return distancia


def constroi_caminho_e_distancia(G, origem, destino, antecessores):
    caminho = []
    distancia = 0
    atual = destino
    while atual != origem:
        caminho.append(atual)
        proximo = antecessores[atual]
        distancia += G[atual][proximo]['peso']
        atual = proximo
    caminho.append(origem)
    caminho.reverse()
    return caminho, distancia


def main():
    # Leitura dos parâmetros de entrada da linha de comando:
    if len(sys.argv) == 5:
        n = int(sys.argv[1])
        p = float(sys.argv[2])
        total_buscas = int(sys.argv[3])
        id_experimento = sys.argv[4]
    # Leitura de n,p do teclado:
    else:
        n = int(input('n: '))
        p = float(input('p: '))
        total_buscas = int(input('toal buscas: '))
        id_experimento = input('identificador experimento: ')

    # Criação da pasta do experimento:
    if not os.path.exists(id_experimento):
        os.makedirs(id_experimento)
    # Remoção de arquivos antigos:
    else:
        for arquivo_antigo in os.listdir(id_experimento):
            os.unlink(os.path.join(id_experimento, arquivo_antigo))

    # Geração da rede:
    G = gera_rede_aleatoria_nx(n, p)

    # Cálculo das distâncias reais entre os vértices:
    distancias_reais = gera_matriz_distancias(G)

    # Determinação da posição dos vértices, conforme suas coordenadas:
    pos = [(dados_vertice['x'], dados_vertice['y'])
           for _, dados_vertice in G.nodes(data=True)]

    # Desenho da rede gerada:
    if n <= 100:
        titulo = 'Rede com n=' + str(n) + ' e p=' + str(p)
        nome_arquivo = os.path.join(id_experimento, '_rede_gerada')
        desenha_rede(G, pos, n, titulo, nome_arquivo)

    # Determinação dos pares de vértices origem-destino utilizados nas busca:
    pares_vertices = obtem_pares_origem_destino(G, total_buscas)

    # Inicialização das listas de tempos e distâncias:
    dados_coletados = {tipo_busca: {'tempos': [], 'distancias': []}
                       for tipo_busca in ['DFS', 'BFS', 'Best-First', 'A-Estrela', 'Dijkstra']}

    # Buscas:
    for origem, destino in pares_vertices:
        # Busca em profundidade:
        G_copia = G.copy()
        t_inicio = time.time()
        caminho, distancia = busca_profundidade(G_copia, origem, destino)
        tempo = time.time() - t_inicio
        mostra_resultado_busca(G_copia, pos, caminho, origem,
                               destino, distancia, tempo, 'DFS', id_experimento)
        dados_coletados['DFS']['tempos'].append(tempo)
        dados_coletados['DFS']['distancias'].append(distancia)

        # Busca em largura:
        G_copia = G.copy()
        t_inicio = time.time()
        caminho, distancia = busca_largura(G_copia, origem, destino)
        tempo = time.time() - t_inicio
        mostra_resultado_busca(G_copia, pos, caminho, origem,
                               destino, distancia, tempo, 'BFS', id_experimento)
        dados_coletados['BFS']['tempos'].append(tempo)
        dados_coletados['BFS']['distancias'].append(distancia)

        # Busca best-first:
        G_copia = G.copy()
        t_inicio = time.time()
        caminho, distancia = busca_best_first(
            G_copia, origem, destino, distancias_reais)
        tempo = time.time() - t_inicio
        mostra_resultado_busca(G_copia, pos, caminho, origem,
                               destino, distancia, tempo, 'Best-First', id_experimento)
        dados_coletados['Best-First']['tempos'].append(tempo)
        dados_coletados['Best-First']['distancias'].append(distancia)

        # Busca A*:
        G_copia = G.copy()
        t_inicio = time.time()
        caminho, distancia = busca_a_estrela(
            G_copia, origem, destino, distancias_reais)
        tempo = time.time() - t_inicio
        mostra_resultado_busca(G_copia, pos, caminho, origem,
                               destino, distancia, tempo, 'A*', id_experimento)
        dados_coletados['A-Estrela']['tempos'].append(tempo)
        dados_coletados['A-Estrela']['distancias'].append(distancia)

        # Busca Dijkstra:
        G_copia = G.copy()
        t_inicio = time.time()
        caminho, distancia = busca_dijkstra(G_copia, origem, destino)
        tempo = time.time() - t_inicio
        mostra_resultado_busca(G_copia, pos, caminho, origem,
                               destino, distancia, tempo, 'Dijkstra', id_experimento)
        dados_coletados['Dijkstra']['tempos'].append(tempo)
        dados_coletados['Dijkstra']['distancias'].append(distancia)

    # Cálculo das médias de tempos e distâncias:
    for tipo_busca in dados_coletados:
        print('\n>', tipo_busca)
        print('\t- Tempo médio de execução: %.8f' %
              np.mean(dados_coletados[tipo_busca]['tempos']))
        print('\t- Distância média do caminho: %.8f' %
              np.mean(dados_coletados[tipo_busca]['distancias']))


if __name__ == '__main__':
    main()
