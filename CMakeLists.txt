cmake_minimum_required(VERSION 3.0.0)

set(PATCH_VERSION 1 CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

set(BUILD_TASK1 ON)    # done
set(BUILD_TASK2 OFF)
set(BUILD_TASK3 OFF)    # done
set(BUILD_TASK4 OFF)

# 01 - hello_world
if (${BUILD_TASK1})
    project(hello_world VERSION ${PROJECT_VERSION})
    
    add_subdirectory(task01 task01)
    message("01 - hello_world build enabled")
    set_property(TARGET hello_world PROPERTY CXX_STANDARD 17)
    set_property(TARGET hello_world PROPERTY CXX_STANDARD 17)
endif()

# 02 - ip_filter
if (${BUILD_TASK2})
    project(ip_filter VERSION ${PROJECT_VERSION})
    add_subdirectory(task02 task02)
    message("02 - ip_filter build enabled")
    set_property(TARGET ip_filter PROPERTY CXX_STANDARD 17)
endif()

# 03 - custom_allocator
if (${BUILD_TASK3})
    project(custom_allocator VERSION ${PROJECT_VERSION})
    add_subdirectory(task03 task03)
    message("03 - custom_allocator build enabled")
    set_property(TARGET custom_allocator PROPERTY CXX_STANDARD 17)
endif()

# 04 -
if (${BUILD_TASK4})

endif()
