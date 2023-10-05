#pragma once

#include "risky.hpp"
#include <array>
#include <cstdint>
#include <concepts>
#include <string_view>

namespace risky {

/// Base class for all registers across a variety of widths, with common conversion operations already defined
template<typename T>
struct RegisterBase {
public:
    inline constexpr RegisterBase(T v) noexcept : _v(v) {}
    inline constexpr RegisterBase() noexcept : _v(0) {}

    inline constexpr operator T() const noexcept { return _v; }
    inline constexpr operator T&() & noexcept { return _v; }
    inline constexpr operator T const&() const& noexcept { return _v; }
private:
    T _v;
};

template<RegisterWidth>
struct IRegister;

template<>
struct IRegister<RegisterWidth::W32> : RegisterBase<std::uint32_t> {};
template<>
struct IRegister<RegisterWidth::W64> : RegisterBase<std::uint64_t> {};

/// Base class for integer register collections, with a common array containing each register value
template<typename Storage, std::size_t COUNT>
struct IRegistersBase {
public:
    typedef Storage Register;
    static constexpr const std::size_t NUMREGS = COUNT;

    constexpr IRegistersBase() noexcept : _regs() {}
    inline constexpr Storage& operator[](std::size_t idx) & noexcept { return _regs[idx]; }
    inline constexpr Storage operator[](std::size_t idx) const& noexcept { return _regs[idx]; }
protected:
    std::array<Storage, COUNT> _regs;
};

template<BaseIntegerISA a>
struct IRegisters;

/// Integer registers defined for the RV32I base instruction set
template<>
struct IRegisters<BaseIntegerISA::RV32I> : IRegistersBase<IRegister<RegisterWidth::W32>, 32> {
#define REG(name, idx) \
    inline constexpr Register name() const& noexcept { return _regs[idx]; } \
    inline constexpr Register& name() & noexcept { return _regs[idx]; }

    #include "names.inc"
#undef REG
};

/// Integer registers defined for the RV64I base intstruction set
template<>
struct IRegisters<BaseIntegerISA::RV64I> : IRegistersBase<IRegister<RegisterWidth::W64>, 32> {
#define REG(name, idx) \
    inline constexpr Register name() const& noexcept { return _regs[idx]; } \
    inline constexpr Register& name() & noexcept { return _regs[idx]; }

    #include "names.inc"
#undef REG
};

/// All integer registers defined for the RV32E base instruction set
template<>
struct IRegisters<BaseIntegerISA::RV32E> : IRegistersBase<IRegister<RegisterWidth::W32>, 16> {

};

}
