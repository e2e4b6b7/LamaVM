/* Lama SM Bytecode interpreter */

#include "decoders/InstructionsDecoder.hpp"
#include "ByteFile.hpp"
#include "state/InterpreterState.hpp"
#include "executors/BinopExecutor.hpp"
#include "executors/BuiltinCallsExecutors.hpp"
#include "executors/Executors.hpp"
#include "executors/CallsExecutors.hpp"
#include "executors/JumpExecutors.hpp"

[[noreturn]] void interpret(ByteFile &bf) {
    auto state = InterpreterState{bf};
    state.frame_stack.frame_push(nullptr, 2);
#define CMD(NAME, PREFIX) \
            case NAME:    \
                /*printf(#NAME);printf("\n");*/ \
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
}

int main(int argc, char *argv[]) {
    assert(argc >= 2);
    auto f = ByteFile::read_file(argv[1]);
    interpret(*f);
}

//todo: word typeallias
//todo: reduce reinterpret casts
//todo: profile
//todo: split executors on files
//todo: single executors file
