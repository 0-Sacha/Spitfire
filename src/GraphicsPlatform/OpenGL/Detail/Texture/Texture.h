#pragma once

#include "Spitfire/Core/Core.h"

namespace Spitfire::OpenGL::Detail
{
	enum class TextureRender : uint8_t
	{
		Linear,
		Nearest
	};

	class Texture
	{
	public:
		Texture(const std::string& filepath);
		Texture(int width, int height, int bpp, unsigned char* buffer, TextureRender render = TextureRender::Linear);
		~Texture();

	public:
		void AttributeSlot(unsigned int slot);
		void Bind() const;
		void Unbind() const;
		const unsigned int GetTextureSlot();

		void TextureSend();
		void SelectTexture();
		static unsigned int GetTextureRender(TextureRender render);

	public:
		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

	public:
		inline uint8_t* GetBuffer() { return m_Buffer; };
		inline void SetBuffer(uint8_t* buffer) { m_Buffer = buffer; };

	private:
		unsigned int m_RendererID, m_Slot;
		std::string m_Filepath;
		uint8_t* m_Buffer;
		int m_Width, m_Height, m_BPP;
	};
}
