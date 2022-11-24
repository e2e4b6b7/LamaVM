#pragma once

#include <string_view>

#include "decoders/InstructionsDecoder.hpp"

std::string_view cmd_name(InstructionType type) {
#define CMD(NAME) case NAME: return #NAME;
    switch (type) {
        CMD(BINOP)
        CMD(CONST)
        CMD(DROP)
        CMD(LD)
        CMD(ST)
        CMD(BEGIN)
        CMD(LINE)
        CMD(CALL_ARRAY)
        CMD(CALL_READ)
        CMD(CALL_LENGTH)
        CMD(CALL_STRING)
        CMD(CALL_WRITE)
        CMD(CALL)
        CMD(JMP)
        CMD(CJMP)
        CMD(SEXP)
        CMD(END)
        CMD(DUP)
        CMD(ELEM)
        CMD(ARRAY)
        CMD(FAIL)
        CMD(TAG)
        CMD(STRING)
        CMD(STI)
        CMD(STA)
        CMD(RET)
        CMD(SWAP)
        CMD(LDA)
        CMD(CALLC)
        CMD(PATT)
        CMD(CLOSURE)
    }
#undef CMD
}
