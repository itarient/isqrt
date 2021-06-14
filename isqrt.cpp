/*
 * Copyright (c) 2021 by George Tarasov (aka itarient)
 *
 * Licensed under the MIT License (See LICENSE file).
 */

#include <type_traits>
#include <iostream>

/* C++ template implementation */

template<unsigned N>
using uc = std::integral_constant<unsigned, N>;

struct maxuc : uc<0xFFFF> {};

template<unsigned N, unsigned k, unsigned k2 = (k * k)> /* TODO: Overflow! */
struct isqrt0_t :
    std::conditional_t<
        (k2 > N),
        uc<k - 1>,
        isqrt0_t<N, k + 1>
    >
{};

template<unsigned N, unsigned k, unsigned k2 = (k * k)> /* TODO: Overflow! */
struct isqrt1_t :
    std::conditional_t<
        (k2 == N),
        uc<k>,
        std::conditional_t<
            (k2 > N),
            isqrt1_t<N, k / 2>,
            isqrt0_t<N, k + 1>
        >
    >
{};

template<unsigned N, unsigned N2 = N / 2>
struct isqrt_t : isqrt1_t<N, N2>
{
    static_assert((N2 <= maxuc::value), "Expecting value overflow");
};

template<> struct isqrt_t<0> : uc<0> {};
template<> struct isqrt_t<1> : uc<1> {};
template<> struct isqrt_t<2> : uc<1> {};
template<> struct isqrt_t<3> : uc<1> {};

/* C/C++ function implementation */

int isqrt0(unsigned N, unsigned k)
{
    int k2 = k * k;
    if (k2 > N)
        return k - 1;
    return isqrt0(N, k + 1);
}

int isqrt1(unsigned N, unsigned k)
{
    int k2 = k * k;
    if (k2 == N)
        return k;
    if (k2 > N)
        return isqrt1(N, k / 2);
    return isqrt0(N, k + 1);
}

int isqrt(unsigned N)
{
    if (N == 0)
        return 0;
    if (N < 4)
        return 1;

    return isqrt1(N, N / 2);
}

/* Test cases */

int main(int argc, char* argv[])
{
    const unsigned N = 131071;
    std::cout << isqrt(N) << std::endl;

    typedef isqrt_t<N> isqrtN_t;
    std::cout << isqrtN_t::value << std::endl;

    return 0;
}
