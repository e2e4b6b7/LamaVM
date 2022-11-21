#pragma once

#include <vector>

#include "decoders/InstructionsDecoder.hpp"
#include "ByteFile.hpp"
#include "FrameStack.hpp"

[[maybe_unused]] void *__start_custom_data;
[[maybe_unused]] void *__stop_custom_data;

struct InterpreterState {
    explicit InterpreterState(ByteFile &file) :
            byte_file{file},
            decoder{InstructionsDecoder{file.code_ptr}},
            globals{new word[file.global_area_size]} {
        __start_custom_data = globals;
        __stop_custom_data = globals + file.global_area_size;
    }

    const ByteFile &byte_file;
    InstructionsDecoder decoder;
    FrameStack<64 * 1024 * 1024> frame_stack{};
    word *globals;

#ifdef LAMA_VM_DEBUG
    int line = 0;
#endif
};
