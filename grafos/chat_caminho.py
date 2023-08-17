import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()
G.add_nodes_from([1, 2, 3, 4, 5, 6])
G.add_edges_from([(1, 2), (1, 5), (2, 4), (2, 3), (3, 4), (3, 6), (4, 5), (4, 6), (5, 6)])

nx.draw(G, with_labels=True, node_size=1000, node_color='lightblue', font_weight='bold')
plt.show()

path = [1, 2, 4, 6]
G_path = G.subgraph(path)

nx.draw(G_path, with_labels=True, node_size=1000, node_color='lightblue', font_weight='bold')
plt.show()

trail = [1, 2, 3, 6, 4, 5]
G_trail = G.subgraph(trail)

nx.draw(G_trail, with_labels=True, node_size=1000, node_color='lightblue', font_weight='bold')
plt.show()
