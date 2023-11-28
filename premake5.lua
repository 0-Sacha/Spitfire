Solution.Projects["ImGui"] 		= "Dependencies/ImGui"

group "Dependencies"
	include (Solution.Projects["ImGui"])
group ""

if (SpitfireUseVulkan) then
	ProjectEnvVar["VULKAN_SDK"] = {
		"VULKAN_SDK",
		"VK_SDK_PATH"
	 }
	 
	VULKAN_SDK = Solution.GetEnvironementVariable("VULKAN_SDK");
	 
	Solution.ProjectsInfo.Defines["Spitfire"] = {
		"%{VULKAN_SDK}/Include",
		"SPITFIRE_USE_VULKAN"
	}
else
	Solution.ProjectsInfo.Defines["Spitfire"] = {
		"GLEW_STATIC",
		"SPITFIRE_USE_OPENGL"
	}
end

Solution.ProjectsInfo.PlatformDefineName["Spitfire"] = "SPITFIRE"

Solution.ProjectsInfo.IncludeDirs["Spitfire"] = {
	"%{Solution.Projects.Spitfire}/",
	"%{Solution.Projects.Spitfire}/src/",
	"%{Solution.Projects.Spitfire}/Dependencies",
	
	"%{Solution.Projects.Spitfire}/Dependencies/ImGui",
}

project "Spitfire"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"

	targetdir 	(Solution.Path.ProjectTargetDirectory)
    objdir 		(Solution.Path.ProjectObjectDirectory)

	includedirs {
		"%{Solution.Projects.Spitfire}/Dependencies/GLEW/include/",
		"%{Solution.Projects.Spitfire}/Dependencies/GLFW/%{cfg.platform}/include/",
	}

	files {
		"src/Spitfire/**.h",
		"src/Spitfire/**.hpp",
		"src/Spitfire/**.inl",
		"src/Spitfire/**.cpp",
	}

	links {
		"ImGui",

		"Dependencies/GLFW/%{cfg.platform}/lib-vc2019/glfw3_mt",
		"User32.lib",
		"Gdi32.lib",
		"Shell32.lib"
	}

	if (SpitfireUseVulkan) then
		files {
			"src/GraphicsPlatform/Vulkan/**.h",
			"src/GraphicsPlatform/Vulkan/**.hpp",
			"src/GraphicsPlatform/Vulkan/**.inl",
			"src/GraphicsPlatform/Vulkan/**.cpp",
		}

		links {
		}
	else
		files {
			"src/GraphicsPlatform/OpenGL/**.h",
			"src/GraphicsPlatform/OpenGL/**.hpp",
			"src/GraphicsPlatform/OpenGL/**.inl",
			"src/GraphicsPlatform/OpenGL/**.cpp",
		}

		links {
			"Dependencies/GLEW/lib/Release/%{cfg.platform}/glew32s",
			"opengl32.lib",
		}
	end

	Solution.IncludeProject("Spitfire")
	Solution.IncludeAndLinkProject("ProjectCore")
