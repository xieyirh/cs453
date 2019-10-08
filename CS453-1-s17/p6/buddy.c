#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "buddy.h"
#include <pthread.h>

static void *pool = NULL;
static Header *freelist[MAX_INDEX];
static unsigned int index_boundary = 0;
pthread_mutex_t mutex;

unsigned int get_list_index(size_t);
unsigned int init_list_index(size_t);

/**
 * malloc function allocates size bytes and return a pointer to the allocated memory
 * @param size The byte size
 * @return a pointer to the allocated memory
 */
void *malloc(size_t size)
{
    pthread_mutex_lock(&mutex);
    void * ret = buddy_malloc(size);
    pthread_mutex_unlock(&mutex);
    return ret;

}

/**
 * Free the memory space pointed by ptr if ptr is NULL, no operation is performed
 * @param ptr space pointed by ptr
 */

void free(void *ptr)
{
    pthread_mutex_lock(&mutex);
    buddy_free(ptr);
    pthread_mutex_unlock(&mutex);
}

/**
 * Allocate memmory for an array of nmemb elements of size bytes each and returns a pointer to the
 * allocated memory
 * @param nmemb array size
 * @param size byte size
 * @return a pointer to the allocated memory
 */
void *calloc(size_t nmemb, size_t size)
{
   pthread_mutex_lock(&mutex);
   void * ret = buddy_calloc(nmemb,size);
   pthread_mutex_unlock(&mutex);
    return ret;
}

/**
 * Change the size fo the memory block pointed by ptr to size bytes.
 * @param ptr Space pointed by ptr
 * @param size new memory size
 * @return a pointer to the new allocated memory
 */
void *realloc(void *ptr, size_t size)
{
   pthread_mutex_lock(&mutex);
   void *ret =buddy_realloc(ptr, size);
   pthread_mutex_unlock(&mutex);
    return ret;
}
    
/**
 * Initialize the memory pool; The memory pool size has to be at least larger than header size
 * @param size memory pool size
 */
void buddy_init(size_t size)
{   
    pthread_mutex_lock(&mutex);
    if( size == 0){
        pool = sbrk(DEF_MEMORY_SIZE);
        if(pool < 0 || errno == ENOMEM){
//            perror("Memory allocation fails!\n");
            exit(ENOMEM);
        }
        index_boundary = DEF_INDEX - 1;
    }
    else if (size < sizeof(Header) + 1){
  //      printf("memory pool is too small to use, the minimumm size is %lu\n", sizeof(Header) + 1);
        exit(ENOMEM);
    }
    else if ( size >= MAX_MEMORY_SIZE) {
    //    perror("Required memory is too big!\n");
        exit(ENOMEM);
    }
    else{
        unsigned int index = get_list_index(size);
    
        pool =sbrk(1ll << index);
        if(pool < 0 || errno == ENOMEM){
      //      perror("Could not allocate memory pool!\n");
            exit(ENOMEM);
        }
        index_boundary = index;
    }
        freelist[index_boundary]= (Header *)pool;
        freelist[index_boundary]->tag = 0;
        freelist[index_boundary]->prev = NULL;
        freelist[index_boundary]->next = NULL;
        freelist[index_boundary]->kval = index_boundary;
    pthread_mutex_unlock(&mutex);
}

/**
 * Get freelist index number
 * @param size size of bytes
 * @return freelist index number, the number has to be in power of 2
 */
unsigned int get_list_index(size_t size)
{
    unsigned int index;

    for(index = 0; index < size + sizeof(Header); index++){
        if ((size <= (1ll << index)))
            break;
    }
    return index;
}

/**
 * User implementation malloc, see description of malloc above
 */
void *buddy_malloc(size_t size)
{
    Header *right;
    Header *left;
    if(pool == NULL){
        buddy_init(0);
    }

    if(size <= 0){
        errno = ENOMEM;
        return NULL;
    }


    unsigned int index = get_list_index(size + sizeof(Header));

    if(index > index_boundary){
      //  perror("Required memory size is too big, no space available!\n");
        errno = ENOMEM;
        return NULL;
    }

    if (freelist[index] != NULL){

        left = freelist[index];
        right = freelist[index]->next;
        left->tag = 1;
        left->prev =NULL;
        left->next = NULL;
        
        if(right == NULL){
            freelist[index]= NULL;
        }
        else {
            freelist[index]= right;
            right->prev = NULL;

        }
        return (char*)left + sizeof(Header); //header block is in front of data block
    }


    unsigned int avail;
    for (avail = index;!freelist[avail]; avail++);

    Header *left_half, *right_half;

    //search the next available empty list
    while(avail != index){
        left_half =freelist[avail];
        left_half->kval = left_half->kval - 1;
        left_half->tag = 0;
        right_half =(Header*) ((char*)left_half + (1ll<<left_half->kval));
        right_half->kval = left_half->kval;
        right_half->tag = 0;

        if(freelist[avail]->next == NULL){
            freelist[avail]= NULL;
        }
        else {
            freelist[avail] = freelist[avail]->next;
            freelist[avail]->prev = NULL;
        }

        avail--;

        left_half->next = right_half;
        left_half->prev = NULL;
        right_half->prev = left_half;
        right_half->next = NULL;

        freelist[avail]= left_half;

    }

    Header *ret_block = freelist[index];

    if(freelist[index]->next == NULL){
        freelist[index]= NULL;
    }
    else {
        freelist[index] = freelist[index]->next;
        freelist[index]->prev = NULL;
    }

    ret_block->tag = 1;
    ret_block->prev = NULL;
    ret_block->next = NULL;
    
    return (char*)ret_block + sizeof(Header); //header is in front of data block
}

/**
 * get buddy block positon
 * @param ptr pointer to the head of block
 * @return return the buddy pointer if there is any, otherwise return null
 */
Header * get_buddy(Header *ptr) 
{
    size_t  base = (size_t) pool;
    size_t current = (size_t)ptr;
    size_t buddy_address = ((current -base) ^ (1ll<< ptr->kval)) + base;
    Header *buddy = (Header *) buddy_address;
    
    if(ptr->kval == buddy->kval && buddy->tag ==0) 
        return buddy;
    else
        return NULL;
}

/**
 * User implementation of free function, see decription of free above
 */
void buddy_free(void *memory)
{
    if(!memory)
        return ;

    Header *block =(Header *) ((char*) memory - sizeof(Header));
    block->tag =0;
    block->prev = NULL;
    block->next = NULL;

    Header *buddy = get_buddy(block);

    while(buddy){
        if(buddy->prev  && buddy->next){
            buddy->next->prev = buddy->prev;
            buddy->prev->next = buddy->next;
        }
        else if (!buddy->prev && buddy->next){
            buddy->next->prev = NULL;
            freelist[buddy->kval] = buddy->next;
        }
        else if(buddy->prev && !buddy->next){
            buddy->prev->next = NULL;
        }
        else if(!buddy->prev && !buddy->next){
            freelist[buddy->kval] = NULL;
        }

        buddy->tag =0;
        buddy->next = NULL;
        buddy-> prev = NULL;

        if(buddy < block){
            block = buddy;
        }
        block->kval = block->kval + 1;
        if (block->kval == index_boundary)
        	break;
        else
        	buddy = get_buddy(block);
    }

    if(freelist[block->kval] != NULL){
        Header * first = freelist[block->kval];
        first->prev = block;
        block->next = first;
    }
    memory = NULL;
    freelist[block->kval] = block;
}

/**
 * User implementation of calloc function, see description above
 */
void *buddy_calloc(size_t num, size_t size)
{
    if( num == 0 || size == 0)
        return NULL;

    char * ptr = (char*)buddy_malloc(num * size);
    if(ptr == NULL){
      //  perror("Memory allocation fails!\n");
        return NULL;
    }
    
    size_t i;
    for(i = 0; i < num * size; i++){
        *(ptr+i)  = 0;
    }

    return ptr;
}

/**
 * User implementation of realloc function, see description above
 */
void *buddy_realloc(void *ptr, size_t size)
{
    size_t min_size;
    if(ptr != NULL && size == 0){
        free(ptr);
        return NULL;
    }

    if(ptr == NULL)
        return buddy_malloc(size);

    if (ptr != NULL && size != 0){
        void *new;
        new  = buddy_malloc(size);
        Header *src =(Header *)( (char*)ptr - (unsigned int)sizeof(Header));
        if(((1ll<<src->kval) - sizeof(Header))< size)
            min_size = 1ll << src->kval;
        else
            min_size = size;
        buddy_memcp(new, ptr, min_size);
        buddy_free(ptr);
        return new;
    } else 
        return NULL;
}

/**
 * copy memory content from src position to destination
 * @param size bytes of size
 * @return the destination pointer
 */
void *buddy_memcp(void *dest, const void *src, size_t size)
{
    char *destination = (char*)dest;
    char * source = (char*)src;
    size_t i;
    for (i = 0; i < size; i++){
        *(destination + i) = *(source + i);
        }
    return dest;

}

/**
 * Print freelist
 */
void printBuddyLists()
{
/*	printf("-------------- Buddy List --------------\n");
	int i;
	for(i = 0; i < 33; i++)
	{
		printf("[%2d] = %p", i, (void*)freelist[i]);
		if(freelist[i])
		{
			printf(" [%2d-%d]", freelist[i]->kval, freelist[i]->tag);
		}
		Header *current = (Header*)freelist[i];
		while(current)
		{
			current = current->next;
			printf(" --> %p", (void*)current);
			if(current)
			{
				printf(" [%2d-%d]", current->kval, current->tag);
			}
		}
		printf("\n");
	}
  */      
}
/*
int main()
{
    printBuddyLists(); 
    void* memory = buddy_malloc(1LL<<2);
    printBuddyLists(); 
    buddy_free(memory); 
    printBuddyLists();
    exit(0);
}
    
*/
