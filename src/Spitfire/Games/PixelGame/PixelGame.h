#pragma once

#include "Spitfire/Renderer/Renderer.h"

namespace Spitfire::Games
{
	/* Buffer => colums of rows  (x => height; y => width)*/
	class PixelGame {
	public:
		PixelGame(const std::string& name, int width, int height, uint8_t pixelSize, int bpp, const std::string& shaderPath = "");
		PixelGame(std::string&& name, int width, int height, uint8_t pixelSize, int bpp, const std::string& shaderPath = "");
		void AlwaysEngine();

	public:
		virtual void Frame(float delta) = 0;

	public:
		inline uint8_t* GetCurrentBuffer() { return m_Buffers[m_CurrentIdBuffer]; };
		inline uint8_t GetCurrentBufferId() { return m_CurrentIdBuffer; };
		inline uint8_t* GetBuffer(uint8_t id) { return m_Buffers[id]; };

		inline void SetBuffer(uint8_t bufferID) { m_CurrentIdBuffer = bufferID; };
		inline void SwapBuffer() { m_CurrentIdBuffer = (m_CurrentIdBuffer == 0 ? 1 : 0); };

		inline void SetPixelCurrent(int x, int y, uint8_t pix) { m_Buffers[m_CurrentIdBuffer][x * m_Width + y] = pix; };
		inline uint8_t GetPixelCurrent(int x, int y) { return m_Buffers[m_CurrentIdBuffer][x * m_Width + y]; };
		inline uint8_t GetPixelOther(int x, int y) { return m_Buffers[(m_CurrentIdBuffer == 0 ? 1 : 0)][x * m_Width + y]; };
		inline void SetPixelId(uint8_t id, int x, int y, uint8_t pix) { m_Buffers[id][x * m_Width + y] = pix; };
		inline uint8_t GetPixelId(uint8_t id, int x, int y) { return m_Buffers[id][x * m_Width + y]; };


	private:
		//Don't use this one
		inline void SetPixelOther(int x, int y, uint8_t pix) { m_Buffers[(m_CurrentIdBuffer == 0 ? 1 : 0)][x * m_Height + y] = pix; };

	public:
		inline int GetWidth() { return m_Width; };
		inline int GetHeight() { return m_Height; };
		inline int GetBPP() { return m_BPP; };
		inline EngineCore::LoggerManager::BasicLogger& Logger() { return m_Logger; };

	private:
		void GetShader(const std::string& shaderPath);
		glm::mat4 GetModelMatrix();
		void OnResize();
		static const size_t GetTime();

	protected:
		void Clear(const uint8_t value);
		void Draw();
		inline void SetPrintFPS(bool value = true) { m_PrintFPS = value; };
		void InitPixelGame(const std::string& shaderPath);

	private:
		std::string m_Name;
		int m_Width, m_Height, m_BPP;
		uint8_t m_PixelSize;
		size_t m_Size;

	private:
		bool m_PrintFPS;
		uint8_t m_CurrentIdBuffer;
		uint8_t* m_Buffers[2];
		EngineCore::LoggerManager::BasicLogger m_Logger;

	private:
		VertexArray* m_VertexArray;
		IndexBuffer* m_IndexBuffer;
		VertexBuffer* m_VertexBuffer;
		Texture* m_Texture;
		Shader* m_Shader;

		unsigned int m_RendererID;
		glm::vec3 m_Translation;
		glm::vec3 m_Scale;
	};

}
