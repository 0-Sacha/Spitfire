#include "Input.h"

#include "Spitfire/Core/Application/Application.h"

#include <GLFW/glfw3.h>

namespace Spitfire
{

	bool Input::IsKeyPressed(int keyCode)
	{
		auto state = glfwGetKey(Application::GetInstance().GetWindow(), keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseBtPressed(int btCode)
	{
		auto state = glfwGetMouseButton(Application::GetInstance().GetWindow(), btCode);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		double xPos, yPos;
		glfwGetCursorPos(Application::GetInstance().GetWindow(), &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}

}
