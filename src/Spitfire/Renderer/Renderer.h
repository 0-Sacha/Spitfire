#pragma once

#include "Spitfire/Core/Core.h"
#include "Spitfire/OpenGL/Core/Core.h"

#include "Spitfire/OpenGL/Asset/VertexBuffer.h"
#include "Spitfire/OpenGL/Asset/VertexArray.h"
#include "Spitfire/OpenGL/Asset/VertexBufferLayout.h"
#include "Spitfire/OpenGL/Shader/Shader.h"
#include "Spitfire/OpenGL/Texture/Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct GLFWwindow;

namespace Spitfire
{
	class PE_API Renderer {
	public:
		static Renderer& GetInstance(int width = 720, int height = 480);
		static void Begin(int width = 720, int height = 480);
		static const bool IsNotClose();
		static void NewFrame();
		static void EndFrame();

	public:
		static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
		static void Draw(const VertexArray* const va, const IndexBuffer* const ib, const Shader* const shader);

	public:
		static const glm::mat4& GetProj();
		static const glm::mat4& GetView();
		static const int GetWidth();
		static const int GetHeight();
		static const GLFWwindow* const GetWindow();
		static void UseImGui(bool value = true);

	public:
		static void ResetClearColor();
		static void Clear();
		static void AddCallbackOnResize(const std::function<void(void)>& Function);
		static void TurnOnVsync();

	public:
		static const int GetNextTexSlot();
		static void Test();


	private:
		Renderer(int width, int height);
		~Renderer();

	public:
		Renderer(const Renderer& other) = delete;

	private:
		static void RunCallbackOnResize(GLFWwindow* window, int width, int height);
		void ComputeMatrix();

	private:
		glm::mat4 m_Proj, m_View;
		int m_Width, m_Height, m_XPos, m_YPos;
		std::vector<std::function<void(void)>> m_CallbackOnResize;
		bool m_UsingImGui = false;
		GLFWwindow* m_Window;
	};
}
