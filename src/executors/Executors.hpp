#pragma once

#include <cstddef>
#include "../state/InterpreterState.hpp"
#include "../decoders/SingleInstructionDecoders.hpp"

#include "BinopExecutor.hpp"
#include "BuiltinCallsExecutors.hpp"
#include "CallsExecutors.hpp"
#include "JumpExecutors.hpp"
#include "MatchingExecutors.hpp"
#include "MemoryExecutors.hpp"

void exec_const(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<SimpleInstruction<1>>();
    state.frame_stack.op_push(box(instruction.arguments[0]));
}

void exec_drop(InterpreterState &state) {
    state.decoder.consume_as<NoArgumentInstruction>();
    state.frame_stack.op_pop();
}

void exec_dup(InterpreterState &state) {
    state.decoder.consume_as<NoArgumentInstruction>();
    state.frame_stack.op_push(state.frame_stack.op_top());
}

void exec_line(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<SimpleInstruction<1>>();
    state.line = instruction.arguments[0];
    printf("Line %d\n", state.line);
}

void exec_elem(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<NoArgumentInstruction>();
    auto res = Belem(reinterpret_cast<void *>(state.frame_stack.op_top2()), state.frame_stack.op_top());
    state.frame_stack.op_pop();
    state.frame_stack.op_top() = reinterpret_cast<int>(res);
}

void exec_fail(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<SimpleInstruction<2>>();
    failure("Matching failed. Line: %d", instruction.arguments[0]);
}
