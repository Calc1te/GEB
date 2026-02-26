#include <iostream>
#include "WJUProblem.h"
#include "DFS.h"
#include "BFS.h"

int main() {
    WJUProblem problem;

    std::cout << "=== Running BFS ===\n";
    BFS bfs(problem);
    const auto bfs_result = bfs.search(problem.problem);

    std::cout << "Found: " << (bfs_result.found ? "yes" : "no") << "\n";
    std::cout << "Best state: " << bfs_result.best_state << "\n";
    std::cout << "Nodes expanded: " << bfs_result.nodes_expanded << "\n";

    if (!bfs_result.best_ops.empty()) {
        std::cout << "Ops: ";
        for (size_t i = 0; i < bfs_result.best_ops.size(); ++i) {
            if (i != 0) {
                std::cout << ",";
            }
            std::cout << bfs_result.best_ops[i];
        }
        std::cout << "\n";
    }

    std::cout << "\n=== Running DFS ===\n";
    DFS dfs(problem, 20);

    const auto result = dfs.search(problem.problem);

    std::cout << "Found: " << (result.found ? "yes" : "no") << "\n";
    std::cout << "Best state: " << result.best_state << "\n";
    std::cout << "Best fitness: " << result.best_fitness << "\n";
    std::cout << "Nodes expanded: " << result.nodes_expanded << "\n";

    if (!result.best_ops.empty()) {
        std::cout << "Ops: ";
        for (size_t i = 0; i < result.best_ops.size(); ++i) {
            if (i != 0) {
                std::cout << ",";
            }
            std::cout << result.best_ops[i];
        }
        std::cout << "\n";
    }

    return 0;
}