#pragma once

#include <vector>
#include <map>
#include <iostream>

#include "decoders/InstructionsDecoder.hpp"
#include "decoders/SingleInstructionDecoders.hpp"
#include "decoders/CommandStructureType.hpp"
#include "ByteFile.hpp"
#include "InstructionName.hpp"
#include "AnalysisState.hpp"
#include "AnalyzeSingle.hpp"

void analyze_collect(ByteFile &bf, AnalysisState &state) {
    auto decoder = InstructionsDecoder{bf.code_ptr};
#define CMD(NAME)                                                              \
case NAME:                                                                     \
    analyze_single(state, decoder.consume_as<command_structure_type<NAME>>()); \
    break;

    while (true) {
        switch (decoder.instruction_type()) {
            CMD(BINOP)
            CMD(CONST)
            CMD(DROP)
            CMD(LD)
            CMD(ST)
            CMD(BEGIN)
            CMD(LINE)
            CMD(CALL_ARRAY)
            CMD(CALL_READ)
            CMD(CALL_LENGTH)
            CMD(CALL_STRING)
            CMD(CALL_WRITE)
            CMD(CALL)
            CMD(JMP)
            CMD(CJMP)
            CMD(SEXP)
            CMD(END)
            CMD(DUP)
            CMD(ELEM)
            CMD(ARRAY)
            CMD(FAIL)
            CMD(TAG)
            CMD(STRING)
            CMD(STI)
            CMD(STA)
            CMD(RET)
            CMD(SWAP)
            CMD(LDA)
            CMD(CALLC)
            CMD(PATT)
            case CLOSURE:
                failure("Unsupported opcode");
            default:
                if (*decoder.ip == static_cast<char>(0xFF)) return;
                failure("Unknown opcode %d", decoder.instruction_type());
        }
    }
#undef CMD
}

template<typename T>
std::vector<std::pair<int, T>> sort_by_count(std::map<T, int> map) {
    std::vector<std::pair<int, T>> acc;
    for (auto [v, count]: map) acc.emplace_back(count, v);
    std::sort(acc.begin(), acc.end(), std::greater<>());
    return acc;
}

void print_analysis_results(const AnalysisState &state) {
    std::cout << "Simple count" << std::endl;
    for (auto [count, type]: sort_by_count(state.simple_counter))
        std::cout << cmd_name(type) << ": " << count << std::endl;

    std::cout << "\nParametrized count" << std::endl;
    for (auto [count, ins]: sort_by_count(state.parametrized_counter)) {
        std::cout << cmd_name(ins.first);
        for (auto arg: ins.second)
            std::cout << " " << arg;
        std::cout << ": " << count << std::endl;
    }

    std::cout << "\nSimple groups of length " << AnalysisState::len << " count" << std::endl;
    for (auto [count, ins]: sort_by_count(state.simple_groups_counter)) {
        for (auto arg: ins)
            std::cout << cmd_name(arg) << "; ";
        std::cout << ": " << count << std::endl;
    }
}

void analyze(ByteFile &bf) {
    auto state = AnalysisState{};
    analyze_collect(bf, state);
    print_analysis_results(state);
}
