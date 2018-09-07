//FLOATING POINT VISUALLY EXPLAINED
//http://fabiensanglard.net/floating_point_visually_explained/index.php

//Что нужно знать про арифметику с плавающей запятой
//https://habr.com/post/112953/


//floating-point underflow — ситуация, когда результат операции с плавающей запятой становится настолько близким к нулю, что порядок числа выходит за пределы разрядной сетки.
//Denormal number - 


//Sign{1}//Exponent{8..15}(порядок)//Mантисса{23..64}// -  
//(-1)^s * M * B^E
// Mant - старшие разряды представляения числа (не нулевые)
// Нормализация - первый бит мантиссы по определению всегда 1 => опускается)
// экономим память и обеспечивает уникальность представления числа.
// иначе множественность представления:
// 2b = 1.000e+1 = 0.100e+2 = 0.010e+3
// 1.01e+1 = 1*2^1 + 0*2^0 + 1*2^-1 = 2.5
// (-1)^s * 1.M * B^E // нормализованное число

// «X=Y» и «X-Y=0» вступали в противоречие
// «X=(X-X)+X» перед операциями умножения и деления, чтобы избежать проблем.


// History:
//DEC VAX vs  Intel K-C-S (Уильям Кэхэн, Джероми Кунен и Гарольд Стоун)
// + KCS: строгость + доп функц (денорм + спец)
//KCS => IEE754
//IEE754-2008 - добавили числа с B=10 - decimal

//float 0.15625
// 0 01111100 01000000000000000000000
// S = 0
// E = 0111 1100 (2) - 127  = 124 - 127 = -3// экспонента/порядок записывается со смещением 127
// M = 1.01 (2)
// F = 1.01(2)e-3 = 0.00101(2) = 1*2^(-3) + 1*2^(-5) = 1/8 + 1/32 = 5/32 =  0.15625
/////////TODO точность? 


/// представление 0:
// E=Emin - 1  == -127 (float/single) = E = 0000 0000
// M = 000000
// S - любой ( -0 прозрачно эквивалентен 0)

// пр, бесконечности
// E = Emax +1 == 128 = E = 1111 1111
// M = 000000
// S - +/-


// NaN:
// E = 1111 1111
// M != 000 ( любой)

// !! по определению  NaN != NaN  (для проверки сравнить с собой)

//////////////////////////////////////
// https://habr.com/post/418247/
// В вещественные SIMD-регистры float-ов влезает в 2 раза больше, чем double-ов. Соответственно, вычисления будут так же раза в 2 быстрее. Если они векторизованы.
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//long double:
// On the x86 architecture, most C compilers implement long double as the 80-bit 
// extended precision type supported by x86 hardware (sometimes stored as 12 or 
// 16 bytes to maintain data structure alignment), as specified in the C99 / C11 
// standards (IEC 60559 floating-point arithmetic (Annex F))
// sizeof ():   -m32 / -m64 / MSVisualStudio
// float :      4  / 4  / 4
// double:      8  / 8  / 8
// long double: 16 / 16 / 8
////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////
//  Tricks With the Floating-Point 
// https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
////////////////////////////////////

////////////////////////////////////
//https://ru.wikipedia.org/wiki/IEEE_754-2008
// http://ru.exploringcomputerarithmetic.org/articles/fp/IEEE-754/basics/
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <math.h>

#define PRD(X)   printf("\t( " #X " ) => %s\n", X?"true":"false")


#define NTH_BIT(b, n) ((b) & (1 << n) ? 1 : 0)
//#define NTH_BIT(b) NTH_BIT((b), 0)

union FloatingPointIEEE754 {
	struct {
		unsigned int m: 23;
		unsigned int e: 8;
		unsigned int s: 1;
	} raw;
	float f;
} ieee754;


void print_float(float f){

    ieee754.f = f;

    printf("%f - foat raw:\n", f);
    printf("\t Sign : %u\n", ieee754.raw.s);
    //printf("\t Exponent : %u%u%u%u %u%u%u%u\n", NTH_BIT(ieee754.raw.m, 0));

}



void print_bits_buf(void const * const ptr, size_t const size )
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
}

#define PRINT_BITS(ARG) print_bits_buf(&ARG, sizeof(ARG))
//#define PRINT_BITS(ARG) PRD(sizeof(ARG));

void print_bits_float(float f){
    print_bits_buf(&f, sizeof(float));
}

void print_bits_double(double d){
    print_bits_buf(&d, sizeof(double));
}


// only _Generic can function overloading in c
#define print_bits(arg) _Generic((arg)  \
    , float: print_bits_float           \
    , double: print_bits_double         \
    ) (arg)                             \




int main(){

    PRD( 16777215.f == 16777216.f );  //false
    PRD( 16777216.f == 16777217.f );  //true 

    PRD( isinf( 1./0 ));
    PRD( isinf( -1./0 ));

    ieee754.f = 0.15625f;
    //PRINT_BITS( ieee754.raw.s );

    //print_bits( 0.15625f );
    //printf("\n");
    //print_bits( 0.15625 );


    int* p = (int*)malloc(100);
    printf("\n%d\n", *(p-1));


    return 0;
}