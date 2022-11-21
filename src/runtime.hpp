#pragma once

#include "globals.hpp"

extern "C" {

[[noreturn]] void failure(const char *s, ...);

word Lread();

word Lwrite(word n);

word Llength(word p);

word Lstring(word p);

word Barray(word bn, ...);

word Bsexp(word bn, ...);

word Barray_patt(word d, word n);

word Belem(word p, word i);

word Btag(word d, word t, word n);

}

auto call_variadic(auto f, int variadic_argc, auto *variadic_argv, auto... args) {
    switch (variadic_argc) {
        case 0:
            return f(args...);
        case 1:
            return f(args..., variadic_argv[0]);
        case 2:
            return f(args..., variadic_argv[0], variadic_argv[1]);
        case 3:
            return f(args..., variadic_argv[0], variadic_argv[1], variadic_argv[2]);
        case 4:
            return f(args..., variadic_argv[0], variadic_argv[1], variadic_argv[2], variadic_argv[3]);
        default:
            failure("Failed to call variadic function");
    }
}
