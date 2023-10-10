#pragma once

#include <concepts>
#include <cstdint>
#include <limits>

namespace risky {

/// Read from START bits to END bits (inclusive) of the given value
template<std::size_t END, std::size_t START, std::unsigned_integral T>
requires requires {
    START <= std::numeric_limits<T>::digits;
    END   <= std::numeric_limits<T>::digits;
    START > END;
}
inline constexpr T readbits(T val) noexcept {
    return (val & ~(~1ULL << END)) >> START;
}

}
