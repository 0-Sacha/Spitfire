
#pragma once

#include "Spitfire/Core/Core.h"
#include "GraphicsPlatform/OpenGL/Detail/Core/Core.h"
#include "VertexBufferLayout.h"

namespace Spitfire::OpenGL::Detail {

	/////---------- VertexBuffer ----------/////

	class VertexBuffer
	{
	public:
		VertexBuffer(float* vertices, uint32_t size);
		~VertexBuffer();

	public:
		void Bind() const;
		void Unbind() const;

		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
		const BufferLayout& GetLayout() const { return m_Layout; }

	private:
		RendererID m_RendererID;
		BufferLayout m_Layout;
	};



	/////---------- VertexBuffer ----------/////

	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* indices, uint32_t count);
		~IndexBuffer();

	public:
		void Bind() const;
		void Unbind() const;

		uint32_t GetCount() const { return m_Count; }

	private:
		RendererID m_RendererID;
		uint32_t m_Count;
	};
}
