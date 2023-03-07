#pragma once

#include "Layer.h"

#include <ranges>

namespace Spitfire {

	class Application;
	
	class LayerStack
	{
	public:
		void PushLayer(Ref<Layer>& layer);
		void PushOverlay(Ref<Layer>& overlay);
		void PopLayer(Ref<Layer>& layer);
		void PopOverlay(Ref<Layer>& overlay);

		void Clear()
		{
			m_Layers.clear();
			m_Overlay.clear();
		}

	public:
		std::vector<Ref<Layer>>& GetLayers() 				{ return m_Layers; }
		const std::vector<Ref<Layer>>& GetLayers() const 	{ return m_Layers; }
		std::vector<Ref<Layer>>& GetOverlays() 				{ return m_Layers; }
		const std::vector<Ref<Layer>>& GetOverlays() const	{ return m_Layers; }

	public:
		void ForEach(std::function<void(Ref<Layer>& layer)> function)
		{
			for (Ref<Layer>& layer : m_Layers)
				function(layer);
			for (Ref<Layer>& overlay : m_Overlay)
				function(overlay);
		}

		void ForEachStopable(std::function<bool(Ref<Layer>& layer)> function)
		{
			for (Ref<Layer>& layer : m_Layers)
				if (function(layer)) return;
			for (Ref<Layer>& overlay : m_Overlay)
				if (function(overlay)) return;
		}

		void ForEachReverse(std::function<void(Ref<Layer>& layer)> function)
		{
			for (Ref<Layer>& overlay : m_Overlay | std::views::reverse)
				function(overlay);
			for (Ref<Layer>& layer : m_Layers | std::views::reverse)
				function(layer);
		}

		void ForEachReverseStopable(std::function<bool(Ref<Layer>& layer)> function)
		{
			for (Ref<Layer>& overlay : m_Overlay | std::views::reverse)
				if (function(overlay)) return;
			for (Ref<Layer>& layer : m_Layers | std::views::reverse)
				if (function(layer)) return;
		}

	private:
		Application* m_ApplicationLinked;
		std::vector<Ref<Layer>> m_Layers;
		std::vector<Ref<Layer>> m_Overlay;
	};

}