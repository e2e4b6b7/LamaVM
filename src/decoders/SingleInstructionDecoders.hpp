#pragma once

#include <cstddef>
#include "InstructionsDecoder.hpp"

#pragma pack(push, 1)

template<size_t nargs>
class SimpleInstruction {
public:
    char instruction;
    int arguments[nargs];

    static constexpr size_t length() {
        return 1 + nargs * sizeof(int);
    }
};

template<>
class SimpleInstruction<0> {
public:
    char instruction;

    static constexpr size_t length() {
        return 1;
    }
};

using NoArgumentInstruction = SimpleInstruction<0>;

template<size_t nargs>
class InstructionWithLowerBits {
public:
    char instruction;
    int arguments[nargs];

    template<typename Value>
    [[nodiscard]] char lower_bits() const {
        static_assert(sizeof(Value) == sizeof(char));
        return static_cast<Value>(low_bits(instruction));
    }

    static constexpr size_t length() {
        return 1 + nargs * sizeof(int);
    }
};

template<>
class InstructionWithLowerBits<0> {
public:
    char instruction;

    template<typename Value>
    [[nodiscard]] char lower_bits() const {
        static_assert(sizeof(Value) == sizeof(char));
        return static_cast<Value>(low_bits(instruction));
    }

    static constexpr size_t length() {
        return 1;
    }
};

template<size_t nargs>
class InstructionWithLowerBit {
public:
    char instruction;
    int arguments[nargs];

    [[nodiscard]] bool lower_bit() const {
        return instruction & 1;
    }

    static constexpr size_t length() {
        return 1 + nargs * sizeof(int);
    }
};

template<>
class InstructionWithLowerBit<0> {
public:
    char instruction;

    [[nodiscard]] bool lower_bit() const {
        return instruction & 1;
    }

    static constexpr size_t length() {
        return 1;
    }
};

#pragma pack(pop)
