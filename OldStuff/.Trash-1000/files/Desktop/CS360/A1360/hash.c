#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <getWord.h>
#include "hash.h"

void hash(char *string){
   Table Hashtable;
   Hashtable.size=100;
   Hashtable.array=malloc (Hashtable.size*sizeof(Node*));
   int x=6;
   Node node1;
   node1.value=malloc (sizeof(int));
   node1.next=NULL;
   Hashtable.array[0]=node1;
   node1.key="potato";
   *(int*)node1.value=x;

   printf("%s %d\n", node1.key, *(int*)node1.value);
   printf("walnuts\n");
}


#define CRC64_REV_POLY      0x95AC9329AC4BC9B5ULL
#define CRC64_INITIALIZER   0xFFFFFFFFFFFFFFFFULL
#define CRC64_TABLE_SIZE    256

unsigned long long crc64(char* string) {
    static int initFlag = 0;
    static unsigned long long table[CRC64_TABLE_SIZE];
    
    if (!initFlag) { initFlag++;
        for (int i = 0; i < CRC64_TABLE_SIZE; i++) {
            unsigned long long part = i;
            for (int j = 0; j < 8; j++) {
                if (part & 1)
                    part = (part >> 1) ^ CRC64_REV_POLY;
                else part >>= 1;
            }
            table[i] = part;
        }
    }
    
    unsigned long long crc = CRC64_INITIALIZER;
    while (*string)
        crc = table[(crc ^ *string++) & 0xff] ^ (crc >> 8);
    return crc;
}

