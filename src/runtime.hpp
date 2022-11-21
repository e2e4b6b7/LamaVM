#pragma once

extern "C" {

[[noreturn]] void failure(const char *s, ...);

int Lread();

int Lwrite(int n);

int Llength(void *p);

void *Lstring(void *p);

void *Barray(int bn, ...);

void *Bsexp(int bn, ...);

int Barray_patt(void *d, int n);

void *Belem(void *p, int i);

int Btag(void *d, int t, int n);

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

