#include <stddef.h>
#include <stdio.h>    
#include <unistd.h>
#include <pthread.h>

// typedef char ALIGN[8];

// union header {
//     struct {
//         size_t size;
//         unsigned is_free;
//         struct header_t *next;
//     } h;
//     ALIGN headerBlock;
// };
// typedef union header header_t;

// header_t *head, *tail;
// pthread_mutex_t global_malloc_lock;

// header_t *get_free_block(size_t size){
//     header_t *start = head;
//     while(start){
//         if(start->h.is_free && start->h.size >= size){
//             return start;
//         }
//         start = start->h.next;
//     }
//     return NULL;

// }

// void *malloc(size_t size){
//    size_t total_size;
//    void *start;
//    header_t *header;
   
//    pthread_mutex_lock(&global_malloc_lock);
//    header = get_free_block(size);
//    if(header){
//         header->h.is_free = 0;
//         pthread_mutex_unlock(&global_malloc_lock);
//         return (void *)(header + 1);
//    }
//    start = sbrk(sizeof(header_t) + size);
//    if(start == (void *) -1){
//         pthread_mutex_lock(&global_malloc_lock);
//         return NULL;
//    }
//    header = start;
//    header->h.size = size;
//    header->h.next = NULL;
//    header->h.is_free = 0;
//    if(!head){
//     head = header;
//    }
//    if(tail){
//     tail->h.next= header;
//    }
//    tail = header;
//    pthread_mutex_unlock(&global_malloc_lock);
//    return (void*)(header + 1);
   
// }
pthread_t thread1, thread2;
pthread_mutex_t mutex;

int testN = 0;
int* testP = &testN;

void* function1(){   
    pthread_mutex_lock(&mutex); 
    printf("VALUE: %d \n", *testP);
    while(*testP < 0xFFFFFFFF){
        *testP+=1;
    }
    printf("VALUE POST ADD: %d \n", *testP);
    pthread_mutex_unlock(&mutex);
}

void* function2(){
    pthread_mutex_lock(&mutex);
    printf("VALUE F2: %d \n", *testP);
    while(*testP < (0xFFFFFFFF * 4)){
        *testP+=2;
    }
    printf("VALUE POST ADD F2: %d \n", *testP);
    pthread_mutex_unlock(&mutex);

}


int main(int argc, char *argv[]){
    if (pthread_mutex_init(&mutex, NULL) != 0) { 
		printf("\n mutex init has failed\n"); 
		return 1; 
	} 
    
    pthread_create( &thread1, NULL, &function1, NULL);
    pthread_create( &thread2, NULL, &function2, NULL);
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
    pthread_mutex_destroy(&mutex); 
    //malloc(21);
}


