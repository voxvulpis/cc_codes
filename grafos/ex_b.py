import networkx as nx
import matplotlib.pyplot as plt

# Criar o grafo G
G = nx.Graph()
G.add_edges_from([(1, 2), (1, 3), (2, 4), (3, 4), (3, 5), (4, 6), (4, 7), (6, 8), (6, 9), (7, 9), (7, 10), (8, 10)])

# Criar o subgrafo induzido G' pelas arestas {(1,3), (4,7), (7,9), (8,10)}
edges = [(1, 3), (4, 7), (7, 9), (8, 10)]
G_prime = G.edge_subgraph(edges)

# Plotar o subgrafo G'
pos = nx.spring_layout(G_prime)  # Layout para organização dos nós
nx.draw(G_prime, pos, with_labels=True, node_color='lightblue', font_weight='bold')
plt.title("Subgrafo Induzido G'")
plt.show()
