#pragma once

#include "Spitfirepch.h"

#ifdef SPITFIRE_PLATFORM_WINDOWS
	#ifdef SPITFIRE_BUILD_DLL
		#define PE_API __declspec(dllexport)
	#else
		#define PE_API __declspec(dllimport)
	#endif
#else
	#error Only windows is suppored
#endif

namespace Spitfire
{

	using RendererID = unsigned int;

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	class Core
	{
	public:
		static EngineCore::LoggerManager::BasicLogger& Logger();
	};
}

#ifdef SPITFIRE_DEBUG
	#define SPITFIRE_ENABLE_ASSERTS
	#define SPITFIRE_ENABLE_LOGGER

	#define SPITFIRE_ENABLE_EVENT_TRACE
#endif

#ifdef SPITFIRE_ENABLE_LOGGER
	#define SPITFIRE_TRACE(...)	Spitfire::Core::Logger().Trace(__VA_ARGS__)
	#define SPITFIRE_INFO(...)		Spitfire::Core::Logger().Info(__VA_ARGS__)
	#define SPITFIRE_WARN(...)		Spitfire::Core::Logger().Warn(__VA_ARGS__)
	#define SPITFIRE_ERROR(...)	Spitfire::Core::Logger().Error(__VA_ARGS__)
	#define SPITFIRE_FATAL(...)	Spitfire::Core::Logger().Fatal(__VA_ARGS__)
#else
	#define SPITFIRE_TRACE(...)
	#define SPITFIRE_INFO(...)
	#define SPITFIRE_WARN(...)
	#define SPITFIRE_ERROR(...)
	#define SPITFIRE_FATAL(...)
#endif


#ifdef SPITFIRE_ENABLE_ASSERTS
	#define SPITFIRE_ASSERT(x, ...) { if(!(x)) { Spitfire::Core::Logger().Fatal("Assertion Failed: {}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SPITFIRE_ASSERT(x, ...)
#endif
