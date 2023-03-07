#pragma once

#include "Spitfire/Core/Core.h"
#include "Spitfire/Core/Application/Application.h"

namespace Spitfire
{
	class ApplicationOpenGL : public Application
	{
	public:
		ApplicationOpenGL(const std::string& name, std::uint32_t width = 1280, std::uint32_t height = 720);

	private:
		void Create();
	};
}
