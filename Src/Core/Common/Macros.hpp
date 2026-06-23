#pragma once

#define UUES_EXPORT __declspec(dllexport)
#define UUES_IMPORT __declspec(dllimport)

#define UUES_UNUSED(x) (void)(x)
#define UUES_BIT(n) (1ULL << (n))
#define UUES_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#ifdef _WIN64
#define UUES_ARCH_X64
#elif _WIN32
#define UUES_ARCH_X86
#endif

#ifdef _DEBUG
#define UUES_DEBUG
#endif

#define UUES_STRINGIFY(x) #x
#define UUES_TOSTRING(x) UUES_STRINGIFY(x)