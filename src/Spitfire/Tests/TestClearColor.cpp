#include "TestClearColor.h"

#include "PixelEngine/Core/Core.h"
#include "PixelEngine/OpenGlCore/Core/Core.h"

#include "imgui/imgui.h"

namespace Test{

	TestClearColor::TestClearColor()
		: m_ClearColor {0.2f, 0.3f, 0.8f, 1.0f}
	{

	}

	TestClearColor::~TestClearColor()
	{

	}

	void TestClearColor::OnUpdate(float delta)
	{

	}

	void TestClearColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Color", m_ClearColor);
	}

}