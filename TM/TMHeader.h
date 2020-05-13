#pragma once

#include <stdio.h>
#include <random>
#include <cstdlib>    
#include <ctime>
#include <string.h>
#include <unistd.h>
//MNIST
#define NUMBER_OF_EXAMPLES 60000
#define NUMBER_OF_TEST 10000
#define FEATURES 784
#define CLAUSES 4000
#define boostTP 1
#define CLASSES 10
#define THRESHOLD 50
#define S 10.00

//XOR
//#define NUMBER_OF_EXAMPLES 5000
//#define NUMBER_OF_TEST 5000
//#define FEATURES 12
//#define CLAUSES 28
//#define boostTP 1
//#define CLASSES 2
//#define THRESHOLD 15
//#define S 3.90

//IRIS
//#define NUMBER_OF_EXAMPLES 120
//#define NUMBER_OF_TEST 30
//#define FEATURES 16
//#define CLAUSES 300
//#define boostTP 1
//#define CLASSES 3
//#define THRESHOLD 10
//#define S 3.00


int X_train[NUMBER_OF_EXAMPLES][FEATURES];
int y_train[NUMBER_OF_EXAMPLES];

int X_test[NUMBER_OF_TEST][FEATURES];
int y_test[NUMBER_OF_TEST];


//enum class Polarity
//{
//    Positive ,
//    Negative
//};


class TA
{   private:
    int noOfStates;
    public:            
        int currentState;
        int currentAction;
        // Methods
        void Initialise_TA(int noOfStates);  //changed
        void Reward(); 
        void Penalty (); 
};

class TA_Teams
{       
    private:
        int noOfStates;
        int noOfInputs;
    public:
        TA* tas;
        
        // Methods
        void Initialise_TA_Teams(int noOfInputs, int noOfStates);  //changed
};

//class Clause
//{       
//    public:
//        int output;
//        Polarity pol;
//        // Functions
//        void Set_Polarity(Polarity pol); //DONE
//        bool Check_Polarity(Polarity pol);//DONE
//
//};

class TM
{
        // Attributes
    private:
        int noOfLiterals;
    public:
        TA_Teams* taTeams;
        int noOfInputs;
        int threshold;
        float s;
        int count = 0;
        int clausePerOutput;
        int* clauseArray;
        // Method
        TA_Teams* Initialise_TM(int noOfInputs, int clausePerOutput , int threshold, float s); //--- Initialises the TM  DONE... Tested
        int* GetNextTrainingExample(int dataindex, int trainingData[][FEATURES]); // Gets inputs DONE... Tested
        int GetNextAnswer(int dataindex, int* answers); // Done... tested
        int* Generate_literals (int* input); //--- Generates the literals DONE ... Tested
        int* Clause_Generator (TA_Teams* taTeam ,int* literals);  //--- generates clauses DONE ... Tested
        int Clause_summation (int* clauses); //--- Clause Polarity will be done here and returns outputs Tested
        int Threshold_Function (int clauseSum);// DONE ... Tested
        bool Prob_feedback_1 ( int clauseSum); // DONE ... Tested 
        bool Prob_feedback_2 ( int clauseSum); //DONE ...   Tested
        void Feedback(int* c, int cSum, int answer,int* literals); // Done... Tested
        void Update (int index, int input[][FEATURES], int answer);
        void Feedback_1 (int index, int c,int* literals); // Done... Tested
        void Feedback_2 (int index, int c,int* literals); // Done... Tested
        void Train_TM(int input[][FEATURES], int* answer_data ,int epochs , int noOfTrainingSamples); // Done... Tested
        void Test_TM(int input[][FEATURES], int* answer_data, int noOfTrainingSamples); // Done... Tested
        void User_Based_Test(); //Done... Tested
};










class McTM
{
     public:
        int noOfClasses;
        TM* tms;

    
        TM* Initialise_McTM(int noOfInputs, int noOfClasses , int clausePerOutput , int threshold, float s);
        float Test_McTM (int input[][FEATURES], int* answer_data , int noOfTrainingSamples);
        void Update_McTM (int index, int input[][FEATURES], unsigned int target);
        void Train_McTM(int input[][FEATURES], int* answer_data ,int epochs , int noOfTrainingSamples);
        ////~McTM()
        ////{
        ////    delete [] tms;
        ////}
}  ;

