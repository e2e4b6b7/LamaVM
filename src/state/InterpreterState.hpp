#pragma once

#include <vector>
#include "../decoders/InstructionsDecoder.hpp"
#include "../ByteFile.hpp"
#include "FrameStack.hpp"

struct InterpreterState {
    explicit InterpreterState(ByteFile &file) : byte_file{file}, decoder{InstructionsDecoder{file.code_ptr}} {}

    ByteFile &byte_file;
    InstructionsDecoder decoder;
    FrameStack<64 * 1024 * 1024> frame_stack;

    int line = 0;
};
