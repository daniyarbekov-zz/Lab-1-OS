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


	long int begIndex, endIndex = 0;
	unsigned long hV = 0;

	char* word;
	int count = 0;
	int length = 0;
	int index = 0;



	while(endIndex <= size){
		if(!isspace((int) *(parser + endIndex)) && endIndex != strlen(string)){
			endIndex++;
		} else{
			length = (int) endIndex - begIndex;
			if(length > 0){
				word = (char*) malloc((length+1)*sizeof(char));
                count = 0;
				while(count<length){
					word[count] = *(parser+begIndex);
					begIndex++;
                    count++;
				}
				word[count] = '\0';
				printf("%s",word);
				hV = hashValue(word);
				index = hV % SIZE;
				if(ifPresent(word,index,wc)){
					free(word);
				}
				
				printf(" hash value is: %ld and index is: %d", hV,index);
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
	
	
}



void wc_destroy(struct wc *wc) {


	for(int i=0; i<100000; i++){    //increment thru hash table	
	
		node *temp = wc->hashMap[i]; // temp always pointing to the head
		node *tempNext = temp->next;
		while (tempNext != NULL){
			node *remove = tempNext; //define the node to be removed			
			tempNext = tempNext->next;
			free(remove);		
		}

        if(temp!=NULL){
            free(temp);
        }

	}
   
	free(wc->hashMap);
}




bool ifPresent (char* str, int index, struct wc *wc){
	if(wc->hashMap[index] == NULL){
		node *dummyHead = (struct node *)malloc(sizeof(struct node));
		node *newNode = (struct node *)malloc(sizeof(struct(node)));

		newNode->value = str;
		newNode->key = index;
		newNode->count = 1;
		newNode->next = NULL;
		wc->hashMap[index] = dummyHead;
		dummyHead->next = newNode;

		return false;
	}
	else{
		node* pointer = wc->hashMap[index];
		node *pointerNext = pointer->next;
		while(pointerNext!= NULL){
			if(strcmp(pointerNext->value, str) == 0){
				pointerNext->count+=1;
				return true;
			}
			pointer = pointerNext;
			pointerNext = pointerNext->next;
		}

		node *pointerNext = (struct node *)malloc(sizeof(struct node));
		pointerNext->value = str;
		pointerNext->key = index;
		pointerNext->count = 1;
		pointerNext->next = NULL;
		pointer->next = pointerNext;
		return false;
	}

	
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





