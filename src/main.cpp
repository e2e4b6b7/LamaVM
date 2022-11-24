/* Lama SM Bytecode interpreter */

#include "analyzer/analyzer.hpp"
#include "decoders/InstructionsDecoder.hpp"
#include "executors/Executors.hpp"
#include "state/InterpreterState.hpp"
#include "ByteFile.hpp"

[[noreturn]] void interpret(ByteFile &bf) {
    auto state = InterpreterState{bf};
    state.frame_stack.frame_push(nullptr, 2);
#define CMD(NAME, PREFIX) \
            case NAME:    \
                exec_##PREFIX(state); \
                break;
    while (true) {
        switch (state.decoder.instruction_type()) {
            CMD(BINOP, binop)
            CMD(CONST, const)
            CMD(DROP, drop)
            CMD(LD, ld)
            CMD(ST, st)
            CMD(BEGIN, begin)
            CMD(LINE, line)
            CMD(CALL_ARRAY, call_array)
            CMD(CALL_READ, call_read)
            CMD(CALL_LENGTH, call_length)
            CMD(CALL_STRING, call_string)
            CMD(CALL_WRITE, call_write)
            CMD(CALL, call)
            CMD(JMP, jmp)
            CMD(CJMP, cjmp)
            CMD(SEXP, sexp)
            CMD(END, end)
            CMD(DUP, dup)
            CMD(ELEM, elem)
            CMD(ARRAY, array)
            CMD(FAIL, fail)
            CMD(TAG, tag)

            case STRING:
            case STI:
            case STA:
            case RET:
            case SWAP:
            case LDA:
            case CLOSURE:
            case CALLC:
            case PATT:
                failure("not implemented");
            default:
                failure("unknown");

        }
    }
#undef CMD
}

int main(int argc, char *argv[]) {
    assert(argc == 3);
    if (std::string{argv[1]} == "analyze") {
        auto f = ByteFile::read_file(argv[2]);
        analyze(*f);
    } else if (std::string{argv[1]} == "execute") {
        auto f = ByteFile::read_file(argv[2]);
        interpret(*f);
    }
}
