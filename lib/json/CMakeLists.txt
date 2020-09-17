set( libjson__DIR "${CMAKE_CURRENT_LIST_DIR}" )

add_library(
    libjson
    ${libjson__DIR}/src/json.c
)

target_include_directories(
    libjson
    PUBLIC
    ${libjson__DIR}/include
)

target_link_libraries(
    libjson
    PUBLIC
    libkirke
)

set_target_properties(
    libjson
    PROPERTIES
    OUTPUT_NAME
    json
)

target_compile_options( 
    libjson
    PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Werror -Wall -Wextra -pedantic-errors>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

if( BUILD_TESTS )

    if( BUILD_COVERAGE_REPORT )
        target_link_libraries(
            libjson
            PRIVATE
            gcov
        )

        set_target_properties(
            libjson
            PROPERTIES
            COMPILE_FLAGS "--coverage"
        )
    endif( BUILD_COVERAGE_REPORT )
    
    # "catch2__" methods defined in project/3rdParty/Catch2/CMakeLists.txt
    catch2__add_test(
        NAME test__libjson
        SOURCES "${libjson__DIR}/test/test__libjson.cpp"
        LINK_LIBRARIES libjson
    )

endif( BUILD_TESTS )
