#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/config/Spec.hpp"
#include "sgpl/hardware/Core.hpp"

using spec_t = sgpl::Spec<>;

TEST_CASE("Test Core") {

  // TODO flesh out stub test
  sgpl::Core<spec_t>{};

}
