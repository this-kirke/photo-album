#ifndef KIRKE__JSON__H
#define KIRKE__JSON__H

#include "kirke/macros.h"

typedef struct Allocator Allocator;
typedef struct String String;

BEGIN_DECLARATIONS

String* json__say_hello( Allocator *allocator );

END_DECLARATIONS

#endif // KIRKE__JSON__H
