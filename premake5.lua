
Solution.Projects["Spitfire"].PlatformDefineName = "SPITFIRE"
Solution.Projects["Spitfire"].Type = "StaticLib"
Solution.Projects["Spitfire"].IncludeDirs = {
	"%{Solution.Projects.Spitfire.Path}/",
	"%{Solution.Projects.Spitfire.Path}/src/",
	"%{Solution.Projects.Spitfire.Path}/Dependencies",
	
	"%{Solution.Projects.Spitfire.Path}/Dependencies/ImGui",
}
Solution.Projects["Spitfire"].ProjectDependencies = {
	"ProjectCore",
	"ImGui"
}

Solution.AddProject("ImGui", "Dependencies/ImGui")
group "Dependencies"
	include (Solution.Projects["ImGui"].Path)
group ""

if (SpitfireUseVulkan) then
	VULKAN_SDK_ENVVAR = {
		"VULKAN_SDK",
		"VK_SDK_PATH"
	}
	 
	VULKAN_SDK = Solution.GetEnvironementVariable("VULKAN_SDK", VULKAN_SDK_ENVVAR);
	 
	Solution.Projects["Spitfire"].Defines = {
		"%{VULKAN_SDK}/Include",
		"SPITFIRE_USE_VULKAN"
	}
else
	Solution.Projects["Spitfire"].Defines = {
		"GLEW_STATIC",
		"SPITFIRE_USE_OPENGL"
	}
end

project "Spitfire"
	kind 		(Solution.Projects["Spitfire"].Type)
	language "C++"
	cppdialect "C++20"

	targetdir 	(Solution.Path.ProjectTargetDirectory)
    objdir 		(Solution.Path.ProjectObjectDirectory)

	includedirs {
		"%{Solution.Projects.Spitfire.Path}/Dependencies/GLEW/include/",
		"%{Solution.Projects.Spitfire.Path}/Dependencies/GLFW/%{cfg.platform}/include/",
	}

	files {
		"src/Spitfire/**.h",
		"src/Spitfire/**.hpp",
		"src/Spitfire/**.inl",
		"src/Spitfire/**.cpp",
	}

	links {
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

	Solution.Project("Spitfire")
