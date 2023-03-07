#include "Application.h"

#include "Spitfire/Core/Input/Input.h"

#include <GLFW/glfw3.h>

namespace Spitfire {

	Application::Application(const ApplicationSpecification& specs)
		: m_ApplicationSpecification{ specs }
		, m_Logger(specs.Name, ProjectCore::LoggerManager::LogSeverity::Trace)
		, m_Window(nullptr)
	{}

	Application::Application(const std::string& name, uint32_t width, uint32_t height)
		: m_ApplicationSpecification{ name, width, height }
		, m_Logger(name, ProjectCore::LoggerManager::LogSeverity::Trace)
		, m_Window(nullptr)
	{}

	Application::~Application()
	{
		DestroyLayer();
		DestroyGLFW();
		s_Instance = nullptr;
	}

	static void GLFWErrorCallback(int error, const char* description)
	{
		Application::GetInstance().Logger().Fatal("GLFW Error {}: {}", error, description);
	}

	static void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height) {
		Application& app = *(Application*)glfwGetWindowUserPointer(window);
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

	void Application::CreateGLFWContext()
	{
		if (s_Instance)
			SPITFIRE_ASSERT(false, "Application already exists!");
		s_Instance = this;

		glfwSetErrorCallback(GLFWErrorCallback);
		if (!glfwInit())
		{
			m_Logger.Fatal("Could not initialize GLFW!");
			return;
		}
	}

	void Application::CreateGLFWWindow()
	{
		m_Window = glfwCreateWindow(m_ApplicationSpecification.Width, m_ApplicationSpecification.Height, m_ApplicationSpecification.Name.c_str(), NULL, NULL);
	}

	void Application::BindGLFWEvent()
	{
		glfwSwapInterval(1); // VSYNC

		glfwSetWindowUserPointer(m_Window, this);

		glfwSetWindowSizeCallback(m_Window, GLFWWindowSizeCallback);
		glfwSetWindowCloseCallback(m_Window, GLFWWindowCloseCallback);
		glfwSetKeyCallback(m_Window, GLFWKeyCallback);
		glfwSetCharCallback(m_Window, GLFWCharCallback);
		glfwSetMouseButtonCallback(m_Window, GLFWMouseButtonCallback);
		glfwSetScrollCallback(m_Window, GLFWScrollCallback);
		glfwSetCursorPosCallback(m_Window, GLFWCursorPosCallback);

	}

	void Application::DestroyLayer()
	{
		m_LayerStack.ForEach([](Ref<Layer>& layer) {
				layer->OnDetach();
			});
		m_LayerStack.Clear();
	}

	void Application::DestroyGLFW()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			TimeStep timeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_LayerStack.ForEach([timeStep](Ref<Layer>& layer) {
				layer->OnUpdate(timeStep);
				});

			m_ImGuiLayer->BeginFrame();
			m_LayerStack.ForEach([](Ref<Layer>& layer) {
				layer->OnImGuiRender();
				});
			m_ImGuiLayer->EndFrame();

			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}
	}

	void Application::PushLayer(Ref<Layer> layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Ref<Layer> overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& event)
	{
		SPITFIRE_EVENT_TRACE(event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(SPITFIRE_BIND_EVENT(OnWindowClose));

		m_LayerStack.ForEachReverseStopable([&event](Ref<Layer>& layer) {
			layer->OnEvent(event);
		return event.Handled;
			});
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		m_ApplicationSpecification.Height = event.GetHeight();
		m_ApplicationSpecification.Width = event.GetWidth();
		return true;
	}

}
