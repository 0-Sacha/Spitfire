#pragma once

#include "Spitfire/Core/Core.h"

#include "Spitfire/Core/Layer/LayerStack.h"
#include "Spitfire/Core/Event/ApplicationEvent.h"
#include "Spitfire/Core/Utils/TimeStep.h"
#include "Spitfire/Core/ImGui/ImGuiLayer.h"

struct GLFWwindow;

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
		virtual ~Application();

	protected:
		void CreateGLFWContext();
		void CreateGLFWWindow();
		void BindGLFWEvent();

		void DestroyLayer();
		void DestroyGLFW();

	public:
		virtual void Run();

	public:
		void PushLayer(Ref<Layer> layer);
		void PushOverlay(Ref<Layer> overlay);

	public:
		GLFWwindow* GetWindow() 												{ return m_Window; }
		const ApplicationSpecification& GetApplicationSpecification() const 	{ return m_ApplicationSpecification; }
		ProjectCore::LoggerManager::BasicLogger& Logger() 						{ return m_Logger; }
	
	public:
		void OnEvent(Event& event);
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

	protected:
		ApplicationSpecification m_ApplicationSpecification;
		ProjectCore::LoggerManager::BasicLogger m_Logger;

		GLFWwindow* m_Window;
		Ref<ImGuiLayer> m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;
		float m_TimeStep = 0.0f;
		float m_FrameTime = 0.0f;
		float m_LastFrameTime = 0.0f;

	public:
		static Application& GetInstance() 	{ return *s_Instance; };
	private:
		static inline Application* s_Instance;
	};
}
