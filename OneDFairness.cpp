#include<iostream>
#include<cstdlib>
#include<vector>
#include<bits/stdc++.h>
using namespace std;
int time1=0;
int binarySearch(vector<int> arr, int l, int r, int x) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
        // If the element is present at the middle 
        // itself 
        if (arr[mid] == x) 
            return mid; 
  
        // If element is smaller than mid, then 
        // it can only be present in left subarray 
        if (arr[mid] > x) 
            return binarySearch(arr, l, mid - 1, x); 
  
        // Else the element can only be present 
        // in right subarray 
        return binarySearch(arr, mid + 1, r, x); 
    } 
  
    // We reach here when element is not 
    // present in array 
    if(time1==0)
    {
	time1++;
    	return (r+1);
    }
    else
    {
	return(l-1);
    } 
} 


int main()
{
	srand((unsigned) time(0));
	vector<int> g1;
	int i=0,s=0,t=0;
	//Generate 100 random numbers.
	while(i<=100)
	{
		int r = ((rand()%100)+(rand()%500))%100;
		g1.push_back(r);
		i++;
	}
	//sort the numbers.
	sort(g1.begin(),g1.end());

	printf("\nRandom 100 Numbers generated \n");
	for(int i=0;i<=100;i++)
	{
		printf("%d ",g1[i]);
	}

	//Generate start and end point of range randomly
	int start = g1[0];
	int end = g1[100];
	int r1 = (rand() % (end - start + 1)) + start;
	int r2 = (rand() % (end - start + 1)) + start; 
	if(r1<r2)
	{
		s = r1;
		t = r2;	
	}
	else
	{
		s = r2;
		t = r1;	
	}
	printf("\n");
	printf("\nThe range is = %d : %d",s,t);

	//if the range is x:x' search the index of the points x and x' in the sorted array.  
	int x1 = binarySearch(g1,0,100,s);
	int y1 = binarySearch(g1,0,100,t);

	//randomly generate an index between the x(index):x'(index) and report point at that index.
	int result = (rand() % (y1 - x1 + 1)) + x1; 
	printf("\n");
	printf("\nFairly chosen point in the range %d:%d = %d\n",s,t,g1[result]);
	
	
	
}

