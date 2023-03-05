

#include "Shader.h"

namespace Spitfire::OpenGL::Detail
{
	Shader::Shader(const std::string& filepath)
	{
		std::ifstream file(filepath);
		if (!file.is_open())
			std::cout << "Can't find file : " << filepath << std::endl;

		auto [vertex, fragment] = ParseShader(file);
		m_RendererID = CreateShader(vertex, fragment);
	}

	Shader::Shader(const char* const fileChar)
	{
		std::stringstream str(fileChar);
		auto [vertex, fragment] = ParseShader(str);
		m_RendererID = CreateShader(vertex, fragment);
	}

	Shader::~Shader()
	{
		GLCall(glDeleteProgram(m_RendererID));
	}

	void Shader::Bind() const
	{
		GLCall(glUseProgram(m_RendererID));
	}

	void Shader::Unbind() const
	{
		GLCall(glUseProgram(0));
	}

	void Shader::SetUniform1i(const std::string& name, int value) {
		GLCall(glUniform1i(GetUniformLocation(name), value));
	}

	void Shader::SetUniform1f(const std::string& name, float value) {
		GLCall(glUniform1f(GetUniformLocation(name), value));
	}

	void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
	}

	void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &(matrix[0][0])));
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLoctaionCache.find(name) != m_UniformLoctaionCache.end())
			return m_UniformLoctaionCache[name];
		GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
		if (location == -1)
			std::cout << "Warning : uniform '" << name << "' doesn't exist!" << std::endl;
		m_UniformLoctaionCache[name] = location;
		return location;
	}



	unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		GLCall(glShaderSource(id, 1, &src, nullptr));
		GLCall(glCompileShader(id));

		int result;
		GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE) {
			int length;
			GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)_malloca(length * sizeof(char));
			GLCall(glGetShaderInfoLog(id, length, &length, message));
			std::cout << "Fail to compile shader " << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << std::endl;
			std::cout << message << std::endl;
			_freea(message);

			GLCall(glDeleteShader(id));
			return 0;
		}
		return id;
	}

	unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
		GLCall(unsigned int program = glCreateProgram());
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		GLCall(glAttachShader(program, vs));
		GLCall(glAttachShader(program, fs));
		GLCall(glLinkProgram(program));
		GLCall(glValidateProgram(program));

		GLCall(glDeleteShader(vs));
		GLCall(glDeleteShader(fs));
		return program;
	}

	std::tuple<std::string, std::string> Shader::ParseShader(std::istream& file) {

		if (file.good()) {
			enum class ShaderType : int {
				NONE = -1,
				VERTEX = 0,
				FRAGMENT = 1
			};

			std::string line;
			std::stringstream strstream[2];
			ShaderType type = ShaderType::NONE;
			while (getline(file, line)) {
				if (line.find("#shader") != std::string::npos) {
					if (line.find("vertex") != std::string::npos)
						type = ShaderType::VERTEX;
					else if (line.find("fragment") != std::string::npos)
						type = ShaderType::FRAGMENT;
				}
				else if (type != ShaderType::NONE) {
					strstream[(int)type] << line << "\n";
				}
			}
			return { strstream[0].str(), strstream[1].str() };
		}

		return { nullptr, nullptr };
	}
}
