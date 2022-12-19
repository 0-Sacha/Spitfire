
#include "Spitfirepch.h"
#include "Layer.h"

namespace Spitfire {
	
	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName) {}

	Layer::Layer(std::string&& debugName)
		: m_DebugName(std::move(debugName)) {}
}