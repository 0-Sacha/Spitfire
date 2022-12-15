
ProjectPublicDefines["PixelEngine"] = {
	"GLEW_STATIC"
}

ProjectPublicIncludes["PixelEngine"] = {
	"%{wks.location}/PixelEngine/src/",
	"%{wks.location}/PixelEngine/src/vendor/",
	"%{wks.location}/PixelEngine/Dependencies/GLEW/include/",
	"%{wks.location}/PixelEngine/Dependencies/GLFW/%{cfg.platform}/include/"
}

ProjectPublicLinks["PixelEngine"] = {
	"Dependencies/GLFW/%{cfg.platform}/lib-vc2019",
	"Dependencies/GLEW/lib/Release/%{cfg.platform}",
	"glew32s.lib",
	"glfw3.lib",
	"opengl32.lib",
	"User32.lib",
	"Gdi32.lib",
	"Shell32.lib"
}

project "PixelEngine"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"


	targetdir 	(project_targetdir .. "/%{prj.name}")
	objdir 		(project_objdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.hpp",
		"src/**.inl",
		"src/**.cpp",
	}

	IncludeProject("PixelEngine")
	IncludeAndLinkProject("EngineCore")

	filter "system:windows"
        postbuildcommands {
			("{COPY} " .. project_targetdir .. "/%{prj.name} ../%{PixelEngine_AppTarget}")
		}
