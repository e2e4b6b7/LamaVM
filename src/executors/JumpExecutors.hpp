#pragma once

#include "../state/InterpreterState.hpp"
#include "../decoders/SingleInstructionDecoders.hpp"

void exec_jmp(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<SimpleInstruction<1>>();
    state.decoder = InstructionsDecoder(state.byte_file.code_ptr + instruction.arguments[0]);
}

void exec_cjmp(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<InstructionWithLowerBit<1>>();
    if (instruction.lower_bit() == (state.frame_stack.op_top() != box(0)))
        state.decoder = InstructionsDecoder(state.byte_file.code_ptr + instruction.arguments[0]);
    state.frame_stack.op_pop();
}
