#include "TMHeader.h"


void TA_Teams::Initialise_TA_Teams(int noOfInputs, int noOfStates)
{
  this->noOfInputs = noOfInputs;
  this->noOfStates = noOfStates;  
  TA *ta;
  ta = new TA[noOfInputs];
  
  //printf (BOLDBLUE "--------Initialising TAs-------- \t\n" RESET);
  for(int i = 0; i<noOfInputs ; i++)
  {
    //printf (BLUE "--------------TA %d -------------\n" RESET, i);
    //printf (BLUE "--------Randomising TA state-------- \t\n" RESET);
    srand(time(NULL)+rand());
    ta[i].Initialise_TA(noOfStates);
    //printf( "test : current state = %d", ta[i].currentState);
  }
  tas = ta;
  //delete[] ta;
}

