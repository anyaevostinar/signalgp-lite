#pragma once

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

struct Divide {

  template<typename Library>
  static void run(
    sgpl::Core<Library>& core,
    const sgpl::Instruction<Library>& inst,
    const sgpl::Program<Library>&
  ) {
    const size_t a = inst.args[0], b = inst.args[1], c = inst.args[2];
    core.registers[a] = core.registers[b] / core.registers[c];
  }

};

} // namespace sgpl
