project "Editor"
  kind "ConsoleApp"
  language "C++"
  files { "Editor.lua", "Resources/**.qrc", "Resources/Icons/**.svg", "Resources/Styles/**.css", "Source/**.*" }
  objdir "Temp/%{cfg.buildcfg}"
  targetdir "Bin/%{cfg.buildcfg}"
  debugdir "Bin/%{cfg.buildcfg}"

  require "External/premake-qt/qt"

  premake.extensions.qt.enable()
  qtpath(qt)
  qtmodules { "core", "gui", "svg", "widgets" }
  qtprefix "Qt5"

  filter "Debug"
    defines "DEBUG"
    symbols "On"
    qtsuffix "d"

  filter "Release"
    optimize "On"
  

  -- windows

  filter "system:windows"
    cppdialect "c++17"
    staticruntime "On"
    systemversion "latest"

  filter { "system:windows", "Debug" }
    postbuildcommands
    {
      ("{COPY} " .. qt .. "/bin/Qt5Cored.dll Bin/%{cfg.buildcfg}"),
      ("{COPY} " .. qt .. "/bin/Qt5Guid.dll Bin/%{cfg.buildcfg}"),
      ("{COPY} " .. qt .. "/bin/Qt5Svgd.dll Bin/%{cfg.buildcfg}"),
      ("{COPY} " .. qt .. "/bin/Qt5Widgetsd.dll Bin/%{cfg.buildcfg}")
    }

  filter { "system:windows", "Release" }  
    postbuildcommands
    {
      ("{COPY} " .. qt .. "/bin/Qt5Core.dll Bin/%{cfg.buildcfg}"),
      ("{COPY} " .. qt .. "/bin/Qt5Gui.dll Bin/%{cfg.buildcfg}"),
      ("{COPY} " .. qt .. "/bin/Qt5Svg.dll Bin/%{cfg.buildcfg}"),
      ("{COPY} " .. qt .. "/bin/Qt5Widgets.dll Bin/%{cfg.buildcfg}")
    }