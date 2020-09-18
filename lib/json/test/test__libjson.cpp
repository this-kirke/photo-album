// 3rdPary Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/json.h"
#include "kirke/string.h"
#include "kirke/system_allocator.h"

TEST_CASE( "json__value__equals", "[json]" ){
    JSON__Value value1;
    JSON__Value value2;

    value1 = (JSON__Value) {
        .type = JSON__ValueType__Null,
    };
    
    value2 = (JSON__Value) {
        .type = JSON__ValueType__Invalid,
    };

    REQUIRE( json__value__equals( NULL, NULL ) );
    REQUIRE_FALSE( json__value__equals( NULL, &value1 ) );
    REQUIRE_FALSE( json__value__equals( &value1, NULL ) );

    REQUIRE( json__value__equals( &value1, &value1 ) );
    REQUIRE_FALSE( json__value__equals( &value1, &value2 ) );

    value1 = (JSON__Value) {
        .type = JSON__ValueType__String,
        .string = string__literal( "A String!" )
    };
    
    value2 = (JSON__Value) {
        .type = JSON__ValueType__Integer,
        .integer = 42
    };

    REQUIRE( json__value__equals( &value1, &value1 ) );
    REQUIRE( json__value__equals( &value2, &value2 ) );
    REQUIRE_FALSE( json__value__equals( &value1, &value2 ) );
}

TEST_CASE( "json__parse", "[json]" ){
    SystemAllocator system_allocator;
    system_allocator__initialize( &system_allocator, NULL );

    String raw_json = string__literal( 
        "{"
        "   \"null\"            :   null,"
        "   \"boolean_true\"    :   true,"
        "   \"boolean_false\"   :   false,"
        "   \"string\"          :   \"a_string\","
        "   \"real\"            :   1234.56789,"
        "   \"integer\"         :   42,"
        "   \"array_string\"    :   [ \"one\", \"two\", \"three\", \"four\" ],"
        "   \"array_integer\"   :   [ 1, 2, 3, 4 ],"
        "   \"array_real\"      :   [ 1.1, 0.2, 3.3, 44.44 ],"
        "   \"array_mixed\"     :   [ null, true, \"one\", 2, 3.3 ]"
        "}" 
    );

    JSON__Object *json = json__parse( &raw_json, system_allocator.allocator );

    json__object__clear( json, system_allocator.allocator );
    allocator__free( system_allocator.allocator, json );
    system_allocator__deinitialize( &system_allocator );
}
