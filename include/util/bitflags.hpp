#pragma once


#include <bit>
#include <concepts>
#include <iterator>


template<typename flag_t>
requires requires() {
    typename flag_t;
    requires requires(flag_t flag) {
        { flag | flag } -> std::convertible_to<flag_t>;
        { flag & flag } -> std::convertible_to<flag_t>;
        { flag != 0   } -> std::convertible_to<bool>;
        requires std::default_initializable<flag_t>;
    };
}
struct BitFlags {    
    BitFlags() = default;
    template<std::same_as<flag_t>... Flags>
    inline constexpr BitFlags(Flags... f) noexcept : _flags((f | ...)) {}
    
    /// Copy the set and add a flag to it, returning the copied set
    template<std::same_as<flag_t>... Flags>
    inline constexpr BitFlags with(Flags... flag) const noexcept {
        auto clone = BitFlags(_flags);
        clone.add(flag...);
        return clone;
    }
    
    /// Add a flag to the set in place
    template<std::same_as<flag_t>... Flags>
    inline constexpr void add(Flags... flag) noexcept { _flags |= (flag | ...); }

    /// Remove the flag from the set in place
    template<std::same_as<flag_t>... Flags>
    inline constexpr void remove(Flags... flag) noexcept { _flags &= ~(flag | ...); }
    
    /// Check if this set contains the given flags
    template<std::same_as<flag_t>... Flags>
    inline constexpr bool has(Flags... rest) const noexcept {
        return (_flags & (rest | ...)) != 0;
    }
    
    /// Get the number of set flags in this bit set
    inline constexpr std::size_t count() const noexcept {
        return std::popcount(_flags);
    }

    inline constexpr operator flag_t() const noexcept { return _flags; }

    struct BitFlagsIter {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = flag_t;
        using pointer           = flag_t*;
        using reference         = flag_t const&;

        constexpr BitFlagsIter(value_type v) noexcept : _val(v) {
            pop();
        }

        constexpr reference operator*() const {
            return _popped;
        }
        constexpr pointer operator->() { return &this->_popped; }

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
        value_type _val;
        value_type _popped;

        void pop() {
            auto idx = std::countr_zero(_val);
            _val &= _val - 1;
            _popped = 1 << idx;
        }
    };

    constexpr BitFlagsIter begin() const noexcept { return BitFlagsIter{_flags}; }
    constexpr BitFlagsIter end() const noexcept  { return BitFlagsIter{0}; }

    inline constexpr bool operator==(BitFlags const& other) const noexcept {
        return _flags == other._flags;
    }

private:
    flag_t _flags;
};
