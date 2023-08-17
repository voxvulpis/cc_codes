import networkx as nx
import matplotlib.pyplot as plt

# Criar o grafo
G = nx.DiGraph()

# Adicionar arestas
edges = [('A', 'B'), ('C', 'B'), ('B', 'F'), ('F', 'D'), ('B', 'D'), ('D', 'C')]
G.add_edges_from(edges)

# Plotar o grafo
pos = nx.circular_layout(G)
nx.draw_networkx_nodes(G, pos)
nx.draw_networkx_edges(G, pos)
nx.draw_networkx_labels(G, pos)

plt.show()
