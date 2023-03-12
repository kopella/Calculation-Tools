add_library(calculation_tools calculation_tools.cc)

target_include_directories(calculation_tools PUBLIC ../include)

if(${CT_ENABLE_ISPC})
    add_subdirectory(ispc)
    target_link_libraries(calculation_tools PRIVATE ispc_ctlib)
endif()