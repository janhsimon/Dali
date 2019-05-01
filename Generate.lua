-- make sure this path is correct on your system
qt = "E:/Qt/5.12.3/msvc2017_64"

workspace "Dali"
  architecture "x64"
  configurations { "Debug", "Release" }
  startproject "Editor"

  include "Editor/Editor.lua"