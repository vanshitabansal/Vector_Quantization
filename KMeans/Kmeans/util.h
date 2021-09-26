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
long double find_tokhura_distance(double tokhura_weights[p],long double x[p],long double y[p]){
	long double num=0,sum=0,total_sum=0;	
	//Calculating Tokhura's distance using weight array	
		sum=0;
		for(int u=0;u<p;u++){
			sum+=tokhura_weights[u]*(x[u]-y[u])*(x[u]-y[u]);
		}		
	
	return sum;
}
long double kmeans(long double x[M][p],long double y[k][p],double tokhura_weights[p]){
	
	long double min_dist=DBL_MAX,temp_dist=0,dist=0;
	int bucket[k]={0},pos=0,region[k][M];
	int distances[k]={0};
	//Classify
	for(int i=0;i<M;i++){ 
		min_dist=1000000000.0;
		for(int j=0;j<k;j++){
			distances[j]=0;
			for(int u=0;u<p;u++){
				distances[j]+=tokhura_weights[u]*(x[i][u]-y[j][u])*(x[i][u]-y[j][u]);
			}

			
		}	
		//temp_dist+=find_tokhura_distance(tokhura_weights,x[i],y[j]);
		for(int j=0;j<k;j++){
			if(min_dist>distances[j]){
				min_dist=distances[j];
				pos=j;
				}
		}
			
		region[pos][bucket[pos]++]=i;
		dist+=min_dist;
		//printf("%lf %d\n",min_dist,pos);
	}

	//Total Distortion
	/*for(int i=0;i<k;i++){
		for(int j=0;j<bucket[i];j++){
			dist+=find_tokhura_distance(tokhura_weights,y[i],x[region[i][j]]);
		}
	}*/

	//Centroid updation
	for(int i=0;i<k;i++){	
		long double centroid[p]={0};
		for(int u=0;u<p;u++){
			for(int j=0;j<bucket[i];j++){
				 centroid[u]+=x[region[i][j]][u];
			}
		 }
		for(int u=0;u<p;u++){
			centroid[u]/=bucket[i];
		}
		for(int u=0;u<p;u++){
			y[i][u]=centroid[u];
		}
	}
	return dist;
}