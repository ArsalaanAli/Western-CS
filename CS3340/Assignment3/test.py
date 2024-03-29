import heapq


class Graph:
    def __init__(self, num_vertices):
        self.num_vertices = num_vertices
        self.adjacency_list = [[] for _ in range(num_vertices)]

    def add_edge(self, u, v, weight):
        self.adjacency_list[u - 1].append((v - 1, weight))
        self.adjacency_list[v - 1].append((u - 1, weight))


def read_graph_from_file(filename):
    with open(filename, 'r') as file:
        num_inputs = int(file.readline().strip())
        graph = Graph(num_inputs)
        for line in file:
            u, v, weight = map(int, line.split())
            graph.add_edge(u, v, weight)
    return graph


def prim(graph):
    visited = [False] * graph.num_vertices
    min_heap = [(0, 0)]  # (weight, vertex)
    min_spanning_tree_weight = 0

    while min_heap:
        weight, vertex = heapq.heappop(min_heap)
        if not visited[vertex]:
            visited[vertex] = True
            min_spanning_tree_weight += weight
            for neighbor, edge_weight in graph.adjacency_list[vertex]:
                if not visited[neighbor]:
                    heapq.heappush(min_heap, (edge_weight, neighbor))

    return min_spanning_tree_weight


# Example usage
filename = 'mst_graph.txt'
graph = read_graph_from_file(filename)
min_spanning_tree_weight = prim(graph)
print("Weight of the minimum spanning tree:", min_spanning_tree_weight)
