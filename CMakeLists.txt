cmake_minimum_required (VERSION 3.8)
project ("Engine")

add_subdirectory (external/glew)
add_subdirectory (external/glfw)
add_subdirectory (external/glm)
add_subdirectory (Engine)

target_include_directories (Engine PRIVATE external/glew/include external/glfw/include external/glm)
