#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EXAMPLES 900

// USE AND PURPOSE
// run with
// gcc Dataset2.c
// ./a.exe
// Generates a file called Dataset2.txt with values x1,y1

// array to hold 900 examples
double examples[EXAMPLES][2];

// function to generate random values, same as Dataset1.c
double random_generator(double a, double b){
	double interval = b -a;
	double div = RAND_MAX / interval;
	double generator = a + (rand()/div);
	return generator;

}

// for writing the examples
FILE *fp1 = NULL;

int main(){

	// for random generator function
	srand((unsigned)time(NULL));

	// for counter
	int i;

	// create file for examples
	fp1 = fopen("Dataset2.txt","w");
	if(fp1 == NULL){
		fprintf(stderr, "Couldn't write Dataset2.txt \n");
	}

	
	// make the txt file more readable
	fprintf(fp1, "x1\t\t y1 \n");

	// 150 random examples in [0.75,1.25]x[0.75,1.25]
	for (i = 0; i < 150 ; i++){

        examples[i][0] = random_generator(0.75 , 1.25);            
        examples[i][1] = random_generator(0.75 , 1.25);
		fprintf(fp1,"%2.5f \t", examples[i][0]);
		fprintf(fp1,"%2.5f \t", examples[i][1]);
		fprintf(fp1,"\n");				
                
    }

    // 150 random examples in [0,0.5]x[0,0.5]
    for (i = 150; i < 300 ; i++){

        examples[i][0] = random_generator(0.0 , 0.5);            
        examples[i][1] = random_generator(0.0 , 0.5);
		fprintf(fp1,"%2.5f \t", examples[i][0]);
		fprintf(fp1,"%2.5f \t", examples[i][1]);
		fprintf(fp1,"\n");				
                
    }

    // 150 random examples in [0,0.5]x[1.5,2]
    for (i = 300; i < 450 ; i++){

        examples[i][0] = random_generator(0.0 , 0.5);            
        examples[i][1] = random_generator(1.5 , 2.0);
		fprintf(fp1,"%2.5f \t", examples[i][0]);
		fprintf(fp1,"%2.5f \t", examples[i][1]);
		fprintf(fp1,"\n");				
                
    }

    // 150 random examples in [1.5,2]x[0,0.5]
    for (i = 450; i < 600 ; i++){

        examples[i][0] = random_generator(1.5 , 2.0);            
        examples[i][1] = random_generator(0.0 , 0.5);
		fprintf(fp1,"%2.5f \t", examples[i][0]);
		fprintf(fp1,"%2.5f \t", examples[i][1]);
		fprintf(fp1,"\n");				
                
    }

    // 150 random examples in [1.5,2]x[1.5,2]
    for (i = 600; i < 750 ; i++){

        examples[i][0] = random_generator(1.5 , 2.0);            
        examples[i][1] = random_generator(1.5 , 2.0);
		fprintf(fp1,"%2.5f \t", examples[i][0]);
		fprintf(fp1,"%2.5f \t", examples[i][1]);
		fprintf(fp1,"\n");				
                
    }

    // 150 random examples in [0,2]x[0,2]
    for (i = 750; i < 900 ; i++){

        examples[i][0] = random_generator(0.0 , 2.0);            
        examples[i][1] = random_generator(0.0 , 2.0);
		fprintf(fp1,"%2.5f \t", examples[i][0]);
		fprintf(fp1,"%2.5f \t", examples[i][1]);
		fprintf(fp1,"\n");				
                
    }

    // close file and exit
    fclose(fp1);
    return 0;



}

