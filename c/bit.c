#include <stdio.h>


#define BYTE_TO_BIN(b) ((b) & 0x80 ? 1 : 0),\
                       ((b) & 0x40 ? 1 : 0),\
                       ((b) & 0x20 ? 1 : 0),\
                       ((b) & 0x10 ? 1 : 0),\
                       ((b) & 0x08 ? 1 : 0),\
                       ((b) & 0x04 ? 1 : 0),\
                       ((b) & 0x02 ? 1 : 0),\
                       ((b) & 0x01 ? 1 : 0)

int main(){
    char c = 0xAB;

    
}