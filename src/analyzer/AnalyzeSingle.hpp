#pragma once

#include <cstddef>
#include <vector>

#include "decoders/SingleInstructionDecoders.hpp"
#include "AnalysisState.hpp"

template<size_t nargs>
void analyze_single(AnalysisState &state, const SimpleInstruction<nargs> &cmd) {
    auto args = std::vector<int>();
    for (size_t i = 0; i < nargs; ++i) args.push_back(cmd.arguments[i]);
    state.addCmd(static_cast<InstructionType>(cmd.instruction), args);
}

template<size_t nargs>
void analyze_single(AnalysisState &state, const InstructionWithLowerBits<nargs> &cmd) {
    auto args = std::vector<int>();
    args.push_back(cmd.template lower_bits<char>());
    for (size_t i = 0; i < nargs; ++i) args.push_back(cmd.arguments[i]);
    state.addCmd(static_cast<InstructionType>(cmd.instruction & HIGH_BITS_MASK), args);
}

template<size_t nargs>
void analyze_single(AnalysisState &state, const InstructionWithLowerBit<nargs> &cmd) {
    auto args = std::vector<int>();
    args.push_back(cmd.lower_bit());
    for (size_t i = 0; i < nargs; ++i) args.push_back(cmd.arguments[i]);
    state.addCmd(static_cast<InstructionType>(cmd.instruction & (~1)), args);
}
