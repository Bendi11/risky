#pragma once

#include "register/register.hpp"
#include "risky.hpp"

namespace risky {

/// Top-level emulator for a RISC-V machine with configurable base instruction set and extensions
template<BaseIntegerISA ISA>
struct RiscV {
public:
    IRegisters<ISA> registers;
    IRegister<ISA.width()> pc;
};

}
