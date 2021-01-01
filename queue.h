#include<stdint.h>
#include "appconst.h"
#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct _queue_ Queue;

struct _queue_ {
    uint32_t size;
    uint32_t count;
    uint32_t rear;
    uint32_t front;
    int32_t data[Q_LEN];
};

typedef struct _queue_result_ QueueResult;

struct _queue_result_ {
    int32_t data;
    uint32_t status;
};

/* public interface */

Queue queue_new(uint32_t size);
uint8_t queue_full(Queue *q);
uint8_t queue_empty(Queue *q);
Queue* queue_add(Queue *q, int32_t ele, QueueResult *res);
Queue* queue_delete(Queue *q, QueueResult *res);
uint32_t queue_length(Queue *q);


#endif // QUEUE_H_INCLUDED
