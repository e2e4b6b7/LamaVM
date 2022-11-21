#pragma once

#include "../state/InterpreterState.hpp"
#include "../decoders/SingleInstructionDecoders.hpp"
#include "Boxing.hpp"

void exec_sexp(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<SimpleInstruction<2>>();
    state.frame_stack.op_push(box(instruction.arguments[0]));
    auto argc = instruction.arguments[1] + 1;
    auto argptr = state.frame_stack.op_ptr(argc);
    auto ret = call_variadic(Bsexp, argc, argptr, box(argc));
    state.frame_stack.op_pop(argc);
    state.frame_stack.op_push(reinterpret_cast<int>(ret));
}

void exec_array(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<SimpleInstruction<1>>();
    auto res = Barray_patt(reinterpret_cast<void *>(state.frame_stack.op_top()), box(instruction.arguments[0]));
    state.frame_stack.op_top() = res;
}

void exec_tag(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<SimpleInstruction<2>>();
    auto res = Btag(reinterpret_cast<void *>(state.frame_stack.op_top()), box(instruction.arguments[0]),
                    box(instruction.arguments[1]));
    state.frame_stack.op_top() = res;
}
