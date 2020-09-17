// 3rdPary Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/json.h"
#include "kirke/string.h"
#include "kirke/system_allocator.h"

TEST_CASE( "json", "[json]" ){
    SystemAllocator system_allocator;
    system_allocator__initialize( &system_allocator, NULL );

    String hello = string__literal( "Hello" );

    String* hello_from_json = json__say_hello( system_allocator.allocator );
    REQUIRE( string__equals( hello_from_json, &hello ) );

    string__clear( hello_from_json, system_allocator.allocator );
    allocator__free( system_allocator.allocator, hello_from_json );

    system_allocator__deinitialize( &system_allocator );
}
