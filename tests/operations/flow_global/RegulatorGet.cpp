#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/operations/flow_global/RegulatorGet.hpp"

#include "sgpl/hardware/Core.hpp"
#include "sgpl/program/Program.hpp"

#include "sgpl/algorithm/execute_core.hpp"

#include "sgpl/spec/Spec.hpp"

#include "sgpl/utility/EmptyType.hpp"

// define libray and spec
using library_t = sgpl::OpLibrary<sgpl::global::RegulatorGet, sgpl::global::Anchor>;

using spec_t = sgpl::Spec<library_t>;

// create peripheral
spec_t::peripheral_t peripheral;

TEST_CASE("Test RegulatorGet") {
  sgpl::Program<spec_t> program;

  std::ifstream is("assets/RegulatorGet.json");

  { cereal::JSONInputArchive archive( is ); archive( program ); }

  is.close();

  sgpl::Core<spec_t> core;

  // load all anchors manually
  // core.LoadLocalAnchors(program);

  core.registers[0] = 1;

  // check initial state
  REQUIRE_THAT(core.registers, Catch::Matchers::Equals(
    emp::array<float, 8>{1, 0, 0, 0, 0, 0, 0, 0}
  ));

  // execute single instruction
  sgpl::advance_core(core, program, peripheral);

  // check final state (value is 0 by default)
  REQUIRE_THAT(core.registers, Catch::Matchers::Equals(
    emp::array<float, 8>{0, 0, 0, 0, 0, 0, 0, 0}
  ));

}
