// LBG.cpp : Defines the entry point for the console application.
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
	printf("This is Vector Quantization using LBG Algorithm (214101056) \n");
	printf("\n-----------------------------------------------------------------------------------------------------------------------\n\n");
	//Declaring all the required arrays and variables

	char arr[1024],*line,ch;
	long double universe[M][p]={{0}},codebook[k][p]={{0}},num=0,dist=0,distortion=DBL_MAX,avg_dist=0,delta=0.0001,epsilon=0.03;
	double tokhura_weights[]={1.0,3.0,7.0,13.0,19.0,22.0,25.0,33.0,42.0,50.0,56.0,61.0};
	int cnt=0,index=0,row=0,col=0,m=0;
	
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
	printf("\n-----------------------------------------------------------------------------------------------------------------------\n\n");

	int count=0; //number of iterations
	index=0,m=1;
	long double y_new1[p]={0},y_new2[p]={0};
	while(m<k){
		distortion=10000000.0;
		count++;
		for(int ind=0;ind<m;ind++){
			for(int i=0;i<p;i++){
				y_new1[i]=codebook[ind][i]*(1+epsilon);
			}
			for(int i=0;i<p;i++){
				y_new2[i]=codebook[ind][i]*(1-epsilon);
			}
			for(int i=0;i<p;i++){
				codebook[ind][i]=y_new1[i];
				if(ind+m<k) codebook[ind+m][i]=y_new2[i];
			}			
		}
		m=2*m;
		while(true){
		
				dist=kmeans(universe,codebook,tokhura_weights,m);		 //finding distortion using kmeans algorithm
				avg_dist=dist*1.0/M;
				if(abs(distortion-avg_dist)>delta)						//if difference between current and previous distortion is less than delta stop		
					distortion=avg_dist;
				else
					break;

		}
		printf("Codebook for m = %d :\n\n",m);
		for(int i=0;i<k;i++){
			for(int j=0;j<p;j++){
				printf("%lf ",codebook[i][j]);
			}
			printf("\n");
		}
		printf("\n-----------------------------------------------------------------------------------------------------------------------\n\n");
		
	}
	printf("Average Distortion using LBG: %lf \n",avg_dist);
	printf("\n-----------------------------------------------------------------------------------------------------------------------\n\n");
	return 0;
}


