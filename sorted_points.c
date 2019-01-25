

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "point.h"
#include "sorted_points.h"

/* this structure should store all the points in a list in sorted order. */
struct sorted_points {
	double data[2];
	struct sorted_points *next; 

	/* you can define this struct to have whatever fields you want. */
};

/* think about where you are going to store a pointer to the next element of the
 * linked list? if needed, you may define other structures. */

struct sorted_points *
sp_init()
{
	struct sorted_points *sp; 

	sp = (struct sorted_points *)malloc(sizeof(struct sorted_points));
	assert(sp);

	sp->next = NULL; // set the next point as NULL
	return sp; // return the updated node
	
}

void
sp_destroy(struct sorted_points *sp)
{
//	TBD();
	free(sp);

}

int
sp_add_point(struct sorted_points *sp, double x, double y)
{
	struct sorted_points *temp, *new; // declare two nodes
	temp = sp_init(); // init temp node
	temp->data[0] = x;
	temp->data[1] = y;
	 

	if (sp == NULL){  // if first not exist
		sp = temp;	 // set temp as first node
	}
	else{    
		new = sp;
	while (new->next != NULL){
		new = new->next;
	}
	new->next = temp; // add the temp node at the end
	}

	return 0;
}

int
sp_remove_first(struct sorted_points *sp, struct point *ret)
{
	
	struct sorted_points *new = NULL;

	if (sp == NULL){
	return 0;	
	}
 	
	else {
	new = sp->next;
	ret->x = sp->data[0];
	ret->y = sp->data[1];
	free (sp);
	sp = new;
	}

	return 1;
}

int
sp_remove_last(struct sorted_points *sp, struct point *ret)
{

	if(sp->next == NULL){ // if only one node
	ret->x = sp->data[0];
	ret->y = sp->data[1];
	free(sp);
	return 0;
	}

	struct sorted_points * temp;
	while (temp->next->next !=NULL) // if the next two is not NULL
		{ temp = temp->next; //move one to the right
		} 


	ret->x = temp->next->data[0];
	ret->y = temp->next->data[1];
	free(temp->next);
	temp->next =NULL;
	return 1;
	
}

int
sp_remove_by_index(struct sorted_points *sp, int index, struct point *ret)
{
	int i = 0;

    struct sorted_points *temp = sp;
    struct sorted_points *temp2 = NULL;

    if (index == 0) { // if want to remove index 0(first node), call remove first node
        return sp_remove_first(sp,ret);
    }
	
	if (index <0){return 0;}

    for (i = 0; i <= index; i++) { //iterate till reaching the desired node
        if (temp->next == NULL) { // if list is too short 
            return 0;
        }
        temp = temp->next;
    }

    temp2 = temp->next;
	ret->x = temp2->data[0];
	ret->y = temp2->data[1];
    temp->next = temp2->next;
    free(temp2);

	return 1;
}

int
sp_delete_duplicates(struct sorted_points *sp)
{
	//TBD();
	return -1;
}
