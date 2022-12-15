
#include "TestTexture.h"

#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

#include "PixelEngine/PixelEngineCore/Renderer.h"

namespace Test {

	TextureTest::TextureTest()
		: m_Translation(200, 200, 0), m_Scale(100, 100, 1)
	{
		
		float vertex[] = {
			-0.5f, -0.5, 0.0f, 0.0f, //0
			 0.5f, -0.5, 1.0f, 0.0f, //1
			 0.5f,  0.5, 1.0f, 1.0f, //2
			-0.5f,  0.5, 0.0f, 1.0f	 //3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VertexArray = new VertexArray;
		m_VertexBuffer = new VertexBuffer(vertex, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = new IndexBuffer(indices, 6);

		#include "Asset/Shader/BaseRGBA.h"
		m_Shader = new Shader(BASE_RGBA_SHADER);
		m_Shader->Bind();

		texture = new Texture("TextureTest.png");
		texture->AttributeSlot(Renderer::GetNextTexSlot());
		m_Shader->SetUniform1i("u_Texture", texture->GetTextureSlot());

		m_VertexArray->Unbind();
		m_VertexBuffer->Unbind();
		m_IndexBuffer->Unbind();
		m_Shader->Unbind();
	}

	TextureTest::~TextureTest()
	{
		delete m_VertexArray;
		delete m_VertexBuffer;
		delete m_IndexBuffer;
		delete texture;
		delete m_Shader;
	}

	void TextureTest::OnUpdate(float delta)
	{

	}

	void TextureTest::OnRender()
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		model = glm::scale(model, m_Scale);

		glm::mat4 mvp = Renderer::GetProj() * Renderer::GetView() * model;

		texture->Bind();
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		Renderer::Draw(m_VertexArray, m_IndexBuffer, m_Shader);
	}

	void TextureTest::OnImGuiRender()
	{
		ImGui::DragFloat3("Translation", &m_Translation.x);
		ImGui::DragFloat3("Scale", &m_Scale.x);
	}

}