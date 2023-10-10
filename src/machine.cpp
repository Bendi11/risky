#include "machine.hpp"
#include "risky.hpp"
#include "util/bitmanip.hpp"
#include "inst/consts.hpp"
#include <iostream>

namespace risky {

template<BaseIntegerISA ISA>
void RiscV<ISA>::exec(std::uint32_t inst) noexcept {
    std::uint8_t opcode = readbits<6, 2>(inst);
    std::cout << std::format("opcode {:b}", opcode) << std::endl;
    switch(opcode) {
        case InstructionConstants::Opcode::OP_IMM: {
            std::uint8_t funct3 = readbits<14, 12>(inst);
            switch(funct3) {
                case InstructionConstants::IMMFunct3::ADDI: {
                    std::uint8_t rd = readbits<11,7>(inst);
                    std::uint8_t rs1 = readbits<19,15>(inst);
                    std::uint16_t imm = readbits<31,20>(inst);

                    std::cout << std::format("rd: {:b}\nrs1: {:b}\nimm: {:b}\n", rd, rs1, imm);

                    registers[rd] = IRegister<ISA.width()>(registers[rs1] + imm);
                } break;
            }
        } break;
    }
}

template void RiscV<BaseIntegerISA::RV32I>::exec(std::uint32_t inst) noexcept;
template<> struct RiscV<BaseIntegerISA::RV32E>;
template<> struct RiscV<BaseIntegerISA::RV64I>;
template<> struct RiscV<BaseIntegerISA::RV128I>;

}
