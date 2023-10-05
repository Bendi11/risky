#pragma once

#include "register/register.hpp"
#include "risky.hpp"
#include <cstdlib>

namespace risky {

/// A memory area that complies with the requirements for RISC-V: little endian, best for operations aligned to 4-byte boundaries while allowing misaligned access
template<RegisterWidth WIDTH>
struct Memory {
public:
    /// Allocate `nb` bytes of memory to use for the emulator
    Memory(std::size_t nb) {
        if(WIDTH == RegisterWidth::W32) {
            nb = (nb > 0xffffffff) ? 0xffffffff : nb;
        }

        _buf = static_cast<std::uint8_t*>(std::malloc(nb));
        if(_buf == nullptr) {
            //FIXME add actual logging and panic
            throw std::exception();
        }

        _len = nb;
    }
    
    /// Get the raw pointer to the beginning of allocated memory
    inline constexpr operator std::uint8_t*() const noexcept { return _buf; }

    /// Check if a read at the given address with `nb` bytes read will be valid
    inline constexpr bool valid_read(IRegister<WIDTH> addr, IRegister<WIDTH> nb = static_cast<IRegister<WIDTH>>(WIDTH)) const noexcept { return (addr + nb) < _len; }
private:
    std::uint8_t *_buf;
    std::size_t _len;
};

}
