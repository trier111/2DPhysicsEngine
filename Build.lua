-- premake5.lua
workspace "2DPhysicsEngineProject"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "ShowCase"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "PhysicsEngine/Build-Core.lua"
group ""

include "ShowCase/Build-App.lua"