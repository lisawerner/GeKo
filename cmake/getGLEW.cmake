set(glew_PREFIX "${DEPENDENCIES_PATH}/glew")
set(glew_INSTALL_DIR "${DEPENDENCIES_PATH}/glew")
set(glew_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${glew_INSTALL_DIR})
	   
ExternalProject_Add (
    glew
	PREFIX ${glew_PREFIX}
    GIT_REPOSITORY "https://github.com/fungos/glew-cmake"
    GIT_TAG "master"
	INSTALL_DIR ${glew_INSTALL_DIR}
    UPDATE_COMMAND ""
    INSTALL_COMMAND "" 
	CMAKE_ARGS ${glew_CMAKE_ARGS}
)

IF (MINGW)
	set(GLEW_INCLUDE_PATH "${DEPENDENCIES_PATH}/glew/src/glew/include")
	set(GLEW_LIB "${DEPENDENCIES_PATH}/glew/src/glew-build/lib/liblibglew_shared.dll.a")
	
ELSEIF (MSVC)
    set(GLEW_INCLUDE_PATH "${DEPENDENCIES_PATH}/glew/src/glew/include")
	set(GLEW_LIB "${DEPENDENCIES_PATH}/glew/src/glew-build/lib/$<CONFIGURATION>/libglew_sharedd.lib")
	
#ELSEIF(APPLE)

    #set(GLEW_INCLUDE_PATH "${DEPENDENCIES_PATH}/glew/src/glew/include")
	#set(GLEW_LIB "${DEPENDENCIES_PATH}/glew/src/glew-build/lib/$<CONFIGURATION>/libglew_sharedd.lib")

ELSEIF("${CMAKE_SYSTEM}" MATCHES "Linux")
	set(GLEW_INCLUDE_PATH "${DEPENDENCIES_PATH}/glew/src/glew/include")
	set(GLEW_LIB "${DEPENDENCIES_PATH}/glew/src/glew-build/lib/libglew.a")

ELSE()
	set(GLEW_INCLUDE_PATH "${DEPENDENCIES_PATH}/glew/src/glew/include")
	set(GLEW_LIB "${DEPENDENCIES_PATH}/glew/src/glew-build/lib/liblibglew_shared.dll.a")

ENDIF ()
