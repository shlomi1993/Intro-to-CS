# Assignment 5 - Stack, Queue and Bracket Balance Problem

In this assignment we had to implement two fundamental Data Structures - a Stack and a Queue.

## Part 1 - Stack

The files stack.h and stack.c contains the impelentation of the stack.

This implenetation of stack allows to:
- initStack -- initialize a stack data-structure.
- destroyStack -- free memory.
- isStackEmpty -- return 1 if the stack is empty, 0 otherwise.
- lenOfStack -- return the number of elemets in the stack.
- capacityOfStack -- return the size of the currently alloacted array in the memory.
- push -- add element to the stack.
- pop -- remove the newest element in the stack (the one on the top).
- top -- return the element on top of the stack
- printStack -- print stack elements in their order.

![image](https://user-images.githubusercontent.com/72878018/120076273-6d444d00-c0ad-11eb-877b-ab598c412b4a.png)

## Part 2 - Queue

The files queue.h and queue.c contains the impelentation of the queue.

This implenetation of stack allows to:
- initQueue -- initialize a queue.
- destroyQueue -- free memory.
- isQueueEmpty -- return 1 if the queue is empty, 0 otherwise.
- lenOfQueue -- return the number of elemets in the queue
- capacityOfQueue -- return the size of the currently alloacted array in the memory.
- enqueue -- add element to the queue.
- dequeue -- remove element the oldest element in the queue.
- peek -- return the element in the head of the queue.

![image](https://user-images.githubusercontent.com/72878018/120076303-906efc80-c0ad-11eb-8ae0-30a68fb1fc0e.png)

## Part 3 - String - bracket balance problem

In this part we used the stack to solve the bracket balance problem in a given string.
The solution is in the files strings.c and strings.h.

![image](https://user-images.githubusercontent.com/72878018/120076325-a7adea00-c0ad-11eb-85be-ac1a9ca62a01.png)

## Notes

- This task was also an intro to generics because the elements in both data structure were structs (element).
- The main.c is only a driver/test code.
