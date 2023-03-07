

#include "Texture.h"
#include "GraphicsPlatform/OpenGL/Detail/Core/Core.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

namespace Spitfire::OpenGL::Detail
{
	Texture::Texture(const std::string& filepath)
		: m_RendererID(0), m_Filepath(filepath), m_Buffer(nullptr)
	{
		stbi_set_flip_vertically_on_load(1);
		m_Buffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		GLCall(glGenTextures(1, &m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		SelectTexture();
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		//if (m_Buffer)
		//	stbi_image_free(m_Buffer);
	}

	Texture::Texture(int width, int height, int bpp, unsigned char* buffer, TextureRender render)
		: m_Buffer(buffer), m_Width(width), m_Height(height), m_BPP(bpp)
	{
		GLCall(glGenTextures(1, &m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		unsigned int res = GetTextureRender(render);
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, res));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, res));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		SelectTexture();
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_RendererID));
	}


	void Texture::AttributeSlot(unsigned int slot)
	{
		m_Slot = slot;
		GLCall(glActiveTexture(GL_TEXTURE0 + m_Slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void Texture::Bind() const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + m_Slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	}

	void Texture::Unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}


	const unsigned int Texture::GetTextureSlot()
	{
		return m_Slot;
	}

	void Texture::SelectTexture()
	{
		switch (m_BPP) {
		case 1:
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_Width, m_Height, 0, GL_RED, GL_UNSIGNED_BYTE, m_Buffer));
			break;
		case 2:
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, m_Width, m_Height, 0, GL_RG, GL_UNSIGNED_BYTE, m_Buffer));
			break;
		case 3:
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_Buffer));
			break;
		case 4:
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Buffer));
			break;
		default:
			ASSERT(false);
			break;
		}
	}

	unsigned int Texture::GetTextureRender(TextureRender render)
	{
		unsigned int res = GL_LINEAR;
		switch (render)
		{
		case TextureRender::Linear:
			break;
		case TextureRender::Nearest:
			res = GL_NEAREST;
			break;
		}
		return res;
	}

	void Texture::TextureSend()
	{
		Bind();
		switch (m_BPP) {
		case 1:
			GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RED, GL_UNSIGNED_BYTE, m_Buffer));
			break;
		case 2:
			GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RG, GL_UNSIGNED_BYTE, m_Buffer));
			break;
		case 3:
			GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, m_Buffer));
			break;
		case 4:
			GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, m_Buffer));
			break;
		default:
			ASSERT(false);
			break;
		}
	}
}
