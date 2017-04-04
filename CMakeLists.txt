cmake_minimum_required(VERSION 3.6)
project(OpenGLSample)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/GLHelper.cpp
        src/GLProgram.cpp
        res/Cube.cpp res/Cube.h)

find_package(
        OpenGL REQUIRED
)

link_libraries(
        # mac
        ${OPENGL_LIBRARY}
        glfw glew
        /usr/local/lib/libSOIL.a
        CoreFoundation

        #linux
#        GL
#        glfw3 GLEW
#        Xxf86vm
#        SOIL
#        dl X11 Xrandr Xinerama Xcursor
#        pthread
)

add_executable(OpenGLSample ${SOURCE_FILES})