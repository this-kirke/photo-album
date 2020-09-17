// Internal Includes
#include "kirke/allocator.h"
#include "kirke/string.h"

String* json__say_hello( Allocator *allocator ){
    static String hello = string__literal( "Hello" );

    return string__clone( &hello, allocator );
}
