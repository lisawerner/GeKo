FILE(REMOVE_RECURSE
  "CMakeFiles/glfw"
  "CMakeFiles/./glfw-complete"
  "dependencies/glfw/src/glfw-stamp/./glfw-install"
  "dependencies/glfw/src/glfw-stamp/./glfw-mkdir"
  "dependencies/glfw/src/glfw-stamp/./glfw-download"
  "dependencies/glfw/src/glfw-stamp/./glfw-update"
  "dependencies/glfw/src/glfw-stamp/./glfw-patch"
  "dependencies/glfw/src/glfw-stamp/./glfw-configure"
  "dependencies/glfw/src/glfw-stamp/./glfw-build"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/glfw.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
