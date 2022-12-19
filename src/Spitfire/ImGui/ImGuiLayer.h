#pragma once

#include "Blackbird/Core/Layer/Layer.h"

#include "Blackbird/Event/ApplicationEvent.h"
#include "Blackbird/Event/KeyboardEvent.h"
#include "Blackbird/Event/MouseEvent.h"

namespace Blackbird {

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
