#pragma once

#include <iostream>
#include "GL/glew.h"

#define ASSERT(x) if(!(x)) __debugbreak();

#define GLCall(x)   Spitfire::OpenGL::Detail::GLClearErrorBuffer();\
					x;\
					ASSERT(Spitfire::OpenGL::Detail:: GLLogError(__FUNCTION__, __FILE__, __LINE__))


namespace Spitfire::OpenGL::Detail
{
	void GLClearErrorBuffer();
	bool GLLogError(const char* function = "", const char* file = "", const int line = 0);

	using RendererID = unsigned int;
};
