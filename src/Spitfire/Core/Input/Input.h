#pragma once

#include "Spitfire/Core/Core.h"

#include "KeyboardKey.h"
#include "MouseBt.h"

namespace Spitfire {

	class Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input& other) = delete;
		Input& operator=(const Input& other) = delete;

	public:
		inline static bool IsKeyPressed(int keyCode) { return GetInstance()->IsKeyPressedImpl(keyCode); }
		inline static bool IsKeyPressed(KeyboardKey key) { return GetInstance()->IsKeyPressedImpl((int)key); }

		inline static bool IsMouseBtPressed(int btCode) { return GetInstance()->IsMouseBtPressedImpl(btCode); }
		inline static bool IsMouseBtPressed(MouseBt bt) { return GetInstance()->IsMouseBtPressedImpl((int)bt); }
		inline static std::pair<float, float> GetMousePosition() { return GetInstance()->GetMousePositionImpl(); };
		inline static float GetMouseX() { return GetInstance()->GetMouseXImpl(); };
		inline static float GetMouseY() { return GetInstance()->GetMouseYImpl(); };

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseBtPressedImpl(int btCode) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* GetInstance();
	};

}