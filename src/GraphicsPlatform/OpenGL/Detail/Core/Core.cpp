
#include "Core.h"

namespace Spitfire::OpenGL::Detail
{
	void GLClearErrorBuffer()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool GLLogError(const char* function /*= ""*/, const char* file /*= ""*/, const int line /*= 0*/)
	{
		bool isError = false;
		GLenum error = glGetError();
		while (error != GL_NO_ERROR) {
			if (!isError && line != 0)
				std::cout << function << "  " << file << " : " << line << std::endl;
			isError = true;
			std::cout << "[GL Error] : error = 0x" << std::hex << error << std::endl;
			error = glGetError();
		}
		return !isError;
	}
}
