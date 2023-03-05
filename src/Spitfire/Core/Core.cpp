
#include "Core.h"

EngineCore::LoggerManager::BasicLogger& Spitfire::Core::Logger()
{
	static EngineCore::LoggerManager::BasicLogger instance("Spitfire");
	return instance;
}
