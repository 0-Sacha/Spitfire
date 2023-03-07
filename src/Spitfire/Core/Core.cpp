
#include "Core.h"

ProjectCore::LoggerManager::BasicLogger& Spitfire::Core::Logger()
{
	static ProjectCore::LoggerManager::BasicLogger instance("Spitfire");
	return instance;
}
