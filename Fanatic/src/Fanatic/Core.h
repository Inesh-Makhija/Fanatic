#pragma once

#include <memory>

#ifdef FNC_PLATFORM_WINDOWS
#if FNC_DYNAMIC_LINK
	#ifdef FNC_BUILD_DLL
		#define FANATIC_API __declspec(dllexport)
	#else
		#define FANATIC_API __declspec(dllimport)
	#endif // FNC_BUILD_DLL
#else
	#define FANATIC_API
#endif // FNC_DYNAMIC_LINK
#else
	#error Fanatic only supports Windows!
#endif // FNC_PLATFORM_WINDOWS

#ifdef FNC_DEBUG
	#define FNC_ENABLE_ASSERTS
#endif // FNC_DEBUG

#ifdef FNC_ENABLE_ASSERTS
	#define FNC_ASSERT(x, ...) { if(!(x)) {FNC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FNC_CORE_ASSERT(x, ...) { if(!(x)) {FNC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FNC_ASSERT(x, ...)
	#define FNC_CORE_ASSERT(x,...)
#endif // FNC_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define FNC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Fanatic {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}