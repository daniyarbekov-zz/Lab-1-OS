#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "wc.h"

/***************\
 *  hash table  |
 ***************/

/* h */

typedef struct node_ {
	char *key;
	int val;
	struct node_ *next;
} node;

#define NUM_BUCKETS_DEFAULT 10000000
typedef struct {
	int size;
	int occupancy;

	node **buckets;
} hash_table;

node *make_node(char *key, int len, int val, node *next);
unsigned long hash(const char *str, int len);

void init_table(hash_table *map);
void table_add(char *word, int len, hash_table *map, int with_val);
void resize_if_needed(hash_table *map);
void table_destroy(hash_table *map);
void table_output(hash_table *map);

/* c */

node * make_node(char *key, int len, int val, node *next)
{
	node *newnode = (node *) malloc(sizeof(node));

	if (len == -1) { /* hehe */
		newnode->key = key;
	} else {
		newnode->key = (char *) malloc(sizeof(char) * (1 + len));
		strncpy(newnode->key, key, len);
		newnode->key[len] = '\0';
	}

	newnode->val = val;
	newnode->next = next;
	return newnode;
}

/* djb2 string hash algorithm from http://www.cse.yorku.ca/~oz/hash.html */ 
unsigned long
hash(const char *str, int len)
{
	unsigned long hash = 5381;
	int i;

	for (i = 0; i < len; ++i) {
		hash = ((hash << 5) + hash) + str[i]; /* hash * 33 + c */
	}

	return hash;
}

void
init_table(hash_table *map)
{
	/* init buckets to default size and to be empty */
	map->buckets = (node **) calloc(NUM_BUCKETS_DEFAULT, sizeof(node *));
	map->size = NUM_BUCKETS_DEFAULT;
	map->occupancy = 0;
}

void
table_add(char *word, int len, hash_table *map, int with_val)
{
	int hax = len == -1 ? strlen(word) : len;
	int hash_in_bucket = hash(word, hax) % map->size;

	/* printf("adding "); */
	/* if (len > 0) { */
	/* 	int i; */
	/* 	for (i = 0; i < len; ++i) putchar(word[i]); */
	/* } else if (len == -1) { */
	/* 	printf("%s", word); */
	/* } else { */
	/* 	assert(0); */
	/* } */
	/* printf(" to buckets %p\n", map->buckets); */

	node **entry = &map->buckets[hash_in_bucket];
	if (*entry) {
		node *prev = *entry;
		node *curr = (*entry)->next;

		int hax = len == -1 ? strlen(prev->key) : len;

		if (!strncmp(prev->key, word, hax)) {
			++prev->val;
			goto end;
		}

		while (curr) {
			hax = len == -1 ? strlen(prev->key) : len;
			if (!strncmp(curr->key, word, hax)) {
				++curr->val;
				prev->next = curr->next;
				curr->next = *entry;
				*entry = curr;
				goto end;
			}

			curr = curr->next;
			prev = prev->next;
		}

		prev->next = make_node(word, len, with_val, NULL);
		++map->occupancy;
	} else {
		*entry = make_node(word, len, with_val, NULL);
		++map->occupancy;
	}

end: /* idk */
	resize_if_needed(map);
}

void
resize_if_needed(hash_table *map)
{
	if (map->occupancy > map->size * MAX_THRESHOLD) {
		/* printf("================= before\n"); */
		/* table_output(map); */
		/* printf("\n"); */

		int old_size = map->size;
		map->size *= 2;
		map->occupancy = 0; 

		node **old_buckets = map->buckets;
		map->buckets = (node **) calloc(map->size, sizeof(node *));

		int i;
		for (i = 0; i < old_size; ++i) {
			node *curr = old_buckets[i];
			while (curr) {
				node *to_del = curr;
				table_add(curr->key, -1, map, curr->val);
				curr = curr->next;
				free(to_del);
			}
		}

		free(old_buckets);

		/* printf("================= after\n"); */
		/* table_output(map); */
		/* printf("\n"); */
	}
}

void
table_destroy(hash_table *map)
{
	int i;
	for (i = 0; i < map->size; ++i) {
		node *curr = map->buckets[i];
		while (curr) {
			node *to_del = curr;
			curr = curr->next;
			free(to_del->key);
			free(to_del);
		}
	}
	free(map->buckets);
}

void
table_output(hash_table *map)
{
	int i;
	for (i = 0; i < map->size; ++i) {
		/* printf("BUCKET %d\n", i); */
		node *curr = map->buckets[i];
		while (curr) {
			printf("%s:%d\n", curr->key, curr->val);
			curr = curr->next;
		}
	}
}

/***************\
 *  word count  |
 ***************/

struct wc {
	hash_table map;
};

void
wc_add(char *word, int len, struct wc *wc)
{
	table_add(word, len, &wc->map, 1);
}

struct wc *
wc_init(char *word_array, long size)
{
	struct wc *wc;

	wc = (struct wc *)malloc(sizeof(struct wc));
	assert(wc);
	init_table(&wc->map);
	
	char *begin, *end;
	begin = end = word_array;
	if (!word_array) {
		return NULL;
	}

	int i = 0;
	for (;;) {
		while (isspace(*begin)) {
			++begin;
			++end;
			++i;
		}
		while (!isspace(*end) && i < size) {
			++end;
			++i;
		}
		
		const int WORDSIZE = end - begin;
		if (WORDSIZE == 0) {
			break;
		} else {
			wc_add(begin, WORDSIZE, wc);

			begin = end;
		}
	}

	return wc;
}

void
wc_output(struct wc *wc)
{
	table_output(&wc->map);
}

void
wc_destroy(struct wc *wc)
{
	table_destroy(&wc->map);
	free(wc);
}












