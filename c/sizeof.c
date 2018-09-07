// from standart 
//
// 1 == sizeof(char) <= sizeof(short) <= sizeof(int) <= sizeof(long) <= sizeof(long long)
//(int/long/pointer)
// LP32:    2/4/4   //Win16
// ILP32:   4/4/4   //Win32, Unix
// LLP64:   4/4/8   //Win64
// LP64:    4/8/8   //Unix
////////////////////////////////////////////////////////////////////////////////


// -m64 / -m32: 
// pointer = 8 / 4
// size_t, time_t,  ptrdiff_t  == 8 / 4
// long = 8 / 4

// MS VS:
// sizeof( long double ) == 8 


////////////////////////////////////////////////////////////////////////////////
struct  bit_field {
    unsigned int u1 : 1;
    unsigned int u2 : 1;
    unsigned int u3 : 1;
    unsigned int u4 : 1;
    unsigned int u5 : 1;
} ;
// sizeof == 4
//The above structure requires 4 bytes of memory space for status variable, but 
//only 2 bits will be used to store the values. If you will use up to 32 variables 
//each one with a width of 1 bit, then also the status structure will use 4 bytes. 
//However as soon as you have 33 variables, it will allocate the next slot of the 
//memory and it will start using 8 bytes.
////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // ptrdiff_t, int64_t , etc  ))
#include <limits.h>   // __WORDSIZE

#define PRS(X)   printf("\n%s\n", X)

#define MY_SIZEOF(A) (size_t)((char*)(&A + 1) - (char*)&A)

#define ARRAY_ELEMENTS(A) (sizeof (A) / sizeof (A)[0])
#define PRINT_SIZEOF(A) printf("\tsizeof( " #A " )\t== %zu\n", sizeof(A)); 
#define PRINT_SIZEOF_M(A) printf("\tsizeof_m( " #A " )\t== %zu\n", MY_SIZEOF(A)); 
#define PRINT_SIZEOF_TYPE(A) printf("sizeof( " #A " )\t== %zu\n", sizeof(A)); 
#define PRINT_ELEMENTS_OF(A) printf("\telements( " #A " )\t== %zu\n", ARRAY_ELEMENTS(A)); 




int main(){
    
    PRINT_SIZEOF_TYPE( size_t )
    PRINT_SIZEOF_TYPE( ptrdiff_t )
    PRINT_SIZEOF_TYPE( char )
    PRINT_SIZEOF_TYPE( wchar_t )
    PRINT_SIZEOF_TYPE( short int )
    PRINT_SIZEOF_TYPE( int )
    PRINT_SIZEOF_TYPE( long )
    PRINT_SIZEOF_TYPE( long long )
    PRINT_SIZEOF_TYPE( float )
    PRINT_SIZEOF_TYPE( double )
    PRINT_SIZEOF_TYPE( long double )
    PRINT_SIZEOF_TYPE( int64_t )

    
    PRINT_SIZEOF_TYPE(struct bit_field );
    
    
    //#if ( __WORDSIZE == 64 )
    #ifdef __x86_64
        //PRINT_SIZEOF_TYPE( __int128 )    //  16 byte == 2word ariphmetis
    #endif

    #ifdef __PPC64__
        PRINT_SIZEOF_TYPE( __float128 )
    #endif
        

    int i;
        PRS("int i");
        PRINT_SIZEOF_M(i);
        PRINT_SIZEOF(i);
        PRINT_SIZEOF(&i);
    
    int* p;
        PRS("int* p");
        PRINT_SIZEOF_M(p);
        PRINT_SIZEOF(p);
        PRINT_SIZEOF(&p);
        PRINT_SIZEOF(*p);

    int ia[100];
        PRS("int ia[100]");
        PRINT_ELEMENTS_OF(ia);
        PRINT_SIZEOF_M(ia);
        PRINT_SIZEOF(ia);      
        PRINT_SIZEOF(&ia);     
        PRINT_SIZEOF(*ia);     

    int *pa = (int*)malloc(sizeof(int) * 100);
        PRS("int *pa = malloc(sizeof(int) * 100)");
        PRINT_ELEMENTS_OF( pa );    
        PRINT_SIZEOF_M(pa);
        PRINT_SIZEOF( pa );
        PRINT_SIZEOF( pa[0] );
        PRINT_SIZEOF( &pa );
        PRINT_SIZEOF( *pa );

        printf("\tpa == %p\n", pa);
        printf("\t&pa == %p\n", &p);


    free(pa);

    
    int *par = (int*)malloc(sizeof(int) * (rand()%100));
        PRS("int *par = malloc(sizeof(int) * (rand()%100))");
        PRINT_ELEMENTS_OF( par );   
        PRINT_SIZEOF_M(par);    
        PRINT_SIZEOF( par );
        PRINT_SIZEOF( par[0] );
        PRINT_SIZEOF( &par );
        PRINT_SIZEOF( *par );
    free(par);
    
    
    return 0;    
}
