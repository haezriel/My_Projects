#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main(){
	int integer;
	char letter;
	char buffer[100];
	int p;
while (NULL!= fgets(buffer, 100, stdin)){
	p=sscanf(buffer, "%d",&integer);
	printf("%d, %d \n", p, integer);
	}
} 
