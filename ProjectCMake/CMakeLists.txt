cmake_minimum_required (VERSION 3.0)

project (MyProject)

find_package(OpenGL REQUIRED)

add_subdirectory(external)

include_directories(
	external/glfw-3.3.2/include/
	external/glm/
	external/glew-2.1.0/include/
	external/enet-1.3.17/include/
	Script/Engine/
	Script/Engine/Physics/
	Script/MonoBehaviour/
	Script/Online/
	Script/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_210
	enet
	ws2_32
	winmm
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)
file(GLOB COMMON Common/*)
file(GLOB SCRIPT Script/*)
file(GLOB ENGINE Script/Engine/*)
file(GLOB MONOBEHAVIOUR Script/MonoBehaviour/*)
file(GLOB ONLINE Script/Online/*)
file(GLOB PHYSICS Script/Engine/Physics/*)
add_executable(MyProject 
	${COMMON}
	${SCRIPT}
	${ENGINE}
	${MONOBEHAVIOUR}
	${ONLINE}
	${PHYSICS}

	Object/TransformVertexShader.vertexshader
	Object/TextureFragmentShader.fragmentshader)
target_link_libraries(MyProject ${ALL_LIBS})
set_property(TARGET MyProject PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Object")
SOURCE_GROUP(Common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(Script REGULAR_EXPRESSION ".*/Script/.*" )
SOURCE_GROUP(Script/Engine REGULAR_EXPRESSION ".*/Script/Engine/.*" )
SOURCE_GROUP(Script/MonoBehaviour REGULAR_EXPRESSION ".*/Script/MonoBehaviour/.*")
SOURCE_GROUP(Script/Online REGULAR_EXPRESSION ".*/Script/Online/.*")
SOURCE_GROUP(Script/Engine/Physics REGULAR_EXPRESSION ".*/Script/Engine/Physics/.*")