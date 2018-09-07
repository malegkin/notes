#include <stdio.h>
#include <arpa/inet.h>

#define _BSD_SOURCE
#include <machine/endian.h>



///////////////////////////////////////////////////////////////////////////////
//little-endian: A0...An  // обратный порядок
// TCP/IP - network byte order
// IBM / SPARC
// При таком порядке байтов удобно проводить сравнение строк (можно сравнивать их целочисленными большей разрядности, каждое из которых содержит несколько символов сразу).


//big-endian: An...A0  // прямой порядок
// x86 memory

//MIPS/ARM могут работать и так и так, в зависимости от сборки ос

//middle-endian
//  Смешанный порядок байтов (англ. middle-endian) иногда используется при работе с числами, 
//длина которых превышает машинное слово. Число представляется последовательностью машинных 
//слов, которые записываются в формате, естественном для данной архитектуры, но сами слова 
//следуют в обратном порядке.
//  ARM?

////////////////////////////////////////////////////////////////////////////////
//                                  <--  increasing addresses
//                                  little end             big              
//Atomic element size 8-bit
//int32_t longVar = 0xA1B2C3D4  ==  [D4, C3, B2, A1]    [A1, B2, C3, D4]    
//Atomic element size 16-bit
//int32_t longVar = 0xA1B2C3D4  ==  [C3D4, A1B2]        [A1B2, C3D4]


////////////////////////////////////////////////////////////////////////////////
// Unicode
// byte order mark(BOM), маркер последовательности байтов, U+FEFF
//          little                    big
// UTF 16:  0xFF 0xFE                 0xFE 0xFF 
// UTF 32:  0xFF 0xFE 0x00 0x00       0x00 0x00 0xFE 0xFF 


//#include <arpa/inet.h>
///htonl(), htons(), ntohl(), ntohs()
//short/long


///////////////////////////////////////////////////////////////////////////////
// байт следует рассматривать как единое недилимое число {0..255} / {0...65535}
// в сети не байт а октеты - посл из 8 бит
int main(void)
{
  //autodetect endian
  //work only if: sizeof(char) < sizeof(short)
  unsigned short us = 1; /* 0x0001 */
  printf("%s\n", *((unsigned char *) &us) == 0 ? "big-endian" : "little-endian");


 union {
    uint32_t u32;
    uint8_t arr[4];
  } x;

  x.arr[0] = 0x11;
  x.arr[1] = 0x22;
  x.arr[2] = 0x33;
  x.arr[3] = 0x44;

  /* Highest-address byte */
  printf("x.u32 = 0x%x\n", x.u32);
  printf("htonl(x.u32) = 0x%x\n", htonl(x.u32));
  printf("ntohl(x.u32) = 0x%x\n", ntohl(x.u32));

  printf("htole32(x.u32) = 0x%x\n", htole32(x.u32));
  printf("htobe32(x.u32) = 0x%x\n", htobe32(x.u32));

  return 0;
}
