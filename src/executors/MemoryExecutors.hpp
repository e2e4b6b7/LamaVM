#pragma once

#include "state/InterpreterState.hpp"
#include "decoders/SingleInstructionDecoders.hpp"

enum Loc : char {
    GLOBAL = 0x00,
    LOCAL = 0x01,
    ARGUMENT = 0x02,
    CLOJURE = 0x03,
};

void exec_st(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<InstructionWithLowerBits<1>>();
    switch (instruction.lower_bits<Loc>()) {
        case GLOBAL:
            state.globals[instruction.arguments[0]] = state.frame_stack.op_top();
            break;
        case LOCAL:
            state.frame_stack.loc_get(instruction.arguments[0]) = state.frame_stack.op_top();
            break;
        case ARGUMENT:
            state.frame_stack.arg(instruction.arguments[0]) = state.frame_stack.op_top();
            break;
        case CLOJURE:
            failure("closure assignment not implemented");
    }
}

void exec_ld(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<InstructionWithLowerBits<1>>();
    switch (instruction.lower_bits<Loc>()) {
        case GLOBAL:
            state.frame_stack.op_push(state.globals[instruction.arguments[0]]);
            break;
        case LOCAL:
            state.frame_stack.op_push(state.frame_stack.loc_get(instruction.arguments[0]));
            break;
        case ARGUMENT:
            state.frame_stack.op_push(state.frame_stack.arg(instruction.arguments[0]));
            break;
        case CLOJURE:
            failure("closure load not implemented");
    }
}
