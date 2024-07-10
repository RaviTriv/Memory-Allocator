#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef char ALIGN[8];

union header
{
    struct
    {
        size_t size;
        unsigned is_free;
        struct header_t *next;
    } h;
    ALIGN headerBlock;
};
typedef union header header_t;

header_t *head = NULL, *tail = NULL;
pthread_mutex_t mutex;

header_t *get_free_block(size_t size)
{
    header_t *start = head;
    while (start)
    {
        if (start->h.is_free && start->h.size >= size)
        {
            return start;
        }
        start = start->h.next;
    }
    return NULL;
}

void *malloc(size_t size)
{
    size_t total_size;
    void *start;
    header_t *header;

    pthread_mutex_lock(&mutex);
    header = get_free_block(size);
    if (header)
    {
        header->h.is_free = 0;
        return (void *)(header + 1);
    }
    start = sbrk(sizeof(header_t) + size);
    if (start == (void *)-1)
    {
        return NULL;
    }
    header = start;
    header->h.size = size;
    header->h.next = NULL;
    header->h.is_free = 0;
    if (!head)
    {
        head = header;
    }
    if (tail)
    {
        tail->h.next = header;
    }
    tail = header;
    pthread_mutex_unlock(&mutex);
    return (void *)(header + 1);
}

int main(int argc, char *argv[])
{
    int n = 5;
    int *t1 = malloc(n);

    for (int i = 0; i < n; i++)
    {
        *(t1 + i) = 19 + i;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d: %d \n", i, *(t1 + i));
    }
}
