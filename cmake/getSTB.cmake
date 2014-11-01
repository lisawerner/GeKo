set(stb_DOWNLOAD_PATH "${DEPENDENCIES_PATH}/Stb/stb_image.h")
	
if (NOT EXISTS "${stb_DOWNLOAD_PATH}")
	set(stb_URL "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h")
	file(DOWNLOAD  "${stb_URL}" "${stb_DOWNLOAD_PATH}")
endif()
	
set(STB_INCLUDE_PATH "${DEPENDENCIES_PATH}/Stb/")

