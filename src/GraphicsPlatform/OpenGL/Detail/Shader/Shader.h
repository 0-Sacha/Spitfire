#pragma once

#include "Spitfire/Core/Core.h"
#include "GraphicsPlatform/OpenGL/Detail/Core/Core.h"

#include <unordered_map>
#include <istream>
#include "glm/glm.hpp"

namespace Spitfire::OpenGL::Detail
{

	class Shader
	{
	private:
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> m_UniformLoctaionCache;
	public:
		Shader(const std::string& filepath);
		Shader(const char* const file);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	private:
		int GetUniformLocation(const std::string& name);

		static std::tuple<std::string, std::string> ParseShader(std::istream& filepath);
		static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		static unsigned int CompileShader(unsigned int type, const std::string& source);
	};
}
