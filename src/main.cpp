#include <format>
#include <iostream>

#include "machine.hpp"
#include "register/register.hpp"
#include "risky.hpp"

using namespace risky;

int main(int, const char *[]) {
    auto spec = IsaSpecification(BaseIntegerISA::RV32I, Extension(Extension::A, Extension::M));
    RiscV<BaseIntegerISA::RV32I> machine(1024);

    std::ostream_iterator<char> out(std::cout);  // Create an output iterator that writes to std::cout
                                                 // Replace std::cout with an ostream to write to a file
    std::format_to(out, "{}\n", spec);
    return 0;
}
