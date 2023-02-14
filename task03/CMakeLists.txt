cmake_minimum_required(VERSION 3.0.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(SRC_HEADERS ../ext/pch.h CLinkedList.h)
set(SRC_SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SRC_HEADERS} ${SRC_SOURCES})
target_precompile_headers(${PROJECT_NAME} PUBLIC ../ext/pch.h)
