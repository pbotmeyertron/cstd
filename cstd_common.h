#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__GNUC__) || defined(__clang__)
    #define cstd_alias __attribute__((may_alias))
#elif defined(_MSC_VER)
    #define cstd_alias __declspec(noalias)
#else
    #error "Compiler not supported."
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define cstd_align(n) __attribute__((aligned(n)))
#elif defined(_MSC_VER)
    #define cstd_align(n) __declspec(align(n))
#elif
    #define cstd_align(n) alignas(n)
#else
    #error "Compiler not supported."
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define cstd_packed __attribute__((packed))
#elif defined(_MSC_VER)
    #define cstd_packed __pragma(pack(push, 1))
#else
    #error "Compiler not supported."
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define cstd_unused(x) (void)(x)
#elif defined(_MSC_VER)
    #define cstd_unused(x) (void)(x)
#else
    #error "Compiler not supported."
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define cstd_inline static inline
#elif defined(_MSC_VER)
    #define cstd_inline static inline
#else
    #error "Compiler not supported."
#endif
