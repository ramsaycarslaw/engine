// Copyright 2020 Ramsay Carslaw

#include <stdio.h>

typedef unsigned int (*fnPtr)();
typedef unsigned int (*fnPtrF1)(float);

typedef struct _State
{
     fnPtr init;
     fnPtrF1 update;
     fnPtrF1 draw;
     fnPtr destroy;
} State;

typedef struct _StateManager
{
     State **stack;
     int capacity;
     int top;
} StateManager;

/*
 * The main function used to drive all the other functions
 */
int
main(int argc, char **argv)
{
     printf("Hello World\n");
     return 0;
}
