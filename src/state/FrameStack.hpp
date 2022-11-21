#pragma once

#include <cstddef>
#include <cassert>
#include <algorithm>

#include "globals.hpp"
#include "executors/Boxing.hpp"

[[maybe_unused]] extern void *__gc_stack_top;
[[maybe_unused]] extern void *__gc_stack_bottom;

template<size_t max_stack>
class FrameStack {
    word *data = new word[max_stack];
    word *fp = nullptr;
    word *sp = reinterpret_cast<word *>(data);

public:
    FrameStack() {
        __gc_stack_top = data;
        __gc_stack_bottom = data;
    }

    ~FrameStack() { delete[] data; }

    void frame_push(const char *ra, int nargs) {
        if (nargs > 1) std::reverse(sp - nargs, sp);
        auto prev_sp = sp - nargs;
        *sp = reinterpret_cast<word>(prev_sp);
        *(sp + 1) = reinterpret_cast<word>(fp);
        *(sp + 2) = reinterpret_cast<word>(ra);
        __gc_stack_bottom = sp += 3;
        fp = sp;
    }

    /**
     * @return previous ip
     */
    const char *frame_pop() {
        auto prev_fp = fp;
        __gc_stack_bottom = sp = reinterpret_cast<word *>(*(prev_fp - 3));
        fp = reinterpret_cast<word *>(*(prev_fp - 2));
        return reinterpret_cast<const char *>((*(prev_fp - 1)));
    }

    word &arg(int i) {
        return *(fp - 4 - i);
    }

    void loc_reserve(int nlocs) {
        if constexpr (lama_vm_debug) { assert(sp == fp); }
        __gc_stack_bottom = sp += nlocs;
    }

    word &loc_get(int i) {
        return *(fp + i);
    }

    void op_push(word value) {
        *sp = value;
        __gc_stack_bottom = ++sp;
    }

    void op_pop() {
        __gc_stack_bottom = --sp;
    }

    void op_pop(int n) {
        __gc_stack_bottom = sp -= n;
    }

    word *op_ptr(int n) {
        return sp - n;
    }

    word &op_top() {
        return *(sp - 1);
    }

    word &op_top2() {
        return *(sp - 2);
    }
};
