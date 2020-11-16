#pragma once
#ifndef SGPL_OPERATIONS_UNARY_RANDOMDRAW_HPP_INCLUDE
#define SGPL_OPERATIONS_UNARY_RANDOMDRAW_HPP_INCLUDE

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"
#include "../../utility/ThreadLocalRandom.hpp"

namespace sgpl {

class RandomDraw {

  template<typename Spec>
  static double map_between_plusminus_one( const typename Spec::tag_t& tag ) {

    constexpr double max = 1.0;
    constexpr double min = -1.0;
    constexpr double max_double = Spec::tag_t::MaxDouble();

    return  (tag.GetDouble() / max_double) * (max - min) + min;

  }

  template<typename Spec>
  static bool is_odd(const typename Spec::tag_t& tag) { return tag.Get(0); }

  static double map_up( const double plusminus_unit_val ) {
    emp_assert( plusminus_unit_val != 0 );

    return 1.0 / (
      plusminus_unit_val * plusminus_unit_val * plusminus_unit_val
    );

  }

  template<typename Spec>
  static float map_draw() {
    const typename Spec::tag_t tag( sgpl::ThreadLocalRandom::Get() );
    return is_odd<Spec>( tag )
      ? map_up( map_between_plusminus_one<Spec>(tag) )
      : map_between_plusminus_one<Spec>( tag )
    ;
  }

public:

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {
    core.registers[ inst.args[0] ] = map_draw<Spec>();
  }

  static std::string name() { return "RandomDraw"; }

  static size_t prevalence() { return 1; }

  static size_t num_registers_to_print() { return 1; }

  static bool should_print_tag() { return false; }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_UNARY_RANDOMDRAW_HPP_INCLUDE