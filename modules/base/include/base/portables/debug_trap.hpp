#pragma once
#ifndef LIGHT_DEBUG_TRAP_H
	#define LIGHT_DEBUG_TRAP_H

// https://github.com/nemequ/portable-snippets/tree/master/debug-trap

	#ifdef LIGHT_DIST
		#ifdef _MSC_VER
			#define lt_debug_trap()                                    \
				LT_FILE_CRITICAL(                                      \
				    "DEBUG_TRAP REQUESTED AT: {}, FILE: {}, LINE: {}", \
				    __FUNCSIG__,                                       \
				    __FILE__,                                          \
				    __LINE__                                           \
				) // or __FUNCSIG__

		#else
			#define lt_debug_trap() \
				LT_FILE_CRITICAL("DEBUG_TRAP REQUESTED AT: {}", __PRETTY_FUNCTION__)

		#endif
	#endif

	#if !defined(lt_debug_trap) && defined(__has_builtin) && !defined(__ibmxl__)
		#if __has_builtin(__builtin_debugtrap)
			#define lt_debug_trap() __builtin_debugtrap()

		#elif __has_builtin(__debugbreak)
			#define lt_debug_trap() __debugbreak()

		#endif
	#endif

	#if !defined(lt_debug_trap)
		#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
			#define lt_debug_trap() __debugbreak()

		#elif defined(__ARMCC_VERSION)
			#define lt_debug_trap() __breakpoint(42)

		#elif defined(__ibmxl__) || defined(__xlC__)
			#include <builtins.h>
			#define lt_debug_trap() __trap(42)

		#elif defined(__DMC__) && defined(_M_IX86)
static inline void lt_debug_trap(void)
{
	__asm int 3h;
}

		#elif defined(__i386__) || defined(__x86_64__)
static inline void lt_debug_trap(void)
{
	__asm__ __volatile__("int3");
}

		#elif defined(__thumb__)
static inline void lt_debug_trap(void)
{
	__asm__ __volatile__(".inst 0xde01");
}

		#elif defined(__aarch64__)
static inline void lt_debug_trap(void)
{
	__asm__ __volatile__(".inst 0xd4200000");
}

		#elif defined(__arm__)
static inline void lt_debug_trap(void)
{
	__asm__ __volatile__(".inst 0xe7f001f0");
}

		#elif defined(__alpha__) && !defined(__osf__)
static inline void lt_debug_trap(void)
{
	__asm__ __volatile__("bpt");
}

		#elif defined(_54_)
static inline void lt_debug_trap(void)
{
	__asm__ __volatile__("ESTOP");
}

		#elif defined(_55_)
static inline void lt_debug_trap(void)
{
	__asm__ __volatile__(";\n .if (.MNEMONIC)\n estop_1\n .else\n estop_1()\n .endif\n NOP");
}

		#elif defined(_64P_)
static inline void lt_debug_trap(void)
{
	__asm__ __volatile__("SWBP 0");
}

		#elif defined(_6x_)
static inline void lt_debug_trap(void)
{
	__asm__ __volatile__("NOP\n .word 0x10000000");
}

		#elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ == 0) && defined(__GNUC__)
			#define lt_debug_trap() __builtin_trap()

		#else
			#include <signal.h>

			#if defined(SIGTRAP)
				#define lt_debug_trap() raise(SIGTRAP)

			#else
				#define lt_debug_trap() raise(SIGABRT)

			#endif
		#endif
	#endif

	#if !defined(lt_debug_trap)
		#if !defined(LIGHT_IGNORE_UNDEFINED_DEBUG_TRAP)
			#error "failed to define LT_BREAK, define LIGHT_IGNORE_UNDEFINED_DEBUG_TRAP in Config.h to disable this error"

		#elif defined(LIGHT_DIST)
			#ifdef _MSC_VER
				#define lt_debug_trap()                                    \
					log_crt(                                               \
					    "DEBUG_TRAP REQUESTED AT: {}, FILE: {}, LINE: {}", \
					    __FUNCSIG__,                                       \
					    __FILE__,                                          \
					    __LINE__                                           \
					) // or __FUNCSIG__

			#else
				#define lt_debug_trap() log_crt("DEBUG_TRAP REQUESTED AT: {}", __PRETTY_FUNCTION__)

			#endif
		#else /* !defined(LIGHT_DIST) */
			#ifdef _MSC_VER
				#define lt_debug_trap()                                    \
					log_crt(                                               \
					    "DEBUG_TRAP REQUESTED AT: {}, FILE: {}, LINE: {}", \
					    __FUNCSIG__,                                       \
					    __FILE__,                                          \
					    __LINE__                                           \
					) // or __FUNCSIG__

			#else
				#define lt_debug_trap() log_crt("DEBUG_TRAP REQUESTED AT: {}", __PRETTY_FUNCTION__)

			#endif
		#endif
	#endif
#endif
