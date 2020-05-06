cmake_minimum_required(VERSION 2.8)
project(test)

if(EMSCRIPTEN)
    message("compile emscripten")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_WEBGL2=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FULL_ES3=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_MEMORY_GROWTH=1")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ERROR_ON_UNDEFINED_SYMBOLS=0")
else()
    include_directories("C:/Libs/glew-2.1.0/include" "C:/Libs/GLFW/include")
endif()

_add_executable(index src/main.cpp)


#Add VTK
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

_target_link_libraries(index
  PRIVATE
  ${VTK_LIBRARIES}
)


if(NOT EMSCRIPTEN)
    target_link_libraries(index 
        "C:/Libs/glew-2.1.0/lib/Release/x64/glew32.lib" 
        "C:/Libs/glew-2.1.0/lib/Release/x64/glew32s.lib" 
        "C:/Libs/GLFW/lib/glfw3.lib"
        opengl32
        )
        
endif()