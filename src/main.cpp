#include <format>
#include <iostream>

#include "machine.hpp"
#include "register/register.hpp"
#include "risky.hpp"

using namespace risky;

int main(int, const char *[]) {
    auto spec = IsaSpecification(BaseIntegerISA::RV32I, BitFlags<Extension>(Extension::I, Extension::M, Extension::A, Extension::F, Extension::D));
    RiscV<BaseIntegerISA::RV32I> machine(1024);

    std::ostream_iterator<char> out(std::cout);

    std::format_to(out, "{}\n", spec);
    return 0;
}
