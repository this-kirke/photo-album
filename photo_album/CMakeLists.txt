set( photo_album__DIR "${CMAKE_CURRENT_LIST_DIR}" )

add_executable(
    photo_album
    ${photo_album__DIR}/src/main.c
)

target_include_directories(
    photo_album
    PRIVATE
    ${photo_album__DIR}/include
)

target_link_libraries(
    photo_album
    PRIVATE
    libkirke
)

if( BUILD_TESTS )
    
    # "catch2__" methods defined in project/3rdParty/Catch2/CMakeLists.txt
    catch2__add_test(
        NAME test__photo_album
        SOURCES "${photo_album__DIR}/test/test__photo_album.cpp"
        LINK_LIBRARIES libkirke
    )

endif( BUILD_TESTS )