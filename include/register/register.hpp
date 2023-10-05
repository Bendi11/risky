#pragma once

#include "risky.hpp"
#include <array>
#include <cstdint>
#include <concepts>
#include <string_view>

namespace risky {

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

template<IsaWidth W>
struct IRegister;

template<>
struct IRegister<IsaWidth::RV32>: RegisterBase<std::uint32_t> {

};


static_assert(CRegister64<IRegister<IsaWidth::RV32>>);
static_assert(CRegister64<freg_t>);

template<register64 R>
struct IRegisters {
public:
    static constexpr const std::size_t COUNT = 32;

    IRegisters() : _regs() {
        
    }

#define REG(name, idx) \
    inline constexpr R name() const& noexcept { return _regs[idx]; } \
    inline constexpr R& name() & noexcept { return _regs[idx]; }

    #include "names.inc"
#undef REG
    
    inline constexpr R& operator[](std::size_t idx) & noexcept { return _regs[idx]; }
private:
    std::array<R, COUNT> _regs;

#define REG(name, ...) #name,
    static constexpr const std::array<const std::string_view, COUNT> REGNAMES = {
        #include "names.inc"
    };
#undef REG
};

}
