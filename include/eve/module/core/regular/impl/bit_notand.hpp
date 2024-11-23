//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_not.hpp>

namespace eve::detail
{
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr bit_value_t<T0, T1, Ts...>
  bit_notand_(EVE_REQUIRES(cpu_), O const &, T0 a, T1 b, Ts... args) noexcept
  {
    using r_t = bit_value_t<T0, T1, Ts...>;
    using b_t = as_integer_t<r_t>;
    if constexpr(sizeof...(Ts) == 0)
    {
      using ra_t = std::conditional_t<scalar_value<T0>,element_type_t<b_t>,b_t>;
      using rb_t = std::conditional_t<scalar_value<T1>,element_type_t<b_t>,b_t>;
      auto ba = bit_cast(a, as<ra_t>{});
      auto bb = bit_cast(b, as<rb_t>{});
      return bit_cast( bit_and(bit_not(b_t(ba)),b_t(bb)), as<r_t>());
    }
    else
    {
      auto that = bit_and(r_t(b), r_t(args...));
      return eve::bit_notand(r_t(a), that);
    }
  }
}
