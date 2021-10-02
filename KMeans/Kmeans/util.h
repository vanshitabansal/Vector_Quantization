// util.h : include file for project specific files
//that are used frequently, but are changed infrequently
#include "stdafx.h"
#include "stdio.h"
#include "ctype.h"
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<time.h>
#define p 12
#define k 8
#define N 320
#define M 6340
void initialize_codebook(long double x[M][p],long double y[k][p]){
	srand(time(0));
	for(int i=0;i<k;i++){	
		int num=rand()%M;
		for(int j=0;j<p;j++){
			y[i][j]=x[num][j];
		}
	}
	
}

long double kmeans(long double x[M][p],long double y[k][p],double tokhura_weights[p]){
	
	long double min_dist=DBL_MAX,temp_dist=0,dist=0;
	int bucket[k]={0},pos=0,region[k][M];
	long double distances[k]={0};

	//Classify
	for(int i=0;i<M;i++){ 
		min_dist=1000000000.0;
		for(int j=0;j<k;j++){
			distances[j]=0;
			for(int u=0;u<p;u++){
				//finding tokhura's distance between universe vector and codebook vector
				distances[j]+=tokhura_weights[u]*(x[i][u]-y[j][u])*(x[i][u]-y[j][u]);
			}
			
		}	
		//finding minimum distance vector in codebook and saving its index
		for(int j=0;j<k;j++){
			if(min_dist>distances[j]){
				min_dist=distances[j];
				pos=j;
				}
		}
		
		//Assigning the universe vector to codebook region
		region[pos][bucket[pos]++]=i;

		//Total distortion
		dist+=min_dist;
		
	}

	//Centroid updation
	for(int i=0;i<k;i++){	
		long double centroid[p]={0};

		//Finding sum of Ci's to get centroid of a region
		for(int u=0;u<p;u++){
			for(int j=0;j<bucket[i];j++){
				 centroid[u]+=x[region[i][j]][u];
			}
		}

		//Finding the centroid of region
		for(int u=0;u<p;u++){
			centroid[u]/=bucket[i];
		}

		//Updating codebook with new centroid
		for(int u=0;u<p;u++){
			y[i][u]=centroid[u];
		}
	}
	return dist;
}
