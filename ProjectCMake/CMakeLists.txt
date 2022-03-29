cmake_minimum_required (VERSION 3.0)

project (MyProject)

find_package(OpenGL REQUIRED)

add_subdirectory(external)

include_directories(
	external/glfw-3.3.2/include/
	external/glm/
	external/glew-2.1.0/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_210
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)
file(GLOB COMMON Common/*)
file(GLOB ALLSCRIPT Script/*)
add_executable(MyProject 
	${COMMON}
	${ALLSCRIPT}

	Object/TransformVertexShader.vertexshader
	Object/TextureFragmentShader.fragmentshader)
target_link_libraries(MyProject ${ALL_LIBS})
set_property(TARGET MyProject PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Object")
SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(Script REGULAR_EXPRESSION ".*/Script/.*" )