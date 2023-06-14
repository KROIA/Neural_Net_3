#pragma once

#include <chrono>

#define NEURAL_NET_VERSION_MAJOR 3
#define NEURAL_NET_VERSION_MINOR 0
#define NEURAL_NET_VERSION_PATCH 0


#ifdef BUILD_STATIC
#define NEURAL_NET_3_STATIC
#endif

#ifndef NEURAL_NET_3_STATIC
	#if defined(NEURAL_NET_3_LIB)
		#define NEURAL_NET_3_EXPORT __declspec(dllexport)
	#else
		#define NEURAL_NET_3_EXPORT __declspec(dllimport)
	#endif
#else
	#define NEURAL_NET_3_EXPORT
#endif


// MSVC Compiler
#ifdef _MSC_VER 
	#define __PRETTY_FUNCTION__ __FUNCSIG__
	typedef std::chrono::steady_clock::time_point TimePoint;
#else
	typedef std::chrono::system_clock::time_point TimePoint;
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
