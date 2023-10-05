#pragma once

#include "memory/memory.hpp"
#include "register/register.hpp"
#include "risky.hpp"

namespace risky {

/// Top-level emulator for a RISC-V machine with configurable base instruction set and extensions
template<BaseIntegerISA ISA>
struct RiscV {
public:
    /// Initialize all state for the VM, allocating all memory for the vm in the process
    RiscV(std::size_t nbytes) : registers{}, pc{0}, memory{nbytes} {}

    IRegisters<ISA> registers;
    IRegister<ISA.width()> pc;
    Memory<ISA.width()> memory;
};

}
