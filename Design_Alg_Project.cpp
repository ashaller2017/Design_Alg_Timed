// Programming Project for COT 4400
// By: Ari Shaller
// Z23411781
// due 8/8/2020
#include <stdlib.h> //library declarations
#include <stdio.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <fstream>


using namespace std;
//function declarations
vector<int> ALG1(vector<int> A, int n, int i);
void ALG2(vector<int> &A, int n, int i);
int ALG3(vector<int> &A, int n, int i);
void Heapsort(vector<int> &A, int n);
void Build_Max_Heap(vector<int> &A);
void Max_Heapify(vector<int> &A, int i);
int Randomized_Select(vector<int>&A, int p, int r, int i);
int Randomized_Partition(vector<int> &A, int p,int r);
int Partition(vector<int> &A, int p,int r);

int main()
{
double i; //i had to be made double for use of floor (compiler warning)
int j, k, m, n; //used variables
m = 5;
n = 200001; //i set my n to 200001 so I could have 200000 elements and ignore the 0 position
clock_t t_1, t_2; //clock type declaration
vector<int> B(n,0);
vector<double > t_avg_alg1(20);
vector<double > t_avg_alg2(20);
vector<double > t_avg_alg3(20);
vector<vector<int> > A (5, vector<int>(200001));

vector<vector<double>> t_alg1(5, vector<double>(20));
vector<vector<double>> t_alg2(5, vector<double>(20));
vector<vector<double>> t_alg3(5, vector<double>(20));



srand(time(NULL)); //helps configure more random integers


for (j = 0; j < 5; j++) //fill 2d vector
	{

		for (k = 1; k <= 200000; k++)
		{
			A[j][k] = rand();


		}
	}





for (n = 10000; n <= 200000; n = n + 10000) //measurement 1
	{
		i = floor((2 * n) / 3); //find i
		for (j = 0; j < 5; j++) //go through each vector
		{
			B.resize(n); //resize b to vector size for correct array implementation
			for (int z = 1; z <= n; z++) //loop in A vector into B starting at 0 position and at vector A in the 1 position
				B[z - 1] = A[j][z]; // I did this so my loops woulndt be 9999 and could be a nice number

			t_1 = clock(); //begin clock
			B = ALG1(B, n, i); //call algoithm 1 and set b equal to it
			t_2 = clock(); //end clock
			cout << B[i] << " "; //print ith order statistic
			int t = ((n / 10000) - 1); //create t to keep track of which measurement is being taken
			t_alg1[j][t] = ((t_2 - t_1) / (CLOCKS_PER_SEC / 1000)); //fill t with times
		}
		int t = ((n / 10000) - 1);
		t_avg_alg1[t] = ((t_alg1[0][t] + t_alg1[1][t] + t_alg1[2][t] + t_alg1[3][t] + t_alg1[4][t]) / m); //find average

	}

cout << endl << "algorithm 2";

//repeat process one for all thre measurements

for (n = 10000; n <= 200000; n = n + 10000) //measurement 2
	{
		i = floor(2 * n / 3);
		for (j = 0; j < 5; j++)
		{
			B.resize(n);
			for (int z = 1; z <= n; z++)
				B[z - 1] = A[j][z];

			t_1 = clock();
			ALG2(B, n, i);
			t_2 = clock();
			cout << B[i] << " ";
			int t = ((n / 10000) - 1);
			t_alg2[j][t] = ((t_2 - t_1) / (CLOCKS_PER_SEC / 1000));
		}
		int t = ((n / 10000) - 1);
		t_avg_alg2[t] = ((t_alg2[0][t] + t_alg2[1][t] + t_alg2[2][t] + t_alg2[3][t] + t_alg2[4][t]) / m);
	}


cout << endl << "algorithm 3";



for (n = 10000; n <= 200000; n = n + 10000) //measurement 3
{
		i = floor(2 * n / 3);
		for (j = 0; j < 5; j++)
		{
			B.resize(n);

			for (int z = 1; z <= n; z++)
				B[z - 1] = A[j][z];


			t_1 = clock();
			int x = ALG3(B, n - 1, i);
			t_2 = clock();
			cout << x << " ";
			int t = ((n / 10000) - 1);
			t_alg3[j][t] = ((t_2 - t_1) / (CLOCKS_PER_SEC / 1000));
		}
		int t = ((n / 10000) - 1);
		t_avg_alg3[t] = ((t_alg3[0][t] + t_alg3[1][t] + t_alg3[2][t] + t_alg3[3][t] + t_alg3[4][t]) / m);
}


ofstream file ("DATA.txt"); //write to DATA.txt all the avg measurements

for (i = 0; i < t_avg_alg1.size(); i++)
	file << t_avg_alg1[i] << " ";
file << endl<< "THIS IS DATA TABLE 2" << endl;
for (i = 0; i <t_avg_alg2.size(); i++)
{
		file << t_avg_alg2[i] << " ";
}
file << endl<< "THIS IS DATA TABLE 3" << endl;
for (i = 0; i < t_avg_alg3.size(); i++)
{
	file << t_avg_alg3[i] << " ";
}
file.close();
system("pause");
return 0;
}
//function declarations
vector<int> ALG1(vector<int> A, int n, int i)
{
	int key;
	int j;
	for (j = 1; j <n; j++)
	{
		key = A[j];
		i = j - 1;
		while (i >= 0 && A[i] > key)
		{
            A[i + 1] = A[i];
			i = i - 1;
		}
		A[i + 1] = key;		
	}
	
return A;
}
void ALG2(vector<int> &A, int n, int i)
{
	Heapsort(A, n);
	return;
}
void Heapsort(vector<int> &A, int n)
{
	vector<int> Heap;
	int i;
	
	Build_Max_Heap(A);
	for (i = n-1; i >= 0; i--)
	{
		swap(A[0], A[i]);
		Heap.insert(Heap.begin(),A[i]);
		A.erase(A.begin()+i);
		Max_Heapify(A, 0);
		
	}
	A = Heap;
	return;
}
void Build_Max_Heap(vector<int> &A)
{
	int n = A.size();
	for (int i = floor(n / 2)-1; i >= 0; i--)
	{
		Max_Heapify(A, i);
	}
	return;
}
void Max_Heapify(vector<int> &A, int i)
{
	int n;
	int l, r, largest;
	n = A.size()-1;
	l = 2 * i;
	r = 2 * i + 1;
	if (l <= n && A[l] > A[i])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}
	if (r <= n && A[r] > A[largest])
	{
		largest = r;
	}
	if (largest != i)
	{
		swap(A[i], A[largest]);
		Max_Heapify(A, largest);
	}
	return;
}
int ALG3(vector<int> &A, int n, int i)
{
	int x;
	x=Randomized_Select(A, 0, n, i);
	return x;
}
int Randomized_Select(vector<int> &A, int p, int r, int i)
{
	int q,k;
 	if (p == r)
		return A[p];
	q = Randomized_Partition(A, p, r);
	k = q - p + 1;
	if (i == k)
		return A[q];
	else if (i < k)
		return Randomized_Select(A, p, q - 1, i);
	else
		return Randomized_Select(A, q + 1, r, i - k);
}
int Randomized_Partition(vector<int>&A, int p, int r)
{
	int i;
	i = (p+rand()%(r-p+1));
	swap(A[r],A[i]);
	return Partition(A, p, r);
}
int Partition(vector<int> &A, int p, int r)
{
	int x = A[r];
	int i = (p - 1);
	for (int j = p; j < r ; j++)
	{
		if (A[j] <= x)
		{
			i++;
			swap(A[i],A[j]);
		}
	}
	swap(A[i+1],A[r]);
	return i + 1;
}
