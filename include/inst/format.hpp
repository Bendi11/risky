#pragma once

#include "register/register.hpp"
#include "risky.hpp"
#include "util/bitmanip.hpp"


namespace risky {

namespace inst {

struct R {
    std::uint8_t funct7;
    std::uint8_t rs2;
    std::uint8_t rs1;
    std::uint8_t funct3;
    std::uint8_t rd;

    /// Read all parameters of the given instruction in R format
    inline constexpr R(std::uint32_t inst) noexcept {
        funct7 = readbits_zext<31,25>(inst);
        rs2    = readbits_zext<24,20>(inst);
        rs1    = readbits_zext<19,15>(inst);
        funct3 = readbits_zext<14, 12>(inst);
        rd     = readbits_zext<11,7>(inst);
    }
};

template<RegisterWidth W>
struct I {
    /// Sign-extended immediate value
    IRegister<W> imm;

    std::uint8_t rs1;
    std::uint8_t funct3;
    std::uint8_t rd;

    /// Read all parameters and sign-extend the given immediate value instruction
    inline constexpr I(std::uint32_t inst) noexcept {
        imm = IRegister<W>{readbits_sext<31,20,std::uint32_t,std::int32_t>(inst)};
        rs1 = readbits_zext<19,15>(inst);
        funct3 = readbits_zext<14,12>(inst);
        rd = readbits_zext<11,7>(inst);
    }
};

}

}
