#include<assert.h>
#include<stdint.h>
#include "queue.h"
#include<stddef.h>
#include<stdio.h>

Queue queue_new(uint32_t size){
    size = ( size > 0 && size < Q_LEN ) ? size : Q_LEN;
    Queue q1 =  { size, 0,0,0,{0} };
    return q1;
}

uint8_t queue_full(Queue *q){
    assert( q != NULL );
    return ( q->count == q->size );
}

uint8_t queue_empty(Queue *q){
    assert( q != NULL );
    return ( q->count == 0 );
}

Queue* queue_add(Queue *q, int32_t ele, QueueResult *res){
    assert( q != NULL );
    if ( q->count < q->size ){
        q->data[q->rear] = ele;
        q->rear = (q->rear+1)%q->size;
        ++q->count;
        res->status = QUEUE_OK;
    }else{
        res->status = QUEUE_FULL;
    }
    return q;
}

Queue* queue_delete(Queue *q, QueueResult *res){
    assert( q != NULL );

    if (q->count != 0){
        res->data = q->data[q->front];
        q->front = (q->front+1)%q->size;
        --q->count;
        res->status = QUEUE_OK;
    }else{
        res->status = QUEUE_EMPTY;
    }
    return q;
}

uint32_t queue_length(Queue *q){
    assert( q != NULL );
    return q->count;
}
