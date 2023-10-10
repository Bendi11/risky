#include "machine.hpp"
#include "risky.hpp"
#include "util/bitmanip.hpp"
#include "inst/consts.hpp"
#include "inst/format.hpp"
#include <iostream>

namespace risky {

template<BaseIntegerISA ISA>
void RiscV<ISA>::exec(std::uint32_t inst) noexcept {
    std::uint8_t opcode = readbits_zext<6, 2>(inst);
    std::cout << std::format("opcode {:b}", opcode) << std::endl;
    switch(opcode) {
        case InstructionConstants::Opcode::OP_IMM: {
            inst::I<ISA.width()> i{inst};
            switch(i.funct3) {
                case InstructionConstants::IMMFunct3::ADDI: {
                    registers[i.rd] = registers[i.rs1] + i.imm;
                } break;
                case InstructionConstants::IMMFunct3::ORI: {
                } break;
            }
        } break;
    }
}

template void RiscV<BaseIntegerISA::RV32E>::exec(std::uint32_t inst) noexcept;
template void RiscV<BaseIntegerISA::RV32I>::exec(std::uint32_t inst) noexcept;
template void RiscV<BaseIntegerISA::RV64I>::exec(std::uint32_t inst) noexcept;

}
