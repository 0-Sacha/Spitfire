#include "LayerStack.h"

namespace Spitfire
{

	void LayerStack::PushLayer(Ref<Layer>& layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Ref<Layer>& overlay)
	{
		m_Overlay.push_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Ref<Layer>& layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin(), layer);
		if (it != m_Layers.end())
		{
			(*it)->OnDetach();
			m_Layers.erase(it);
		}
	}

	void LayerStack::PopOverlay(Ref<Layer>& overlay)
	{
		auto it = std::find(m_Overlay.begin(), m_Overlay.end(), overlay);
		if (it != m_Overlay.end())
		{
			(*it)->OnDetach();
			m_Overlay.erase(it);
		}
	}

}
