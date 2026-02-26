//
// Created by Calcite on 26-2-26.
//

#ifndef DFS_H
#define DFS_H

#include <string>
#include <vector>

class WJUProblem;

class DFS {
public:
    struct Result {
        bool found = false;
        std::string best_state;
        std::vector<int> best_ops;
        int best_fitness = 0;
        int nodes_expanded = 0;
    };

    explicit DFS(WJUProblem &problem, int max_depth = 50);

    Result search(const std::string &start);

private:
    struct SearchTreeNode {
        std::string state;
        int depth = 0;
        int fitness = 0;
        int operation = -1; // 0: wx, 1: wj, 2: jjj, 3: uu
        int parent = -1;
    };

    WJUProblem &problem_;
    int max_depth_;

    std::string apply_operation(const std::string &state, int op);
    std::vector<int> reconstruct_ops(const std::vector<SearchTreeNode> &nodes, int node_index);
};

#endif //DFS_H
