project "Editor"
  kind "ConsoleApp"
  language "C++"
  files { "Editor.lua", "Resources/**.qrc", "Source/**.*" }
  objdir "Temp/%{cfg.buildcfg}"
  targetdir "Bin/%{cfg.buildcfg}"
  debugdir "Bin/%{cfg.buildcfg}"

  require "External/premake-qt/qt"

  premake.extensions.qt.enable()
  qtpath(qt)
  qtmodules { "core", "gui", "widgets" }
  qtprefix "Qt5"
  
  filter "system:windows"
    cppdialect "c++17"
    staticruntime "On"
    systemversion "latest"

  filter "Debug"
    defines "DEBUG"
    symbols "On"
    qtsuffix "d"

  filter "Release"
    optimize "On"
  
  filter { "Debug", "system:windows" }
    postbuildcommands
    {
      ("{COPY} " .. qt .. "/bin/Qt5Cored.dll Bin/%{cfg.buildcfg}"),
      ("{COPY} " .. qt .. "/bin/Qt5Guid.dll Bin/%{cfg.buildcfg}"),
      ("{COPY} " .. qt .. "/bin/Qt5Widgetsd.dll Bin/%{cfg.buildcfg}")
    }

  filter { "Release", "system:windows" }  
    postbuildcommands
    {
      ("{COPY} " .. qt .. "/bin/Qt5Core.dll Bin/"),
      ("{COPY} " .. qt .. "/bin/Qt5Gui.dll Bin/"),
      ("{COPY} " .. qt .. "/bin/Qt5Widgets.dll Bin/")
    }