

#include "OrthographicCameraController.h"
#include "Spitfire/Core/Input/Input.h"

namespace Spitfire::Utils {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool hasRotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_HasRotation(hasRotation)
	{
	}

	void OrthographicCameraController::OnUpdate(TimeStep ts)
	{
		#define OCC_ONUPDATE_SIN sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts
		#define OCC_ONUPDATE_COS cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts

		if(Input::IsKeyPressed(KeyboardKey::A)) {
			m_CameraPosition.x -= OCC_ONUPDATE_COS;
			m_CameraPosition.y -= OCC_ONUPDATE_SIN;
		} else if(Input::IsKeyPressed(KeyboardKey::D)) {
			m_CameraPosition.x += OCC_ONUPDATE_COS;
			m_CameraPosition.y += OCC_ONUPDATE_SIN;
		} else if (Input::IsKeyPressed(KeyboardKey::W)) {
			m_CameraPosition.x -= OCC_ONUPDATE_SIN;
			m_CameraPosition.y += OCC_ONUPDATE_COS;
		} else if (Input::IsKeyPressed(KeyboardKey::S)) {
			m_CameraPosition.x += OCC_ONUPDATE_SIN;
			m_CameraPosition.y -= OCC_ONUPDATE_COS;
		}

		if(m_HasRotation)
		{
			if (Input::IsKeyPressed(KeyboardKey::Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(KeyboardKey::E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel; // ?
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(SPITFIRE_BIND_EVENT(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(SPITFIRE_BIND_EVENT(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_ZoomLevel -= event.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
	{
		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}