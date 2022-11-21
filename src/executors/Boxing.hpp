#pragma once

#include "globals.hpp"

constexpr int unbox(word v) {
    return static_cast<int>(v) >> 1u;
}

constexpr word box(int v) {
    return static_cast<word>(v << 1u) | 1u;
}

constexpr bool is_boxed(word v) {
    return v & 1u;
}
