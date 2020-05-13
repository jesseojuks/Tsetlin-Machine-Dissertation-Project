/* TSETLIN AUTOMATA CLASS */
// STEP 1: Initialise FSM using vectors or array(PROBS ARRAY FIRST AS SIMPLE TO DO)
//***** Make sure to do with vectors --- Better implementation *****

#include "TMHeader.h"

void TA::Initialise_TA(int noOfStates)
{
    this->noOfStates = noOfStates;  
    int * state;
    state = new int[2*noOfStates];
    int output;
    for (int i = 0; i < (2*noOfStates); i++)
    {
        if (i < noOfStates)
        {
            output = 0;
        }
        else
        {
            output = 1;
        }
        state[i] = output;
    }
    
    //int chosenState = (rand() > RAND_MAX/2) ?  (noOfStates-1): (noOfStates);
    int chosenState = noOfStates - 1;
    currentState = chosenState;
    //printf ("Chosen State: %d \n",chosenState);
    int action = state[chosenState];
    currentAction = action;
    //delete [] state;
}

void TA::Reward ()
{
  if (currentState < noOfStates and currentState > 0)
  {
    currentState--;
    currentAction = 00;
  }
  else if (currentState == 0)
  {
    currentState = 0;
    currentAction = 0;
  }
  else if (currentState >= noOfStates and currentState < ((2*noOfStates)-1))
  {
    currentState++ ;
    currentAction = 1;
  }
  else if (currentState == ((2*noOfStates)-1) )
  {
    currentState = ((2*noOfStates)-1) ;
    currentAction = 1;
  }
  
}

void TA::Penalty ()
{
   if (currentState < noOfStates and currentState != (noOfStates - 1))
   {
    currentState++ ;
    currentAction = 0;
   }
   else if (currentState == (noOfStates - 1))
   {
    currentState++ ;
    currentAction = 1;
   }
   else if (currentState > noOfStates)
   {
    currentState--;
    currentAction = 1;
   }
   else if(currentState == noOfStates)
   {
    currentState--;
    currentAction = 0;
   }
   
}


