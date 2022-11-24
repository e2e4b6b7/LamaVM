#pragma once

#include <string_view>
#include <fstream>
#include <cstring>

#include "runtime.hpp"

/* The unpacked representation of bytecode file */
struct ByteFile {
private:
    /** A pointer to the beginning of the string table */
    const char *string_ptr;
    /** A pointer to the beginning of publics table */
    const int *public_ptr;
public:
    /** A pointer to the bytecode itself */
    const char *code_ptr;

    /// Next parameters should not be changed as they are fully deserialized as bytes

    /** The size (in bytes) of the string table */
    const uint32_t stringtab_size{};
    /** The size (in words) of global area */
    const uint32_t global_area_size{};
    /** The number of public symbols */
    const uint32_t public_symbols_number{};
private:
    const char buffer[0];

public:

    ByteFile() = delete;

    /** Gets a string from a string table by an index */
    std::string_view get_string(int pos) {
        return string_ptr + pos;
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

        auto byte_file_memory = reinterpret_cast<char *>(malloc(static_cast<size_t>(sizeof(void *) * 4 + fileSize)));
        if (byte_file_memory == nullptr) failure("*** FAILURE: unable to allocate memory.\n");

        auto byte_file = reinterpret_cast<ByteFile *>(byte_file_memory);

        file.read(const_cast<char *>(reinterpret_cast<const char *>(&byte_file->stringtab_size)),
                  static_cast<int>(fileSize));
        if (file.fail()) failure("%s\n", strerror(errno));

        byte_file->string_ptr = byte_file->buffer + byte_file->public_symbols_number * 2 * sizeof(int);
        byte_file->public_ptr = reinterpret_cast<const int *>(byte_file->buffer);
        byte_file->code_ptr = byte_file->string_ptr + byte_file->stringtab_size;

        return byte_file;
    }
};
