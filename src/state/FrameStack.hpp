#pragma once

#include <cstddef>
#include <cassert>

[[maybe_unused]] extern void *__gc_stack_top;
[[maybe_unused]] extern void *__gc_stack_bottom;

/// todo: check indices
/// todo: optimize fp sp
/// todo: check fp sp requirements
/// todo: int * will fix most of casts
/// todo: meow meow meow meow meow meow meow meow
template<size_t max_stack>
class FrameStack {
    char *data = new char[max_stack];
    char *fp = nullptr;
    char *sp = data;

public:
    int frame_counter = 0;
    std::vector<int> op_counter;
    std::vector<int> locals_counter;

    FrameStack() {
        memset(data, 0, max_stack);
        __gc_stack_top = data;
        __gc_stack_bottom = data + max_stack;
    }

    ~FrameStack() { delete[] data; }

    void frame_push(const char *ra, int nargs) {
//        printf("Push %d\n", ++frame_counter);
//        op_counter.push_back(0);

        auto prev_sp = sp - nargs * sizeof(int);

        sp += 3 * sizeof(char *);
        auto ptrs = reinterpret_cast<const char **>(sp - 1);
        *ptrs = prev_sp;
        *(ptrs - 1) = fp;
        *(ptrs - 2) = ra;

        fp = sp;
    }

    /**
     * @return previous ip
     */
    const char *frame_pop() {
//        printf("Pop %d\n", --frame_counter);
//        assert(op_counter.back() == 1);
//        op_counter.pop_back();
//        locals_counter.pop_back();

        auto ptrs = reinterpret_cast<char **>(fp - 1);
        sp = *ptrs;
        fp = *(ptrs - 1);
        return *(ptrs - 2);
    }

    int &arg(int i) {
        return *(reinterpret_cast<int *>(fp - 1 - 3 * sizeof(char *)) - i);
    }

    void loc_reserve(int nlocs) {
        assert(sp - fp == 0);
//        locals_counter.push_back(nlocs);
        sp += sizeof(int) * nlocs;
    }

    int &loc_get(int i) {
        return *(reinterpret_cast<int *>(fp - 1) + 1 + i);
    }

    void op_push(int value) {
//        assert((sp - fp) / 4 == locals_counter.back() + op_counter.back());
//        op_counter.back()++;
        sp += sizeof(int);
        *(reinterpret_cast<int *>(sp - 1)) = value;
    }

    void op_pop() {
//        assert((sp - fp) / 4 == locals_counter.back() + op_counter.back());
//        op_counter.back()--;
        sp -= sizeof(int);
    }

    void op_pop(int n) {
//        assert((sp - fp) / 4 == locals_counter.back() + op_counter.back());
//        op_counter.back() -= n;
        sp -= n * sizeof(int);
    }

    int *op_ptr(int n) {
        return reinterpret_cast<int *>(sp - 1) - n + 1;
    }

    int &op_top() {
        return *(reinterpret_cast<int *>(sp - 1));
    }

    int &op_top2() {
        return *(reinterpret_cast<int *>(sp - 1) - 1);
    }
};
