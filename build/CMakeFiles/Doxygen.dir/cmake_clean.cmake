FILE(REMOVE_RECURSE
  "CMakeFiles/Doxygen"
  "CMakeFiles/Doxygen-complete"
  "Doxygen-prefix/src/Doxygen-stamp/Doxygen-install"
  "Doxygen-prefix/src/Doxygen-stamp/Doxygen-mkdir"
  "Doxygen-prefix/src/Doxygen-stamp/Doxygen-download"
  "Doxygen-prefix/src/Doxygen-stamp/Doxygen-update"
  "Doxygen-prefix/src/Doxygen-stamp/Doxygen-patch"
  "Doxygen-prefix/src/Doxygen-stamp/Doxygen-configure"
  "Doxygen-prefix/src/Doxygen-stamp/Doxygen-build"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/Doxygen.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
