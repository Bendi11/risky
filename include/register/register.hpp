#pragma once

#include "risky.hpp"
#include <array>
#include <cstdint>
#include <concepts>
#include <string_view>

namespace risky {


/// A register of the specified width
template<RegisterWidth>
struct WidthStorage;

template<>
struct WidthStorage<RegisterWidth::W32> { typedef std::int32_t type; };
template<>
struct WidthStorage<RegisterWidth::W64>{  typedef std::int64_t type; };

template<RegisterWidth W>
using IRegister = WidthStorage<W>::type;

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

#define REG(name, idx) \
    inline constexpr Register name() const& noexcept { return _regs[idx]; } \
    inline constexpr Register& name() & noexcept { return _regs[idx]; }

/// Integer registers defined for the RV32I base instruction set
template<>
struct IRegisters<BaseIntegerISA::RV32I> : IRegistersBase<IRegister<RegisterWidth::W32>, 32> {
    #include "names_i.inc"
};

/// Integer registers defined for the RV64I base intstruction set
template<>
struct IRegisters<BaseIntegerISA::RV64I> : IRegistersBase<IRegister<RegisterWidth::W64>, 32> {
    #include "names_i.inc"
};

/// All integer registers defined for the RV32E base instruction set
template<>
struct IRegisters<BaseIntegerISA::RV32E> : IRegistersBase<IRegister<RegisterWidth::W32>, 16> {
};


#undef REG

}
