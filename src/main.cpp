#include <format>
#include <iostream>

#include "machine.hpp"
#include "register/register.hpp"
#include "risky.hpp"
#include "util/bitmanip.hpp"

using namespace risky;

int main(int, const char *[]) {
    auto spec = IsaSpecification(BaseIntegerISA::RV32I, BitFlags<Extension>(Extension::I, Extension::M, Extension::A, Extension::F, Extension::D));
    RiscV<BaseIntegerISA::RV32I> machine(1024, BitFlags<Extension>(Extension::G));

    std::ostream_iterator<char> out(std::cout);
    
    std::uint64_t c = 0b011100000;
    std::format_to(out, "{:b}[6:4] = {:08b}\n", c, readbits_zext<6,4>(c));

    machine.exec(0xc1800093);
    machine.exec(0x1f408013);
    std::format_to(out, "{}\n", static_cast<std::int32_t>(machine.registers[0]));
    return 0;
}
