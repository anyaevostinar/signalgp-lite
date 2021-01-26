#pragma once
#ifndef SGPL_OPERATIONS_FLOW_GLOBAL_REGULATORADJ_HPP_INCLUDE
#define SGPL_OPERATIONS_FLOW_GLOBAL_REGULATORADJ_HPP_INCLUDE

#include <map>
#include <string>

#include "../../../../third-party/Empirical/include/emp/tools/hash_namify.hpp"
#include "../../../../third-party/Empirical/include/emp/tools/string_utils.hpp"

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {
namespace global {

template< size_t JUMP_TABLE_IDX=0 >
struct RegulatorAdj {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {

    auto& jump_table = core.GetGlobalJumpTable( JUMP_TABLE_IDX );
    for ( const auto uid : jump_table.MatchRaw(inst.tag) ) {
      // (+) values down regulate
      // (-) values up regulate
      jump_table.AdjRegulator(
        uid,
        core.registers[ inst.args[0] ]
      );
    }

  }

  static std::string name() { return "Adjust Global Regulator"; }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& inst ) {

    using tag_t = typename Spec::tag_t;

    return std::map<std::string, std::string>{
      { "argument a", emp::to_string( static_cast<int>( inst.args[0] ) ) },
      { "summary", "adjust global regulator value by a" },
      { "tag bits", emp::to_string( inst.tag ) },
      { "tag moniker", emp::hash_namify( std::hash< tag_t >{}( inst.tag ) ) },
    };
  }

};

} // namespace global
} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_FLOW_GLOBAL_REGULATORADJ_HPP_INCLUDE
