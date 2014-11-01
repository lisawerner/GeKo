IF (WIN32)

	set(opengl_DOWNLOAD_PATH "${DEPENDENCIES_PATH}/OpenGL/GL/glcorearb.h")
	
	if (NOT EXISTS "${opengl_DOWNLOAD_PATH}")
		set(opengl_URL "http://www.opengl.org/registry/api/glcorearb.h")
		file(DOWNLOAD  "${opengl_URL}" "${opengl_DOWNLOAD_PATH}")
	endif()
	
	set(OpenGL3_INCLUDE_PATH "${DEPENDENCIES_PATH}/OpenGL/")
	set(OpenGL3_LIB OpenGL32)

#ELSEIF(APPLE)

ELSEIF("${CMAKE_SYSTEM}" MATCHES "Linux")

	set(opengl_DOWNLOAD_PATH "${DEPENDENCIES_PATH}/OpenGL/GL/glcorearb.h")
	
	if (NOT EXISTS "${opengl_DOWNLOAD_PATH}")
		set(opengl_URL "http://www.opengl.org/registry/api/glcorearb.h")
		file(DOWNLOAD  "${opengl_URL}" "${opengl_DOWNLOAD_PATH}")
	endif()
	
	SET(OpenGL3_INCLUDE_PATH "${DEPENDENCIES_PATH}/OpenGL/")
	SET(OpenGL3_LIB "GL" CACHE STRING "OpenGL lib for Linux")
    	

ENDIF ()
