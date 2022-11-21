#pragma once

#include "state/InterpreterState.hpp"
#include "decoders/SingleInstructionDecoders.hpp"

void exec_call_read(InterpreterState &state) {
    state.decoder.consume_as<NoArgumentInstruction>();
    state.frame_stack.op_push(Lread());
}

void exec_call_write(InterpreterState &state) {
    state.decoder.consume_as<NoArgumentInstruction>();
    Lwrite(state.frame_stack.op_top());
}

void exec_call_length(InterpreterState &state) {
    state.decoder.consume_as<NoArgumentInstruction>();
    state.frame_stack.op_top() = Llength(state.frame_stack.op_top());
}

void exec_call_string(InterpreterState &state) {
    state.decoder.consume_as<NoArgumentInstruction>();
    state.frame_stack.op_top() = Lstring(state.frame_stack.op_top());
}

void exec_call_array(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<SimpleInstruction<1>>();
    int nargs = instruction.arguments[0];
    auto res = call_variadic(Barray, nargs, state.frame_stack.op_ptr(nargs), box(nargs));
    state.frame_stack.op_pop(nargs);
    state.frame_stack.op_push(res);
}

void exec_elem(InterpreterState &state) {
    state.decoder.consume_as<NoArgumentInstruction>();
    auto res = Belem(state.frame_stack.op_top2(), state.frame_stack.op_top());
    state.frame_stack.op_pop();
    state.frame_stack.op_top() = res;
}
