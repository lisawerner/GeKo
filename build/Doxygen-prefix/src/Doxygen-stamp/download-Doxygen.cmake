message(STATUS "downloading...
     src='http://ftp.stack.nl/pub/users/dimitri/doxygen-1.8.8.linux.bin.tar.gz'
     dst='/home/maik/projects/lisa_geko/GeKo/build/Doxygen-prefix/src/doxygen-1.8.8.linux.bin.tar.gz'
     timeout='none'")




file(DOWNLOAD
  "http://ftp.stack.nl/pub/users/dimitri/doxygen-1.8.8.linux.bin.tar.gz"
  "/home/maik/projects/lisa_geko/GeKo/build/Doxygen-prefix/src/doxygen-1.8.8.linux.bin.tar.gz"
  SHOW_PROGRESS
  # no EXPECTED_HASH
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://ftp.stack.nl/pub/users/dimitri/doxygen-1.8.8.linux.bin.tar.gz' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")
