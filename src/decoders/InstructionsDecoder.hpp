#pragma once

constexpr int LOW_BITS_COUNT = 4;
constexpr char LOW_BITS_MASK = (1 << LOW_BITS_COUNT) - 1;
constexpr char HIGH_BITS_MASK = ~LOW_BITS_MASK;

enum InstructionType : char {
    /** Meaningful lower bits */
    BINOP = 0x00,
    CONST = 0x10,
    STRING = 0x11,
    SEXP = 0x12,
    STI = 0x13,
    STA = 0x14,
    JMP = 0x15,
    END = 0x16,
    RET = 0x17,
    DROP = 0x18,
    DUP = 0x19,
    SWAP = 0x1A,
    ELEM = 0x1B,
    /** Meaningful lower bits */
    LD = 0x20,
    /** Meaningful lower bits */
    LDA = 0x30,
    /** Meaningful lower bits */
    ST = 0x40,
    /** Meaningful lower bit */
    CJMP = 0x50,
    CALL_READ = 0x70,
    CALL_WRITE = 0x71,
    CALL_LENGTH = 0x72,
    CALL_STRING = 0x73,
    CALL_ARRAY = 0x74,
    /** Meaningful lower bit */
    BEGIN = 0x52,
    CLOSURE = 0x54,
    CALLC = 0x55,
    CALL = 0x56,
    TAG = 0x57,
    ARRAY = 0x58,
    FAIL = 0x59,
    LINE = 0x5A,
    /** Meaningful lower bits */
    PATT = 0x60,
};

constexpr char high_bits(char instruction) {
    return static_cast<char>((instruction & HIGH_BITS_MASK) >> LOW_BITS_COUNT);
}

constexpr char low_bits(char instruction) {
    return static_cast<char>(instruction & LOW_BITS_MASK);
}

class InstructionsDecoder {
public:
    const char *ip;

    explicit InstructionsDecoder(const char *ip) : ip(ip) {}

    [[nodiscard]] InstructionType instruction_type() const {
        auto raw_instruction_type = static_cast<InstructionType>(*ip);
        auto h = high_bits(raw_instruction_type);
        switch (h) { /// process operation with meaningful lower bits
            case high_bits(InstructionType::BINOP) :
                return InstructionType::BINOP;
            case high_bits(InstructionType::LD) :
                return InstructionType::LD;
            case high_bits(InstructionType::LDA) :
                return InstructionType::LDA;
            case high_bits(InstructionType::ST) :
                return InstructionType::ST;
            case high_bits(InstructionType::PATT) :
                return InstructionType::PATT;
            default:
                switch (*ip) { /// process operation with meaningful lower bit
                    case InstructionType::CJMP + 1:
                        return InstructionType::CJMP;
                    case InstructionType::BEGIN + 1:
                        return InstructionType::BEGIN;
                    default: /// default case
                        return raw_instruction_type;
                }
        }
    }

    template<class Command>
    const Command &consume_as() {
        auto command = reinterpret_cast<const Command *>(ip);
        ip += command->length();
        return *command;
    }

    template<class Command>
    const Command &view_as() {
        return *reinterpret_cast<const Command *>(ip);
    }
};
