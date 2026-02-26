//
// Created by Calcite on 26-2-26.
//

#include "BFS.h"
#include "WJUProblem.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>

BFS::BFS(WJUProblem &problem) : problem_(problem) {}

std::string BFS::apply_operation(const std::string &state, int op) {
    switch (op) {
        case 0:
            return problem_.wx(state);
        case 1:
            return problem_.wj(state);
        case 2:
            return problem_.jjj(state);
        case 3:
            return problem_.uu(state);
        default:
            return state;
    }
}

std::vector<int> BFS::reconstruct_ops(const std::vector<SearchTreeNode> &nodes, int node_index) {
    std::vector<int> ops;
    int current = node_index;
    while (current != -1) {
        const int op = nodes[current].operation;
        if (op != -1) {
            ops.push_back(op);
        }
        current = nodes[current].parent;
    }
    std::reverse(ops.begin(), ops.end());
    return ops;
}

BFS::Result BFS::search(const std::string &start) {
    Result result;
    std::vector<SearchTreeNode> nodes;
    nodes.reserve(1024);

    std::queue<int> q;
    std::unordered_set<std::string> visited;

    SearchTreeNode root;
    root.state = start;
    root.depth = 0;
    nodes.push_back(root);
    q.push(0);
    visited.insert(start);

    result.best_state = start;

    std::cout << "[BFS] Starting search from: \"" << start << "\"\n";
    std::cout << "[BFS] Target: \"" << problem_.solution << "\"\n";

    while (!q.empty()) {
        const int node_index = q.front();
        q.pop();
        // Copy data to avoid invalidation on vector resize
        const std::string current_state = nodes[node_index].state;
        const int current_depth = nodes[node_index].depth;

        ++result.nodes_expanded;

        const char* op_names[] = {"wx", "wj", "jjj", "uu"};
        if (result.nodes_expanded % 1000 == 0) {
            std::cout << "[BFS] Expanded node " << result.nodes_expanded
                      << " | depth=" << current_depth
                      << " | queue_size=" << q.size()
                      << " | state_len=" << current_state.length() << "\n";
        }

        if (current_state == problem_.solution) {
            result.found = true;
            result.best_state = current_state;
            result.best_ops = reconstruct_ops(nodes, node_index);
            std::cout << "[BFS] SOLUTION FOUND! State: \"" << result.best_state << "\"\n";
            std::cout << "[BFS] Path: ";
            for (size_t i = 0; i < result.best_ops.size(); ++i) {
                if (i != 0) std::cout << " -> ";
                std::cout << op_names[result.best_ops[i]];
            }
            std::cout << "\n";
            return result;
        }

        for (int op = 0; op < 4; ++op) {
            std::string new_state = apply_operation(current_state, op);

            if (new_state == current_state) continue;

            // Pruning condition from DFS
            if (new_state.length() > 128) continue;

            if (visited.find(new_state) == visited.end()) {
                visited.insert(new_state);

                SearchTreeNode child;
                child.state = new_state;
                child.depth = current_depth + 1;
                child.operation = op;
                child.parent = node_index;

                nodes.push_back(child);
                q.push(static_cast<int>(nodes.size() - 1));
            }
        }
    }

    std::cout << "[BFS] Search exhausted. Best state found: \"" << result.best_state << "\"\n";
    std::cout << "[BFS] Total nodes expanded: " << result.nodes_expanded << "\n";

    return result;
}


