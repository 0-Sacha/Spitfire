#include "ImGuiLayerVulkan.h"

#include "GraphicsPlatform/OpenGL/Application/ApplicationOpenGL.h"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "Dependencies/ImGui/backends/imgui_impl_glfw.h"
#include "Dependencies/ImGui/backends/imgui_impl_vulkan.h"

namespace Spitfire
{

	void ImGuiLayerVulkan::OnAttachPlatformImpl()
	{
		Application& app = Application::GetInstance();

		ImGui_ImplGlfw_InitForOpenGL(app.GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayerVulkan::OnDetachPlatformImpl()
	{
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayerVulkan::BeginFramePlatformImpl()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
	}

	void ImGuiLayerVulkan::EndFramePlatformImpl()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}
