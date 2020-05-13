#include "TM.cpp"
#include "McTM.cpp"
#include "TMHeader.h"
#include <stdio.h>
#include <stdlib.h>


void read_file(const char* trainData,const char* testData)
{
 //Creates FILE object to access the files
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
 
	const char *s = " ";
	char *token = NULL;
// Error Handling for if file is not available
	fp = fopen(trainData, "r");
  if (fp == NULL)
  {
   printf("Error opening1\n");
   exit(EXIT_FAILURE);
  }
// Section for getting features and labels of training data and putting the into their respective arrays
	for (int i = 0; i < NUMBER_OF_EXAMPLES; i++)
 {
   getline(&line, &len, fp);
 
   token = strtok(line, s);
   for (int j = 0; j < FEATURES; j++) {
    X_train[i][j] = atoi(token);
    token=strtok(NULL,s);
   }
   y_train[i] = atoi(token);
	}
// Section for getting features and labels of testing data and putting the into their respective arrays
	fp = fopen(testData, "r");
	if (fp == NULL)
  {
   printf("Error opening2\n");
   exit(EXIT_FAILURE);
  }

	for (int i = 0; i < NUMBER_OF_TEST; i++)
  {
   getline(&line, &len, fp);
 
   token = strtok(line, s);
    for (int j = 0; j < FEATURES; j++)
    {
     X_test[i][j] = atoi(token);
     token=strtok(NULL,s);
    }
    y_test[i] = atoi(token);
  }
}

void output_digit(int index, int X[][FEATURES])
{
		int y = 1;
		for (int x = 0; x < FEATURES; x++)
		{ 
			if ((X[index][x]) == 1)
			{
				printf("@");
			}
			else
			{
				printf(".");
			}
			if (y % 28 == 0)
			{
				y = 1;
				printf("\n");
			}
			else
			{
				y++;
			}
			
		}
		//printf("\n");
	
}

int main()
{
 
  McTM* t = new McTM;
		//MNIST
  read_file("MNISTTraining.txt","MNISTTest.txt");
		printf("MNISTDemo\n");
	 printf("MNIST Sample\n");
		srand(time(NULL)+rand());
		int ran = rand() % 10000
		output_digit(ran, X_test);
		printf("Label = %d", y_test[ran]);
  int epochs = 5;
  int ensemble= 60000;

//XOR		
//		read_file("NoisyXOR.dat","NoisyXORtr.dat");
//		printf("Noisy XOR Demo\n");
//		srand(time(NULL)+rand());
//  int epochs = 200;
//  int ensemble= 5000;

//IRIS
//		read_file("Iris.dat","Iriste.dat");
//		printf("Iris Demo\n");
//		srand(time(NULL)+rand());
//  int epochs = 500;
//  int ensemble= 1000;
//	
		
  printf("\n\n");
  t->Initialise_McTM(FEATURES,CLASSES,CLAUSES,THRESHOLD,S);
  printf("\t Initializing  MCTM... \n ");
  printf("\t Number of Input Features = %d \n ", FEATURES);
  printf("\t Number of Number Of Classes = %d \n ", CLASSES);
  printf("\t Number of Clauses per Output = %d \n ", CLAUSES);
  printf("\t Threshold = %d \n ", THRESHOLD);
  printf("\t s = %f \n\n", S);
  
  //for (int i = 0; i < 10 ; i++)
  //{
  t->Train_McTM(X_train,y_train, epochs, ensemble);
//  //t.Test_TM(X_test,y_test,trainingsample);
////  printf("\t Training Data \n ");
////		//t->Test_McTM(X_train,y_train,trainingsample);
////  printf("\t Mean Accuracy = %f%% \n ", t->Test_McTM(X_train,y_train,ensemble) );
  printf("\t Testing Data \n ");
//		//t->Test_McTM(X_test,y_test,NUMBER_OF_TEST);
  printf("\t Mean Accuracy = %f%% \n ",   t->Test_McTM(X_test,y_test,ensemble) );
  //}
  //t.User_Based_Test();
 
 return 0;
	delete t;
}