#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


unsigned long hashValue (char* str);

int main() {
    char *string,*found;

    string = strdup("Hello there, peasants!");
    printf("Original string: '%s'\n",string);
    
    char *parser = string;


	long int begIndex = 0;
	long int  endIndex = 0;
	int length = 0;
    int count = 0;
	char *word;

	unsigned long hV = 0;


	while(*(parser + endIndex)){
		if(!isspace((int) *(parser + endIndex))){
			endIndex++;
		} else {

			length = (int) endIndex - begIndex;
            printf("%d\n", length);
			if(length > 0){
				word = (char*) malloc((length+1)*sizeof(char));
                count = 0;
				while(count<length){
					word[count] = *(parser+begIndex);
					begIndex++;
                    count++;
				}
				word[count] = '\0';
                printf("%s\n",word);
                free(word);
				hV = hashValue(word);
				endIndex++;
				begIndex = endIndex;
			} else{
				begIndex++;
				endIndex++;
			}
		}
	}



    return(0);
}

unsigned long hashValue (char* str){
	//1000th prime value;
	unsigned long hash = 5381;
	int c;

	while (*(str++)!= '\0'){
		hash = ((hash<<5) + hash) + c;
	}
	return hash;
}