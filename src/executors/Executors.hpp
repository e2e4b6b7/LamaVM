#pragma once

#include <cstddef>

#include "state/InterpreterState.hpp"
#include "decoders/SingleInstructionDecoders.hpp"

#include "BinopExecutor.hpp"
#include "BuiltinCallsExecutors.hpp"
#include "CallsExecutors.hpp"
#include "JumpExecutors.hpp"
#include "MatchingExecutors.hpp"
#include "MemoryExecutors.hpp"
#include "StackOpsExecutors.hpp"

void exec_line(InterpreterState &state) {
    [[maybe_unused]] auto instruction = state.decoder.consume_as<SimpleInstruction<1>>();
#ifdef LAMA_VM_DEBUG
        state.line = instruction.arguments[0];
#endif
}

void exec_fail(InterpreterState &state) {
    auto instruction = state.decoder.consume_as<SimpleInstruction<2>>();
    failure("Matching failed. Line: %d", instruction.arguments[0]);
}
