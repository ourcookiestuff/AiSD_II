#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <sstream>

std::vector<std::string> parseLineStops(std::string line) {
    std::vector<std::string> stops;
    std::stringstream ss(line);
    std::string stop;
    ss >> stop;
    while (ss >> stop) {
        stops.push_back(stop);
    }
    return stops;
}

void createGraph(const std::vector<std::string> &stops, const std::vector<std::vector<std::string>> &lines, std::unordered_map<std::string, int> &stopIndexMap, std::vector<std::vector<int>> &adjList) {
    for (size_t i = 0; i < stops.size(); ++i) {
        stopIndexMap[stops[i]] = i;
    }

    for (const auto &line: lines) {
        std::vector<int> lineStops;
        for (const std::string &stop : line) {
            lineStops.push_back(stopIndexMap[stop]);
        }
        for (size_t j = 0; j < lineStops.size(); ++j) {
            int u = lineStops[j-1];
            int v = lineStops[j];
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
    }
}

std::vector<int> BFS(int startIndex, int endIndex, const std::vector<std::vector<int>> &adjList) {
   std::queue<int> q;
    std::vector<bool> visited(adjList.size(), false);
    std::vector<int> prev(adjList.size(), -1);
    visited[startIndex] = true;
    q.push(startIndex);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for(int neighbor : adjList[current]) {
            if(!visited[neighbor]) {
                visited[neighbor] = true;
                prev[neighbor] = current;
                q.push(neighbor);
                if (neighbor == endIndex)   {
                    return prev;
                }
                
            }
        }
    }
    return prev;
}

void printRoute(const std::vector<int> &prev, int startIndex, int endIndex, const std::vector<std::string> &stops) {
   if (prev[endIndex] == -1) {
        std::cout << "NO ROUTE" << std::endl;
        return;
    }

    std::vector<int> path;
    for (int at = endIndex; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); i++) {
        if (i > 0) std::cout << " ";
        std::cout << stops[path[i]];
    }
    std::cout << std::endl; 
}

int main() {
    /*std::vector<std::string> stops = {"Quackville", "NoodlePark", "BubbleBorough", "GigglesTown", "HiccupHill", "Sneezewind", "FluffyFalls"};
    std::vector<std::vector<std::string>> lines = {
        {"A100", "Quackville", "NoodlePark", "BubbleBorough", "HiccupHill", "Sneezewind", "FluffyFalls"},
        {"M1", "NoodlePark", "Sneezewind"}
    };
    std::string startStop = "Quackville";
    std::string endStop = "FluffyFalls";

    std::unordered_map<std::string, int> stopIndexMap;
    std::vector<std::vector<int>> adjList(stops.size());*/

    int n;
    std::cin >> n;
    std::cin.ignore();
    
    std::vector<std::string> stops(n);
    for (int i = 0; i < n; i++) {
        getline(std::cin, stops[i]);
    }
    
    int m;
    std::cin >> m;
    std::cin.ignore();
    
    std::vector<std::vector<std::string>> lines(m);
    std::string line;
    for (int i = 0; i < m; i++) {
        getline(std::cin, line);
        lines[i] = parseLineStops(line);
    }
    
    std::string startStop, endStop;
    getline(std::cin, line);
    std::stringstream ss(line);
    ss >> startStop >> endStop;
    
    std::unordered_map<std::string, int> stopIndexMap;
    std::vector<std::vector<int>> adjList(n);

    createGraph(stops, lines, stopIndexMap, adjList);

    // Sprawdzanie czy przystanki istnieją w mapie
    if (stopIndexMap.count(startStop) == 0 || stopIndexMap.count(endStop) == 0) {
        std::cout << "NO ROUTE" << std::endl;
        return 0;
    }

    int startIndex = stopIndexMap[startStop];
    int endIndex = stopIndexMap[endStop];

    // Wyszukiwanie najkrótszej ścieżki
    std::vector<int> prev = BFS(startIndex, endIndex, adjList);

    // Drukowanie wyniku
    std::cout << "Wynik: ";
    printRoute(prev, startIndex, endIndex, stops);
}