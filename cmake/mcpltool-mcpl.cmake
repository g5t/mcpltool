include(FetchContent)
FetchContent_Declare(
        MCPL
        GIT_REPOSITORY https://github.com/mctools/mcpl.git
        GIT_TAG v1.6.2
)
# FetchContent_MakeAvailable(MCPL)

# DO NOT use FetchContent_MakeAvailable(MCPL) as it will add the mcpl build AND install target to the global scope
FetchContent_GetProperties(MCPL)
if (NOT MCPL_POPULATED)
    FetchContent_Populate(MCPL)
    add_subdirectory(${mcpl_SOURCE_DIR} ${mcpl_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Directly include mcpl in the compiled python module -- it's source _must_ be specified
foreach(TARGET IN LISTS CXX_TARGETS)
    target_include_directories(${TARGET} PUBLIC "${MCPL_SOURCE_DIR}/src/mcpl")
    target_sources(${TARGET} PUBLIC "${MCPL_SOURCE_DIR}/src/mcpl/mcpl.c")
endforeach()