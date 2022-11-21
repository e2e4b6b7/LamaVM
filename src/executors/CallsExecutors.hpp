#pragma once

#include "../globals.hpp"
#include "../state/InterpreterState.hpp"
#include "../decoders/SingleInstructionDecoders.hpp"

void exec_call(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<SimpleInstruction<2>>();

    state.frame_stack.frame_push(state.decoder.ip, instruction.arguments[1]);
    state.decoder = InstructionsDecoder(state.byte_file.code_ptr + instruction.arguments[0]);

    if constexpr (lama_vm_debug) {
        auto begin_instruction = state.decoder.view_as<SimpleInstruction<2>>();
        if (begin_instruction.instruction != BEGIN) failure("Invalid call address");
        if (begin_instruction.arguments[0] != instruction.arguments[1]) failure("Arguments count does not match");
    }
}

void exec_begin(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<SimpleInstruction<2>>();
    state.frame_stack.loc_reserve(instruction.arguments[1]);
}

void exec_end(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<NoArgumentInstruction>();
    auto rv = state.frame_stack.op_top();
    auto ip = state.frame_stack.frame_pop();
    if (ip == nullptr) on_finish();
    state.decoder = InstructionsDecoder(ip);
    state.frame_stack.op_push(rv);
}
