// Copyright 2020 Ramsay Carslaw
// File: state.h
// Description: The header file for the state manger
// Author: Ramsay Carslaw
// Created: 18/07/2020


// -------------------------------------------------------------------------------- 
//   Header Gaurds
// -------------------------------------------------------------------------------- 

#ifndef ENGINE_STATEMANAGER_H
#define ENGINE_STATEMANAGER_H

// -------------------------------------------------------------------------------- 
//   Includes
// -------------------------------------------------------------------------------- 

#include <stdlib.h>
#include <stdio.h>

// -------------------------------------------------------------------------------- 
//   Structs and Types
// -------------------------------------------------------------------------------- 

/*
* Define some function pointers for the state
*/
typedef unsigned int (*fnPtr)();
/*
* The other pointer for update and draw with the float parameter
*/
typedef unsigned int (*fnPtrF1)(float);

/*
* State is the struct responsible for storing a state in the game
*/
typedef struct _State
{
     fnPtr init;
     fnPtrF1 update;
     fnPtrF1 draw;
     fnPtr destroy;
} State;

/*
* StateManager stores a stack of the states needed to be evaluated
*/
typedef struct _StateManager
{
     State **stack;
     int capacity;
     int top;
} StateManager;


// -------------------------------------------------------------------------------- 
//   Function Definitions
// -------------------------------------------------------------------------------- 

/*
* Initialise the states
*/
int STATEMANAGER_init(StateManager *statemanager);
/*
* Used to remove heap alloocated mem in init
*/
int STATEMANAGER_free(StateManager *statemanager);

/* 
* Dynamically increase the memory ascociated with statemanger
*/
int STATEMANGER_scale(StateManager *statemanger);

/* 
* Push to the statemanger stack
*/
int STATEMANAGER_push(StateManager *statemanager, State *state);
/*
* Pop from the statemanger stack
*/
int STATEMANAGER_pop(StateManager *statemanager);
/*
* Get the top of the state stack
*/
State *STATEMANAGER_top(StateManager *statemanager);
/*
* Update the states on the stack
*/
int STATEMANAGER_update(StateManager *statemanager, float deltatime);
/*
 * Draw all the changes to the game
*/
int STATEMANAGER_draw(StateManager *statemanager, float deltatime);


// -------------------------------------------------------------------------------- 
//   Header Gaurd II
// -------------------------------------------------------------------------------- 

#endif


// -------------------------------------------------------------------------------- 
//   End of file state.h
// -------------------------------------------------------------------------------- 
