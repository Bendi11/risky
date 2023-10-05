#pragma once

#include "util/bitflags.hpp"
#include <concepts>
#include <cstdint>
#include <format>

namespace risky {

/// Enumeration over all valid base integer instruction sets that can be expanded upon with extensions
enum struct BaseIntegerISA : std::uint8_t {
    RV32I =  1,
    RV32E =  2,
    RV64I =  3,
    RV128I = 4,
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

struct IsaSpecification {
    BaseIntegerISA isa;
    Extension extensions;

    inline constexpr IsaSpecification(BaseIntegerISA _isa, Extension _ext) noexcept : isa(_isa), extensions(_ext) {}
};

}

template<>
struct std::formatter<risky::BaseIntegerISA> {
    constexpr formatter() {}
    constexpr auto parse(auto& ctx) const noexcept { return std::begin(ctx); }
    auto format(const risky::BaseIntegerISA& obj, auto& ctx) const noexcept {
        auto&& out = ctx.out();
        switch(obj) {
            case risky::BaseIntegerISA::RV32I: return std::format_to(out, "RV32I"); break;
            case risky::BaseIntegerISA::RV32E: return std::format_to(out, "RV32E"); break;
            case risky::BaseIntegerISA::RV64I: return std::format_to(out, "RV64I"); break;
            default: return std::format_to(out, "UNKNOWN"); break;
        }
    }
};

template<>
struct std::formatter<risky::Extension> {
    constexpr formatter() {}
    constexpr auto parse(auto& ctx) const noexcept { return std::begin(ctx); }
    constexpr auto format(const risky::Extension& obj, auto& ctx) const noexcept {
        auto&& out = ctx.out();
        for(auto ext : obj) {
            char ch;
            switch(ext) {
                case risky::Extension::M: ch = 'M'; break;
                case risky::Extension::A: ch = 'A'; break;
                case risky::Extension::P: ch = 'P'; break;
                case risky::Extension::D: ch = 'D'; break;
                case risky::Extension::Q: ch = 'Q'; break;
                case risky::Extension::L: ch = 'L'; break;
                case risky::Extension::C: ch = 'C'; break;
                case risky::Extension::B: ch = 'B'; break;
                case risky::Extension::J: ch = 'J'; break;
                case risky::Extension::T: ch = 'T'; break;
                case risky::Extension::V: ch = 'V'; break;
                case risky::Extension::N: ch = 'N'; break;
                default: ch = 'U'; break;
            }
            std::format_to(out, "{}", ch);
        }

        return out;
    }
};

template <>
struct std::formatter<risky::IsaSpecification> {
    constexpr formatter() {}

    constexpr auto parse(auto& ctx) const noexcept { return std::begin(ctx); }
    
    template<typename FormatContext>
    auto format(const risky::IsaSpecification& obj, FormatContext& ctx) const noexcept {
        return std::format_to(ctx.out(), "{}{}", obj.isa, obj.extensions);
    }
};
