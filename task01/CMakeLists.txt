cmake_minimum_required(VERSION 3.0.0)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
configure_file(version.h.in version.h)

set(PROJECT_NAME_TEST ${PROJECT_NAME}_test)
set(PROJECT_LIB_NAME ${PROJECT_NAME}_lib)

# lib
add_library(${PROJECT_LIB_NAME} lib.cpp)
target_include_directories(${PROJECT_LIB_NAME} PRIVATE "${CMAKE_BINARY_DIR}/task01")

# cli
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIB_NAME})

# test
add_executable(${PROJECT_NAME_TEST} test_version.cpp)
set_target_properties(${PROJECT_NAME_TEST} PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME_TEST} PUBLIC ${Boost_LIBRARIES} PRIVATE ${PROJECT_LIB_NAME})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)
include (CPack)
#enable_testing()
#add_test(${PROJECT_NAME_TEST} ${PROJECT_NAME_TEST})
