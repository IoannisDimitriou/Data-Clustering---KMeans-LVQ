// Ioannis Dimitriou, 3214, cs03214@uoi.gr
// Nikoleta-Dimitra Bena, 3289, cs03289@uoi.gr
// Serafeim-Ilias Antoniou, 2640, cs02640@uoi.gr

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <math.h> 

#define M 2
#define EXAMPLES 900

double n = 0.1; // learning rate

void load_examples();
void initialize_centroids();
void train();
void results();

// array to hold examples
float examples[EXAMPLES][2];
// array to hold centroids
float centroids[M][2];
// how much each centroid moved at the end of an epoch
double centroid_move[M];

// for file manipulation
FILE *fp1 = NULL;
FILE *fp2 = NULL;

int main(){

	int i,j;

	// open Dataset2.txt for reading
	fp1 = fopen("Dataset2.txt","r");
	if(fp1 == NULL)
	{
		fprintf(stderr,"Couldn't read Dataset2.txt \n");
		exit(1);
	}
	// open a txt file to write the results of the algorithm
	fp2 = fopen("LVQresults.txt","w");
	if(fp2 == NULL)
	{
		fprintf(stderr,"Couldn't write LVQresults.txt \n");
		exit(1);
	}

	// initialize movement for each centroid to zero
	for(i = 0; i < M; i++){
		centroid_move[i] = 0;
	}
	
	load_examples();
	initialize_centroids();
	train();
	results();


	fclose(fp1);
	fclose(fp2);
	
	return 0;
}

// function to load the examples from Dataset2.txt file
void load_examples(){

	int i;

	// ignore first line of the file which contains parameter information
	char buffer1[100];
	fgets(buffer1, 100, fp1);
	
	for(i = 0; i < EXAMPLES; i++){
		fscanf(fp1, "%10f", &examples[i][0]);
		fscanf(fp1, "%10f", &examples[i][1]);
	}
}

// function to initialize centroids for each cluster
void initialize_centroids(){

	int i,r1,r2;

	r1 = rand() % (EXAMPLES +1);
	r2 = r1;
	i = 1;

	// initialize centroid for first cluster using a random example
	centroids[0][0] = examples[r1][0];
	centroids[0][1] = examples[r1][1];

	// initialize centroids for the rest of the clusters using a random example
	while(i < M){

		if(r1 == r2){
			r1 = rand() % (EXAMPLES +1);
		}

		centroids[i][0] = examples[r1][0];
		centroids[i][1] = examples[r1][1];

		r2 = r1;
		i++;
	}
}

// main implementation of the lvg algorithm
void train(){

	int i,j,pos;
	double distance[M];
	double min;

	// calculate the Euclideian distance
	for(i = 0; i < EXAMPLES; i++){
		for(j = 0; j < M; j++){

			distance[j] = sqrt(pow((examples[i][0] - centroids[j][0]),2.0) + pow((examples[i][1] - centroids[j][1]),2.0));
		}

		// assign example to the min cluster centroid
		min = distance[0];
		pos = 0;

		for(j = 1; j < M; j++){
			if(distance[j] < min){
				min = distance[j];
				pos = j;
			}
		}

		//update the weights of winner neuron
		centroids[pos][0] += n * (examples[i][0] - centroids[pos][0]);
		centroids[pos][1] += n * (examples[i][1] - centroids[pos][1]);

	}

}

// function to calculate the results
void results(){

	int i,j,pos;
	double distance[M];
	double min,total1,total2,threshold;

	// obtain winning unit and calculate its movement
	for(i = 0; i < EXAMPLES; i++){
		for(j = 0; j < M; j++){
			distance[j] = sqrt(pow((examples[i][0] - centroids[j][0]),2.0) + pow((examples[i][1] - centroids[j][1]),2.0));
		}

		min = distance[0];
		pos = 0;

		for(j = 1; j < M; j++){
			if(distance[j] < min){
				min = distance[j];
				pos = j;
			}
		}

		centroid_move[pos] += pow((examples[i][0] - centroids[pos][0]),2.0) + pow((examples[i][1] - centroids[pos][1]),2.0);
	}

	total2 = 0.0;
	for(i = 0; i < M; i++){
		total2 += centroid_move[i];
	}

	total1 = 0.0;

	// repeat the same with a smaller learning rate until a threshold condition

	while(1){

		threshold = fabs(total2 - total1);

		if(threshold < 0.001){
			break;
		}

		total1 = total2;

		// reduce learning rate

		n *= 0.95;

		train();

		for(i = 0; i < M; i++){
			centroid_move[i] = 0;
		}

		for(i = 0; i < EXAMPLES; i++){
			for(j = 0; j < M; j++){
				distance[j] = sqrt(pow((examples[i][0] - centroids[j][0]),2.0) + pow((examples[i][1] - centroids[j][1]),2.0));
			}

			min = distance[0];
			pos = 0;

			for(j = 1; j < M; j++){
				if(distance[j] < min){
					min = distance[j];
					pos = j;
				}
			}

			centroid_move[pos] += pow((examples[i][0] - centroids[pos][0]),2.0) + pow((examples[i][1] - centroids[pos][1]),2.0);
		}

		total2 = 0.0;

		for(i = 0; i < M; i++){
			total2 += centroid_move[i];
		}

	}

	// write the results in a txt file

	fprintf(fp2, "Centroids\n");
	fprintf(fp2,"x1\t  y1\n");

	for(i = 0; i < M; i++){
		fprintf(fp2, "%f , %f \n", centroids[i][0], centroids[i][1]);
	}

	fprintf(fp2,"\nTotal clustering error: %10f \n", total2);


}