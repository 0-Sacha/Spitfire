#pragma once

#include "Spitfire/Core/ImGui/ImGuiLayer.h"

namespace Spitfire
{
	class ImGuiLayerOpenGL : public ImGuiLayer
	{
	protected:
		void OnAttachPlatformImpl() override;
		void OnDetachPlatformImpl() override;
		void BeginFramePlatformImpl() override;
		void EndFramePlatformImpl() override;
	};
}
