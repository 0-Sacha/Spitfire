#pragma once

#include "Spitfire/Core/Layer/Layer.h"

#include "Spitfire/Core/Event/ApplicationEvent.h"
#include "Spitfire/Core/Event/KeyboardEvent.h"
#include "Spitfire/Core/Event/MouseEvent.h"

#include "imgui.h"

namespace Spitfire
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() = default;

	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& event) override;
		void OnImGuiRender() override;
	
	protected:
		virtual void OnAttachPlatformImpl() = 0;
		virtual void OnDetachPlatformImpl() = 0;
		virtual void BeginFramePlatformImpl() = 0;
		virtual void EndFramePlatformImpl() = 0;

	public:
		void BeginFrame();
		void EndFrame();
		void BeginFrameDockspace();
		void EndFrameDockspace();

		void SetMenubarCallback(const std::function<void()>& menubarCallback) { m_MenubarCallback = menubarCallback; }

	private:
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);

		std::function<void()> m_MenubarCallback;
	};
}
