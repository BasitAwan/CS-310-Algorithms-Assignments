/*the recurrence relation is T(n)= 3T(n+1), the input is the week number a bool to show if priming is happending or not
The running time is o(n) as every week is divided into 3 weeks and those weeks are divided into 3 more but because we 
are keeping track of already calculated values it take linear time. The sub problems are about 3, priming is done then we can have a high as well,
if priming is not done we can't have a high and can also have a priming. 

*/


#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

using namespace std;
struct siteDate {
  int site;
  int date;
};

int *high;
int *low;
int **memory;
int **path;
int number = 999999;



int findCost(bool prim, int week)
{
	if (prim && number== week-1)
	{
		if (high[week]>low[week])
		{
			path[week][1]=1;
			return high[week];
		}
		else
		{
			path[week][0]=1;
			return low[week];
		}
	}
	if (number==week+1)
	{
		path[week][0]=1;
		return low[week];
	}
	if (prim)
	{
		if (memory[week][2]==-1)
		{
			memory[week][2]= findCost(true,week+1);
		}
		if (memory[week][1]==-1)
		{
			memory[week][1]= high[week]+findCost(false,week+1);
		}
		if (memory[week][0]==-1)
		{
			memory[week][0]= low[week]+findCost(false,week+1);
		}
		int x = memory[week][2];
		int y = memory[week][1];
		int z = memory[week][0];

		int max = x; 

		if (y > max) { 
			max = y;
		} 
		if (z > max) { 
			max = z;
		} 
		if (max==x)
		{
			path[week][2]= 1;
		}
		else if (max==y)
		{
			path[week][1]= 1;
		}
		else if (max==z)
		{
			path[week][0]= 1;
		}
		return max; 


	}
	else
	{
		if (memory[week][2]==-1)
		{
			memory[week][2]= findCost(true,week+1);
		}
		if (memory[week][0]==-1)
		{
			memory[week][0]= low[week]+findCost(false,week+1);
		}
		int x = memory[week][2];
		int z = memory[week][0];

		int max = x; 
		if (z > max) { 
			max = z;
		} 
		if (max==x)
		{
			path[week][2]= 1;
		}
		else if (max==z)
		{
			path[week][0]= 1;
		}
		return max; 


	}

}

int main() {
  string line;
  string filename;
  // cout << "Enter name of the file please:";
  // cin >> filename;
  filename= "test.txt";
  ifstream myfile(filename.c_str());

  bool check = false;
  int counter = 0;
  if (myfile.is_open()) {
  	myfile >> line;
  	myfile >> line;
	number = stoi(line);
	high = new int[number];
	low = new int[number];
	memory = new int*[number];
	path = new int*[number];
	for (int i = 0; i < number; ++i)
	{
		memory[i]= new int[number];
		path[i]= new int[number];
		for (int j = 0; j < 3; ++j)
		{
			memory[i][j]= -1;
			path[i][j]= -1;
		}
	}

    myfile >> line;
    for (int i = 0; i < number; ++i)
    {
    	myfile >> line;
    	int cost = stoi(line);
    	high[i] = cost;
    }
    myfile >> line;
    for (int i = 0; i < number; ++i)
    {
    	myfile >> line;
    	int cost = stoi(line);
    	low[i] = cost;
    }
  }

  int cost = findCost(true,0);
  bool prim = true;
  for (int i = 0; i <number; ++i)
  {
  	if (path[i][2]>0&& !prim)
	{
		string output = "Week" + to_string(i+1) +" :Priming";
		cout<<output<<endl;
		prim=true;
	}
	else if (path[i][1]>0 && (i<1||path[i-1][2]>0) && prim)
	{
		string output = "Week" + to_string(i+1) +" :High " + to_string(high[i]);
		cout<<output<<endl;
		prim=false;
	}
	else if (path[i][0]>0)
	{
		string output = "Week" + to_string(i+1) +" :Low " + to_string(low[i]);
		cout<<output<<endl;
	}
  }

  cout << "Total Revenue: "<< cost << endl;
  

   

  return 0;
}