#include "VertexArray.h"

#include "GL/glew.h"

namespace Spitfire::OpenGL::Detail
{

	uint32_t ShaderData::GetAPIType(ShaderData::Type type) {
		switch (type)
		{
		case ShaderData::Type::Bool:		return GL_BOOL;
		case ShaderData::Type::Int:			return GL_INT;
		case ShaderData::Type::Int2:		return GL_INT;
		case ShaderData::Type::Int3:		return GL_INT;
		case ShaderData::Type::Int4:		return GL_INT;
		case ShaderData::Type::Float:		return GL_FLOAT;
		case ShaderData::Type::Float2:		return GL_FLOAT;
		case ShaderData::Type::Float3:		return GL_FLOAT;
		case ShaderData::Type::Float4:		return GL_FLOAT;
		case ShaderData::Type::Mat3:		return GL_FLOAT;
		case ShaderData::Type::Mat4:		return GL_FLOAT;
		}

		SPITFIRE_ASSERT(false, "Unkown ShaderDataType!");
		return 0;
	}

	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(const Ref<VertexBuffer> vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderData::GetAPIType(element.ShaderDataType),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::SetIndexBuffer(const Ref<IndexBuffer> indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}
