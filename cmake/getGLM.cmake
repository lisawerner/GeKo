set(glm_PREFIX "${DEPENDENCIES_PATH}/glm")
set(glm_INSTALL_DIR "${DEPENDENCIES_PATH}/glm")
set(glm_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${glm_INSTALL_DIR})

if("${CMAKE_SYSTEM}" MATCHES "Linux")
  set(glm_GIT_TAG "0.9.6")

else()
  set(glm_GIT_TAG "0.9.5.4")

endif()

ExternalProject_Add (
    glm
    PREFIX ${glm_PREFIX}
    GIT_REPOSITORY "https://github.com/g-truc/glm"
    GIT_TAG ${glm_GIT_TAG}
    INSTALL_DIR ${glm_INSTALL_DIR}
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
    CMAKE_ARGS ${glm_CMAKE_ARGS}
)

set(GLM_INCLUDE_PATH "${DEPENDENCIES_PATH}/glm/src/glm")
