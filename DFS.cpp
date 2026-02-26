//
// Created by Calcite on 26-2-26.
//

#include "DFS.h"
#include "WJUProblem.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <stack>
#include <unordered_map>

DFS::DFS(WJUProblem &problem, int max_depth)
    : problem_(problem), max_depth_(max_depth) {}

std::string DFS::apply_operation(const std::string &state, int op) {
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

std::vector<int> DFS::reconstruct_ops(const std::vector<SearchTreeNode> &nodes, int node_index) {
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

DFS::Result DFS::search(const std::string &start) {
    Result result;
    std::vector<SearchTreeNode> nodes;
    nodes.reserve(1024);

    std::stack<int> stack;
    std::unordered_map<std::string, int> best_depth;

    SearchTreeNode root;
    root.state = start;
    root.depth = 0;
    root.fitness = problem_.fitness(start);
    nodes.push_back(root);
    stack.push(0);
    best_depth[start] = 0;

    result.best_state = start;
    result.best_fitness = root.fitness;

    std::cout << "[DFS] Starting search from: \"" << start << "\" (fitness=" << root.fitness << ")\n";
    std::cout << "[DFS] Target: \"" << problem_.solution << "\", Max depth: " << max_depth_ << "\n";

    while (!stack.empty()) {
        const int node_index = stack.top();
        stack.pop();
        const SearchTreeNode &node = nodes[node_index];
        ++result.nodes_expanded;

        const char* op_names[] = {"wx", "wj", "jjj", "uu"};
        std::cout << "[DFS] Expanded node " << result.nodes_expanded
                  << " | depth=" << node.depth
                  << " | state=\"" << node.state << "\" "
                  << " | fitness=" << node.fitness;
        if (node.operation != -1) {
            std::cout << " | op=" << op_names[node.operation];
        }
        std::cout << "\n";

        if (node.state == problem_.solution) {
            result.found = true;
            result.best_state = node.state;
            result.best_fitness = node.fitness;
            result.best_ops = reconstruct_ops(nodes, node_index);
            std::cout << "[DFS] SOLUTION FOUND! State: \"" << result.best_state << "\"\n";
            std::cout << "[DFS] Path: ";
            for (size_t i = 0; i < result.best_ops.size(); ++i) {
                if (i != 0) std::cout << " -> ";
                std::cout << op_names[result.best_ops[i]];
            }
            std::cout << "\n";
            return result;
        }

        if (node.fitness > result.best_fitness) {
            result.best_state = node.state;
            result.best_fitness = node.fitness;
            result.best_ops = reconstruct_ops(nodes, node_index);
            std::cout << "[DFS] New best fitness: " << result.best_fitness
                      << " | state=\"" << result.best_state << "\"\n";
        }

        if (node.depth >= max_depth_) {
            std::cout << "[DFS] Max depth reached, pruning node\n";
            continue;
        }

        std::vector<SearchTreeNode> children;
        children.reserve(4);
        for (int op = 0; op < 4; ++op) {
            SearchTreeNode child;
            child.state = apply_operation(node.state, op);
            if (child.state == node.state) {
                continue;
            }
            if (child.state.length() > 64) {
                std::cout << "[DFS]   Pruning child: length " << child.state.length() << " > 64\n";
                continue;
            }
            child.depth = node.depth + 1;
            auto it = best_depth.find(child.state);
            if (it != best_depth.end() && it->second <= child.depth) {
                std::cout << "[DFS]   Skipping state \"" << child.state
                          << "\" (already visited at depth " << it->second << ")\n";
                continue;
            }
            best_depth[child.state] = child.depth;
            child.fitness = problem_.fitness(child.state);
            child.operation = op;
            child.parent = node_index;
            children.push_back(child);
            std::cout << "[DFS]   Child " << (int)children.size() << ": op=" << op_names[op]
                      << " state=\"" << child.state << "\" fitness=" << child.fitness << "\n";
        }

        std::sort(children.begin(), children.end(), [](const SearchTreeNode &a, const SearchTreeNode &b) {
            return a.fitness > b.fitness;
        });

        // Push in reverse order so the highest fitness is explored first in DFS.
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            nodes.push_back(*it);
            stack.push(static_cast<int>(nodes.size() - 1));
        }
    }

    std::cout << "[DFS] Search exhausted. Best state found: \"" << result.best_state
              << "\" (fitness=" << result.best_fitness << ")\n";
    std::cout << "[DFS] Total nodes expanded: " << result.nodes_expanded << "\n";

    return result;
}
