#pragma once

#include "util/bitflags.hpp"
#include <concepts>
#include <cstdint>

/// Enumeration over all valid base integer instruction sets that can be expanded upon with extensions
struct BaseIntegerISA : BitFlags<std::uint8_t> {
    typedef std::uint8_t flag_t;
    
    /// Instruction set flags used to enable or disable functionality of the emulator
    static constexpr const flag_t
        RV32I = (1 << 0),
        RV32E = (1 << 1),
        RV64I = (1 << 2);
    
    BaseIntegerISA() = delete;
    template<typename... F>
    inline constexpr BaseIntegerISA(F... base) noexcept : BitFlags(base...) {}
};

struct Extension : BitFlags<std::uint16_t> {
    typedef std::uint16_t flag_t;

    static constexpr const flag_t
        M = 1 << 0,
        A = 1 << 1,
        P = 1 << 2,
        D = 1 << 3,
        Q = 1 << 4,
        L = 1 << 5,
        C = 1 << 6,
        B = 1 << 7,
        J = 1 << 8,
        T = 1 << 9,
        V = 1 << 10,
        N = 1 << 11;

    Extension() = default;
    template<typename... F>
    inline constexpr Extension(F... base) noexcept : BitFlags(base...) {}
};
