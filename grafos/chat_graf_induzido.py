import networkx as nx
import matplotlib.pyplot as plt

# Criar o grafo G
G = nx.Graph()
G.add_edges_from([(4, 5), (4, 6), (5, 6)])

# Criar o subgrafo induzido G' pelos vértices {4, 5, 6}
vertices = [4, 5, 6]
G_prime = G.subgraph(vertices)

# Plotar o subgrafo G'
pos = nx.spring_layout(G_prime)  # Layout para organização dos nós
nx.draw(G_prime, pos, with_labels=True, node_color='lightblue', font_weight='bold')
plt.title("Subgrafo Induzido G'")
plt.show()
