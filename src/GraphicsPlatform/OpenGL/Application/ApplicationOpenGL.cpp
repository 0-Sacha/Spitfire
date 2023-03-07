#include "ApplicationOpenGL.h"

#include "GraphicsPlatform/OpenGL/ImGui/ImGuiLayerOpenGL.h"

#include "GL/glew.h"
#include <GLFW/glfw3.h>

namespace Spitfire
{

	ApplicationOpenGL::ApplicationOpenGL(const std::string& name, uint32_t width, uint32_t height)
		: Application(name, width, height)
	{
		Create();
	}

	void ApplicationOpenGL::Create()
	{
		CreateGLFWContext();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glewInit();
		
		CreateGLFWWindow();
		glfwMakeContextCurrent(m_Window);

		BindGLFWEvent();
		m_ImGuiLayer = std::make_shared<ImGuiLayerOpenGL>();
		PushLayer(m_ImGuiLayer);
	}

}
