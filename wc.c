#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "wc.h"
#include "sorted_points.h"


typedef struct node {
	char *value;
	int key;
	int count;
	struct node *next;
} node;

struct wc {
	node ** hashMap;
};



struct wc *wc_init(char *word_array, long size)
{
	struct wc *wc;

	wc = (struct wc *)malloc(sizeof(struct wc));

	long int SIZE = size/10;
	
	wc.hashMap = (struct node * ) malloc(SIZE * sizeof(struct node))
	assert(wc);

	//string parsing 
	char *parser = word_array;


	long int begIndex = 0;
	long int  endIndex = 0;
	int length = 0;
	char *word;

	unsigned long hV = 0;


	while(parser + endIndex !=NULL){
		if(!isspace((int) (parser + endIndex))){
			endIndex++;
		} else {
			length = (int) endIndex - begIndex;
			if(length > 0){
				word = (char*) malloc((length+1)*sizeof(char));
				while(begIndex!=endIndex){
					word[begIndex] = parser+begIndex;
					begIndex++;
				}
				word[begIndex] = '\0';

				hashValue = hV(word);
				endIndex++;
				begIndex = endIndex;
			} else{
				begIndex++;
				endIndex++;
			}
		}
	}

	return wc;
}

void
wc_output(struct wc *wc)
{
	TBD();
}

void
wc_destroy(struct wc *wc)
{
	TBD();
	free(wc);
}



//cse.yorku.ca/~oz/html, we use 5381 as it says it works fine with it
unsigned long hashValue (char* str){
	//1000th prime value;
	unsigned long hash = 5381;
	int c;

	while (*(str++)!= '\0'){
		hash = ((hash<<5) + hash) + c;
	}
	return hash;
}





