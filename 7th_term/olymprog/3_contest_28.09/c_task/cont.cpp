#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> read_graph(int n, int m) {
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    return graph;
}

void dfs(int v, const std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::vector<int>& component) {
    
    visited[v] = true;
    component.push_back(v);
    for (int neighbor : graph[v]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, component);
        }
    }
}


std::vector<std::vector<int>> find_connected_components(int n, const std::vector<std::vector<int>>& graph) {
    std::vector<bool> visited(n + 1, false);
    std::vector<std::vector<int>> components;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            std::vector<int> component;
            dfs(i, graph, visited, component);
            std::sort(component.begin(), component.end()); // Сортировка вершин внутри компоненты по возрастанию
            components.push_back(component);
        }
    }
    // Сортировка компонент по минимальному элементу по возрастанию
    std::sort(components.begin(), components.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[0] < b[0];
    });

    return components;
}





int main() {
    int t, n, m;
    std::cin >> t >> n >> m;

    std::vector<std::vector<int>> graph = read_graph(n, m);
    std::vector<std::vector<int>> components = find_connected_components(n, graph);
    int sum = 0;
    for (int i = 0; i < components.size(); ++i) {
        sum += components[i];
    }

    std::cout << sum;
}

/*

input

5 4
1 2
2 3
1 3
4 5


output
1 2 3
4 5


*/

/* 

1. adopt t to read_graph
2. добавить взвешивание
3. move downward, upward restricted
3. 


*/