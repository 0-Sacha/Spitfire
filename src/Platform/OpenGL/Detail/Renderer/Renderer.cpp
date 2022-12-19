
#include "Spitfirepch.h"

#include "Renderer.h"
#include "Spitfire/Core/Application/Application.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifdef SPITFIRE_USE_OPENGL
	#include "Platform/OpenGL/OpenGL.h"
#endif

namespace Spitfire::OpenGL::Detail
{
	Renderer::Renderer(int width, int height) {

		ASSERT(width != 0 && height != 0);

		m_Width = width;
		m_Height = height;

		if (!glfwInit())
			return;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //OpenGL 3.?
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //OpenGl ?.3
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(m_Width, m_Height, "Pixel Engine", nullptr, nullptr);
		if (!m_Window)
		{
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_Window);

		if (glewInit() != GLEW_OK)
			std::cout << "GLEW Error" << std::endl;


		Spitfire::Core::Logger().Info("OpenGl Version : {}", (const char*)glGetString(GL_VERSION));

		ComputeMatrix();

		glfwSetWindowSizeCallback(m_Window, RunCallbackOnResize);
	}

	Renderer& Renderer::GetInstance(int width, int height) {
		static Renderer renderer(width, height);
		return renderer;
	}

	void Renderer::Begin(int width, int height)
	{
		GetInstance(width, height);
	}


	Renderer::~Renderer()
	{
		glfwTerminate();
	}

	void Renderer::Test()
	{

	}

	void Renderer::RunCallbackOnResize(GLFWwindow* window, int width, int height)
	{
		GetInstance().m_Width = width;
		GetInstance().m_Height = height;

		glViewport(0, 0, width, height);
		GetInstance().ComputeMatrix();

		if (window == GetInstance().m_Window)
			for (auto& Func : GetInstance().m_CallbackOnResize)
				Func();
	}

	void Renderer::ComputeMatrix()
	{
		m_Proj = glm::ortho(0.0f, (float)m_Width, 0.0f, (float)m_Height, -1.0f, 1.0f);
		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	}

	void Renderer::ResetClearColor() {
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	}

	void Renderer::Clear() {
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}


	void Renderer::AddCallbackOnResize(const std::function<void(void)>& Function)
	{
		GetInstance().m_CallbackOnResize.push_back(Function);
	}

	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
		shader.Bind();
		va.Bind();
		ib.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::Draw(const VertexArray* const va, const IndexBuffer* const ib, const Shader* const shader)
	{
		shader->Bind();
		va->Bind();
		ib->Bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	}

	const glm::mat4& Renderer::GetProj()
	{
		return GetInstance().m_Proj;
	}

	const glm::mat4& Renderer::GetView()
	{
		return GetInstance().m_View;
	}

	const int Renderer::GetWidth()
	{
		return GetInstance().m_Width;
	}

	const int Renderer::GetHeight()
	{
		return GetInstance().m_Height;
	}

	const GLFWwindow* const Renderer::GetWindow()
	{
		return GetInstance().m_Window;
	}

	void Renderer::UseImGui(bool value)
	{
		GetInstance().m_UsingImGui = value;

		if (value) {
			ImGui::CreateContext();
			ImGui_ImplGlfw_InitForOpenGL(GetInstance().m_Window, true);
			ImGui_ImplOpenGL3_Init("#version 410");
			ImGui::StyleColorsDark();
		}
		else {
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}
	}

	const int Renderer::GetNextTexSlot()
	{
		static int i = 0;
		return i++;
	}

	void Renderer::TurnOnVsync()
	{
		glfwSwapInterval(1);	//Vsync
	}

	const bool Renderer::IsNotClose()
	{
		return !glfwWindowShouldClose(GetInstance().m_Window);
	}

	void Renderer::NewFrame()
	{
		Renderer::ResetClearColor();
		Renderer::Clear();

		if (GetInstance().m_UsingImGui)
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
		}
	}

	void Renderer::EndFrame()
	{
		if (GetInstance().m_UsingImGui) {
			ImGuiIO& io = ImGui::GetIO();
			Application& app = Application::GetInstance();
			io.DisplaySize = ImVec2((float)app.GetApplicationSpecification().Width, (float)app.GetApplicationSpecification().Height);

			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
		}

		glfwSwapBuffers(GetInstance().m_Window);
		glfwPollEvents();
	}
}
