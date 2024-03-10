
#include <stdio.h>
#include <string.h>
#include "../cvec.h"

void
test(void *element_addr, void *any)
{

  const int s = *((int *)element_addr);
  
  printf("iter_func %d\n", s);

}


 int
 main()
 {
    cvec_t vec;

    CVEC_NEW(vec, int, 5);

    printf("tsz %lu, size %lu, tcap %lu, ncap %lu, pcap %lu, aa %p, va %p\n", vec.tsz, vec.size, vec.tcap, vec.ncap, vec.pcap, vec.aaddr, vec.vaddr);
    
    cvec_push(&vec, &(int){3});
    cvec_push(&vec, &(int){4});
    cvec_push(&vec, &(int){5});
    printf("tsz %lu, size %lu, tcap %lu, ncap %lu, pcap %lu, aa %p, va %p\n", vec.tsz, vec.size, vec.tcap, vec.ncap, vec.pcap, vec.aaddr, vec.vaddr);
 
    cvec_insert(&vec, &(int){-1}, 0);
    cvec_insert(&vec, &(int){-1}, 4);
    printf("tsz %lu, size %lu, tcap %lu, ncap %lu, pcap %lu, aa %p, va %p\n", vec.tsz, vec.size, vec.tcap, vec.ncap, vec.pcap, vec.aaddr, vec.vaddr);

    int a;
    int b;
    int c;
    cvec_get(&vec, &a, 0); printf("a= %d\n",a);
    cvec_get(&vec, &a, 3); printf("a= %d\n",a);

    c =  cvec_erase(&vec, 0, NULL);
    b =  cvec_get(&vec, &a, 0);
    printf ("st= %d, a= %d\n", b, a); 

    c =  cvec_erase(&vec, 0, NULL);
    b =  cvec_get(&vec, &a, 0);
    printf ("st= %d, a= %d\n", b, a); 

    c =  cvec_erase(&vec, 0, NULL);
    b =  cvec_get(&vec, &a, 0);
    printf ("st= %d, a= %d\n", b, a); 


    cvec_iter(&vec, NULL, test);

    printf("tsz %lu size %lu tcap %lu ncap %lu pcap %lu aa %p, va %p\n", vec.tsz, vec.size, vec.tcap, vec.ncap, vec.pcap, vec.aaddr, vec.vaddr);
    
    cvec_destroy(&vec, NULL);
    return 0;
 }