#pragma once

#include "OrthographicCamera.h"

#include "Spitfire/Core/TimeStep.h"

#include "Spitfire/Event/ApplicationEvent.h"
#include "Spitfire/Event/MouseEvent.h"

namespace Spitfire::Utils {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool hasRotation = false);

	public:
		void OnUpdate(TimeStep ts);
		void OnEvent(Event& event);

		OrthographicCamera GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_HasRotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
	};

}