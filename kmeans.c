#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define EXAMPLES 900
#define M 10

void load_examples();
void initialize_centroids();
void train();
void results();

// array to hold examples
float examples[EXAMPLES][2];
// array to hold centroids
float centroids[M][2];
// arrays for cluster manipulation
int cluster[EXAMPLES];
int next_cluster[EXAMPLES];
// arrays for distance calculation
double total_distance[M][2];
int counter[M];

// for file manipulation
FILE *fp1 = NULL;
FILE *fp2 = NULL;


int main(){

	int i,j;

	// open Dataset2.txt for reading the examples
	fp1 = fopen("Dataset2.txt","r");
	if(fp1 == NULL)
	{
		fprintf(stderr,"Couldn't read Dataset2.txt \n");
		exit(1);
	}

	// open a txt file to write the results of the algorithm
	fp2 = fopen("KmeansResults.txt","w");
	if(fp2 == NULL)
	{
		fprintf(stderr,"Couldn't write KmeansResults.txt \n");
		exit(1);
	}

	// initialize cluster to -1 because there are no clusters yet
	for(i = 0; i < EXAMPLES; i++){
		cluster[i] = -1;
		next_cluster[i] = -1;
	}

	// initialize total distance array to 0
	for(i = 0; i < M; i++){
		counter[i] = 0;
		for(j = 0; j < 2; j++){
			total_distance[i][j] = 0;
		}
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
	fgets(buffer1,100,fp1);
	
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

// main implementation of k-means algorithm
void train(){

	int i,j;
	int pos;
	double distance[M];
	double min;

	// calculate the Euclideian distance
	for(i = 0; i < EXAMPLES; i++){
		for(j = 0; j < M; j++){

			distance[j] = sqrt(pow((examples[i][0] - centroids[j][0]),2.0) + pow((examples[i][1] - centroids[j][1]),2.0));
		}

		// assign example to the min cluster centroid
		pos = 0;
		min = distance[0];

		for(j = 1; j < M; j++){
			if(distance[j] < min){
				min = distance[j];
				pos = j;
			}
		}

		// sum distances for all examples
		next_cluster[i] = pos;
		counter[pos]++;
		total_distance[pos][0] += examples[i][0];
		total_distance[pos][1] += examples[i][1];
	}

	// getting the new centroid
	for(i = 0; i < M; i++){
		centroids[i][0] = total_distance[i][0] / counter[i];
		centroids[i][1] = total_distance[i][1] / counter[i];
	}
}

// function to calculate the results
void results(){

	int i,j;
	double error;
	int ack = 0;

	// check if wj vectors have changed, if yes then start new loop, else finish
	while(ack == 0){

		for(i = 0; i < EXAMPLES; i++){
			cluster[i] = next_cluster[i];
		}

		train();

		ack = 1;

		for(i = 0; i < EXAMPLES; i++){
			if(next_cluster[i] != cluster[i]){
				ack = 0;
				break;
			}
		}
	}

	// calculate total variance by adding the distance of each example from the centroid of the cluster

	error = 0;

	for(i = 0; i < M; i++){
		for(j = 0; j < EXAMPLES; j++){
			if(next_cluster[j] == i){

				error += pow((examples[j][0] - centroids[i][0]),2.0) + pow((examples[j][1] - centroids[i][1]),2.0);
			}
		}
	}

	// write the results in a txt file

	fprintf(fp2, "Centroids\n");
	fprintf(fp2,"x1\t  y1\n");

	for(i = 0; i < M; i++){
		fprintf(fp2, "%f, %f \n",centroids[i][0],centroids[i][1]);
	}

	fprintf(fp2,"\nTotal clustering error: %10f \n", error);
}
