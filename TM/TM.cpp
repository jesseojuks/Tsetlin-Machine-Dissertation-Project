#include "TMHeader.h"
#include "TA_Teams.cpp"
#include "TA.cpp"
#include "Clause.cpp"
#include <cstdlib>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;




TA_Teams* TM::Initialise_TM(int noOfInputs, int clausePerOutput, int threshold, float s)
{
    this->noOfInputs = noOfInputs;
    this->clausePerOutput = clausePerOutput;
    this->threshold = threshold;
    this->s = s;
    this->noOfLiterals = 2*noOfInputs;

    TA_Teams * team;
    team = new TA_Teams[clausePerOutput];
    
    //printf (BOLDRED "---------------Initialising Tsetlin Machine with %d Input feature(s) and %d Clause(s)----------\t\n" RESET, noOfInputs , clausePerOutput);
    //printf (BOLDGREEN "--------Initialising TA Teams-------- \t\n" RESET);
    for(int i =0 ; i<  clausePerOutput ; i++)
    {
        //printf (GREEN "\t TA Team %d \t\n" RESET, i);
        srand(time(NULL)+rand());
    
        team[i].Initialise_TA_Teams(noOfLiterals,100);
    }
    taTeams = team;
  
    return taTeams;
    delete[] team;
}

int* TM::GetNextTrainingExample(int dataindex, int trainingData[][FEATURES])
{
    int* inputs;
    inputs = new int [noOfInputs];
    for(int i = 0; i < noOfInputs ; i++)
    {
        inputs[i] = trainingData[dataindex][i];
    }
    return inputs;
}

int TM::GetNextAnswer(int dataindex, int* answers)
{
    int answer = answers[dataindex];
    return answer;
}

int* TM::Generate_literals (int* input)
{
    int* literals ;
    literals = new int [noOfLiterals];
    int j = 0;
    //printf("\t step 3 \n ");
    for (int i = 0; i<noOfLiterals ; i++)
    {
        if ((i % 2) == 0)
        {    
            literals[i] = input [j];   
        }
        else
        {
            literals[i] = 1^input[j];
            j++;
        }
    }
   return literals;

}

int* TM::Clause_Generator (TA_Teams* taTeam ,int* literals )
{
    int* clauses;
    clauses = new int[clausePerOutput];
    //printf("\t CG error 1  \n\n ");
    for (int i = 0; i < clausePerOutput; i++)
    {   
        int sum = 1;
        int x = 1;
        for (int j = 0; j < noOfLiterals; j++)
        {
         
            if (taTeam[i].tas[j].currentAction == 1 && literals[j] == 0)
            {
             sum = 0;
             break;
            }
            else if(taTeam[i].tas[j].currentAction == 0)
            {
             x++;
            }
            if (x == noOfLiterals)
            {
             sum = 1; // was 1 before incase
            }
        }
        //printf("\t CG error 3  \n\n ");
        clauses[i] = sum;

    }
    //printf("\t CG error 4  \n\n ");
    clauseArray = clauses;
    return clauseArray;
    delete[] clauses;
}

int TM::Clause_summation (int* clauses)
{
    int sum = 0;
    int neg = 0;
    for (int i = 0 ; i < clausePerOutput ;  i++)
    
    {
        if ((i % 2) == 0 )
        {
            //Polarity p = Polarity::Positive;
            //clauses[i].Set_Polarity(p);
            sum += clauses[i];
        }
        else
        {
            //Polarity n = Polarity::Negative;
            //clauses[i].Set_Polarity(n);
            neg += clauses[i];
        }
    }
    int clauseSum = sum - neg;
    clauseSum = (clauseSum > threshold) ? threshold : clauseSum;
    clauseSum = (clauseSum < -threshold) ? -threshold : clauseSum;
    return clauseSum;
}
int TM::Threshold_Function (int clauseSum)
{
    int clauseOutput;
    if ( clauseSum < 0)
    {
        clauseOutput = 0;
    }
    else
    {
        clauseOutput = 1;
    }
    return clauseOutput;
}

bool TM::Prob_feedback_1 ( int clauseSum)
{
    bool prob = false;
    if (1.0*rand()/RAND_MAX <= 1.0*(threshold - clauseSum)/(2*threshold))
    {
        prob = true;
     
    }
    return prob;
}
               
bool TM::Prob_feedback_2 ( int clauseSum)
{
    bool prob = false;
    if (1.0*rand()/RAND_MAX <= 1.0*(threshold + clauseSum)/(2*threshold))
    {
        prob = true;
    }
    return prob;
}


void TM::Feedback_1 (int index, int c , int* literals )
{
 if (c == 1)
 {
  for (int i = 0; i < noOfLiterals ; i++)
  {
    if(literals[i] == 1)
    {
     if(taTeams[index].tas[i].currentAction == 1)
     {
      if( boostTP or 1.0*rand()/RAND_MAX <= 1.0*(s-1)/s)
      {
       //printf("\t TA Teams %d TA %d is rewarded,", index ,i);
       taTeams[index].tas[i].Reward();
       
      }
     }
     else if(taTeams[index].tas[i].currentAction == 0)
     {
     if(boostTP or 1.0*rand()/RAND_MAX <= 1.0*(s-1)/s)
      {
       //printf("\t TA Teams %d TA %d is Penalized,", index ,i);
       taTeams[index].tas[i].Penalty();
       
      }
     }
    }
    else if(literals[i] == 0)
    {
     if(1.0*rand()/RAND_MAX <= 1.0/s)
     {
      //printf("\t TA Teams %d TA %d is rewarded,", index ,i);
      taTeams[index].tas[i].Reward();
      
     }
    }
  }
 }
 else if (c == 0)
 {
  for (int i = 0; i < noOfLiterals ; i++)
  {
     
     if(taTeams[index].tas[i].currentAction == 1)
     {
      if(1.0*rand()/RAND_MAX <= 1.0/s)
      {
      // printf("\t TA Teams %d TA %d is Penalized,", index ,i);
       taTeams[index].tas[i].Penalty();
       

      }
     }
     else if(taTeams[index].tas[i].currentAction == 0)
     {
      if(1.0*rand()/RAND_MAX <= 1.0/s)
      {
       //printf("\t TA Teams %d TA %d is rewarded,", index ,i);
       taTeams[index].tas[i].Reward();
       
      }
     }
    
  }
 }
}

void TM::Feedback_2 (int index, int c , int* literals)
{
 if (c == 1)
 {
  for (int i = 0; i < noOfLiterals ; i++)
  {
    if(literals[i] == 0 && taTeams[index].tas[i].currentAction == 0 )
    {
    // printf("\t TA Teams %d TA %d is Penalized,", index ,i);
     taTeams[index].tas[i].Penalty();
     
    }
  }
 }
}


void TM::Update (int index, int input[][FEATURES], int answer)
{
      //printf("\t Error 3  \n\n ");
      int* literals = Generate_literals (input[index]);
      //printf("\t Error 4  \n\n ");
      Clause_Generator (taTeams,literals);
      //printf("\t Error 5  \n\n ");
      Feedback(clauseArray,Clause_summation (clauseArray), answer,literals);
      
      //printf("\t Error 6  \n\n ");
      
      delete[] literals;
      delete[] clauseArray;
}

// Single Class Funtionality

void TM::Feedback(int* c, int cSum , int answer, int* literals)
{
// printf("\t step 7 \n ");
 //Polarity p = Polarity::Positive;
 //Polarity n = Polarity::Negative;
 if (answer == 1)
 {
   for (int i = 0; i < clausePerOutput; i++)
   {
     if ((i % 2) == 0)
     {
      if (Prob_feedback_1(cSum))
      {
       //printf("\t FeedBack 1 for clause %d \n", i);
       Feedback_1(i,c[i], literals);
      }
     }
     else if ((i % 2) == 1)
     {
      if (Prob_feedback_2(cSum))
      {
       //printf("\t FeedBack 2 for clause %d \n", i);
       Feedback_2(i,c[i],literals) ;
      }
     }
   }
 }
 else if (answer == 0)
 {
   for (int i = 0; i < clausePerOutput; i++)
   {
     if ((i % 2) == 0)
     {
      if (Prob_feedback_2(cSum))
      {
       //printf("\t FeedBack 2 for clause %d \n", i);
       Feedback_2(i,c[i], literals);
      }
     }
     else if ((i % 2) == 0)
     {
      if (Prob_feedback_1(cSum))
      {
      //printf("\t FeedBack 1 for clause %d \n", i);
       Feedback_1(i,c[i], literals);
      }
     }
   }
 }
 
}

void TM::Train_TM(int input[][FEATURES], int* answer_data ,int epochs , int noOfTrainingSamples)
{

 printf("\t Training TM...  \n\n ");
  for (int i = 0; i < epochs; i++ )
  {
   printf("\t Error 1  \n\n ");
   count=0;
    auto start = high_resolution_clock::now(); 
     for (int j = 0; j < noOfTrainingSamples; j++)
     {
      int index = rand() % NUMBER_OF_EXAMPLES;
      int answer = GetNextAnswer(index, answer_data);
      Update(index, input, answer);
     }
  auto stop = high_resolution_clock::now();
  duration<double>elapsed_seconds = stop-start;
  cout << "\t Time taken: " << elapsed_seconds.count() << "s" << endl;
  }
  printf("\t TM is trained...  \n\n ");
}

void TM::Test_TM(int input[][FEATURES], int* answer_data, int noOfTrainingSamples)
{
    printf("\t Testing TM...  \n\n ");
    count=0;
    auto start = high_resolution_clock::now(); 
     for (int j = 0; j < noOfTrainingSamples; j++)
     {
      int index = rand() % NUMBER_OF_TEST;
      int answer = GetNextAnswer(index, answer_data);
      int* literals = Generate_literals (GetNextTrainingExample(index, input));
      Clause_Generator (taTeams,literals);
      int sum = Clause_summation (clauseArray);
      int output = Threshold_Function (sum);
      if (answer == output)
      {
       count++;
      }
     }
      
  float accuracy = ((double(count)/(noOfTrainingSamples) )*100);
  auto stop = high_resolution_clock::now();
  duration<double>elapsed_seconds = stop-start;
  printf("\t Mean Accuracy of testing = %f%% \n ", accuracy );
  cout << "\t Time taken: " << elapsed_seconds.count() << "s" << endl;
}

void TM::User_Based_Test()
{
 printf("\t User Based Testing  \n\n ");
  char choise = 'Y';
  int user_input[2];
  do
	{
		if (choise == 'Y' or choise == 'y')
		{
  
   cout << "\t enter data 1: "; cin >> user_input[0]; cout << endl;
			cout << "\t enter data 2: "; cin >> user_input[1]; cout << endl;
			int* literals = Generate_literals (user_input);
   Clause_Generator (taTeams,literals);
   //t.Clause_summation (t.clauseArray);
   int output = Threshold_Function ((Clause_summation (clauseArray)));
			cout << "\t output = " << output << endl;
   int answer = user_input[0] xor user_input[1];
   if (output == answer)
   {
    cout << "\t CORRECT ANSWER! \n" << endl;
   }
   else
   {
    cout << "\t INCORRECT ANSWER! \n" << endl;
   }
   
			cout << "\t Again? Y/N "; cin >> choise;   
	}
 else
		{
			break;
		}
	} while ((choise == 'Y' || 'y') && (choise != 'n' || 'N'));
}
