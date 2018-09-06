// FCM模糊聚类.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include<iostream>

using namespace std;

int N,K;
int* CenterIndex;
double *Center;
double *CenterCopy;
double *DataSet;
double **Cluster;
int *Top;

void InitData();
void InitCenter();
void CreatRandomArray(int N,int K,int* centerIndex);
void CopyCenter();
void UpdateCluster();
void UpdateCenter();
int GetIndex(double value,double* centerIndex);
void AddtoCluster(int index,double value);
void print();
bool IsEqual(double* center,double* centercopy);


int _tmain(int argc, _TCHAR* argv[])
{
	int Flag = 1;
	InitData();
	while(Flag)
	{
		UpdateCluster();
		UpdateCenter();
		if(IsEqual(Center,CenterCopy))
		{
			Flag=0;
		}
		else
		{
			CopyCenter();
		}
	}
	print();
	getchar();getchar();getchar();
	return 0;
}

void InitData()
{
	int i =0;
	int a;
	do
	{
	cout<<"请输入数据元素的个数:";
	cin>>N;
	cout<<"请输入分类数:";
	cin>>K;
	}while(N<K);
	
	CenterIndex = new int[sizeof(int)*K];
	Center = new double[sizeof(double)*K];
	CenterCopy = new double[sizeof(double)*K];
	DataSet = new double[sizeof(double)*N];
	Cluster = new double*[sizeof(double*)*K];
	Top = new int[sizeof(int)*K];

	for(i=0;i<K;i++)
	{
		Cluster[i] = new double[sizeof(double)*N];
		Top[i]=0;
	}

	for(i=0;i<N;i++)
	{
		a = rand()%100;
		DataSet[i]=a;
	}

	InitCenter();
	UpdateCluster();
}

void InitCenter()
{
	int i=0;
	//CreatRandomArray(N,K,CenterIndex);
	for(i=0;i<K;i++)
	{
		//Center[i] = DataSet[CenterIndex[i]];
		Center[i] = DataSet[i];
	}
	CopyCenter();
}

void CreatRandomArray(int N,int K,int* centerIndex)
{
	int i=0,j=0;
	for(i=0;i<K;i++)
	{
		centerIndex[i]=i;
		/*
		int a = rand()%N;
		for(j=0;j<i;j++)
		{
			if(centerIndex[j]==a)
				break;
		}
		if(j>=i)
			centerIndex[i]=a;
		else
			i--;*/
	}
}

void CopyCenter()
{
	int i=0;
	for(i=0;i<K;i++)
	{
		CenterCopy[i]=Center[i];
	}
}

void UpdateCluster()
{
	int i,tindex;
	for(i=0;i<K;i++)
	{
		Top[i]=0;
	}
	for(i=0;i<N;i++)
	{
		tindex=GetIndex(DataSet[i],Center);
		AddtoCluster(tindex,DataSet[i]);
	}
}

int GetIndex(double value,double* center)
{
	int i=0;
	int index=0;
	double min = fabs(value-center[i]);
	for(i=0;i<K;i++)
	{
		if(fabs(value-center[i])<min)
		{
			index=i;
			min=fabs(value-center[i]);
		}
	}
	return index;
}

void AddtoCluster(int index,double value)
{
	Cluster[index][Top[index]]=value;
	Top[index]++;
}

void UpdateCenter()
{
	int i,j;
	double sum;

	for(i=0;i<K;i++)
	{
		sum=0.0;
		for(j=0;j<Top[i];j++)
		{
			sum+=Cluster[i][j];
		}
		if(Top[i]>0)
		{
			Center[i]=sum/Top[i];
		}
	}
}

bool IsEqual(double* center,double* centercopy)
{
	int i;
	for(i=0;i<K;i++)
	{
		if(center[i]!=centercopy[i])
			return 0;
	}
	return 1;
}

void print()
{
	int i,j;
	cout<<"=========================================="<<endl;
	for(i=0;i<K;i++)
	{
		cout<<"第"<<i<<"组：质心为："<<Center[i]<<endl;
		cout<<"数据元素为:\n";
		for(j=0;j<Top[i];j++)
		{
			cout<<Cluster[i][j]<<'\t';
		}
		cout<<endl;
	}
}