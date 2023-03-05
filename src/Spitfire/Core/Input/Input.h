#pragma once

#include "Spitfire/Core/Core.h"

#include "KeyboardKey.h"
#include "MouseBt.h"

namespace Spitfire
{

	class Input
	{
	public:
		inline static bool IsKeyPressed(int keyCode);
		inline static bool IsMouseBtPressed(int btCode);
		inline static std::pair<float, float> GetMousePosition();

	public:
		inline static bool IsKeyPressed(KeyboardKey key)	{ return IsKeyPressed((int)key); }
		inline static bool IsMouseBtPressed(MouseBt bt)		{ return IsMouseBtPressed((int)bt); }
		inline static float GetMouseX()						{ return GetMousePosition().first; }
		inline static float GetMouseY()						{ return GetMousePosition().second; };
	};

}
