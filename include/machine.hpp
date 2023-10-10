#pragma once

#include "memory/memory.hpp"
#include "register/register.hpp"
#include "risky.hpp"
#include "util/bitflags.hpp"

namespace risky {

/// Top-level emulator for a RISC-V machine with configurable base instruction set and extensions
template<BaseIntegerISA ISA>
struct RiscV {
public:
    typedef IRegister<ISA.width()> Register;

    /// Initialize all state for the VM, allocating all memory for the vm in the process
    RiscV(std::size_t nbytes, BitFlags<Extension> ext) : extensions{ext}, registers{}, pc{0}, memory{nbytes} {}
    
    /// Decode and execute a single 4-byte instruction
    void exec(std::uint32_t inst) noexcept;
    
    BitFlags<Extension> extensions;
    IRegisters<ISA> registers;
    Register pc;
    Memory<ISA.width()> memory;
};

}
