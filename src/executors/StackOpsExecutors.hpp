#pragma once

#include "state/InterpreterState.hpp"
#include "decoders/SingleInstructionDecoders.hpp"

void exec_drop(InterpreterState &state) {
    state.decoder.consume_as<NoArgumentInstruction>();
    state.frame_stack.op_pop();
}

void exec_dup(InterpreterState &state) {
    state.decoder.consume_as<NoArgumentInstruction>();
    state.frame_stack.op_push(state.frame_stack.op_top());
}

void exec_const(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<SimpleInstruction<1>>();
    state.frame_stack.op_push(box(instruction.arguments[0]));
}
