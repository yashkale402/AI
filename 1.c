Practical  
1)  Given an initial state of a 8-puzzle problem and final state to be reached- 
Find the most cost-effective path to reach the final state from initial state using A* 
Algorithm in Python. 
Consider g(n) = Depth of node and h(n) = Number of misplaced tiles. 
OUTPUT: 
import heapq 
class Node: 
def __init__(self, state, parent=None): 
self.state = state 
self.parent = parent 
self.g = 0  # Cost from start to current node 
self.h = self.calculate_h()  # Heuristic cost to the goal 
self.f = self.g + self.h  # Total cost 
def calculate_h(self): 
"""Calculate the number of misplaced tiles.""" 
goal_state = [[1, 2, 3], [8, 0, 4], [7, 6, 5]] 
return sum(1 for i in range(3) for j in range(3) if self.state[i][j] != 
goal_state[i][j] and self.state[i][j] != 0) 
def __lt__(self, other): 
return self.f < other.f 
def get_empty_tile_position(state): 
"""Find the position of the empty tile (0).""" 
for i in range(3): 
for j in range(3): 
if state[i][j] == 0: 
return i, j 
def generate_neighbors(node): 
"""Generate all possible states from the current node.""" 
neighbors = [] 
directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # Up, Down, Left, Right 
empty_i, empty_j = get_empty_tile_position(node.state) 
for direction in directions: 
new_i, new_j = empty_i + direction[0], empty_j + direction[1] 
if 0 <= new_i < 3 and 0 <= new_j < 3:  # Check bounds 
new_state = [list(row) for row in node.state]  # Copy current state 
# Swap the empty tile with the adjacent tile 
new_state[empty_i][empty_j], new_state[new_i][new_j] = 
new_state[new_i][new_j], new_state[empty_i][empty_j] 
neighbors.append(Node(new_state, node)) 
return neighbors 
def a_star(initial_state): 
"""Perform A* search to find the solution to the 8-puzzle.""" 
initial_node = Node(initial_state) 
open_set = [] 
heapq.heappush(open_set, initial_node) 
closed_set = set() 
while open_set: 
current_node = heapq.heappop(open_set) 
# Check if the goal state is reached 
if current_node.h == 0: 
return reconstruct_path(current_node) 
closed_set.add(tuple(map(tuple, current_node.state))) 
for neighbor in generate_neighbors(current_node): 
if tuple(map(tuple, neighbor.state)) in closed_set: 
continue 
neighbor.g = current_node.g + 1 
neighbor.f = neighbor.g + neighbor.h 
if all(neighbor.f <= open_node.f for open_node in open_set if 
neighbor.state == open_node.state): 
heapq.heappush(open_set, neighbor) 
return None  # No solution found 
def reconstruct_path(node): 
"""Reconstruct the path from the initial state to the goal state.""" 
path = [] 
while node: 
path.append(node.state) 
node = node.parent 
return path[::-1]  # Reverse to get the path from start to goal 
# Example usage 
if __name__ == "__main__": 
initial_state = [[2, 8, 3], [1, 6, 4], [7, 0, 5]] 
goal_state = [[1, 2, 3], [8, 0, 4], [7, 6, 5]] 
solution_path = a_star(initial_state) 
if solution_path: 
print("Solution path:") 
for step in solution_path: 
for row in step: 
print(row) 
print()  # Newline for better readability 
else: 
print("No solution found.") 
2) Consider the following graph- 
The numbers written on edges represent the distance between the nodes. 
The numbers written on nodes represent the heuristic value. 
Implement A* algorithm in Python for above graph and find out most cost
effective path from A to J. 
OUTPUT: 
import heapq 
class Node: 
def __init__(self, name, heuristic): 
self.name = name 
self.heuristic = heuristic 
self.edges = {}  # edges will hold neighbor and cost 
self.g = float('inf')  # Cost from start node 
self.f = float('inf')  # Total cost (g + h) 
def add_edge(self, neighbor, cost): 
self.edges[neighbor] = cost 
def __lt__(self, other): 
return self.f < other.f 
def a_star(start_node, goal_node): 
open_set = [] 
start_node.g = 0 
start_node.f = start_node.heuristic 
heapq.heappush(open_set, start_node) 
came_from = {} 
while open_set: 
current_node = heapq.heappop(open_set) 
# Check if we reached the goal 
if current_node.name == goal_node.name: 
return reconstruct_path(came_from, current_node) 
for neighbor_name, cost in current_node.edges.items(): 
neighbor_node = neighbor_name 
tentative_g = current_node.g + cost 
if tentative_g < neighbor_node.g: 
came_from[neighbor_node] = current_node 
neighbor_node.g = tentative_g 
neighbor_node.f = neighbor_node.g + neighbor_node.heuristic 
if neighbor_node not in open_set: 
heapq.heappush(open_set, neighbor_node) 
return None  # No path found 
def reconstruct_path(came_from, current_node): 
total_path = [current_node.name] 
while current_node in came_from: 
current_node = came_from[current_node] 
total_path.append(current_node.name) 
return total_path[::-1]  # Reverse the path 
# Define the graph nodes and heuristics 
nodes = { 
'A': Node('A', 10), 
'B': Node('B', 8), 
'C': Node('C', 5), 
'D': Node('D', 7), 
'E': Node('E', 3), 
'F': Node('F', 6), 
'G': Node('G', 5), 
'H': Node('H', 3), 
'I': Node('I', 1), 
'J': Node('J', 1) 
} 
# Define the edges 
nodes['A'].add_edge(nodes['B'], 6) 
nodes['A'].add_edge(nodes['F'], 3) 
nodes['B'].add_edge(nodes['D'], 2) 
nodes['B'].add_edge(nodes['C'], 3) 
nodes['C'].add_edge(nodes['D'], 1) 
nodes['C'].add_edge(nodes['E'], 5) 
nodes['D'].add_edge(nodes['E'], 8) 
nodes['E'].add_edge(nodes['I'], 5) 
nodes['E'].add_edge(nodes['J'], 5) 
nodes['J'].add_edge(nodes['I'], 3) 
nodes['I'].add_edge(nodes['G'], 3) 
nodes['I'].add_edge(nodes['H'], 2) 
nodes['F'].add_edge(nodes['H'], 7) 
nodes['G'].add_edge(nodes['F'], 1) 
# Run the A* algorithm 
start_node = nodes['A'] 
goal_node = nodes['J'] 
path = a_star(start_node, goal_node) 
# Print the results 
if path: 
print("Path from A to J:", " -> ".join(path)) 
else: 
print("No path found.") 
3) Implement AO* algorithm in python for following graph and find out minimum 
cost solution. 
OUTPUT: 
Class Node: 
def __init__(self, name): 
self.name = name 
self.edges = {}  # edges will hold neighbor and cost 
self.is_goal = False 
def add_edge(self, neighbor, cost): 
self.edges[neighbor] = cost 
def ao_star(start_node): 
"""Perform AO* search to find the minimum cost solution.""" 
solution_found = False 
best_cost = float('inf') 
best_path = [] 
# Initialize the open list 
open_list = {start_node: (0, [])} 
while open_list: 
# Get the node with the lowest cost 
current_node = min(open_list, key=lambda k: open_list[k][0]) 
current_cost, path = open_list[current_node] 
# Check if current node is a goal 
if current_node.is_goal: 
solution_found = True 
if current_cost < best_cost: 
best_cost = current_cost 
best_path = path + [current_node.name] 
# Remove the current node from open list 
del open_list[current_node] 
# Explore neighbors 
for neighbor, cost in current_node.edges.items(): 
total_cost = current_cost + cost 
new_path = path + [current_node.name] 
# Update the open list 
if neighbor not in open_list or total_cost < open_list[neighbor][0]: 
open_list[neighbor] = (total_cost, new_path) 
return best_cost, best_path if solution_found else None 
# Define the graph nodes 
A = Node('A') 
B = Node('B') 
C = Node('C') 
D = Node('D') 
E = Node('E') 
F = Node('F') 
# Define edges 
A.add_edge(B, 4) 
A.add_edge(C, 5) 
A.add_edge(D, 5) 
B.add_edge(C, 2) 
C.add_edge(E, 2) 
D.add_edge(E, 2) 
D.add_edge(F, 4) 
# Mark goal nodes 
F.is_goal = True 
# Run the AO* algorithm 
cost, path = ao_star(A) 
# Print the results 
if path: 
print("Minimum cost:", cost) 
print("Path:", " -> ".join(path)) 
else: 
print("No solution found.") 
4) Write a Python program to implement Water Jug Problem. 
OUTPUT: 
from collections import deque 
class JugState: 
def __init__(self, jug1, jug2, target, capacity1, capacity2): 
self.jug1 = jug1 
self.jug2 = jug2 
self.target = target 
self.capacity1 = capacity1 
self.capacity2 = capacity2 
def is_goal(self): 
return self.jug1 == self.target or self.jug2 == self.target 
def get_possible_states(self): 
states = [] 
# Fill jug1 
states.append(JugState(self.capacity1, self.jug2, self.target, self.capacity1, 
self.capacity2)) 
# Fill jug2 
states.append(JugState(self.jug1, self.capacity2, self.target, self.capacity1, 
self.capacity2)) 
# Empty jug1 
states.append(JugState(0, self.jug2, self.target, self.capacity1, self.capacity2)) 
# Empty jug2 
states.append(JugState(self.jug1, 0, self.target, self.capacity1, self.capacity2)) 
# Pour jug1 to jug2 
transfer = min(self.jug1, self.capacity2 - self.jug2) 
states.append(JugState(self.jug1 - transfer, self.jug2 + transfer, self.target, 
self.capacity1, self.capacity2)) 
# Pour jug2 to jug1 
transfer = min(self.jug2, self.capacity1 - self.jug1) 
states.append(JugState(self.jug1 + transfer, self.jug2 - transfer, self.target, 
self.capacity1, self.capacity2)) 
return states 
def bfs_water_jug(capacity1, capacity2, target): 
initial_state = JugState(0, 0, target, capacity1, capacity2) 
queue = deque([initial_state]) 
visited = set() 
while queue: 
current_state = queue.popleft() 
if current_state.is_goal(): 
return f"Solution found: Jug1 = {current_state.jug1}, Jug2 = 
{current_state.jug2}" 
visited.add((current_state.jug1, current_state.jug2)) 
for state in current_state.get_possible_states(): 
if (state.jug1, state.jug2) not in visited: 
queue.append(state) 
return "No solution found." 
# Example usage 
if __name__ == "__main__": 
capacity1 = 4  # Capacity of Jug 1 
capacity2 = 3  # Capacity of Jug 2 
target = 2     # Target amount to measure 
result = bfs_water_jug(capacity1, capacity2, target) 
print(result) 
5) Write a Python program to implement Breadth First Search Traversal Using a 
Recursive Method. 
OUTPUT : 
from collections import deque 
class Graph: 
def __init__(self): 
self.graph = {} 
def add_edge(self, u, v): 
if u not in self.graph: 
self.graph[u] = [] 
self.graph[u].append(v) 
def bfs_recursive(self, start): 
visited = set() 
queue = deque([start]) 
self._bfs_helper(queue, visited) 
def _bfs_helper(self, queue, visited): 
if not queue: 
return 
node = queue.popleft() 
if node not in visited: 
visited.add(node) 
print(node, end=' ') 
# Enqueue all adjacent nodes that haven't been visited 
for neighbor in self.graph.get(node, []): 
if neighbor not in visited: 
queue.append(neighbor) 
# Recursive call for the next level of nodes 
self._bfs_helper(queue, visited) 
# Example usage 
if __name__ == "__main__": 
g = Graph() 
g.add_edge(0, 1) 
g.add_edge(0, 2) 
g.add_edge(1, 3) 
g.add_edge(1, 4) 
g.add_edge(2, 5) 
g.add_edge(2, 6) 
print("Breadth First Search Traversal starting from node 0:") 
g.bfs_recursive(0) 
6) Write a Python program to implement Depth First Search Traversal Using a 
Recursive Method. 
OUTPUT :  
class Graph: 
def __init__(self): 
self.graph = {} 
def add_edge(self, u, v): 
if u not in self.graph: 
self.graph[u] = [] 
self.graph[u].append(v) 
def dfs_recursive(self, start): 
visited = set()  # Set to keep track of visited nodes 
self._dfs_helper(start, visited) 
def _dfs_helper(self, node, visited): 
if node not in visited: 
visited.add(node) 
print(node, end=' ') 
# Recursively visit all the neighbors 
for neighbor in self.graph.get(node, []): 
self._dfs_helper(neighbor, visited) 
# Example usage 
if __name__ == "__main__": 
g = Graph() 
g.add_edge(0, 1) 
g.add_edge(0, 2) 
g.add_edge(1, 3) 
g.add_edge(1, 4) 
g.add_edge(2, 5) 
g.add_edge(2, 6) 
print("Depth First Search Traversal starting from node 0:") 
g.dfs_recursive(0) 
7)  Write a Python program to implement Breadth First Search Traversal. 
OUTPUT : 
from collections import deque 
class Graph: 
def __init__(self): 
self.graph = {} 
def add_edge(self, u, v): 
if u not in self.graph: 
self.graph[u] = [] 
if v not in self.graph: 
self.graph[v] = [] 
self.graph[u].append(v) 
self.graph[v].append(u)  # For undirected graph 
def bfs(self, start): 
visited = set()  # Set to keep track of visited nodes 
queue = deque([start])  # Initialize the queue with the starting node 
while queue: 
node = queue.popleft()  # Dequeue a vertex from the queue 
if node not in visited: 
print(node, end=' ')  # Print the current node 
visited.add(node)  # Mark the node as visited 
# Enqueue all adjacent nodes that haven't been visited 
for neighbor in self.graph.get(node, []): 
if neighbor not in visited: 
queue.append(neighbor) 
# Example usage 
if __name__ == "__main__": 
g = Graph() 
g.add_edge(0, 1) 
g.add_edge(0, 2) 
g.add_edge(1, 3) 
g.add_edge(1, 4) 
g.add_edge(2, 5) 
g.add_edge(2, 6) 
print("BFS Traversal starting from node 0:") 
g.bfs(0) 
8) Write a Python program to implement Depth First Search Traversal. 
OUTPUT: 
import networkx as nx 
import matplotlib.pyplot as plt 
class Graph: 
def __init__(self, directed=False): 
self.graph = nx.DiGraph() if directed else nx.Graph() 
def add_edge(self, u, v): 
self.graph.add_edge(u, v) 
def dfs(self, start, visited=None): 
if visited is None: 
visited = set()  # Initialize visited set on the first call 
visited.add(start)  # Mark the current node as visited 
print(start, end=' ')  # Print the current node 
# Recur for all the vertices adjacent to this vertex 
for neighbor in self.graph.neighbors(start): 
if neighbor not in visited: 
self.dfs(neighbor, visited)  # Recursive call 
def display_graph(self): 
pos = nx.spring_layout(self.graph)  # Positions for all nodes 
nx.draw(self.graph, pos, with_labels=True, node_color='lightgreen', 
node_size=1000, font_size=16) 
plt.show() 
# Example usage 
if __name__ == "__main__": 
g = Graph(directed=False)  # Set directed=True for a directed graph 
g.add_edge(0, 1) 
g.add_edge(0, 2) 
g.add_edge(1, 3) 
g.add_edge(1, 4) 
g.add_edge(2, 5) 
g.add_edge(2, 6) 
print("Graph structure:") 
g.display_graph() 
print("\nDFS Traversal starting from node 0:") 
g.dfs(0) 
9)  Write a Python program to implement Simple Chatbot. 
OUTPUT: 
import random 
class SimpleChatbot: 
def __init__(self): 
self.responses = { 
"hello": ["Hi there!", "Hello!", "Greetings!", "How can I assist you 
today?"], 
"how are you": ["I'm just a computer program, but thanks for asking!", 
"Doing great! How about you?", "I'm here to help you!"], 
"what is your name": ["I'm a simple chatbot.", "You can call me Chatbot!", 
"Just a friendly bot here!"], 
"bye": ["Goodbye!", "See you later!", "Take care!"], 
} 
def get_response(self, user_input): 
# Normalize the input to lower case 
user_input = user_input.lower() 
# Check if the input matches any known responses 
for key in self.responses: 
if key in user_input: 
return random.choice(self.responses[key]) 
return "I'm sorry, I don't understand that." 
def chat(self): 
print("Chatbot: Hello! I'm your simple chatbot. Type 'bye' to exit.") 
while True: 
user_input = input("You: ") 
if user_input.lower() == "bye": 
print("Chatbot: Goodbye!") 
break 
response = self.get_response(user_input) 
print(f"Chatbot: {response}") 
if __name__ == "__main__": 
chatbot = SimpleChatbot() 
chatbot.chat() 