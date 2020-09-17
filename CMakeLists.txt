cmake_minimum_required( VERSION 3.12 )

set( CMAKE_VERBOSE_MAKEFILE OFF )

option( BUILD_TESTS "Build tests with project." OFF )
option( BUILD_COVERAGE_REPORT "Build test coverage report with project and tests." OFF )
option( BUILD_DOCUMENTATION "Build project documentation." OFF )

if( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
    set( BUILD_COVERAGE_REPORT OFF CACHE BOOL "Disabled BUILD_COVERAGE_REPORT because compiler is Clang" )
endif( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )

project( photo_album )

set( CMAKE_C_STANDARD 11 )
set( CMAKE_C_STANDARD_REQUIRED ON )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON )

add_subdirectory( 3rdParty )
add_subdirectory( lib/json )
add_subdirectory( exec/photo_album )

if( BUILD_TESTS )
    if( BUILD_COVERAGE_REPORT )
        # "catch2__" methods defined in project/3rdParty/Catch2/CMakeLists.txt
        catch2__build_test_executable( 
            GENERATE_COVERAGE_REPORT
            COVERAGE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs/coverage 
        )
    else( BUILD_COVERAGE_REPORT )
        catch2__build_test_executable()
    endif( BUILD_COVERAGE_REPORT )

endif( BUILD_TESTS )

if( BUILD_DOCUMENTATION )

    find_package( Doxygen )
        
    if( DOXYGEN_FOUND )

        set( DOXYGEN_PROJECT_NAME "photo-album" )
        set( DOXYGEN_PROJECT_BRIEF "Technology showcase for LEANTechniques. Retrieves and displays JSON-formatted photo almbum data from https://jsonplaceholder.typicode.com/photos" )
        set( DOXYGEN_LAYOUT_FILE "${CMAKE_CURRENT_LIST_DIR}/doc/DoxygenLayout.xml" )
        set( DOXYGEN_STRIP_FROM_PATH "${CMAKE_CURRENT_LIST_DIR}" )
        set( DOXYGEN_DISABLE_INDEX YES )
        set( DOXYGEN_GENERATE_TREEVIEW YES )

        set( DOXYGEN_TYPEDEF_HIDES_STRUCT YES )
        set( DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/docs" )
        set( DOXYGEN_HTML_OUTPUT "." )
        set( DOXYGEN_HTML_EXTRA_STYLESHEET "${CMAKE_CURRENT_LIST_DIR}/3rdParty/doxygen_dark_theme/custom_dark_theme.css" "${CMAKE_CURRENT_LIST_DIR}/3rdParty/doxygen_dark_theme/custom.css" )

        set( DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES )
        set( DOXYGEN_EXCLUDE_PATTERNS "*/test/*" )

        doxygen_add_docs(
            docs
            lib
            doc
            ALL
        )

    endif( DOXYGEN_FOUND )

endif( BUILD_DOCUMENTATION )
