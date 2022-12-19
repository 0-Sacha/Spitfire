#pragma once

#include "Spitfire/Core/Core.h"
#include "VertexBuffer.h"

namespace Spitfire::OpenGL::Detail {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

	public:
		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const Ref<VertexBuffer> vertexBuffer);
		void SetIndexBuffer(const Ref<IndexBuffer> indexBuffer);

		const std::vector<Ref<VertexBuffer>> GetVertexBuffers() const { return m_VertexBuffers; }
		const Ref<IndexBuffer> GetIndexBuffer() const { return m_IndexBuffer; };
	
	private:
		RendererID m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}