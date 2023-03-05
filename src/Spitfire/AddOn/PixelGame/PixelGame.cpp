
#include "PixelGame.h"

/*
#include "Asset/Shader/BaseMonochrome.h"
#include "Asset/Shader/BaseRG.h"
#include "Asset/Shader/BaseRGB.h"
#include "Asset/Shader/BaseRGBA.h"

namespace Spitfire::Games
{
	PixelGame::PixelGame(const std::string& name, int width, int height, uint8_t pixelSize, int bpp, const std::string& shaderPath)
		: m_Name(name), m_Width(width), m_Height(height), m_BPP(bpp), m_PixelSize(pixelSize)
	{
		InitPixelGame(shaderPath);
		m_Logger.SetName(m_Name);
	}

	PixelGame::PixelGame(std::string&& name, int width, int height, uint8_t pixelSize, int bpp, const std::string& shaderPath)
		: m_Name(std::move(name)), m_Width(width), m_Height(height), m_BPP(bpp), m_PixelSize(pixelSize)
	{
		InitPixelGame(shaderPath);
		m_Logger.SetName(m_Name);
	}


	void PixelGame::InitPixelGame(const std::string& shaderPath)
	{
		m_Size = m_Width * m_Height * m_BPP;
		m_CurrentIdBuffer = 0;
		m_Buffers[0] = new uint8_t[m_Size];
		m_Buffers[1] = new uint8_t[m_Size];

		Renderer::Begin(m_Width * m_PixelSize, m_Height * m_PixelSize);

		float vertex2D[] = {
				-0.5f, -0.5f, 0.0f, 0.0f,	//0
				 0.5f, -0.5f, 1.0f, 0.0f,	//1
				 0.5f,  0.5f, 1.0f, 1.0f,	//2
				-0.5f,  0.5f, 0.0f, 1.0f	//3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VertexArray = new VertexArray;
		m_VertexBuffer = new VertexBuffer(vertex2D, 4 * 4 * sizeof(float));

		BufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		m_IndexBuffer = new IndexBuffer(indices, 6);

		GetShader(shaderPath);
		m_Shader->Unbind();

		m_Texture = new Texture(m_Width, m_Height, m_BPP, m_Buffers[m_CurrentIdBuffer], TextureRender::Nearest);
		m_Texture->AttributeSlot(Renderer::GetNextTexSlot());
		m_Texture->Bind();
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", m_Texture->GetTextureSlot());

		m_VertexArray->Unbind();
		m_VertexBuffer->Unbind();
		m_IndexBuffer->Unbind();
		m_Shader->Unbind();
		m_Texture->Unbind();

		OnResize();

		Renderer::AddCallbackOnResize([&]() { this->OnResize(); });
	}

	void PixelGame::AlwaysEngine()
	{
		size_t old = PixelGame::GetTime(), cur;
		float delta;


		while (Renderer::IsNotClose())
		{
			Renderer::NewFrame();

			cur = GetTime();
			delta = (float)(cur - old) / 1000;
			Frame(delta);
			old = cur;

			if (m_PrintFPS)
				m_Logger.Trace("FPS : {}", 1000.0f / delta);

			Draw();

			Renderer::EndFrame();
		}
	}

	void PixelGame::Clear(const uint8_t value) {
		uint8_t* subBuffer = m_Buffers[m_CurrentIdBuffer];
		for (size_t i = 0; i < m_Size; ++i)
			*subBuffer++ = value;
	}

	void PixelGame::Draw()
	{
		m_Texture->SetBuffer(m_Buffers[m_CurrentIdBuffer]);
		m_Texture->TextureSend();

		glm::mat4 mvp = Renderer::GetProj() * Renderer::GetView() * GetModelMatrix();

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		Renderer::Draw(m_VertexArray, m_IndexBuffer, m_Shader);
	}

	void PixelGame::OnResize()
	{
#define SubFact 0.95f

		m_Translation = glm::vec3(Renderer::GetWidth() / 2, Renderer::GetHeight() / 2, 0);
		float fact = (float)m_Width / m_Height;
		if (Renderer::GetWidth() >= Renderer::GetHeight()) {
			m_Scale = glm::vec3(SubFact * fact * Renderer::GetHeight(), SubFact * Renderer::GetHeight(), 1.0f);
		}
		else {
			std::cout << "AFF" << std::endl;
			fact = 1.0f / fact;
			m_Scale = glm::vec3(SubFact * Renderer::GetWidth(), SubFact * fact * Renderer::GetWidth(), 1.0f);
		}
	}

	glm::mat4 PixelGame::GetModelMatrix()
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		model = glm::scale(model, m_Scale);
		return model;
	}


	const size_t PixelGame::GetTime()
	{
		return std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();
	}

	void PixelGame::GetShader(const std::string& shaderPath)
	{
		if (shaderPath != "")
			m_Shader = new Shader(shaderPath);
		else {
			switch (m_BPP) {
			case 1:
				m_Shader = new Shader(BASE_MONOCHROME_SHADER);
				break;
			case 2:
				m_Shader = new Shader(BASE_RG_SHADER);
				break;
			case 3:
				m_Shader = new Shader(BASE_RGB_SHADER);
				break;
			case 4:
				m_Shader = new Shader(BASE_RGBA_SHADER);
				break;
			default:
				ASSERT(false);
				break;
			}
		}
	}
}
*/
