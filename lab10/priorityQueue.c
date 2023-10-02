#include <stdio.h>
#include <stdlib.h>
typedef struct heap
{
    int *data;
    int last_index;
} heap_t;

heap_t *init_heap(int m)
{
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    heap->data = (int *)malloc(sizeof(int) * m);
    heap->last_index = 0;
    return heap;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

heap_t *perculateUp(heap_t *h, int i)
{
    while (i > 1)
    {
        if (h->data[i] > h->data[i / 2])
        {
            // value of current node > parent
            swap(&h->data[i], &h->data[i / 2]);
            i /= 2;
        }
        else
            break;
    }
    return h;
}

heap_t *insert(heap_t *h, int data)
{
    h->last_index++;
    // the list start with index 1
    h->data[h->last_index] = data;
    return perculateUp(h, h->last_index);
}

heap_t *perculateDown(heap_t *h, int i)
{
    // compare node's value to their children
    while (i < h->last_index)
    {
        int left = (h->last_index >= 2 * i) ? h->data[2 * i] : -1;
        int right = (h->last_index >= 2 * i + 1) ? h->data[2 * i + 1] : -1;
        if (left > right && left > h->data[i])
        {
            swap(&h->data[2 * i], &h->data[i]);
            i = 2 * i;
        }
        else if (right > left && right > h->data[i])
        {
            swap(&h->data[2 * i + 1], &h->data[i]);
            i = 2 * i + 1;
        }
        else
            break;
    }
    return h;
}

heap_t *delete_max(heap_t *h)
{
    h->data[1] = h->data[h->last_index];
    h->last_index--;
    h->last_index = (h->last_index < 0) ? 0 : h->last_index;
    return perculateDown(h, 1);
}

int find_max(heap_t *h)
{
    return (h->last_index > 0) ? h->data[1] : -1;
}

heap_t *update_key(heap_t *h, int old, int new)
{
    int i;
    for (i = 1; i <= h->last_index; i++)
    {
        if (h->data[i] == old)
        {
            h->data[i] = new;
            break;
        }
    }
    h = (h->data[i] > h->data[i / 2]) ? perculateUp(h, i) : perculateDown(h, i);
    return h;
}

void bfs(heap_t *h)
{
    int i;
    for (i = 1; i <= h->last_index; i++)
    {
        printf("%d ", h->data[i]);
    }
    printf("\n");
}

int main(void)
{
    heap_t *max_heap = NULL;
    int m, n, i;
    int command, data;
    int old_key, new_key;
    scanf("%d %d", &m, &n);
    max_heap = init_heap(m);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            scanf("%d", &data);
            insert(max_heap, data);
            break;
        case 2:
            delete_max(max_heap);
            break;
        case 3:
            printf("%d\n", find_max(max_heap));
            break;
        case 4:
            scanf("%d %d", &old_key, &new_key);
            update_key(max_heap, old_key,
                       new_key);
            break;
        case 5:
            bfs(max_heap);
            break;
        }
    }
    return 0;
}