/*My implementation in this problem is of two steps first in majority function I split the array
into two until the size of the array is 2 and then compare the two values if both values are same I 
return the value if not I return -1. The function uses these function to compare values again if one of
them is -1 it return the other one, if both of them don't match it returns -1. So the end result of this
is that we get the majority species. We then check this the count of this species in the array and if its
more than half the size than print that it was a success and print its indices.

The recurrence relation is T(n)= 2T(n/2)
and the time complexity is O(n) as the code needs to over the array only twice

*/
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>
#include<time.h> 
#include <stdio.h> 
#include <stdlib.h> 

using namespace std;
struct teamTime
{
  int team;
  int time;
};
int decode(int first,int second)
{
  if (first==second)
  {
    return first;
  }
  return -1;
}
int majority(int *array, int start,int size){
  if (size<=2)
  {
    if (size==2)
    {
      return decode(array[start+1],array[start+2]);
    }
    if (size==1)
    {
      return array[start];
    }
  }
  else {
    int first = majority(array,0,size/2);
    int second = majority(array,size/2,size/2);
    if (first==-1)
    {
      if (second==-1)
      {
        return -1;
      }
      else
      {
        return second;
      }

    }
    else if (second==-1)
    {
      if (first==-1)
      {
        return -1;
      }
      else
      {
        return first;
      }

    }
    if (first==second)
    {
      return first;
    }
  }
}
int main() {
  string line;
  string filename;
  cout << "Enter name of the file please:";
  cin >> filename;
  ifstream myfile(filename.c_str());
  int *array;
  int number = 999999;
  int species =0;
  srand(time(0));
  if (myfile.is_open()) {
    string line;
    myfile>> line;
    myfile >> number;
    myfile >> line;
    myfile >> species;
    array = new int[number];
    for (int i = 0; i < number; ++i)
    {
      array[i]= rand()%species+1;
    }
    

  }
  cout << "[";
  for (int i = 0; i < number ; ++i)
  {
    cout << array[i] << ", ";
  }
  cout << ']' <<endl;
  int major = majority(array,0,number);
  if (major>-1)
  {
    int count=0;
    for (int i = 0; i < number; ++i)
    {
      if (array[i]==major)
      {
        count++;
      }
    }
    if (count>number/2)
    {
      cout << "SUCESS"  << endl;
      cout << "[";
      for (int i = 0; i < number; ++i)
      {
        if (array[i]==major)
        {
          cout<< i << ", ";
        }
      }
      cout << ']' << endl;
    }
    else{
      cout << "FAILURE" << endl;
    }
      
  }
  else{
    cout << "FAILURE" << endl;

  }

  return 0;
    
}