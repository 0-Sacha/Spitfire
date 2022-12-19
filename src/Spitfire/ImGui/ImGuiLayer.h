#pragma once

#include "Spitfire/Core/Layer/Layer.h"

#include "Spitfire/Core/Event/ApplicationEvent.h"
#include "Spitfire/Core/Event/KeyboardEvent.h"
#include "Spitfire/Core/Event/MouseEvent.h"

namespace Spitfire {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() = default;

	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& event);
		void OnImGuiRender() override;
		
	public:
		void BeginFrame();
		void EndFrame();

	private:
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);
	};
}
