// Kmeans.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stdio.h"
#include "ctype.h"
#include<stdlib.h>
#include "util.h"    //this is the header file containing all the functions used while prediction
#include <math.h>
#include<float.h>
#define p 12
#define k 8
#define N 320
#define M 6340
FILE *file_input, *file_output,*ref,*test,*normalised;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("This is Assignment 4 (214101056) \n");
	printf("Please wait..The processing is going on! \n");
	printf("---------------------------------------------------------------------------------\n");
	//Declaring all the required arrays and variables

	char arr[2048],line[150],ch;
	long double universe[M][p]={{0}},codebook[k][p]={{0}},num=0,dist=0,distortion=DBL_MAX,avg_dist=0,delta=0.00001;
	double tokhura_weights[p]={1.0,3.0,7.0,13.0,19.0,22.0,25.0,33.0,42.0,50.0,56.0,61.0};
	int cnt=0,index=0,row=0,col=0;
	
	file_input = fopen("Universe.csv","r"); //open input file in read mode
	
	//till end of fileis not reached
	while(!feof(file_input))
	{
		fgets(line, 150, file_input); 
		cnt=0;
		while(line[cnt]!='\n'){
			arr[index++]=line[cnt++];
			if(line[cnt]==',') 
			{
				cnt++;	
				arr[index++]='\0';
				index=0;
				num=atof(arr);
				if(col==p){					
					col=0;
					row++;
				}
				universe[row][col]=num;
				col++;
			}
		}				
		
	}
	
	/*for(int i=0;i<6340;i++){
		for(int j=0;j<12;j++){
			printf("%lf ",universe[i][j]);
		}
		printf("\n ");
	}*/

	initialize_codebook(universe,codebook);
	/*for(int i=0;i<k;i++){
		for(int j=0;j<p;j++){
			printf("%lf ",codebook[i][j]);
		}
		printf("\n ");
	}*/
	int count=0;
	while(true){count++;
		dist=kmeans(universe,codebook,tokhura_weights);
		
		avg_dist=dist*1.0/M;
		printf("Average Distortion: %lf %d\n",avg_dist,count);
		if(abs(distortion-avg_dist)>delta)			
			distortion=avg_dist;
		else
			break;

	}
	printf("Average Distortion: %lf %d\n",avg_dist,count);
	return 0;
}

