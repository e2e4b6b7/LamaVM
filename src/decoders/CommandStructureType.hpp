#pragma once

#include "InstructionsDecoder.hpp"
#include "SingleInstructionDecoders.hpp"

template<InstructionType it>
struct CommandStructureTypeBox;

template<InstructionType it>
using command_structure_type = typename CommandStructureTypeBox<it>::type;

#define CST(INSTRUCTION_TYPE, STRUCTURE_TYPE)      \
template<>                                         \
struct CommandStructureTypeBox<INSTRUCTION_TYPE> { \
    using type = STRUCTURE_TYPE;                   \
};

CST(BINOP, InstructionWithLowerBits<0>)
CST(CONST, SimpleInstruction<1>)
CST(STRING, SimpleInstruction<1>)
CST(SEXP, SimpleInstruction<2>)
CST(STI, NoArgumentInstruction)
CST(STA, NoArgumentInstruction)
CST(JMP, SimpleInstruction<1>)
CST(END, NoArgumentInstruction)
CST(RET, NoArgumentInstruction)
CST(DROP, NoArgumentInstruction)
CST(DUP, NoArgumentInstruction)
CST(SWAP, NoArgumentInstruction)
CST(ELEM, NoArgumentInstruction)
CST(LD, InstructionWithLowerBits<1>)
CST(LDA, InstructionWithLowerBits<1>)
CST(ST, InstructionWithLowerBits<1>)
CST(CJMP, InstructionWithLowerBit<1>)
CST(CALL_READ, NoArgumentInstruction)
CST(CALL_WRITE, NoArgumentInstruction)
CST(CALL_LENGTH, NoArgumentInstruction)
CST(CALL_STRING, NoArgumentInstruction)
CST(CALL_ARRAY, SimpleInstruction<1>)
CST(BEGIN, SimpleInstruction<2>)
// CST(CLOSURE, SimpleInstruction<3>) Unsupported instruction
CST(CALLC, SimpleInstruction<1>)
CST(CALL, SimpleInstruction<2>)
CST(TAG, SimpleInstruction<2>)
CST(ARRAY, SimpleInstruction<1>)
CST(FAIL, SimpleInstruction<2>)
CST(LINE, SimpleInstruction<1>)
CST(PATT, NoArgumentInstruction)

#undef CST
