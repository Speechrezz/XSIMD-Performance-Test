#pragma once

#include "Register.hpp"

#ifdef SSIMD_SSE
#include <cmath>

namespace ssimd
{

template<>
struct Register<float, sse> : public RegisterOverloads<float, sse>
{
	__m128 data;

	Register() = default;
	SSIMD_INLINE Register(const Register<float, sse>& other) noexcept : data(other.data) {}
	SSIMD_INLINE Register(const __m128& newData) : data(newData) {}
	SSIMD_INLINE Register(float scalar) noexcept : Register(broadcast(scalar)) {}

	static SSIMD_INLINE constexpr size_t size() { return 4; }
	static SSIMD_INLINE constexpr size_t alignment() { return 16; }

	static SSIMD_INLINE Register<float, sse> broadcast(float scalar)
	{
		return { _mm_set1_ps(scalar) };
	}

	static SSIMD_INLINE Register<float, sse> loadUnaligned(const float* memory)
	{
		return { _mm_loadu_ps(memory) };
	}
	static SSIMD_INLINE Register<float, sse> loadAligned(const float* memory)
	{
		return { _mm_load_ps(memory) };
	}

	SSIMD_INLINE void storeUnaligned(float* memory) const
	{
		_mm_storeu_ps(memory, data);
	}
	SSIMD_INLINE void storeAligned(float* memory) const
	{
		_mm_store_ps(memory, data);
	}
};


// ---Arithmetic---

SSIMD_INLINE Register<float, sse> add(const Register<float, sse>& reg1, const Register<float, sse>& reg2)
{
	return { _mm_add_ps(reg1.data, reg2.data) };
}

SSIMD_INLINE Register<float, sse> sub(const Register<float, sse>& reg1, const Register<float, sse>& reg2)
{
	return { _mm_sub_ps(reg1.data, reg2.data) };
}

SSIMD_INLINE Register<float, sse> mul(const Register<float, sse>& reg1, const Register<float, sse>& reg2)
{
	return { _mm_mul_ps(reg1.data, reg2.data) };
}

SSIMD_INLINE Register<float, sse> div(const Register<float, sse>& reg1, const Register<float, sse>& reg2)
{
	return { _mm_div_ps(reg1.data, reg2.data) };
}


// ---Unary---

SSIMD_INLINE Register<float, sse> neg(const Register<float, sse>& reg)
{
	__m128 mask = _mm_set1_ps(-0.0f);
	return { _mm_xor_ps(reg.data, mask) };
}


// ---Rounding---

SSIMD_INLINE Register<float, sse> round(const Register<float, sse>& reg)
{
	return { _mm_round_ps(reg.data, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC) };
}

SSIMD_INLINE Register<float, sse> ceil(const Register<float, sse>& reg)
{
	return { _mm_round_ps(reg.data, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC) };
}

SSIMD_INLINE Register<float, sse> floor(const Register<float, sse>& reg)
{
	return { _mm_round_ps(reg.data, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC) };
}

SSIMD_INLINE Register<float, sse> trunc(const Register<float, sse>& reg)
{
	return { _mm_round_ps(reg.data, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) };
}

// ---Trig---

SSIMD_INLINE Register<float, sse> sin(const Register<float, sse>& reg)
{
#ifdef SSIMD_MSVC
	return { _mm_sin_ps(reg.data) };
#else
	return generic::sin(reg);
#endif
}

} // namespace ssimd

#endif