#ifndef KIRKE__JSON__H
#define KIRKE__JSON__H

// Internal Includes
#include "kirke/array.h"
#include "kirke/macros.h"
#include "kirke/string.h"

BEGIN_DECLARATIONS

typedef enum JSON__ValueType{
    JSON__ValueType__Invalid,
    JSON__ValueType__Null,
    JSON__ValueType__Boolean,
    JSON__ValueType__String,
    JSON__ValueType__Integer,
    JSON__ValueType__Real,
    JSON__ValueType__Array,
    JSON__ValueType__Object,
    JSON__ValueType__COUNT
} JSON__ValueType;

typedef struct JSON__Value JSON__Value;
ARRAY__DECLARE( Array__JSON__Value, array__json__value, JSON__Value )

typedef struct JSON__Object JSON__Object;
ARRAY__DECLARE( Array__JSON__Object, array__json__object, JSON__Object )

struct JSON__Value{
    JSON__ValueType type;
    union{
        bool boolean;
        long long integer;
        double real;
        String string;
        Array__JSON__Value array;
        Array__JSON__Object children;
    };
};

struct JSON__Object{
    JSON__Object *parent;    
    String key;
    JSON__Value value;
};

void json__value__clear( JSON__Value *value, Allocator *allocator );
bool json__value__equals( JSON__Value const *first, JSON__Value const *second );

void json__object__clear( JSON__Object *object, Allocator *allocator );
bool json__object__equals( JSON__Object const *first, JSON__Object const *second );

JSON__Object* json__parse( String const *json, Allocator *allocator );

END_DECLARATIONS

#endif // KIRKE__JSON__H
