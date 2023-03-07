#include "ImGuiLayerOpenGL.h"

#include "GraphicsPlatform/OpenGL/Application/ApplicationOpenGL.h"

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "Dependencies/ImGui/backends/imgui_impl_glfw.h"
#include "Dependencies/ImGui/backends/imgui_impl_opengl3.h"

namespace Spitfire
{

	void ImGuiLayerOpenGL::OnAttachPlatformImpl()
	{
		Application& app = Application::GetInstance();

		ImGui_ImplGlfw_InitForOpenGL(app.GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayerOpenGL::OnDetachPlatformImpl()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
	}

	void ImGuiLayerOpenGL::BeginFramePlatformImpl()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
	}

	void ImGuiLayerOpenGL::EndFramePlatformImpl()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}
