#pragma once

#include "Spitfire/Core/Core.h"

#include "Spitfire/Core/Layer/LayerStack.h"
#include "Spitfire/Core/Event/ApplicationEvent.h"

#include "Spitfire/Core/Utils/TimeStep.h"

#include "Spitfire/ImGui/ImGuiLayer.h"


#define SPITFIRE_BIND_APPEVENT(func) std::bind(&Application::func, this, std::placeholders::_1)

namespace Spitfire
{

	struct ApplicationSpecification
	{
		std::string Name = "Spitfire App";
		uint32_t Width = 1280;
		uint32_t Height = 720;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specs = ApplicationSpecification{});
		Application(const std::string& name, uint32_t width = 1280, uint32_t height = 720);
		virtual ~Application() = default;

	private:
		void Create(const ApplicationSpecification& specs);

	public:
		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		GLFWwindow* GetWindow() { return m_Window; }
		static Application& GetInstance() { return *s_Instance; };

		ApplicationSpecification& GetApplicationSpecification() { return m_ApplicationSpecification; }
		const ApplicationSpecification& GetApplicationSpecification() const { return m_ApplicationSpecification; }

		EngineCore::LoggerManager::BasicLogger& GetLogger() { return m_Logger; }
		static EngineCore::LoggerManager::BasicLogger& Logger() { return GetInstance().GetLogger(); }


	private:
		bool OnWindowClose(WindowCloseEvent& event);

	private:
		GLFWwindow* m_Window;
		ApplicationSpecification m_ApplicationSpecification;

		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		float m_TimeStep = 0.0f;
		float m_FrameTime = 0.0f;
		float m_LastFrameTime = 0.0f;

		EngineCore::LoggerManager::BasicLogger m_Logger;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}
