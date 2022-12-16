#include "Spitfirepch.h"
#include "Spitfire/Core/Core.h"
#include "VertexBufferLayout.h"

namespace Spitfire {

	/////---------- ShaderData ----------/////

	uint32_t ShaderData::GetSizeOf(ShaderData::Type type)
	{
		switch (type)
		{
			case ShaderData::Type::Bool:	return 1;
			case ShaderData::Type::Int:		return 4;
			case ShaderData::Type::Int2:	return 4 * 2;
			case ShaderData::Type::Int3:	return 4 * 3;
			case ShaderData::Type::Int4:	return 4 * 4;
			case ShaderData::Type::Float:	return 4;
			case ShaderData::Type::Float2:	return 4 * 2;
			case ShaderData::Type::Float3:	return 4 * 3;
			case ShaderData::Type::Float4:	return 4 * 4;
			case ShaderData::Type::Mat3:	return 4 * 3 * 3;
			case ShaderData::Type::Mat4:	return 4 * 4 * 4;
		}

		SPITFIRE_ASSERT(false, "Unkown ShaderDataType!");
		return 0;
	}

	uint32_t ShaderData::GetComponentCountOf(ShaderData::Type type)
	{
		switch (type)
		{
			case ShaderData::Type::Bool:	return 1;
			case ShaderData::Type::Int:		return 1;
			case ShaderData::Type::Int2:	return 2;
			case ShaderData::Type::Int3:	return 3;
			case ShaderData::Type::Int4:	return 4;
			case ShaderData::Type::Float:	return 1;
			case ShaderData::Type::Float2:	return 2;
			case ShaderData::Type::Float3:	return 3;
			case ShaderData::Type::Float4:	return 4;
			case ShaderData::Type::Mat3:	return 3 * 3;
			case ShaderData::Type::Mat4:	return 4 * 4;
		}
		SPITFIRE_ASSERT(false, "Unkown ShaderDataType!");
		return 0;
	}



	/////---------- BufferLayout ----------/////

	BufferLayout::BufferLayout(const std::initializer_list<BufferElements>& elements)
		: m_Elements(elements)
	{
		CalculateOffsetAndStride();
	}

	void BufferLayout::CalculateOffsetAndStride()
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements) {
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

}


















