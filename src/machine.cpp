#include "machine.hpp"
#include "risky.hpp"
#include "util/bitmanip.hpp"
#include "inst/consts.hpp"
#include "inst/format.hpp"
#include <bit>
#include <iostream>

namespace risky {

template<BaseIntegerISA ISA>
void RiscV<ISA>::exec(std::uint32_t inst) noexcept {
    std::uint8_t opcode = readbits_zext<6, 2>(inst);
    switch(opcode) {
        case InstructionConstants::Opcode::OP: {
            inst::R r{inst};
            auto& rd = registers[r.rd];
            auto rs1 = registers[r.rs1];
            auto rs2 = registers[r.rs2];

            switch(r.funct3) {
                case InstructionConstants::Funct3::ADD: {
                    if(r.funct7 != 0x20) {
                        rd = rs1 + rs2;
                    } else {
                        rd = rs1 - rs2;
                    }
                } break; 
                case InstructionConstants::Funct3::XOR: {
                    rd = rs1 ^ rs2;
                } break;
                case InstructionConstants::Funct3::OR: {
                    rd = rs1 | rs2;
                } break;
                case InstructionConstants::Funct3::AND: {
                    rd = rs1 & rs2;
                } break;
            }
        } break;

        case InstructionConstants::Opcode::OP_IMM: {
            inst::I<ISA.width()> i{inst};
            auto& rd = registers[i.rd];
            auto rs1 = registers[i.rs1];

            switch(i.funct3) {
                case InstructionConstants::Funct3::ADD: {
                    rd = rs1 + i.imm;
                } break;
                case InstructionConstants::Funct3::OR: {
                    rd = rs1 | i.imm;
                } break;
                case InstructionConstants::Funct3::XOR: {
                    rd = rs1 ^ i.imm;
                } break;
                case InstructionConstants::Funct3::AND: {
                    rd = rs1 & i.imm;
                } break;
                case InstructionConstants::Funct3::SLT: {
                    rd = (rs1 < i.imm) ? 1 : 0;
                } break;
                case InstructionConstants::Funct3::SLTU: {
                    rd = (std::bit_cast<URegister>(rs1) < std::bit_cast<URegister>(i.imm)) ? 1 : 0;
                } break;
            }
        } break;
    }
}

template void RiscV<BaseIntegerISA::RV32E>::exec(std::uint32_t inst) noexcept;
template void RiscV<BaseIntegerISA::RV32I>::exec(std::uint32_t inst) noexcept;
template void RiscV<BaseIntegerISA::RV64I>::exec(std::uint32_t inst) noexcept;

}
