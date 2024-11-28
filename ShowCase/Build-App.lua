project "ShowCase"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }
   
   SFML_DIR = "D:/01prog/libs/SFML"

   includedirs
   {
      "Source",

      -- Include Core
      "../PhysicsEngine/Source",
      "%{SFML_DIR}/include"      
   }
   
   libdirs {
      "%{SFML_DIR}/lib"
   }
   
   defines {
      "SFML_STATIC"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "WINDOWS" }
      links { "opengl32", "winmm", "gdi32", "ws2_32" }

   -- Debug configuration
   filter "configurations:Debug"
      defines { "DEBUG" }
      defines { "_ITERATOR_DEBUG_LEVEL=2" }
      runtime "Debug"
      symbols "On"
      links {
         "PhysicsEngine",
         "sfml-graphics-s-d",
         "sfml-window-s-d", 
         "sfml-system-s-d",
         "freetype",        
         "opengl32",   
         "winmm",      
         "gdi32"
      }
      buildoptions { "/MDd" }
	  
	  linkoptions {
      "/DEBUG:FULL",
      "/PDB:%{SFML_DIR}/lib/Debug/sfml-graphics-s-d.pdb",
      "/PDB:%{SFML_DIR}/lib/Debug/sfml-window-s-d.pdb",    
      "/PDB:%{SFML_DIR}/lib/Debug/sfml-system-s-d.pdb"     
		}

   -- Release configuration
   filter "configurations:Release"
      defines { "RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"
      links {
         "PhysicsEngine",
         "sfml-graphics-s",
         "sfml-window-s", 
         "sfml-system-s",
         "freetype",        
         "opengl32",   
         "winmm",      
         "gdi32"
      }
      buildoptions { "/MD" }

   -- Distribution configuration
   filter "configurations:Dist"
      defines { "DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"
      links {
         "PhysicsEngine",
         "sfml-graphics-s",
         "sfml-window-s", 
         "sfml-system-s",
         "freetype",        
         "opengl32",   
         "winmm",      
         "gdi32"
      }
      buildoptions { "/MD" }