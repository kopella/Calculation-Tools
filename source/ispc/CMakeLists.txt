add_library(ispc_ctlib basic.ispc linear_algebra.ispc)

set_target_properties(ispc_ctlib
    PROPERTIES
    LINKER_LANGUAGE C
)