set(assimp_PREFIX "${DEPENDENCIES_PATH}/assimp")
set(assimp_INSTALL_DIR "${DEPENDENCIES_PATH}/assimp")
set(assimp_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${assimp_INSTALL_DIR}
					  #-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
					  #-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
					  #-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                      #-DCMAKE_DEBUG_POSTFIX=d
                      -DASSIMP_ENABLE_BOOST_WORKAROUND=ON
                      -DASSIMP_BUILD_ASSIMP_TOOLS=OFF
                      -DASSIMP_BUILD_TESTS=OFF
					  -DASSIMP_BUILD_SAMPLES=OFF
					  -DASSIMP_BUILD_NO_IFC_IMPORTER=ON
    )
	
	
ExternalProject_Add (
    assimp
	PREFIX ${assimp_PREFIX}
    GIT_REPOSITORY "https://github.com/assimp/assimp"
    GIT_TAG "master"
	INSTALL_DIR ${assimp_INSTALL_DIR}
    UPDATE_COMMAND ""
    INSTALL_COMMAND "" 
	CMAKE_ARGS ${assimp_CMAKE_ARGS}
)

IF (MINGW)

	set(ASSIMP_INCLUDE_PATH "${DEPENDENCIES_PATH}/assimp/src/assimp/include")

ELSEIF (MSVC)

    set(ASSIMP_INCLUDE_PATH "${DEPENDENCIES_PATH}/assimp/src/assimp/include")

#ELSEIF(APPLE)

    #set(ASSIMP_INCLUDE_PATH "${DEPENDENCIES_PATH}/glfw/src/glfw/include")

ELSEIF("${CMAKE_SYSTEM}" MATCHES "Linux")
	set(ASSIMP_INCLUDE_PATH "${DEPENDENCIES_PATH}/assimp/src/assimp/include")

ELSE()
	set(ASSIMP_INCLUDE_PATH "${DEPENDENCIES_PATH}/assimp/src/assimp/include")
	
ENDIF ()
