#include <stdlib.h>
#include <stdio.h>

#include "allocator.h"
#include "dlist.h"

int main(){

    printf("initialzing allocator\n");
    int x = allocator_init(1500);
    printf("allocation successful");
    int sizes[12] = {200,5000, 50, 25, 25, 300, 50, 50, 20, 20 , 10,50};
    int i;
    int *result;
    printf("testing first fit\n");
    for( i=0; i< 12; i++){
        result = allocate(1, sizes[i], free_list, allocated_list);
        if (result != NULL){
            //temp_node = dlist_iter_begin(allocated_list);
            deallocate(result);
        }
    
    }
    printf("testing best fit\n");
    for( i=0; i< 12; i++){
        result = allocate(2, sizes[i], free_list, allocated_list);
        if (result != NULL){
            deallocate(result);
        }
    
    }
    printf("testing worst fit\n");
    for( i=0; i< 12; i++){
        result = allocate(3, sizes[i], free_list, allocated_list);
        if (result != NULL){
            deallocate(result);
        
        }
    
    }

}
