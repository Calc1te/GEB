//
// Created by Calcite on 26-2-26.
//

#ifndef BFS_H
#define BFS_H

#include <string>
#include <vector>

class WJUProblem;

class BFS {
public:
    struct Result {
        bool found = false;
        std::string best_state;
        std::vector<int> best_ops;
        int nodes_expanded = 0;
    };

    explicit BFS(WJUProblem &problem);

    Result search(const std::string &start);

private:
    struct SearchTreeNode {
        std::string state;
        int depth = 0;
        int operation = -1; // 0: wx, 1: wj, 2: jjj, 3: uu
        int parent = -1;
    };

    WJUProblem &problem_;

    std::string apply_operation(const std::string &state, int op);
    std::vector<int> reconstruct_ops(const std::vector<SearchTreeNode> &nodes, int node_index);
};

#endif //BFS_H

