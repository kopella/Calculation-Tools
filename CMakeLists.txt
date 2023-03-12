cmake_minimum_required(VERSION 3.18)
project(CalculationTools
    VERSION 0.1.0
    LANGUAGES CXX C ISPC
)

option(CT_ENABLE_ISPC "Enable Intel® ISPC." ON)

if(${CT_ENABLE_ISPC})
    message(STATUS "ISPC is enabled")
endif()

include(FetchContent)

add_subdirectory(source)

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    include(CTest)
    add_subdirectory(test)
endif()
