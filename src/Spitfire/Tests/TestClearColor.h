#pragma once

#include "Test.h"

namespace Test{

	class PE_API TestClearColor : public BaseTest
	{
	public:
		TestClearColor();
		~TestClearColor() override;


		void OnUpdate(float delta) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};

}

