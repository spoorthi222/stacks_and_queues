#include<assert.h>
#include "stack.h"
#include<stdint.h>
#include <stddef.h> //for NULL defining

Stack stack_new(uint32_t size) {
    size = ( size > 0 && size < MAX_DEPTH)? size : MAX_DEPTH;
    Stack s1 = { size, -1, {0} };
    return s1;
}

uint8_t stack_full( const Stack *stk){
    assert( stk != NULL);
    return ( (stk->top+1) == stk->size );
}

uint8_t stack_empty(const Stack *stk){
    assert( stk != NULL );
    return ( stk->top == -1);
}

Stack* stack_push(Stack *stk,char ele,StackResult *res){
    assert( stk != NULL );
    if( (stk->top+1) < stk->size){
        stk->data[++stk->top] = ele;
        res->status = STACK_OK;
        res->data = ele;
    }else{
        res->status = STACK_FULL;
    }
    return stk;
}

Stack* stack_pop(Stack *stk,StackResult *res){
    assert( stk != NULL );
    if ( stk->top != -1){ //if stk not empty
        res->data = stk->data[stk->top];
        --stk->top;
        res->status = STACK_OK;
    }else{
        res->status = STACK_EMPTY;
    }
    return stk;
}

Stack* stack_peek(Stack *stk, StackResult *res){
    assert( stk != NULL );
    if ( stk->top != -1){ //if stk not empty
        res->data = stk->data[stk->top];
        res->status = STACK_OK;
    }else{
        res->status = STACK_EMPTY;
    }
    return stk;
}

// Returns 1 if character1 and character2 are matching left
// and right Brackets
uint8_t isMatchingPair(char character1, char character2)
{
    if (character1 == '(' && character2 == ')')
        return 1;
    else if (character1 == '{' && character2 == '}')
        return 1;
    else if (character1 == '[' && character2 == ']')
        return 1;
    else
        return 0;
}

// Return 1 if expression has balanced Brackets
uint8_t areBracketsBalanced(char exp[])
{
    int i = 0;

    // Declare an empty character stack
    Stack s1 = stack_new(20);
    Stack *stack = &s1;
    StackResult res;
    assert (stack_empty(stack));

    // Traverse the given expression to check matching
    // brackets
    while (exp[i])
    {
        // If the exp[i] is a starting bracket then push
        // it
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '['){
             stack = stack_push(stack, exp[i],&res);
             //printf("%c",res.data);
        }


        // If exp[i] is an ending bracket then pop from
        // stack and check if the popped bracket is a
        // matching pair*/
        if (exp[i] == '}' || exp[i] == ')'
            || exp[i] == ']') {
            // If we see an ending bracket without a pair
            // then return false
            if (stack ->top == -1)
                return 0;

            // Pop the top element from stack, if it is not
            // a pair bracket of character then there is a
            // mismatch.
            // his happens for expressions like {(})
            else {
                stack = stack_pop(stack,&res);
                if (!isMatchingPair(res.data, exp[i]))
                    return 0;
            }

        }
        i++;
    }

    // If there is something left in expression then there
    // is a starting bracket without a closing
    // bracket
    if (stack->top == -1){
         return 1; // balanced
    }
    else{
        return 0; // not balanced
    }

}
