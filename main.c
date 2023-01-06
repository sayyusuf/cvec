
#include "argv_lib.h"
#include <stdio.h>
#include <string.h>
//GENERATE_VECTOR_HEADER(int, INT)


 int    main()
 {
    argv_t *vec;
    char *as[]= {"hello", "world", NULL};
    vec = argv_new(as, strdup);
    argv_push(vec, "hello");

   printf("%s\n", vec->vector[3]);

 } 