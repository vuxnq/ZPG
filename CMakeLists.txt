cmake_minimum_required(VERSION 3.30)
project(ZPG)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# By default CONFIG (which is set by -DCMAKE_BUILD_TYPE=DEBUG
# or -DCMAKE_BUILD_TYPE=RELEASE) is set to DEBUG
add_compile_options(
#        -Wall
#        -Wextra
#        -Wconversion
#        -pedantic
        $<$<CONFIG:DEBUG>:-g3>
        $<$<CONFIG:DEBUG>:-Og>
        $<$<CONFIG:RELEASE>:-O3>
)

if (NOT DISABLE_ASAN AND $<CONFIG:DEBUG>)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
endif()

file(GLOB_RECURSE sandbox_headers "src/**.h")
file(GLOB_RECURSE sandbox_sources "src/**.cpp")

add_executable(ZPG
        ${sandbox_headers}
        ${sandbox_sources}
        # src/PCH.h
)

target_include_directories(ZPG PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)

# target_precompile_headers(ZPG PUBLIC src/PCH.h)

target_compile_definitions(ZPG
        PUBLIC $<$<CONFIG:DEBUG>:SANDBOX_ENABLE_ASSERTS>
        PUBLIC $<$<CONFIG:DEBUG>:SANDBOX_ENABLE_LOGGING>
        PUBLIC $<$<CONFIG:DEBUG>:SANDBOX_OPENGL_CALL_ERROR_CHECK>
        # PUBLIC SANDBOX_ENABLE_PROFILING
        PUBLIC SANDBOX_FUNCTION_CURRYING_USE_LAMBDA
        PUBLIC GLFW_INCLUDE_NONE
)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLFW3 REQUIRED glfw3)
target_link_libraries(ZPG PUBLIC glfw)

find_package(glm REQUIRED)
target_link_libraries(ZPG PUBLIC glm::glm)

# add_subdirectory(vendor/glad)
# target_link_libraries(ZPG PUBLIC glad)

find_package(OpenGL REQUIRED)
target_link_libraries(ZPG PUBLIC OpenGL::GL)
find_package(GLEW REQUIRED)
target_link_libraries(ZPG PUBLIC GLEW::glew)



add_custom_target(run
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR} $<TARGET_FILE:ZPG>
        DEPENDS ZPG
)