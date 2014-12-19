cmake_minimum_required(VERSION 2.8)
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

include_directories(
    ${OpenGL3_INCLUDE_PATH}
    ${GLEW_INCLUDE_PATH}
    ${GLFW3_INCLUDE_PATH}
    ${GLM_INCLUDE_PATH}
	${ASSIMP_INCLUDE_PATH}
	${STB_INCLUDE_PATH}
	${OPENAL_INCLUDE_PATH}
	#${TBB_INCLUDE_PATH}
    ${EXTERNAL_LIBRARY_PATHS}
    ${CMAKE_SOURCE_DIR}/src/libraries/
)

file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADER *.h)

add_definitions(-DSHADERS_PATH="${SHADERS_PATH}")
add_definitions(-DRESOURCES_PATH="${RESOURCES_PATH}")
add_definitions(-DGLFW_INCLUDE_GLCOREARB)
add_definitions(-DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED)

add_executable(${ProjectId} ${SOURCES} ${HEADER})

target_link_libraries(
    ${ProjectId}
    ${ALL_LIBRARIES}
    ${GLFW3_LIB}
    ${GLEW_LIB}
    ${OpenGL3_LIB}
	${ASSIMP_LIB}
	${OPENAL_LIB}
	#${TBB_LIB}
)

#used to delay in build order
add_dependencies(
	${ProjectId}
	glew
	glfw
	glm
	OpenAL
	#TBB
)

IF (MINGW)

	#Copy needed dll files to current bin folder
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  
			${CMAKE_BINARY_DIR}/dependencies/glew/src/glew-build/bin/libglew.dll      
			$<TARGET_FILE_DIR:${PROJECT_NAME}>
		)
		
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  
			${CMAKE_SOURCE_DIR}/dependencies/assimp/libMinGW/libassimp.dll   
			$<TARGET_FILE_DIR:${PROJECT_NAME}>
		)
		

ELSEIF (MSVC)

	#Copy needed dll files to current bin folder
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  
			${CMAKE_BINARY_DIR}/dependencies/glew/src/glew-build/bin/$<CONFIGURATION>/glewd.dll      
			$<TARGET_FILE_DIR:${PROJECT_NAME}>
		)
		
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  
			${CMAKE_SOURCE_DIR}/dependencies/assimp/lib/assimp_release-dll_win32/Assimp32.dll   
			$<TARGET_FILE_DIR:${PROJECT_NAME}>
		)
	
	#copy TBB DLLS
	#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	#	COMMAND ${CMAKE_COMMAND} -E copy_if_different  
	#		${TBB_SOURCE_DIR}/bin/ia32/${_TBB_COMPILER}/tbb.dll   
	#		$<TARGET_FILE_DIR:${PROJECT_NAME}>
	#	)
		
	#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	#	COMMAND ${CMAKE_COMMAND} -E copy_if_different  
	#		${TBB_SOURCE_DIR}/bin/ia32/${_TBB_COMPILER}/tbbmalloc.dll   
	#		$<TARGET_FILE_DIR:${PROJECT_NAME}>
	#	)
		
ENDIF()