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

pthread_mutex_t mutext;

int testN = 0;
int* testP = &testN;

void testMutex(int inputA, int inpuptB){
    printf("TEST VALUE: %d\n", *testP);
    pthread_mutex_lock(&mutext);
    *testP+=2;
    printf("TEST VALUE: %d\n", *testP);

}
void testMutextSecond(){
    *testP+=1;
    printf("TEST VALUE FROM SEECOND FUNCTION: %d", *testP);
}

int main(int argc, char *argv[]){
    testMutex(1, 2);
    testMutextSecond();
    //malloc(21);
}


