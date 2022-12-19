#pragma once

#include "Spitfire/Core/Core.h"

namespace Spitfire {

	/////---------- ShaderData ----------/////

	class ShaderData
	{
	public:
		enum class Type
		{
			None = 0,
			Bool,
			Int, Int2, Int3, Int4,
			Float, Float2, Float3, Float4,
			Mat3, Mat4
		};

	public:
		static uint32_t GetSizeOf(ShaderData::Type type);
		static uint32_t GetComponentCountOf(ShaderData::Type type);
		static uint32_t GetAPIType(ShaderData::Type type);
	};


	/////---------- BufferElements ----------/////

	struct BufferElements
	{
	public:
		BufferElements() = default;

		BufferElements(ShaderData::Type type, const std::string& name, bool normalized = false)
			: ShaderDataType(type), Name(name), Size(ShaderData::GetSizeOf(type)), Offset(0), Normalized(normalized)
		{ }

		BufferElements(ShaderData::Type type, std::string&& name, bool normalized = false)
			: ShaderDataType(type), Name(std::move(name)), Size(ShaderData::GetSizeOf(type)), Offset(0), Normalized(normalized)
		{ }

	public:
		inline uint32_t GetComponentCount() const { return ShaderData::GetComponentCountOf(ShaderDataType); }

	public:
		ShaderData::Type ShaderDataType;
		std::string Name;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;
	};


	/////---------- BufferLayout ----------/////

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElements>& elements);

	public:
		inline const std::vector<BufferElements>& GetElements() { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }

	public:
		inline std::vector<BufferElements>::iterator begin() { return m_Elements.begin(); }
		inline std::vector<BufferElements>::iterator end() { return m_Elements.end(); }

		inline std::vector<BufferElements>::const_iterator begin() const { return m_Elements.begin(); }
		inline std::vector<BufferElements>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride();

	private:
		std::vector<BufferElements> m_Elements;
		uint32_t m_Stride;
	};
}
