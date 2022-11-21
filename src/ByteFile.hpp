#pragma once

#include <string_view>
#include <fstream>
#include <cstring>
#include "runtime.hpp"

[[maybe_unused]] void *__start_custom_data;
[[maybe_unused]] void *__stop_custom_data;

/* The unpacked representation of bytecode file */
struct ByteFile {
private:
    /** A pointer to the beginning of the string table */
    const char *string_ptr;
    /** A pointer to the beginning of publics table */
    const int *public_ptr;
    /** A pointer to the global area */
    int *global_ptr;
    /** The size (in bytes) of the string table */
    int stringtab_size;
    /** The size (in words) of global area */
    int global_area_size;
    /** The number of public symbols */
    int public_symbols_number;

    char buffer[0];

public:
    /** A pointer to the bytecode itself */
    const char *code_ptr;

    /* Gets a string from a string table by an index */
    std::string_view get_string(int pos) {
        return string_ptr + pos;
    }

    int &global(int index) {
        return global_ptr[index];
    }

    /** Gets a name for a public symbol */
    std::string_view get_public_name(int i) {
        return get_string(public_ptr[i * 2]);
    }

    /** Gets an offset for a public symbol */
    int get_public_offset(int i) {
        return public_ptr[i * 2 + 1];
    }

    /** Reads a binary bytecode file by name and unpacks it */
    static ByteFile *read_file(char *filename) {
        auto file = std::ifstream(filename, std::ios::binary);
        if (!file.is_open() || file.fail()) failure("%s\n", strerror(errno));

        file.seekg(0, std::ios::end);
        auto fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
        if (file.fail()) failure("%s\n", strerror(errno));

        auto byte_file_memory = reinterpret_cast<char *>(malloc(sizeof(void *) * 4 + fileSize));
        if (byte_file_memory == nullptr) failure("*** FAILURE: unable to allocate memory.\n");

        auto byte_file = reinterpret_cast<ByteFile *>(byte_file_memory);

        file.read(reinterpret_cast<char *>(&byte_file->stringtab_size), fileSize);
        if (file.fail()) failure("%s\n", strerror(errno));

        byte_file->string_ptr = byte_file->buffer + byte_file->public_symbols_number * 2 * sizeof(int);
        byte_file->public_ptr = reinterpret_cast<int *>(byte_file->buffer);
        byte_file->code_ptr = byte_file->string_ptr + byte_file->stringtab_size;
        byte_file->global_ptr = reinterpret_cast<int *>(malloc(byte_file->global_area_size * sizeof(int)));

        //TODO: Fix architecture
        __start_custom_data = byte_file->global_ptr;
        __stop_custom_data = byte_file->global_ptr + byte_file->global_area_size;

        return byte_file;
    }
};
