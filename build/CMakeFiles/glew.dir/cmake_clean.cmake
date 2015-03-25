FILE(REMOVE_RECURSE
  "CMakeFiles/glew"
  "CMakeFiles/./glew-complete"
  "dependencies/glew/src/glew-stamp/./glew-install"
  "dependencies/glew/src/glew-stamp/./glew-mkdir"
  "dependencies/glew/src/glew-stamp/./glew-download"
  "dependencies/glew/src/glew-stamp/./glew-update"
  "dependencies/glew/src/glew-stamp/./glew-patch"
  "dependencies/glew/src/glew-stamp/./glew-configure"
  "dependencies/glew/src/glew-stamp/./glew-build"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/glew.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
