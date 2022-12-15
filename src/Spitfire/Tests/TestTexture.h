#pragma once

#include "Test.h"
#include "glm/glm.hpp"

class Shader;
class VertexArray;
class VertexBuffer;
class IndexBuffer;
class Texture;

namespace Test{

	class PE_API TextureTest : public BaseTest
	{
	public:
		TextureTest();
		~TextureTest() override;


		void OnUpdate(float delta) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		glm::vec3 m_Translation, m_Scale;
		VertexArray* m_VertexArray;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
		Texture* texture;
		Shader* m_Shader;
	};

}

