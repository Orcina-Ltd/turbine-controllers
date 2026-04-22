cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
set(PROJECT BladedControllerWrapper)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

project(${PROJECT} LANGUAGES C CXX)

if (DEFINED ENV{MSYSTEM})
    set(MSYSTEM $ENV{MSYSTEM})
    message(STATUS "MSYS2 environment: ${MSYSTEM}")
    if (MSYSTEM STREQUAL "MSYS")
        message(FATAL_ERROR "You're in the MSYS shell. Use a MinGW shell (e.g. MINGW64/MINGW32).")
    endif()
endif()
if (MSVC)
    message(STATUS "MSVC detected")
endif()

set(SRC src)
set(INCLUDE include)
set(DEF def)

add_library(${PROJECT} SHARED
    ${INCLUDE}/Actuator.hpp
    ${INCLUDE}/OrcFxAPI.h
    ${INCLUDE}/OrcFxAPI_wrapper.hpp
    ${INCLUDE}/OrcFxAPIExplicitLink.h
    ${INCLUDE}/Utils.hpp
    ${SRC}/Actuator.cpp
    ${SRC}/ExtFn.cpp
    ${SRC}/OrcFxAPI_wrapper.cpp
    ${SRC}/OrcFxAPIExplicitLink.c
    ${SRC}/RegisterCapabilities.c
    ${SRC}/Utils.cpp
    ${DEF}/${PROJECT}.def
)

if (MSVC)
    set_property(TARGET ${PROJECT} PROPERTY
        MSVC_RUNTIME_LIBRARY 
        "$<$<CONFIG:Debug>:MultiThreadedDebugDLL>$<$<CONFIG:Release>:MultiThreaded>"
    )
endif()
if (DEFINED MSYSTEM)
    target_link_options(${PROJECT} PRIVATE -static LINKER:--enable-stdcall-fixup)
    set_target_properties(${PROJECT} PROPERTIES IMPORT_PREFIX "")
    set_target_properties(${PROJECT} PROPERTIES PREFIX "")
    add_custom_command(TARGET ${PROJECT} POST_BUILD
        COMMAND ${CMAKE_STRIP} --strip-unneeded $<TARGET_FILE:${PROJECT}>
    )
endif()
# add_custom_command(TARGET ${PROJECT} POST_BUILD
    # COMMAND ${CMAKE_COMMAND} -E copy_if_different
        # $<TARGET_FILE:${PROJECT}>
        # ${CMAKE_SOURCE_DIR}/example/
# )

target_include_directories(${PROJECT} PRIVATE ${INCLUDE})
target_compile_definitions(${PROJECT} PRIVATE UNICODE _UNICODE)
target_compile_features(${PROJECT} PRIVATE cxx_std_20)