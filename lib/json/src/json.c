// Internal Includes
#include "kirke/allocator.h"
#include "kirke/string.h"

#include "kirke/json.h"

ARRAY__DEFINE( Array__JSON__Value, array__json__value, JSON__Value, json__value__equals )
ARRAY__DEFINE( Array__JSON__Object, array__json__object, JSON__Object, json__object__equals )

void skip_whitespace( String *string ){
    while( string->data[ 0 ] == '\t' || *string->data == '\n' || *string->data == '\r' || *string->data == ' '){
        string->data++;
        string->length--;
        string->capacity--;
    }
}

void json__value__clear( JSON__Value *value, Allocator *allocator ){
    if( value == NULL ){
        return;
    }

    switch( value->type ){
        case JSON__ValueType__String:
            string__clear( &value->string, allocator );
            break;
        case JSON__ValueType__Array:
            array__json__value__clear( &value->array, allocator );
            break;
        case JSON__ValueType__Object:
            array__json__object__clear( &value->children, allocator );
            break;
        default:
            break;
    }
}

bool json__value__equals( JSON__Value const *first, JSON__Value const *second ){
    if( first == NULL || second == NULL ){
        if( first == second ){
            return true;
        }
        return false;
    }

    if( first->type != second->type ){
        return false;
    }

    switch( first->type ){
        case JSON__ValueType__Invalid:
        case JSON__ValueType__Null:
            return true;
        case JSON__ValueType__Boolean:
            return first->boolean == second->boolean; 
        case JSON__ValueType__Integer:
            return first->integer == second->integer;
        case JSON__ValueType__Real:
            return first->real == second->real;
        case JSON__ValueType__String:
            return string__equals( &first->string, &second->string );
        case JSON__ValueType__Array:
            return array__json__value__equals( &first->array, &second->array );
        case JSON__ValueType__Object:
            return array__json__object__equals( &first->children, &second->children );
        default:
            return false;
    }
}

void json__object__clear( JSON__Object *object, Allocator *allocator ){
    if( object == NULL ){
        return;
    }

    string__clear( &object->key, allocator );
    json__value__clear( &object->value, allocator );
}

bool json__object__equals( JSON__Object const *first, JSON__Object const *second ){
    if( first == NULL || second == NULL ){
        if( first == second ){
            return true;
        }
        return false;
    }

    if( !string__equals( &first->key, &second->key ) ){
        return false;
    }

    if( !json__value__equals( &first->value, &second->value ) ){
        return false;
    }

    return true;
}

JSON__Object* json__parse( String const *json, Allocator *allocator ){
    String *json_clone = string__clone( json, allocator );
    skip_whitespace( json_clone );

    JSON__Object* return_value = allocator__alloc( allocator, sizeof( JSON__Object ) );


    string__clear( json_clone, allocator );
    allocator__free( allocator, json_clone );

    return return_value;
}
