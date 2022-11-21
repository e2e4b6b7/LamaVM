#pragma once

#include <cstddef>

#include "decoders/InstructionsDecoder.hpp"
#include "decoders/SingleInstructionDecoders.hpp"
#include "state/InterpreterState.hpp"
#include "runtime.hpp"
#include "Boxing.hpp"

enum BINOP : char {
    PLUS = 0x01,
    MINUS = 0x02,
    MULTIPLY = 0x03,
    DIVIDE = 0x04,
    REMAINDER = 0x05,
    LESS = 0x06,
    LESS_EQUAL = 0x07,
    GREATER = 0x08,
    GREATER_EQUAL = 0x09,
    EQUAL = 0x0A,
    NOT_EQUAL = 0x0B,
    AND = 0x0C,
    OR = 0x0D,
};

void exec_binop(InterpreterState &state) {
#define BINOP_CODE_BOXED_UNBOXED(OP) \
            state.frame_stack.op_top2() = box(unbox(state.frame_stack.op_top2()) OP unbox(state.frame_stack.op_top())); \
            state.frame_stack.op_pop(); \
            break;
#define BINOP_CODE_BOXED(OP) \
            state.frame_stack.op_top2() = box(state.frame_stack.op_top2() OP state.frame_stack.op_top()); \
            state.frame_stack.op_pop(); \
            break;
#define BINOP_CODE(OP) \
            state.frame_stack.op_top2() = state.frame_stack.op_top2() OP state.frame_stack.op_top(); \
            state.frame_stack.op_pop(); \
            break;
    auto instruction = state.decoder.consume_as<InstructionWithLowerBits<0>>();
    switch (instruction.lower_bits<enum BINOP>()) {
        case PLUS: BINOP_CODE_BOXED_UNBOXED(+)
        case MINUS: BINOP_CODE_BOXED_UNBOXED(-)
        case MULTIPLY: BINOP_CODE_BOXED_UNBOXED(*)
        case DIVIDE: BINOP_CODE_BOXED_UNBOXED(/)
        case REMAINDER: BINOP_CODE_BOXED_UNBOXED(%)
        case LESS: BINOP_CODE_BOXED_UNBOXED(<)
        case LESS_EQUAL: BINOP_CODE_BOXED_UNBOXED(<=)
        case GREATER: BINOP_CODE_BOXED_UNBOXED(>)
        case GREATER_EQUAL: BINOP_CODE_BOXED_UNBOXED(>=)
        case EQUAL: BINOP_CODE_BOXED(==)
        case NOT_EQUAL: BINOP_CODE_BOXED(!=)
        case AND: BINOP_CODE(&&)
        case OR: BINOP_CODE(||)
        default: failure("Unknown binop");
    }
#undef BINOP_CODE
#undef BINOP_CODE_BOXED
#undef BINOP_CODE_BOXED_UNBOXED
}
