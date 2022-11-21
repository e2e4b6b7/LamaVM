#pragma once

#include "../globals.hpp"

constexpr word unbox(word v) {
    return v >> 1u;
}

constexpr word box(word v) {
    return (v << 1u) | 1u;
}

constexpr bool is_boxed(word v) {
    return v & 1u;
}

void *ref(word v) {
    if constexpr (lama_vm_debug) { assert(!is_boxed(v)); }
    return reinterpret_cast<void *>(v);
}

word from_ref(void *v) {
    if constexpr (lama_vm_debug) { assert(is_boxed(reinterpret_cast<word>(v))); }
    return reinterpret_cast<word>(v);
}
