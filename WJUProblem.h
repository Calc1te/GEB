//
// Created by Calcite on 26-2-26.
//

#ifndef WJUPROBLEM_H
#define WJUPROBLEM_H
#include <string>
#include <random>
#include <unordered_map>

class WJUProblem {
public:
 std::string problem = "wj";
 std::string solution = "wu";


 std::string wx (std::string input);

 std::string wj (std:: string input);

 std::string jjj (std::string input);

 std::string uu (std::string input);

 int fitness (const std::string &input) const;

private:
 mutable std::unordered_map<std::string, int> fitness_cache_;
};



#endif //WJUPROBLEM_H
