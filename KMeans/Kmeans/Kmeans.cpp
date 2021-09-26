// Kmeans.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stdio.h"
#include "ctype.h"
#include<stdlib.h>
#include "util.h"    //this is the header file containing all the functions used while prediction
#include <math.h>
#include<float.h>
#include<string.h>
#define p 12
#define k 8
#define M 6340
FILE *file_input, *file_output;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("This is Vector Quantization using KMeans or LLoyd's Algorithm  (214101056) \n");
	printf("---------------------------------------------------------------------------------\n");

	//Declaring all the required arrays and variables
	char arr[1024],*line,ch;
	long double universe[M][p]={{0}},codebook[k][p]={{0}},num=0,dist=0,distortion=100000000.0,avg_dist=0,delta=0.00001;
	double tokhura_weights[]={1.0,3.0,7.0,13.0,19.0,22.0,25.0,33.0,42.0,50.0,56.0,61.0};
	int cnt=0,index=0,row=0,col=0;
	
	file_input = fopen("Universe.csv","r"); //open input file in read mode
	
	//Reading the csv file and writing data in a 2D array.
	while(fgets(arr, 1024, file_input))
	{
		line=strtok(arr,",");
		col=0;
		while(line!=NULL){
			universe[row][col]=atof(line);
			++col;
			line=strtok(NULL,",");
		}
		row++;
		
	}
	
	printf("Universe array generated!\n\n");

	initialize_codebook(universe,codebook);

	printf("The initialised codebook : \n\n");
	for(int i=0;i<k;i++){
		for(int j=0;j<p;j++){
			printf("%lf ",codebook[i][j]);
		}
		printf("\n");
	}
	printf("---------------------------------------------------------------------------------\n");

	int count=0; //number of iterations
	while(true){
		count++;
		dist=kmeans(universe,codebook,tokhura_weights);	 //finding distortion using kmeans algorithm	
		avg_dist=dist*1.0/M;
		
		if(abs(distortion-avg_dist)>delta)				//if difference between current and previous distortion is less than delta stop		
			distortion=avg_dist;
		else
			break;

	}
	printf("The final codebook : \n\n");
	for(int i=0;i<k;i++){
		for(int j=0;j<p;j++){
			printf("%lf ",codebook[i][j]);
		}
		printf("\n");
	}
	printf("---------------------------------------------------------------------------------\n");
	printf("Average Distortion using Kmeans: %lf \n",avg_dist);
	return 0;
}

