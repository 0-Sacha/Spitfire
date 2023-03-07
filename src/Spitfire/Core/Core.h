#pragma once

#include "ProjectCore/LoggerManager/LoggerManager.h"

#include <utility>

namespace Spitfire
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	class Core
	{
	public:
		static ProjectCore::LoggerManager::BasicLogger& Logger();
	};
}

#ifdef SPITFIRE_DEBUG
	#define SPITFIRE_ENABLE_ASSERTS
	#define SPITFIRE_ENABLE_LOGGER

	#define SPITFIRE_ENABLE_EVENT_TRACE
#endif

#ifdef SPITFIRE_ENABLE_LOGGER
	#define SPITFIRE_TRACE(...)	Spitfire::Core::Logger().Trace(__VA_ARGS__)
	#define SPITFIRE_INFO(...)	Spitfire::Core::Logger().Info(__VA_ARGS__)
	#define SPITFIRE_WARN(...)	Spitfire::Core::Logger().Warn(__VA_ARGS__)
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
