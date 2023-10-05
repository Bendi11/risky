#pragma once


#include <concepts>


template<typename flag_t>
requires requires() {
    typename flag_t;
    requires requires(flag_t flag) {
        { flag | flag } -> std::convertible_to<flag_t>;
        { flag & flag } -> std::convertible_to<flag_t>;
        { flag != 0   } -> std::convertible_to<bool>;
        std::default_initializable<flag_t>;
    };
}
struct BitFlags {    
    BitFlags() = default;
    inline constexpr BitFlags(flag_t base) noexcept : _flags(base) {}

    template<typename... Flags>
    requires(std::same_as<Flags, flag_t> && ...)
    inline constexpr BitFlags(Flags... f) noexcept : _flags((f | ...)) {}

    inline constexpr BitFlags with(flag_t flag) noexcept {
        auto clone = BitFlags(_flags);
        clone.add(flag);
        return clone;
    }

    inline constexpr void add(flag_t flag) noexcept { _flags |= flag; }
    
    template<typename... Flags>
    requires(std::same_as<Flags, flag_t> && ...)
    inline constexpr bool has(Flags... rest) noexcept {
        return (_flags & (rest | ...)) != 0;
    }

private:
    flag_t _flags;
};

