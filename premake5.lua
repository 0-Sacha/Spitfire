
Solution.Projects["ImGui"] 		= "Dependencies/imgui"

group "Dependencies"
	include (Solution.Projects["ImGui"])
group ""

Solution.ProjectsInfo.Defines["Spitfire"] = {
	"GLEW_STATIC",
	"SPITFIRE_USE_OPENGL"
}

Solution.ProjectsInfo.Includes["Spitfire"] = {
	"%{Solution.Projects.Spitfire}/",
	"%{Solution.Projects.Spitfire}/src/",

	"%{Solution.Projects.Spitfire}/Dependencies",
	"%{Solution.Projects.Spitfire}/Dependencies/GLEW/include/",
	"%{Solution.Projects.Spitfire}/Dependencies/GLFW/%{cfg.platform}/include/",
	"%{Solution.Projects.Spitfire}/Dependencies/ImGui",
	"%{Solution.Projects.Spitfire}/Dependencies/glm",
	"%{Solution.Projects.Spitfire}/Dependencies/stb_image"
}

project "Spitfire"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	pchheader "Spitfirepch.h"
	pchsource "src/Spitfirepch.cpp"

	targetdir 	(Solution.Path.ProjectTargetDirectory)
    objdir 		(Solution.Path.ProjectObjectDirectory)

	files {
		"src/**.h",
		"src/**.hpp",
		"src/**.inl",
		"src/**.cpp",
	}

	Solution.IncludeProject("Spitfire")
	Solution.IncludeAndLinkProject("EngineCore")

	links {
		"Dependencies/GLFW/%{cfg.platform}/lib-vc2019/glfw3_mt",
		"Dependencies/GLEW/lib/Release/%{cfg.platform}/glew32s",
		"ImGui",

		"opengl32.lib",
		"User32.lib",
		"Gdi32.lib",
		"Shell32.lib"
	}
