#pragma once

#include <concepts>
#include <cstdint>
#include <limits>

namespace risky {

template<std::size_t N>
struct Underlying;

template<std::size_t N>
requires(N <= 8)
struct Underlying<N> {
    typedef std::uint8_t unsigned_t;
    typedef std::int8_t  signed_t;
};

template<std::size_t N>
requires(N > 8 && N <= 16)
struct Underlying<N> {
    typedef std::uint16_t unsigned_t;
    typedef std::int16_t  signed_t;
};

template<std::size_t N>
requires(N > 16 && N <= 32)
struct Underlying<N> {
    typedef std::uint32_t unsigned_t;
    typedef std::int32_t  signed_t;
};

template<std::size_t N>
requires(N > 32 && N <= 64)
struct Underlying<N> {
    typedef std::uint64_t unsigned_t;
    typedef std::int64_t  signed_t;
};

/// An unsigned value that is guranteed to contain at most N bits
template<bool SIGN, std::size_t BITS>
requires(BITS <= 64)
struct BitIntegerBase {
    typedef BitIntegerBase<SIGN, BITS> Self;
    
    template<std::unsigned_integral T>
    requires(std::numeric_limits<T>::digits <= BITS)
    inline static constexpr Self z_ext() noexcept {

    }
};

}
