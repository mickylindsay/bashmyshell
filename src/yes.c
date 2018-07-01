/*
yes
Repeatedly outputs provided text or "y" until killed.
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	int i;
	char *buf;
	for (i = 1; i < argc - 1; i++){
		argv[i][strlen(argv[i])] = ' ';
	}
	
	if(argc == 1)
		buf = "y";	
	else
		buf = *(argv+1);
	
	while(1){
		puts(buf);
	}
	return 1;
}