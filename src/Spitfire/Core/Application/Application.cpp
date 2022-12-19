
#include "Spitfirepch.h"

#include "Application.h"

#include "Spitfire/Core/Input/Input.h"

#ifdef SPITFIRE_USE_OPENGL
	#include "Platform/OpenGL/OpenGL.h"
#endif

namespace Spitfire {

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& specs)
		: m_Logger(specs.Name, EngineCore::LoggerManager::LogSeverity::Trace)
	{
		Create(specs);
	}


	Application::Application(const std::string& name, uint32_t width, uint32_t height)
		: m_Logger(name, EngineCore::LoggerManager::LogSeverity::Trace)
	{
		ApplicationSpecification specs;
		specs.Name = name;
		specs.Width = width;
		specs.Height = height;
		Create(specs);
	}

	static void GLFWErrorCallback(int error, const char* description)
	{
		Application::Logger().Fatal("GLFW Error {}: {}", error, description);
	}

	static void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height) {
		Application& app = *(Application*)glfwGetWindowUserPointer(window);
		app.GetApplicationSpecification().Height = height;
		app.GetApplicationSpecification().Width = width;

		WindowResizeEvent event(width, height);
		app.OnEvent(event);
	}

	static void GLFWWindowCloseCallback(GLFWwindow* window) {
		Application& app = *(Application*)glfwGetWindowUserPointer(window);

		WindowCloseEvent event;
		app.OnEvent(event);
	}

	static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Application& app = *(Application*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			KeyPressedEvent event(key, 0);
			app.OnEvent(event);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent event(key);
			app.OnEvent(event);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent event(key, 1);
			app.OnEvent(event);
			break;
		}
		}
	}

	static void GLFWCharCallback(GLFWwindow* window, uint32_t keyCode) {
		Application& app = *(Application*)glfwGetWindowUserPointer(window);

		KeyTypedEvent event(keyCode);
		app.OnEvent(event);
	}

	static void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		Application& app = *(Application*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent event(button);
			app.OnEvent(event);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent event(button);
			app.OnEvent(event);
			break;
		}
		}
	}

	static void GLFWScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
		Application& app = *(Application*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		app.OnEvent(event);
	}

	static void GLFWCursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
		Application& app = *(Application*)glfwGetWindowUserPointer(window);

		MouseMouvedEvent event((float)xPos, (float)yPos);
		app.OnEvent(event);
	}

	void Application::Create(const ApplicationSpecification& specs)
	{
		if(!s_Instance)
		{
			//Init Core
		}
		else
		{
			SPITFIRE_ASSERT(false, "Application already exists!");
		}
		s_Instance = this;

		glfwSetErrorCallback(GLFWErrorCallback);
		if (!glfwInit())
		{
			Logger().Fatal("Could not initialize GLFW!");
			return;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glewInit();

		m_Window = glfwCreateWindow(specs.Width, specs.Height, specs.Name.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_Window);
		
		SPITFIRE_INFO("OpenGl Info : RIP");
		// SPITFIRE_INFO(" - Vendor : {}", glGetString(GL_VENDOR));
		// SPITFIRE_INFO(" - Renderer : {}", glGetString(GL_RENDERER));
		// SPITFIRE_INFO(" - Version  : {}", glGetString(GL_VERSION));
		
		glfwSwapInterval(1); // VSYNC
		
		glfwSetWindowUserPointer(m_Window, this);

		glfwSetWindowSizeCallback(m_Window, GLFWWindowSizeCallback);
		glfwSetWindowCloseCallback(m_Window, GLFWWindowCloseCallback);
		glfwSetKeyCallback(m_Window, GLFWKeyCallback);
		glfwSetCharCallback(m_Window, GLFWCharCallback);
		glfwSetMouseButtonCallback(m_Window, GLFWMouseButtonCallback);
		glfwSetScrollCallback(m_Window, GLFWScrollCallback);
		glfwSetCursorPosCallback(m_Window, GLFWCursorPosCallback);

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}


	void Application::Run()
	{
		while(m_Running) {
			float time = (float)glfwGetTime();
			TimeStep timeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timeStep);

			m_ImGuiLayer->BeginFrame();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->EndFrame();

			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& event)
	{
		SPITFIRE_EVENT_TRACE(event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(SPITFIRE_BIND_APPEVENT(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin() && !event.Handled; )
			(*--it)->OnEvent(event);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}
}
