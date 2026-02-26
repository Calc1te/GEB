//
// Created by Calcite on 26-2-26.
//

#include "WJUProblem.h"
#include <algorithm>
#include <vector>

std::mt19937 gen(std::random_device{}());
std::uniform_int_distribution<int> dist(1, 100);

std::string WJUProblem::wx (std::string input) {
    if (*input.begin() == 'w') {
        const std::string result = input.erase(0,1);
        return 'w' + result + result;
    }
    return input;
}

std::string WJUProblem::wj (std:: string input) {
    if (input.back() == 'j') {
        return input + 'u';
    }
    return input;
}

std::string WJUProblem::jjj (std::string input) {
    if (input.find("jjj") != std::string::npos) {
        return input.replace(input.find("jjj"), 3, "u");
    }
    return input;
}

std::string WJUProblem::uu (std::string input) {
    if (input.find("uu") != std::string::npos) {
        return input.erase(input.find("uu"), 2);
    }
    return input;
}

int WJUProblem::fitness(const std::string &input) const {
    return - input.length() - solution.length();
}
