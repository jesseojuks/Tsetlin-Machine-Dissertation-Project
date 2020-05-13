#include "TMHeader.h"
#include <cstdlib>
#include <iostream>
using namespace std;


TM* McTM::Initialise_McTM(int noOfInputs, int noOfClasses , int clausePerOutput , int threshold, float s)
{
    this->noOfClasses = noOfClasses;
    TM * tm;
    tm = new TM[noOfClasses];
    
    for(int i =0 ; i<  noOfClasses ; i++)
    {
       
        srand(time(NULL)+rand());
    
        tm[i].Initialise_TM(noOfInputs,clausePerOutput/noOfClasses,threshold,s);
    }
    tms = tm;
    
    return tms;
  delete[] tm;
}

float McTM::Test_McTM (int input[][FEATURES], int* answer_data , int noOfTrainingSamples)
{
  int max_class;
  int max_class_sum;
  int count = 0;

  for (int i = 0; i < noOfTrainingSamples; i++ )
  {
      int index = rand() % NUMBER_OF_TEST;
      int* literals = tms[0].Generate_literals (input[index]);
      tms[0].Clause_Generator (tms[0].taTeams,literals);
      delete[] literals;
      max_class_sum = tms[0].Clause_summation (tms[0].clauseArray);
      max_class = 0;
      for (int j = 1; j < CLASSES; j++)
      {
        int* literals = tms[j].Generate_literals (input[index]);
        tms[j].Clause_Generator (tms[j].taTeams,literals);
        delete[] literals;
        int class_sum = tms[j].Clause_summation (tms[j].clauseArray);
			if (max_class_sum < class_sum)
      {
				max_class_sum = class_sum;
				max_class = j;
			}
      }
      if (max_class != answer_data[index])
      {
			count += 1;
      }
  }
  return (1.0 - 1.0 * count / noOfTrainingSamples);  
}

void McTM::Update_McTM (int index, int input[][FEATURES], unsigned int target)
{
    tms[target].Update(index, input, 1);
    unsigned int negativeTarget = rand() % noOfClasses;
    while (negativeTarget == target)
    {
		negativeTarget = rand() % noOfClasses;
	}
    tms[negativeTarget].Update(index, input, 0);
}

void McTM::Train_McTM(int input[][FEATURES], int* answer_data ,int epochs , int noOfTrainingSamples)
{
    printf("\t Starting Training of McTM  \n ");
    for (int i = 0; i < epochs; i++ )
  {
    //printf("\t Epoch %d  \n ", i+1);
    auto start = high_resolution_clock::now(); 
     for (int j = 0; j < noOfTrainingSamples; j++)
     {
      int index = rand() % NUMBER_OF_EXAMPLES;
      
      Update_McTM(index, input, answer_data[index]);
     
    }
  
  auto stop = high_resolution_clock::now();
  duration<double>elapsed_seconds = stop-start;
  
  //cout << "\t Time taken: " << elapsed_seconds.count() << "s" << endl;
  //printf("\t Mean Accuracy of Test Data = %f%% \n ",Test_McTM(X_test,y_test,NUMBER_OF_TEST) );
  }
  printf("\t McTM is trained...  \n\n ");
}
