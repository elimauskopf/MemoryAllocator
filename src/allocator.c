//Eli Mauskopf
//Fall 2018


#include <stdlib.h>
#include <stdio.h>

#include "dlist.h"
#include "dnode.h"
#include "allocator.h"

int 
allocator_init(size_t size){
    mem_pointer = malloc(size);
    if (mem_pointer == NULL){
        return -1;
    }
    free_list = dlist_create();
    allocated_list = dlist_create();
    dlist_add_front(free_list, mem_pointer, size ); //add node with memory to list 

    return 0;
    
}

struct dnode *Firstfit(size_t size, struct dlist *free){
   
    struct dnode *cur_node = dlist_iter_begin(free);

    if(size <= cur_node->size){
        return cur_node;
    }
    while(cur_node != NULL){
        if(size <= cur_node->size){
            return cur_node;
        } else {
            cur_node  = dlist_iter_next(free);
        }        
    }


        
    return NULL; //couldnt find apprpriate size
    
}


struct dnode *Bestfit(size_t size, struct dlist *free){
   
    struct dnode *cur_node = dlist_iter_begin(free); //initialize best fit node to return, and cur node for iteration
    struct dnode *best_fit_node = NULL;
    int diff = 999999;  //create diff and temp dif for comparison of fits
    int temp_diff;

    if (cur_node == NULL){
        return NULL; // list was empy
    }


    while(cur_node != NULL){ //loop through free list and find node with best fit
        if(size <= cur_node->size){
            temp_diff = cur_node->size - size;
            if(temp_diff < diff){
                best_fit_node = cur_node;
                diff = temp_diff;
            }
        } 
         cur_node  = dlist_iter_next(free);
                
    }

    if(best_fit_node == NULL){
        return NULL;
    }

    
    return best_fit_node; 
    
}


struct dnode *Worstfit(size_t size, struct dlist *free){
   
    struct dnode *cur_node = dlist_iter_begin(free); //initialize best fit node to return, and cur node for iteration
    struct dnode *worst_fit_node = NULL;
    int diff = -999999;  //create diff and temp dif for comparison of fits
    int temp_diff;

    if(cur_node == NULL){
        return NULL; //list was empty
    }

    while(cur_node != NULL){ //loop through free list and find node with best fit
        if(size <= cur_node->size){
            temp_diff = cur_node->size - size;
            if(temp_diff > diff){
                worst_fit_node = cur_node;
                diff = temp_diff;
            }
        } 
           cur_node  = dlist_iter_next(free);
                
    }

    if(worst_fit_node == NULL){
        return NULL;
    }

    return worst_fit_node; //couldnt find apprpriate size
    
}

int *allocate(int strategy, size_t size, struct dlist *free, struct dlist *allocated){
        struct dnode *found_node = NULL;

        if(strategy ==1){
            found_node = Firstfit(size, free);
        } 
        else if (strategy == 2){
            found_node = Bestfit(size, free);
        }
        else {
            found_node = Worstfit(size, free);
        }
    
        if(found_node == NULL){
            printf("could not find node\n");
            return NULL;
        }
        printf("found node has size: %d\n", found_node->size);
        int *pointer = found_node->data; 
        dlist_add_front(allocated, found_node->data, size); 
        found_node->size -= size;
        found_node->data += size;

        return pointer;
}

int deallocate(void *ptr){
    /*
    struct dnode *cur_node = dlist_iter_begin(allocated_list);
    bool found = false;
    printf("cur node size %d\n", cur_node->size);
    while(dlist_iter_has_next(allocated_list) || found == false ){
        if(ptr == cur_node->data){
            found = true;
        } else {
            cur_node  = dlist_iter_next(allocated_list);
        }        
    }
    if(found == false){
        return -1;
    }
        printf("got here\n");
  */  

   struct dnode *temp =  dlist_iter_begin(allocated_list); 
   struct dnode *result = NULL;
    bool found = false;

    //check first node
    if(temp->data == ptr){
        result = temp;
        found = true;
    }
   while(dlist_iter_has_next(allocated_list) && found == false){
            if (temp->data == ptr){
                found = true;
                result = temp;
            }
        temp = dlist_iter_next(allocated_list);
           }
   if( result == NULL){
        return -1;
   }

  // printf("found node size %d\n", result->size);
   dlist_add_front(free_list, result->data, result->size);
   dlist_find_remove(allocated_list, ptr);
   return 0; 
}
