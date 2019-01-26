#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "wc.h"
#include "sorted_points.h"
#include <stdbool.h>
#include <ctype.h>


typedef struct node {
	char *value;
	int key;
	int count;
	struct node *next;
} node;

struct wc {
	node ** hashMap;
};


void wc_destroy(struct wc *wc);
void wc_output(struct wc *wc);
bool ifPresent (char* str, int index, struct wc *wc);
unsigned long hashValue (char* str);


int SIZE = 100000;

struct wc *wc_init(char *word_array, long size)
{
	struct wc *wc;

	wc = (struct wc *)malloc(sizeof(struct wc));

	SIZE = size/10;

	printf("The string is : %s\n",word_array);
	printf("The length of string is %ld\n", size);
	
	assert(wc);

	wc->hashMap = malloc(SIZE * sizeof(node*));
	printf("%d\n",SIZE);

	for(int i = 0; i < SIZE; i++){
		wc->hashMap[i] = NULL;
		//printf("%d",i);
	}

	//string parsing 
	char *parser = word_array;


	long int begIndex =0;
	long int endIndex = 0;
	unsigned long hV = 0;

	char* word;
	int count = 0;
	int length = 0;
	int index = 0;




	while(endIndex <= size){
		if(!isspace((int) *(parser + endIndex)) && endIndex != size){
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
				
				hV = hashValue(word);
				index = hV % SIZE;
				printf("The word is %s, its hash value is %ld, its length is %d and its index is %d\n",word,hV, length,index);
				if(ifPresent(word,index,wc)){
					free(word);
				}
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



void wc_output(struct wc *wc) {
	node *temp;
	node *tempNext;

	if(wc == NULL){
		return;
	}

	printf("OUTPUT IS INITIALIZED\n");

	for (int i = 0; i < SIZE; i++) { // increment thru  hash table
		
		temp = wc->hashMap[i]; // temp always pointing to the NULL or dummy head
		if(temp != NULL){
			tempNext = temp->next;
		
			while (tempNext != NULL){ 
				printf("%s:%i\n", tempNext->value, tempNext->count);
				tempNext  = tempNext->next;
			}
		}

	}
	printf("OUTPUT IS COMPLETE\n");

}


void wc_destroy(struct wc *wc) {
	node *remove;
	node *temp;
	node *tempNext;

	if(wc == NULL){
		return;
	}

	printf("NODE INITIALIZED DESTRUCTION\n");

	for(int i = 0; i < SIZE; i++){    //increment thru hash table	
		temp = wc->hashMap[i];

		if(temp != NULL){
			tempNext = temp->next;
			
			printf("NODE IS NOT NULL AND THE INDEX IS %d\n", i);

			while (tempNext != NULL){
				remove = tempNext; //define the node to be removed			
				tempNext = tempNext->next;
				printf("Removing node is: %s\n", remove->value);
				free(remove->value);
				free(remove);		
			}

			free(temp);
		} else{
			printf("NODE IS NULLLL!\n");
		}
	}

	printf("DESTRUCTION IS COMPLETE");
   
	free(wc->hashMap);
}




bool ifPresent (char* str, int index, struct wc *wc){

	if(wc->hashMap[index] == NULL){
		printf("NODE HASNT BEEN INTIALIZED: %s\n", str);

		node *dummyHead = (node *)malloc(sizeof(node));
		node *newNode = (node *)malloc(sizeof(node));
		newNode->value = str;
		newNode->key = index;
		newNode->count = 1;
		newNode->next = NULL;
		printf("NODE INITIALIZED TEST: %s\n", newNode->value);
		wc->hashMap[index] = dummyHead;
		dummyHead->next = newNode;
		printf("NODE IS SET:%s \n",wc->hashMap[index]->next->value);
		return false;
	}
	else{
		printf("HASHED INTO SAME SLOT\n");
		node* pointer = wc->hashMap[index];
		node *pointerNext = pointer->next;
		while(pointerNext!= NULL){
			if(strcmp(pointerNext->value, str) == 0){
				printf("DUPLICATE\n");
				pointerNext->count+=1;
				printf("INCREASE COUNTER: %d\n",pointerNext->count);
				return true;
			}
			pointer = pointerNext;
			pointerNext = pointerNext->next;
		}

		pointerNext = (node *)malloc(sizeof(node));
		pointerNext->value = str;
		pointerNext->key = index;
		pointerNext->count = 1;
		pointerNext->next = NULL;
		pointer->next = pointerNext;
		printf("POINTER BEFORE: %s\n",pointer->value);
		printf("APPEND TO END: %s\n",pointerNext->value);
		return false;
	}

	
}

//cse.yorku.ca/~oz/html, we use 5381 as it says it works fine with it
unsigned long hashValue (char* str){
	//1000th prime value;
	unsigned long hash = 5381;

	while (*(str)!= '\0'){
		hash = ((hash<<5) + hash) + *str;
		str++;
	}
	return hash;
}




