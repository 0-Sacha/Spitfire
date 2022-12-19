#pragma once


// Target Define
#ifdef TARGET_DEBUG
	#define SPITFIRE_DEBUG
#endif

#ifdef TARGET_RELEASE
	#define SPITFIRE_RELEASE
#endif

#ifdef TARGET_DIST
	#define SPITFIRE_DIST
#endif


// Architecture Define
#ifdef ARCHITECTURE_X86
	#error Spitfire doesn't support x86
#endif

#ifdef ARCHITECTURE_X64
	#define SPITFIRE_X64
#endif


// Platform Define 
#ifdef PLATFORM_WINDOWS
	#define SPITFIRE_PLATFORM_WINDOWS
#endif

#ifdef PLATFORM_LINUX
	#error Spitfire doesn't support Linux
#endif


// Compiler Define
#ifdef COMPILER_MSVC
#endif

#ifdef COMPILER_GCC
#endif





// Include
#include "EngineCore/FMT/Format/Container/AllContainer.h"
#include "EngineCore/LoggerManager/LoggerManager.h"

// Container
#include <array>
#include <deque>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>


#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <functional>
#include <memory>

#ifdef SPITFIRE_PLATFORM_WINDOWS
	#include <Windows.h>
	#define SPITFIRE_RENDERER_OPENGL
#endif
