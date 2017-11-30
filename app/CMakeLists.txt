# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# app glue, use native activity
add_library(
    app-glue
    STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# GVR libraries
# gvr library path
MESSAGE(STATUS "Source dir: ${CMAKE_SOURCE_DIR}")
set(
    GVR_JNILIB_DIR
    ${CMAKE_SOURCE_DIR}/../gvr-libraries/jni)

# gvr base
add_library(
    gvr-base
    SHARED
    IMPORTED)
set_target_properties(
    gvr-base PROPERTIES IMPORTED_LOCATION
    ${GVR_JNILIB_DIR}/${ANDROID_ABI}/libgvr.so)

# GVR audio
add_library(
    gvr-audio
    SHARED
    IMPORTED)
set_target_properties(
    gvr-audio PROPERTIES IMPORTED_LOCATION
    ${GVR_JNILIB_DIR}/${ANDROID_ABI}/libgvr_audio.so)

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(
    CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library( # Sets the name of the library.
             native-app

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/util/Log.h
             src/main/cpp/engine/Engine.cpp
             src/main/cpp/main_activity.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# include 文件查找路径
target_include_directories(
    native-app
    PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
target_link_libraries( # Specifies the target library.
                        native-app
                        app-glue
                        gvr-base
                        android
                        EGL
                        GLESv3

                        # Links the target library to the log library
                        # included in the NDK.
                        ${log-lib} )