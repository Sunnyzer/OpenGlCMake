if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
	add_definitions( "/MP" )
endif()

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

### GLFW ###

add_subdirectory (glfw-3.3.2)
add_subdirectory (glm)
include_directories(
	glfw-3.3.2/include/GLFW/
	glew-2.1.0/include/
)

### GLEW ###

set(GLEW_SOURCE
	glfw-3.3.2/include/GLFW/
	glew-2.1.0/src/glew.c
)

add_library( GLEW_210 STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
)

target_link_libraries(GLEW_210
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)