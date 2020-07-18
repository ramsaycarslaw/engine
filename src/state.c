// Copyright (C) 2020 Ramsay Carslaw
// File: /src/state.c
// Description: The state manager for the engine implementation
// Author: Ramsay Carslaw
// Created: 2020-07-18

// +=----------------------------------------------------------------------------=+ 
//   Includes
// +=----------------------------------------------------------------------------=+ 

#include "../include/state.h"

// +=----------------------------------------------------------------------------=+ 
//   Function Definitions For Stack Implementation and Memory Managment
// +=----------------------------------------------------------------------------=+

/*
* Initialise the states, returns 0 on success and 1 on failure
*/
int STATEMANAGER_init(StateManager *statemanager)
{
     /* Initialise the capacity to 3, this is also a minumimum */
     statemanager -> capacity = 3;
     
     /* Malloc the stack; memory controlled is passed to calling function*/
     statemanager -> stack = (State**) malloc(statemanager -> capacity * sizeof(State*));
     /* Check that malloc worked as expected */
     if (statemanager -> stack == NULL)
     {
	  printf("ERROR: insufficient mem allocating StateManager...\n");
	  return 1;
     }
     
     /* There is no top when we first initialise */
     statemanager->top = -1;
     return 0;
}

/*
* Used to remove heap alloocated mem in init, returns 0 on success, 1 on error
*/
int STATEMANAGER_free(StateManager *statemanager)
{
     /* Check the statemeanger is valid */
     if (statemanager->stack == NULL)
     {
	  printf("ERROR: statemanger stack is already NULL...\n");
	  return 1;
     }

     /* Pop items from the stack until there are none left*/
     do
     {
	  STATEMANAGER_pop(statemanager);
     }
     while (statemanager -> top > -1);

     /*
       Free all the memory and return zero to show success
      */
     free(statemanager->stack);
     return 0;
}

/*
 * Statemanager scale is used to dynamically scale (increase) the memory 
 * ascociated with statemanager
 */
int STATEMANGER_scale(StateManager *statemanger)
{
     statemanger -> capacity *= 2;
     /* double everything to be safe */
     statemanger -> stack = (State**) realloc(statemanger -> stack,
					      statemanger -> capacity * sizeof(State**));

     /* pass back the new size of statemanger */
     return statemanger -> capacity;
}

/* 
* Push to the statemanger stack
*/
int STATEMANAGER_push(StateManager *statemanager, State *state)
{
     /* Check there is enough room to add to the statemanger */
     if (statemanager -> top + 1 == statemanager -> capacity)
     {
	  STATEMANGER_scale(statemanager);
     }
     /* Add the new State */
     statemanager -> top++;
     statemanager -> stack[statemanager -> top] = state;

     /* return new top index */
     return statemanager -> top;
}

/*
* Pop from the statemanger stack
*/
int STATEMANAGER_pop(StateManager *statemanager)
{
     if (statemanager -> top == -1)
     {
	  /* No errors but we reached the end of the stack */
	  return 0;
     }
     State *top = STATEMANAGER_top(statemanager);

     /* Try and destroy the top item */
     if (top -> destroy != NULL)
     {
	  top -> destroy();
     }

     /* remove the pointer from the stack */
     statemanager -> stack[statemanager -> top] = NULL;
     statemanager -> top--;
     return statemanager -> top;
}
/*
* Get the top of the state stack
*/
State *STATEMANAGER_top(StateManager *statemanager)
{
     return statemanager -> stack[statemanager -> top];
}

// +=----------------------------------------------------------------------------=+
//    Main Loop related functions
// +=----------------------------------------------------------------------------=+

/*
* Update the states on the stack
*/
int STATEMANAGER_update(StateManager *statemanager, float deltatime)
{
     /* Get the top of the statemanger stack */
     State *state = STATEMANAGER_top(statemanager);

     /* Actually update here */
     if (state -> update != NULL)
     {
	  return state -> update(deltatime);
     }
     /* If we reach here something has gone wrong during updating the state */
     return 1;
}
/*
 * Draw all the changes to the game
*/
int STATEMANAGER_draw(StateManager *statemanager, float deltatime)
{
     /* Get the top of the statemanger stack */
     State *state = STATEMANAGER_top(statemanager);

     /* Actually update here */
     if (state -> draw != NULL)
     {
	  return state -> draw(deltatime);
     }
     /* If we reach here something has gone wrong during updating the state */
     return 1;
}

// +=----------------------------------------------------------------------------=+
// End of file
// +=----------------------------------------------------------------------------=+
