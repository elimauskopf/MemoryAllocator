#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_


struct dlist* free_list;
struct dlist* allocated_list;
int *mem_pointer;
int allocator_init(size_t size);

struct dnode *Firstfit(size_t size, struct dlist *free);
struct dnode *Bestfit(size_t size, struct dlist *free);
struct dnode *Worstfit(size_t size, struct dlist *free);

int *allocate(int strategy, size_t size, struct dlist *l, struct dlist *allocated);

int deallocate(void *ptr);

#endif /* _ALLOCATOR_H_ */
