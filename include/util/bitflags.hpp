#pragma once


#include <bit>
#include <concepts>
#include <iterator>
#include <type_traits>


template<typename Flag>
requires(std::is_enum_v<Flag>)
struct BitFlags {
    using Underlying = std::underlying_type_t<Flag>;

    inline constexpr BitFlags() noexcept = default;
    explicit inline constexpr BitFlags(Underlying f) noexcept : _flags(f) {}

    template<std::same_as<Flag>... Flags>
    inline constexpr BitFlags(Flags... f) noexcept : _flags((static_cast<Underlying>(f) | ...)) {}
    
    /// Copy the set and add a flag to it, returning the copied set
    template<std::same_as<Flag>... Flags>
    inline constexpr BitFlags with(Flags... flag) const noexcept {
        auto clone = BitFlags(*this);
        clone.add(flag...);
        return clone;
    }

    /// Add a flag to the set in place
    template<std::same_as<Flag>... Flags>
    inline constexpr void add(Flags... flag) noexcept { _flags |= (static_cast<Underlying>(flag) | ...); }

    /// Remove the flag from the set in place
    template<std::same_as<Flag>... Flags>
    inline constexpr void remove(Flags... flag) noexcept { _flags &= ~(static_cast<Underlying>(flag) | ...); }
    
    /// Check if this set contains the given flags
    template<std::same_as<Flag>... Flags>
    inline constexpr bool has(Flags... rest) const noexcept {
        return (_flags & (static_cast<Underlying>(rest) | ...)) != 0;
    }
    
    /// Get the number of set flags in this bit set
    inline constexpr std::size_t count() const noexcept {
        return std::popcount(_flags);
    }

    inline constexpr operator Underlying() const noexcept { return _flags; }

    struct BitFlagsIter {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = Flag;
        using pointer           = Flag*;
        using reference         = Flag const&;

        constexpr BitFlagsIter(Underlying v) noexcept : _val(v) {
            pop();
        }

        constexpr reference operator*() const {
            return _popped;
        }
        constexpr pointer operator->() { return static_cast<pointer>(&this->_popped); }

        // Prefix increment
        constexpr BitFlagsIter& operator++() {
            pop(); 
            return *this;
        }

        // Postfix increment
        constexpr BitFlagsIter operator++(int) { BitFlagsIter tmp = *this; ++(*this); return tmp; }

        friend constexpr bool operator== (const BitFlagsIter& a, const BitFlagsIter& b) { return a._popped == b._popped; };
        friend constexpr bool operator!= (const BitFlagsIter& a, const BitFlagsIter& b) { return a._popped != b._popped; };     

    private:
        Underlying _val;
        Flag _popped;

        void pop() {
            auto idx = std::countr_zero(_val);
            _val &= _val - 1;
            _popped = static_cast<Flag>(1ULL << idx);
        }
    };

    constexpr BitFlagsIter begin() const noexcept { return BitFlagsIter{_flags}; }
    constexpr BitFlagsIter end() const noexcept  { return BitFlagsIter{0}; }

    inline constexpr bool operator==(BitFlags<Flag> const& other) const noexcept {
        return _flags == other._flags;
    }

    inline constexpr bool operator!=(BitFlags<Flag> const& other) const noexcept { return _flags != other._flags; }

    inline constexpr bool operator==(Flag const& other) const noexcept {
        return _flags == static_cast<Underlying>(other);
    }
    friend constexpr inline BitFlags<Flag> operator|(BitFlags<Flag> const& a, BitFlags<Flag> const& b) noexcept { return Flag(a._flags | b._flags); }

private:
    Underlying _flags;
};
