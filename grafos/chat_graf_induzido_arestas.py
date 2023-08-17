import networkx as nx
import matplotlib.pyplot as plt

# Criar o grafo G
G = nx.Graph()
G.add_edges_from([(1, 2), (1, 5), (2, 4), (2, 3), (3, 4), (3, 6), (4, 5), (4, 6), (5, 6)])

# Criar o subgrafo induzido G' pelas arestas {(2, 4), (3, 6), (4, 6)}
edges = [(2, 4), (3, 6), (4, 6)]
G_prime = G.edge_subgraph(edges)

# Plotar o subgrafo G'
pos = nx.spring_layout(G_prime)  # Layout para organização dos nós
nx.draw(G_prime, pos, with_labels=True, node_color='lightblue', font_weight='bold')
plt.title("Subgrafo Induzido G'")
plt.show()
