#pragma once

#include "Spitfire/Core/Core.h"
#include "Spitfire/Core/Application/Application.h"

namespace Spitfire
{
	class ApplicationVulkan: public Application
	{
	public:
		ApplicationVulkan(const std::string& name, std::uint32_t width = 1280, std::uint32_t height = 720);
		~ApplicationVulkan() override;

	public:
		void Run() override;

		VkInstance GetInstance();
		VkPhysicalDevice GetPhysicalDevice();
		VkDevice GetDevice();

	private:
		void Create();
		void Destroy();
	};
}
