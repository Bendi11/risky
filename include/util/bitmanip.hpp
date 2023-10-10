#pragma once

#include <bit>
#include <concepts>
#include <cstdint>
#include <limits>

namespace risky {

/// Read from START bits to END bits (inclusive) of the given value
template<std::size_t END, std::size_t START, std::unsigned_integral T>
requires requires {
    START <= std::numeric_limits<T>::digits;
    END   <= std::numeric_limits<T>::digits;
    START < END;
}
inline constexpr T readbits_zext(T val) noexcept {
    return (val & ~(~1ULL << END)) >> START;
}

/// Read START to END (inclusive) bits of the original value `val` and sign-extend them
template<std::size_t END, std::size_t START, std::unsigned_integral T, std::signed_integral R = std::make_signed<T>>
requires requires {
    START <= std::numeric_limits<T>::digits;
    END   <= std::numeric_limits<T>::digits;
    START < END;
} inline constexpr R readbits_sext(T val) noexcept {
    constexpr T LEN = END - START;
    constexpr T BITMASK = 1ULL << LEN;
    
    T read = readbits_zext<END,START,T>(val);
    return std::bit_cast<R>((read ^ BITMASK) - BITMASK);
}

}
