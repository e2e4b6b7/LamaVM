#pragma once

#include "../state/InterpreterState.hpp"
#include "../decoders/SingleInstructionDecoders.hpp"
#include <cstdarg>

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
    state.frame_stack.op_top() = Llength(reinterpret_cast<int *>(state.frame_stack.op_top()));
}

void exec_call_string(InterpreterState &state) {
    state.decoder.consume_as<NoArgumentInstruction>();
    state.frame_stack.op_top() = from_ref(Lstring(ref(state.frame_stack.op_top())));
}

void exec_call_array(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<SimpleInstruction<1>>();
    int nargs = instruction.arguments[0];
    auto res = call_variadic(Barray, nargs, state.frame_stack.op_ptr(nargs), box(nargs));
    state.frame_stack.op_pop(nargs);
    state.frame_stack.op_push(reinterpret_cast<int>(res));
}
