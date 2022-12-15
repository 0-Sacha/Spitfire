
#include "Test.h"

#include "PixelEngine/PixelEngineCore/Renderer.h"

#include "imgui/imgui.h"

namespace Test {

	TestMenu::TestMenu(int width, int height)
	{
		Renderer::Begin(width, height);
		Renderer::UseImGui();
		m_CurrentTest = this;
	}

	TestMenu::~TestMenu() = default;

	TestMenu& TestMenu::GetInstance(int width, int height)
	{
		static TestMenu instance(width, height);
		return instance;
	}

	void TestMenu::AlwaysEngine()
	{
		TestMenu& instance = GetInstance();
		instance.m_CurrentTest = &instance;

		while(Renderer::IsNotClose()){
			Renderer::NewFrame();

			if (instance.m_CurrentTest) {
				instance.m_CurrentTest->OnUpdate(0.0f);
				instance.m_CurrentTest->OnRender();

				ImGui::Begin("Test");
				if (instance.m_CurrentTest != &instance && ImGui::Button("<-")) {
					delete instance.m_CurrentTest;
					instance.m_CurrentTest = &instance;
				}
				instance.m_CurrentTest->OnImGuiRender();
				ImGui::End();
			}

			Renderer::EndFrame();
		}
	}

	void TestMenu::Begin(int width, int height)
	{
		GetInstance(width, height);
	}

	void TestMenu::OnImGuiRender()
	{
		for(auto &test : m_Tests){
			if (ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
	}

}