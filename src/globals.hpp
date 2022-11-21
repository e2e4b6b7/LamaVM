#pragma once

#include <cstdio>
#include <cstdlib>

#define LAMA_VM_DEBUG

#ifdef LAMA_VM_DEBUG
constexpr bool lama_vm_debug = true;
#else
constexpr bool lama_vm_debug = false;
#endif

using word = uint32_t;

static_assert(sizeof(word) == sizeof(void*));
static_assert(sizeof(word) == sizeof(int));

[[noreturn]] void on_finish() {
    printf("\nFinished\n");
    exit(0);
}
