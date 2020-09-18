// 3rdPary Includes
#include "catch2/catch.hpp"

// Internal Includes
#include "kirke/string.h"
#include "kirke/system_allocator.h"

#include "kirke/json.h"

extern "C" void skip_whitespace( String *string );

TEST_CASE( "test__json__skip_whitespace", "[json]" ){
    String leading_whitespace = string__literal( "\t\n\r word" );
    String expected_string = string__literal( "word" );

    skip_whitespace( &leading_whitespace );

    REQUIRE( string__equals( &leading_whitespace, &expected_string ) );
}

TEST_CASE( "test__json__value__equals", "[json]" ){
    JSON__Value value1;
    JSON__Value value2;

    value1.type = JSON__ValueType__Null;
    value2.type = JSON__ValueType__Invalid;

    REQUIRE( json__value__equals( NULL, NULL ) );
    REQUIRE_FALSE( json__value__equals( NULL, &value1 ) );
    REQUIRE_FALSE( json__value__equals( &value1, NULL ) );

    REQUIRE( json__value__equals( &value1, &value1 ) );
    REQUIRE_FALSE( json__value__equals( &value1, &value2 ) );

    value1.type = JSON__ValueType__String;
    value1.string = string__literal( "A String!" );
    
    value2.type = JSON__ValueType__Integer;
    value2.integer = 42;

    REQUIRE( json__value__equals( &value1, &value1 ) );
    REQUIRE( json__value__equals( &value2, &value2 ) );
    REQUIRE_FALSE( json__value__equals( &value1, &value2 ) );
}

class JSON__TestFixture {
    protected:
        JSON__TestFixture(){
            system_allocator__initialize( &system_allocator, NULL );
        }

        ~JSON__TestFixture(){
            system_allocator__deinitialize( &system_allocator );
        }

        SystemAllocator system_allocator;
};

TEST_CASE_METHOD( JSON__TestFixture, "test__json__parse__null", "[json]" ){
    String raw_json = string__literal( "null" );

    JSON__Value *value = json__parse( &raw_json, system_allocator.allocator );

    REQUIRE( value->type == JSON__ValueType__Null );

    json__value__clear( value, system_allocator.allocator );
    allocator__free( system_allocator.allocator, value );
}

TEST_CASE_METHOD( JSON__TestFixture, "test__json__parse__boolean", "[json]" ){
    String true_json = string__literal( "true" );
    JSON__Value true_value = {
        .type = JSON__ValueType__Boolean,
        .boolean = true
    };
    JSON__Value *true_parsed = json__parse( &true_json, system_allocator.allocator );
    
    REQUIRE( json__value__equals( true_parsed, &true_value ) );
    json__value__clear( true_parsed, system_allocator.allocator );
    allocator__free( system_allocator.allocator, true_parsed );

    String false_json = string__literal( "false" );
    JSON__Value false_value = {
        .type = JSON__ValueType__Boolean,
        .boolean = false
    };
    JSON__Value *false_parsed = json__parse( &false_json, system_allocator.allocator );

    REQUIRE( json__value__equals( false_parsed, &false_value ) );
    json__value__clear( false_parsed, system_allocator.allocator );
    allocator__free( system_allocator.allocator, false_parsed );
}
TEST_CASE_METHOD( JSON__TestFixture, "test__json__parse", "[json]" ){
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

    JSON__Value *json = json__parse( &raw_json, system_allocator.allocator );

    json__value__clear( json, system_allocator.allocator );
    allocator__free( system_allocator.allocator, json );
}
