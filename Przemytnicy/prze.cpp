#include <iostream>
#include <climits>
#include <fstream>
#include <vector>

// Struktura reprezentująca krawędź grafu
struct Edge {
    int destination;
    int cost;

    Edge(int dest, int c) : destination(dest), cost(c) {}
};

// Struktura pary (koszt, wierzchołek)
struct Node {
    int cost;
    int vertex;

    Node() : cost(0), vertex(0) {}
    Node(int c, int v) : cost(c), vertex(v) {}
};

// Implementacja kopca
class MinHeap {
public:
    MinHeap(int max_size) {
        size = 0;
        capacity = max_size;
        heap = new Node[max_size];
    }

    ~MinHeap() {
        delete[] heap;
    }

    void push(Node element) {
        if (size == capacity) return; // Kopiec pełny
        heap[size] = element;
        push_heap_up(size);
        size++;
    }

    Node top() {
        if (size == 0) return Node(-1, -1); // Kopiec pusty
        return heap[0];
    }

    void pop() {
        if (size == 0) return; // Kopiec pusty
        heap[0] = heap[size - 1];
        size--;
        push_heap_down(0);
    }

    bool empty() const {
        return size == 0;
    }

private:
    Node* heap;
    int size;
    int capacity;

    void push_heap_up(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap[idx].cost >= heap[parent].cost) break;
            std::swap(heap[idx], heap[parent]);
            idx = parent;
        }
    }

    void push_heap_down(int idx) {
        int n = size;
        while (true) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int smallest = idx;

            if (left < n && heap[left].cost < heap[smallest].cost)
                smallest = left;
            if (right < n && heap[right].cost < heap[smallest].cost)
                smallest = right;

            if (smallest == idx) break;

            std::swap(heap[idx], heap[smallest]);
            idx = smallest;
        }
    }
};

// Funkcja wykonująca algorytm Dijkstry w celu znalezienia najkrótszej ścieżki
std::vector<int> dijkstra(const std::vector<std::vector<Edge>>& graph, int start) {
    int n = graph.size();
    std::vector<int> costs(n, INT_MAX);
    costs[start] = 0;

    MinHeap pq(n * n); // Kopiec o maksymalnym rozmiarze n*n
    pq.push(Node(0, start));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.cost > costs[current.vertex]) continue;

        for (const Edge& edge : graph[current.vertex]) {
            int neighbor = edge.destination;
            int cost = current.cost + edge.cost;
            if (cost < costs[neighbor]) {
                costs[neighbor] = cost;
                pq.push(Node(cost, neighbor));
            }
        }
    }

    return costs;
}

int main() {
    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
        return 1;
    }

    int n; // liczba rodzajów metali
    input >> n;

    std::vector<int> prices(n + 1); // Tablica cen metali
    for (int i = 1; i <= n; ++i)
        input >> prices[i];

    int m; // liczba procesów przemiany
    input >> m;

    std::vector<std::vector<Edge>> graph(n + 1); // Graf przemiany metali
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        input >> a >> b >> c;
        graph[a].emplace_back(b, c);
    }

    input.close();

    // Koszt najkrótszych ścieżek od złota (metal 1) do wszystkich innych metali
    std::vector<int> min_costs_from_gold = dijkstra(graph, 1);

    // Koszt najkrótszych ścieżek od wszystkich metali do złota (metal 1)
    std::vector<std::vector<Edge>> reverse_graph(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (const Edge& edge : graph[i]) {
            reverse_graph[edge.destination].emplace_back(i, edge.cost);
        }
    }
    std::vector<int> min_costs_to_gold = dijkstra(reverse_graph, 1);

    // Znalezienie minimalnego całkowitego kosztu
    int min_total_cost = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        if (min_costs_from_gold[i] < INT_MAX && min_costs_to_gold[i] < INT_MAX) {
            int total_cost = min_costs_from_gold[i] + min_costs_to_gold[i] + (prices[i] / 2);
            if (total_cost < min_total_cost) {
                min_total_cost = total_cost;
            }
        }
    }

    std::cout << min_total_cost << std::endl;
}
