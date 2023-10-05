#pragma once

#include <array>
#include <cstdint>
#include <concepts>
#include <string_view>

namespace risky {

typedef double freg_t;

template<typename T>
concept register64 = requires(T a) {
    sizeof(T) == 8;
    std::default_initializable<T>;
};

struct ireg_t {
public:
    inline constexpr ireg_t(std::uint64_t v) noexcept : _v(v) {}
    inline constexpr ireg_t() noexcept : _v(0) {}

    inline constexpr operator std::uint64_t() const noexcept { return _v; }
    inline constexpr operator std::uint64_t&() & noexcept { return _v; }
    inline constexpr operator std::uint64_t const&() const& noexcept { return _v; }

    inline constexpr std::uint32_t upper() const { return (std::uint32_t)(_v >> 32); }
    inline constexpr std::uint32_t lower() const { return (std::uint32_t)(_v & 0xFFFFFFFF); }
private:
    std::uint64_t _v;
};


static_assert(register64<ireg_t>);
static_assert(register64<freg_t>);

template<register64 R>
struct iregs {
public:
    static constexpr const std::size_t COUNT = 32;

    iregs() : _regs() {
        
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
