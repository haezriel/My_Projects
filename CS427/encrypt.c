#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>


void makekey();
void getkey();
unsigned char gethex(char buf);
uint16_t leftrotate(uint16_t in);
uint16_t rightrotate(uint16_t in);
void F(uint16_t R0, uint16_t R1, int round);
uint8_t K(int x);
uint16_t G(uint16_t R, int round, uint8_t subkey[]);
uint16_t f[2];
uint8_t key[8];
uint64_t big_key;
uint64_t word_block;
int debug=0;
unsigned char ftable[]=
{0xa3,0xd7,0x09,0x83,0xf8,0x48,0xf6,0xf4,0xb3,0x21,0x15,0x78,0x99,0xb1,0xaf,0xf9,
0xe7,0x2d,0x4d,0x8a,0xce,0x4c,0xca,0x2e,0x52,0x95,0xd9,0x1e,0x4e,0x38,0x44,0x28,
0x0a,0xdf,0x02,0xa0,0x17,0xf1,0x60,0x68,0x12,0xb7,0x7a,0xc3,0xe9,0xfa,0x3d,0x53,
0x96,0x84,0x6b,0xba,0xf2,0x63,0x9a,0x19,0x7c,0xae,0xe5,0xf5,0xf7,0x16,0x6a,0xa2,
0x39,0xb6,0x7b,0x0f,0xc1,0x93,0x81,0x1b,0xee,0xb4,0x1a,0xea,0xd0,0x91,0x2f,0xb8,
0x55,0xb9,0xda,0x85,0x3f,0x41,0xbf,0xe0,0x5a,0x58,0x80,0x5f,0x66,0x0b,0xd8,0x90,
0x35,0xd5,0xc0,0xa7,0x33,0x06,0x65,0x69,0x45,0x00,0x94,0x56,0x6d,0x98,0x9b,0x76,
0x97,0xfc,0xb2,0xc2,0xb0,0xfe,0xdb,0x20,0xe1,0xeb,0xd6,0xe4,0xdd,0x47,0x4a,0x1d,
0x42,0xed,0x9e,0x6e,0x49,0x3c,0xcd,0x43,0x27,0xd2,0x07,0xd4,0xde,0xc7,0x67,0x18,
0x89,0xcb,0x30,0x1f,0x8d,0xc6,0x8f,0xaa,0xc8,0x74,0xdc,0xc9,0x5d,0x5c,0x31,0xa4,
0x70,0x88,0x61,0x2c,0x9f,0x0d,0x2b,0x87,0x50,0x82,0x54,0x64,0x26,0x7d,0x03,0x40,
0x34,0x4b,0x1c,0x73,0xd1,0xc4,0xfd,0x3b,0xcc,0xfb,0x7f,0xab,0xe6,0x3e,0x5b,0xa5,
0xad,0x04,0x23,0x9c,0x14,0x51,0x22,0xf0,0x29,0x79,0x71,0x7e,0xff,0x8c,0x0e,0xe2,
0x0c,0xef,0xbc,0x72,0x75,0x6f,0x37,0xa1,0xec,0xd3,0x8e,0x62,0x8b,0x86,0x10,0xe8,
0x08,0x77,0x11,0xbe,0x92,0x4f,0x24,0xc5,0x32,0x36,0x9d,0xcf,0xf3,0xa6,0xbb,0xac,
0x5e,0x6c,0xa9,0x13,0x57,0x25,0xb5,0xe3,0xbd,0xa8,0x3a,0x01,0x05,0x59,0x2a,0x46};

int main(int argc, char *argv []){
int done=0;
char k;
if(argc==2 ){
	sscanf(argv[1],"%c",&k);
	if(k=='k'){
	printf("Generating key.\n");
	makekey();
}
if(k=='d'){
	printf("Debugging Mode On\n");
	debug=1;
}
}
else
	printf("Utilizing key in key.txt.\n");
int round;
printf("Encrypting, printing to cyphertext.txt.\n");
FILE *fp;
FILE *fp2;
fp=fopen("plaintext.txt","r+");
if(fp==NULL){
	printf("No plaintext.txt file found.\n");
	exit(1);
}
fp2=fopen("cyphertext.txt","w+");

size_t bsize=0;
while(1){
uint64_t block=0;
bsize=fread(&block, sizeof(uint8_t), 8, fp);
if(bsize!=8){
	block=block<<8|(uint8_t)bsize;
	done=1;
}
uint16_t R[4];
uint16_t W[4];
getkey();
if(debug==1)
printf("key: %"PRIx64"\n",big_key);
W[0]=block>>48&0xffff;
W[1]=block>>32&0xffff;
W[2]=block>>16&0xffff;
W[3]=block&0xffff;

for (int i=0;i<4;i++){
	uint16_t key16=key[i*2]<<8|key[i*2+1];
	R[i]=W[i]^key16;
	if(debug==1)
	printf("%x",R[i]);
}
if(debug==1)
printf("\nblock whitening complete.\n");
W[1]=rightrotate(W[1]);
for(round=0;round<16;round++){
	uint16_t interm[4];
	f[0]=0;
	f[1]=0;
	F(R[0],R[1],round);
	interm[0]=R[2]^f[0];
	interm[0]=rightrotate(interm[0]);
	interm[1]=R[3];
	interm[1]=leftrotate(interm[1]);
	interm[1]=interm[1]^f[1];
	interm[2]=R[0];
	interm[3]=R[1];
	R[0]=interm[0];
	R[1]=interm[1];
	R[2]=interm[2];
	R[3]=interm[3];	
	if(debug==1)
	printf("%x%x%x%x\n",R[0],R[1],R[2],R[3]);
}
//printf("%"PRIx64"\n",big_key);

uint16_t y[4];
y[0]=R[2];
y[1]=R[3];
y[2]=R[0];
y[3]=R[1];

uint64_t C[4];

for (int i=0;i<4;i++){
	uint16_t key16=big_key>>(3-i)*16&0xffff;
	C[i]=y[i]^key16;

}

uint64_t cyphertext=C[0]<<48|C[1]<<32|C[2]<<16|C[3];
fwrite(&cyphertext, sizeof(cyphertext), 1, fp2);
if(done){
	fclose(fp);
	fclose(fp2);
	exit(0);
}

}


}

void makekey(){
FILE *fp;
time_t t;
srand((unsigned) time(&t));
fp=fopen("key.txt","w+");


for(int i=0;i<8;i++){
key[i]=rand()%256;
big_key=big_key|key[i];
if(i<7)big_key=big_key<<8;
}
fwrite(&big_key,sizeof(big_key),1,fp);
fclose(fp);
return;
}

void getkey(){
FILE *fp;
fp=fopen("key.txt","r+");
if(fp==NULL){
	printf("No key.txt found, to make a key, use ./encrypt k\n");
	exit(1);
}
size_t size;
if((size=fread(&big_key,sizeof(big_key),1,fp))!=1){
	printf("Bad Key or no key.txt found.\n");
	exit(1);
}

for(int i=0;i<8;i++){
	key[7-i]=big_key>>8*i&0xff;
}
fclose(fp);
	//printf("%"PRIx64"\n",big_key);
return;
}


void F(uint16_t R0, uint16_t R1, int round){
	uint8_t subkey[12];
	for(int i=0;i<12;i++){
		subkey[i]=K(4*round+i%4);
		if(debug==1)
		printf("Round %d, subkey#%d=%x \n",round, i, subkey[i]);
	}
	uint8_t gkeys1[4];
	uint8_t gkeys2[4];
	for(int i=0;i<4;i++){
		gkeys1[i]=subkey[i];
		gkeys2[i]=subkey[i+4];
	}
	uint16_t T0=G(R0,round,gkeys1);
	uint16_t T1=G(R1,round,gkeys2);
	f[0]=(T0+2*T1+(subkey[8]<<8|subkey[9]))%65536;
	f[1]=(2*T0+T1+(subkey[10]<<8|subkey[11]))%65536;
	if(debug==1)
	printf("T0: %x T1: %x f0: %x f1: %x\n",T0,T1,f[0],f[1]);

}

uint8_t K(int x){
uint64_t big_key_shift=big_key&0x8000000000000000;
big_key=big_key_shift>>63|big_key<<1;
if(debug==1)
printf("%"PRIx64"\n",big_key);
for(int i=0;i<8;i++){
	key[i]=big_key>>(8*i)&0xff;
	//printf("key #%d, %x\n",i,key[i]);
}
return key[x%8];

}
uint16_t G(uint16_t R,int round,uint8_t subkey[]){
uint8_t g1=R>>8&0xff;
uint8_t g2=R&0xff;
uint8_t g3=ftable[(g2^subkey[0])]^g1;
uint8_t g4=ftable[(g3^subkey[1])]^g2;
uint16_t g5=ftable[(g4^subkey[2])]^g3;
uint16_t g6=ftable[(g5^subkey[3])]^g4;
if(debug==1)
printf("g1: %x g2: %x g3: %x g4: %x g5: %x g6: %x\n",g1,g2,g3,g4,g5,g6);
return (g5<<8|g6);
}
uint16_t rightrotate(uint16_t in){
uint16_t shift=in& 0x0001;
in=shift<<15|in>>1;
return in;
}
uint16_t leftrotate(uint16_t in){
uint16_t shift=in& 0x8000;
in=shift>>15|in<<1;
return in;
}


