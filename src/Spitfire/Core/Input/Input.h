#pragma once

#include "Spitfire/Core/Core.h"

#include "KeyboardKey.h"
#include "MouseBt.h"

namespace Spitfire
{

	class Input
	{
	public:
		static bool IsKeyPressed(int keyCode);
		static bool IsMouseBtPressed(int btCode);
		static std::pair<float, float> GetMousePosition();

	public:
		inline static bool IsKeyPressed(KeyboardKey key)	{ return IsKeyPressed((int)key); }
		inline static bool IsMouseBtPressed(MouseBt bt)		{ return IsMouseBtPressed((int)bt); }
		inline static float GetMouseX()						{ return GetMousePosition().first; }
		inline static float GetMouseY()						{ return GetMousePosition().second; };
	};

}
