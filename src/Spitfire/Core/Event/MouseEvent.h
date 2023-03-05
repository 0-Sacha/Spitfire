#pragma once

#include "Event.h"
#include "Spitfire/Core/Input/MouseBt.h"


// MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled

namespace Spitfire
{
	class MouseEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategory_Input | EventCategory_Mouse)
	};

	class MouseMouvedEvent : public MouseEvent
	{
	public:
		MouseMouvedEvent(float x, float y)
			: m_X(x), m_Y(y) { }

		inline float GetX() const { return m_X; }
		inline float GetY() const { return m_Y; }

		std::string ToString() const override {
			std::string str;
			EngineCore::FMT::FormatInString(str, "MouseMoved: {}, {}", m_X, m_Y);
			return str;
		}

		EVENT_CLASS_TYPE(MouseMoved)

	private:
		float m_X;
		float m_Y;
	};

	class MouseScrolledEvent : public MouseEvent
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) { }
		
		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override {
			std::string str;
			EngineCore::FMT::FormatInString(str, "MouseScrolled: {}, {}", m_XOffset, m_YOffset);
			return str;
		}

		EVENT_CLASS_TYPE(MouseScrolled)

	private:
		float m_XOffset;
		float m_YOffset;
	};

	class MouseButtonEvent : public MouseEvent
	{
	public:
		inline int GetBtCode() const{ return m_BtCode; }
		inline MouseBt GetMouseBt() const { return (MouseBt)m_BtCode; }

	protected:
		MouseButtonEvent(int btCode)
			: m_BtCode(btCode) { }

		MouseButtonEvent(MouseBt bt)
			: m_BtCode((int)bt) { }

		int m_BtCode;
	};


	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) { }

		std::string ToString() const override {
			std::string str;
			EngineCore::FMT::FormatInString(str, "MouseButtonPressed: {}", m_BtCode);
			return str;
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) { }

		std::string ToString() const override {
			std::string str;
			EngineCore::FMT::FormatInString(str, "MouseButtonReleased: {}", m_BtCode);
			return str;
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
