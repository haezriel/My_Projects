#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>


//This is a modulo multiplier that I've found and used before,
//not my work.
uint64_t powerMod(__uint128_t base, __uint128_t exp, __uint128_t modulus) {
  base %= modulus;
  __uint128_t result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}


int miller_rabin(uint64_t n,uint64_t a){
    uint64_t q = n - 1; 
    uint64_t k = 0;
    //printf("%" PRIu64 ", " "%" PRIu64 ", " "%" PRIu64 "\n",n,q,k);
    while (q % 2 == 0){
        q = q / 2;
        k = k + 1;
      }
    uint64_t t = powerMod(a, q, n);
    if (t == 1) return 1;
    while (k > 0){
        if (t == n - 1)
            return 1;
        t = (t * t) % n;
        k = k - 1;
      }
    return 0;
}

int Prime(uint64_t n){
	for(int i=0;i<8;i++){
		uint64_t a=rand()%(n-2)+1;
		if(miller_rabin(n,a)==0)
			return 0;
	}
	return 1;
}

void keygen(){
char buffer[100];
int seed;
printf("Commencing Key Generation.\n");
printf ("Please input a positive integer seed value:\n");
fgets(buffer,100,stdin);
sscanf(buffer,"%d",&seed);

srand(seed);
uint64_t g=2;
uint64_t q,p;
while(1){
	q = (rand()%0x80000000)|0x80000000;
	if (q%12!=5) continue;
	if(Prime(q)==1){
		p=(2*q+1);
		if(Prime(p)==1)
			break;
	}
}

uint64_t d=rand()%p;
uint64_t e2=powerMod(g,d,p);
FILE *fp;
FILE *fp2;
fp=fopen("prikey.txt","w+");
fp2=fopen("pubkey.txt","w+");
fprintf(fp, "%" PRIu64 " ""%" PRIu64 " ""%" PRIu64,p,g,d);
fprintf(fp2,  "%" PRIu64 " ""%" PRIu64 " ""%" PRIu64,p,g,e2);
printf("Secret Key: " "%" PRIu64 " ""%" PRIu64 " ""%" PRIu64"\n",p,g,d);
printf("Public Key: "  "%" PRIu64 " ""%" PRIu64 " ""%" PRIu64"\n",p,g,e2);
fclose(fp);
fclose(fp2);
printf("Key Generation complete.\n");
return;
}

//KEYGEN ENDS HERE


void encrypt(){
printf("Commencing Encryption.\n");

uint64_t p;
uint64_t g;
uint64_t e2;

char buffer[100];
FILE *fp;
FILE *fp2;
FILE *fp3;
fp=fopen("ptext.txt","r+");
if(fp==NULL){
	printf("No ptext.txt file found.\n");
	return;
}
fp2=fopen("pubkey.txt","r+");
if(fp2==NULL){
	printf("No pubkey.txt file found.\n");
	return;
}
fp3=fopen("ctext.txt","w+");

fgets(buffer,sizeof(buffer),fp2);
if(3!=sscanf(buffer,"%lu %lu %lu",&p,&g,&e2)){
	printf("Keyfile error.\n");
	return;
}


while(1){
	__uint128_t C1,C2;
	__uint128_t m;
	uint64_t k;
	int bsize=0;
	int done=0;
	uint64_t block=0;
	bsize=fread(&block, sizeof(uint8_t), 4, fp);
if(bsize!=4){
	block=block<<8|(uint8_t)bsize;
	done=1;
}
	m=block;
	printf("m: " "%" PRIu64 ", ",(uint64_t)m);
	k=rand()%p;
	C1=powerMod(g,k,p);
	C2=powerMod(e2,k,p);
	m=powerMod(m,1,p);
	C2=powerMod(C2*m,1,p);
	
	printf("C1: " "%" PRIu64  ", ""C2: " "%" PRIu64  "\n",(uint64_t)C1,(uint64_t)C2);

	fwrite(&C1, sizeof(uint64_t), 1, fp3);
	fwrite(&C2, sizeof(uint64_t), 1, fp3);
	if(done){
		fclose(fp);
		fclose(fp2);
		fclose(fp3);
		break;
	}
}

printf("Encryption complete.\n");
}

//END OF ENCRYPTION BLOCK


void decrypt(){
printf("Commencing Decryption.\n");

uint64_t p;
uint64_t g;
uint64_t d;


char buffer[100];
FILE *fp;
FILE *fp2;
FILE *fp3;
fp=fopen("ctext.txt","r+");
if(fp==NULL){
	printf("No ctext.txt file found.\n");
	return;
}
fp2=fopen("prikey.txt","r+");
if(fp2==NULL){
	printf("No prikey.txt file found.\n");
	return;
}
fp3=fopen("dtext.txt","w+");

fgets(buffer,sizeof(buffer),fp2);
if(3!=sscanf(buffer,"%lu %lu %lu",&p,&g,&d)){
	printf("Keyfile error.\n");
	return;
}

	__uint128_t C1,C2;
	uint64_t temp;
	int bsize=0;

	uint64_t block[2];
	__uint128_t m;
	bsize=fread(&block, sizeof(uint64_t), 2, fp);
while(1){

	if(bsize!=2){
		fclose(fp);
		fclose(fp2);
		fclose(fp3);
		break;
	}

	C1=block[0];
	C2=block[1];


	printf("C1: " "%" PRIu64  ", ""C2: " "%" PRIu64  ", ",(uint64_t)C1,(uint64_t)C2);
	temp=p-1-d;
	C1=powerMod(C1,temp,p);
	C2=powerMod(C2,1,p);
	m=powerMod(C2*C1,1,p);

	printf("m: " "%" PRIu64 "\n",(uint64_t)m);


block[0]=0;
block[1]=0;

bsize=fread(&block, sizeof(uint64_t), 2, fp);
if(bsize!=2){
	uint8_t brick=m&0xff;
	m=m>>8;
	fwrite(&m, sizeof(uint8_t)*brick, 1, fp2);
	fclose(fp);
	fclose(fp2);
	fclose(fp3);
	break;
}

	fwrite(&m, sizeof(uint32_t), 1, fp3);

}
printf("Decrypted Output: \n");
int c;
FILE *file;
file = fopen("dtext.txt", "r");
if (file) {
    while ((c = getc(file)) != EOF)
        putchar(c);
    fclose(file);
}
printf("\n");

printf("Decryption complete.\n");
}

int main(){
			char input;	
			char buffer[10];
			printf("Please enter <k> for key generation, <e> for encryption, <d> for decryption, or <q> to quit:\n");
	while(NULL!=fgets(buffer,10,stdin)){	
		
		sscanf(buffer,"%c",&input);
		switch(input){
			case 'k':
				keygen();
				break;
			case 'e':
				encrypt();
				break;
			case 'd':
				decrypt();
				break;
			case 'q':
				printf("Quitting.\n");
				exit(1);
			default:
				break;
		}
		printf("Please enter <k> for key generation, <e> for encryption, <d> for decryption, or <q> to quit:\n");
	}
}

