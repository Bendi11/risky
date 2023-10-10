#pragma once

#include <cstdint>


namespace risky {

/// Constants used to identify operations using values encoded into each instruction
struct InstructionConstants {
    /// Constants encoded in bits 6:2 of an instruction identifying the kind of operation to perform
    ///
    /// Taken from RISC-V ISM Vol. 1 v2.2 chapter 19
    struct Opcode {
        static constexpr inline std::uint8_t
            LOAD =      0b00000,
            LOAD_FP =   0b00001,
            CUSTOM_0 =  0b00010,
            MISC_MEM =  0b00011,
            OP_IMM =    0b00100,
            AUIPC =     0b00101,
            OP_IMM_32 = 0b00110,
            STORE =     0b01000,
            STORE_FP =  0b01001,
            CUSTOM_1 =  0b01010,
            AMO =       0b01011,
            OP =        0b01100,
            LUI =       0b01101,
            OP_32 =     0b01110,
            MADD =      0b10000,
            MSUB =      0b10001,
            NMSUB =     0b10010,
            NMADD =     0b10011,
            OP_FP =     0b10100,
            CUSTOM_2 =  0b10110,
            BRANCH =    0b11000,
            JALR =      0b11001,
            JAL  =      0b11011,
            SYSTEM =    0b11100,
            CUSTOM_3 =  0b11110;
    };

    struct Funct3 {
        static constexpr inline std::uint8_t
            ADD =  0b000,
            SLT =  0b010,
            SLTU = 0b011,
            XOR =  0b100,
            OR  =  0b110,
            AND =  0b111;
    };
};

}
