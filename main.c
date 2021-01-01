#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
#include "stack.h"
#include "queue.h"

void test_empty_stack(){
    Stack s1 = stack_new(20);
    Stack *stk = &s1;
    assert (stack_empty(stk));

}

void test_full_stack(){
    Stack s1 = stack_new(2);
    Stack *stk = &s1;
    StackResult res;
    stk = stack_push(stk,10,&res);
    assert(res.status == STACK_OK);
    stk = stack_push(stk,20,&res);
    assert(res.status == STACK_OK);
    stk = stack_push(stk,30,&res);
    assert(res.status == STACK_FULL);
    assert(stack_full(stk)==1);
}

void test_stack(){
    Stack s1 = stack_new(5);
    Stack *stk = &s1;
    StackResult res;
    stk = stack_push(stk,10,&res);
    stk = stack_push(stk,20,&res);
    stk = stack_peek(stk,&res);
    assert( res.status == STACK_OK && res.data == 20);
    stk = stack_pop(stk,&res);
    assert( res.status == STACK_OK && res.data == 20);
    stk = stack_peek(stk,&res);
    assert( res.status == STACK_OK && res.data == 10);
    stk = stack_pop(stk,&res);
    assert(stack_empty(stk)==1);

}

void test_balanced_brackets(){
    assert(areBracketsBalanced("{()}"));
}

void test_empty(){
    Queue q1 = queue_new(2);
    Queue *q = &q1;
    assert(queue_empty(q));
}

void test_add(){
    Queue q1 = queue_new(3);
    Queue *q = &q1;
    QueueResult res;

    q =queue_add(q,10,&res);
    q =queue_add(q,20,&res);
    q =queue_add(q,30,&res);

    assert(queue_length(q)==3);
    q =queue_add(q,40,&res);
    assert(res.status == QUEUE_FULL);
    assert(queue_full(q));

}

void test_Qdelete(){
    Queue q1 = queue_new(3);
    Queue *q = &q1;
    QueueResult res;

    q =queue_add(q,10,&res);
    q =queue_add(q,20,&res);
    q =queue_add(q,30,&res);

    q = queue_delete(q, &res);
    assert( res.data == 10);
    //printf("%d\n",queue_length(q));
    assert(queue_length(q) == 2);

    q = queue_delete(q, &res);
    q = queue_delete(q, &res);
    q = queue_delete(q, &res);

    assert(res.status == QUEUE_EMPTY);
    assert(queue_empty(q));
    assert(queue_length(q) ==  0 );
}

int postfix(char p[20])
{
	Stack s = stack_new(5);
	Stack *stk = &s;

	StackResult res;
	for(int i=0;i<strlen(p);i++)
    {
        if(isdigit(p[i]))
        {
            stk=stack_push(stk,p[i],&res);
         }
        else
        {
           char a,b;
            int c=0;
            a = stk->data[stk->top];
            stk = stack_pop(stk,&res);
            b = stk->data[stk->top];
            stk = stack_pop(stk,&res);
            if(p[i]=='+')
            {
            c = a -'0' + b - '0';
            //printf("%d",c);
            }
            else if(p[i]=='-')
            {
                c = (b-'0') - (a-'0');
            }
            else if(p[i]=='*')
            {
                c = (b-'0') * (a-'0');
            }
            else if(p[i]=='/')
            {
                c = (b-'0')/(a-'0');
            }
            char pf = c+'0';
            stk = stack_push(stk,pf,&res);
        }
    }

stk = stack_peek(stk,&res);
assert(res.data=='6');
}

void constant_memory()
{
Queue k= queue_new(10);
Queue *q=&k;
QueueResult Qres;

q=queue_add(q,10,&Qres);
q=queue_add(q,20,&Qres);
q=queue_add(q,30,&Qres);
q=queue_add(q,40,&Qres);

assert(q->count==4);
int d2count=1;
int d3count=q->count;

while(d2count<=d3count)
{
int dcount=1;
while(dcount<q->count)
{
	q = queue_delete(q,&Qres);
	q = queue_add(q,Qres.data,&Qres);
	dcount++;
}
	q = queue_delete(q,&Qres);

d2count++;
}
assert(Qres.data==10);
}

void stackTOqueue()
{
	Stack stk = stack_new(10);
Stack *s=&stk;
StackResult Sres;

Queue k= queue_new(10);
Queue *q=&k;
QueueResult Qres;

s = stack_push(s,93,&Sres);
s = stack_push(s,53,&Sres);
s = stack_push(s,73,&Sres);
s = stack_push(s,83,&Sres);

int element = 53;
int count = 0;
int i=0;
while(i<=s->top+1)
{
s = stack_peek(s,&Sres);
if(Sres.data==element)
{
	break;
}
else
{
	s = stack_pop(s,&Sres);
	q = queue_add(q,Sres.data,&Qres);
	count++;
}
i++;
}

int dcount=count;
int d1count=count;
while(count!=0)
{
	q= queue_delete(q,&Qres);
	s= stack_push(s,Qres.data,&Sres);
	count--;
}
s = stack_peek(s,&Sres);
assert(Sres.data==73);

while(dcount!=0)
{
	s=stack_pop(s,&Sres);
	q=queue_add(q,Sres.data,&Qres);
	dcount--;
}

s = stack_peek(s,&Sres);
assert(Sres.data==53);

while(d1count!=0)
{
	q= queue_delete(q,&Qres);
	s= stack_push(s,Qres.data,&Sres);
	d1count--;
}

s = stack_peek(s,&Sres);
assert(Sres.data==83);

}

Stack* deleteQueue(Stack *s1,Stack *s2,StackResult Sres1,StackResult Sres2)
{
	while(s1->top>-1)
	{
	s1 = stack_pop(s1,&Sres1);
	int32_t popelement = Sres1.data;
	s2 = stack_push(s2,popelement,&Sres2);
	}
	s2 = stack_pop(s2,&Sres2);
	return s2;
}

void queueUsingStacks()
{
	Stack stk1 = stack_new(10);
	Stack *s1=&stk1;
	StackResult Sres1;

	s1 = stack_push(s1,10,&Sres1);
	s1 = stack_push(s1,20,&Sres1);
	s1 = stack_push(s1,50,&Sres1);

	Stack stk2 = stack_new(10);
	Stack *s2=&stk2;
	StackResult Sres2;


	s2 = deleteQueue(s1,s2,Sres1,Sres2);
	s1 = stack_peek(s1,&Sres1);
	assert(s1->top==-1);

	s2 = stack_peek(s2,&Sres2);
	assert(Sres2.data==20);

}






int main()
{
    //printf("Hello world!\n");
    //test_empty_stack();
    //test_full_stack();
    //test_stack();
    //test_balanced_brackets();
    //test_empty();
    //test_add();
    //test_Qdelete();

    //char p[20]="423+1*+3-";
    //postfix(p);

   // constant_memory();



    //stackTOqueue();


    queueUsingStacks();

    return 0;
}
