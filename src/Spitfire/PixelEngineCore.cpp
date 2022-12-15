
#include "PixelEngineCore.h"


CPPTools::LogSystem::LogSystem& PixelEngine::Logger()
{
	static CPPTools::LogSystem::LogSystem instance("PixelEngine");
	return instance;
}
