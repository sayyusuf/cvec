
#include "argv_lib.h"
#include <stdio.h>

//GENERATE_VECTOR_HEADER(int, INT)


 int    main()
 {
    argv_t *vec;
    vec = argv_new(NULL,NULL);
    argv_push(vec, "hello");

   printf("%p\n", vec->vector);

 } 