#pragma once

#include <map>
#include <list>
#include <vector>

#include "decoders/InstructionsDecoder.hpp"

class AnalysisState {
public:
    static constexpr int len = 3;

    std::map<InstructionType, int> simple_counter;
    std::map<std::pair<InstructionType, std::vector<int>>, int> parametrized_counter;
    std::map<std::list<InstructionType>, int> simple_groups_counter;
    std::list<InstructionType> suffix;

    void addCmd(InstructionType type, const std::vector<int> &args) {
        simple_counter[type]++;
        if (type != CJMP && type != JMP && type != LINE && type != FAIL) {
            parametrized_counter[{type, args}]++;
            suffix.emplace_back(type);
            if (suffix.size() == len) {
                simple_groups_counter[suffix]++;
                suffix.pop_front();
            }
        }
    }
};
