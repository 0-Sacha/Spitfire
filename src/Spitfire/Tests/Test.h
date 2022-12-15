#pragma once

#include "PixelEngine/Core/Core.h"

#include <functional>

namespace Test {

	class PE_API BaseTest {
	public:
		BaseTest() = default;
		virtual ~BaseTest() = default;

		virtual void OnUpdate(float delta) {};
		virtual void OnRender() {};
		virtual void OnImGuiRender() {};
	};

	class PE_API TestMenu : public BaseTest {
	public:
		static TestMenu& GetInstance(int width = 720, int height = 480);
		static void AlwaysEngine();
		static void Begin(int width = 720, int height = 480);

		template<typename T>
		static void RegisterTest(const std::string& name){
			GetInstance().m_Tests.push_back(std::make_pair(name, []() { return new T; }));
		}

	public:
		void OnImGuiRender() override;

	private:
		TestMenu(int width, int height);
		~TestMenu();

	private:
		BaseTest* m_CurrentTest;
		std::vector<std::pair<std::string, std::function<BaseTest* ()>>> m_Tests;
	};

}