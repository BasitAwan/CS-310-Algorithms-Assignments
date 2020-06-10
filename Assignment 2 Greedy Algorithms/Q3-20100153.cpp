/* The algorithm I used uses two 1d arrays containing row and col and one 2d for the board formed
I traverse row requirements and for each row try to fill match it with the col of the highest capacity
which does not has not been matched with the row. I do this untill all row requirements are fullfilled and
in order to check if it's possible I just check if all the columns are filled in other words all unmatched columns
don't require a row anymore. 
Because each row is checking for each column hence the running time is o(n^2)


*/
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <set> 
#include <fstream>
#include <list> 
#include <stack>
#include <algorithm> 

using namespace std;





int main()
{
	string line;
	string filename;
	cout << "Enter name of the file please:";
	cin.getline(filename);
	ifstream myfile (filename.c_str());
  int n=0;
  int *row;
  int *col;
  int **table;
	if (myfile.is_open())
	{

		myfile >> line;
    myfile >> n;
    row = new int[n];
    col = new int[n];
    table = new int*[n];
    for (int i = 0; i < n; ++i)
    {
      table[i]=new int[n];
    }
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < n; ++j)
      {
        table[i][j]=0;
      }
    }

    myfile >> line;
    for (int i = 0; i < n; ++i)
    {
      myfile >> row[i];
    }

    myfile >> line;
    for (int i = 0; i < n; ++i)
    {
      myfile >> col[i];
    }
    
    for (int i = 0; i < n; ++i)
    {
      while(col[i]!=0)
      {
        int max = 0;
        int *dupRow = new int[n];
        for (int i = 0; i < n; ++i)
        {
          dupRow[i]=row[i];
        }
        do{
          max = distance(dupRow, max_element(dupRow , dupRow + n));
          dupRow[max]=0;

        }while(table[max][i]==1);
        

        if (row[max] < 1)
        {
          cout << "Not Possible";
          return 0 ;
        }
        col[i]--;
        row[max]--;
        table[max][i] = 1;

      }

    }

    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < n; ++j)
      {
        if (table[i][j]==1)
        {
         cout << "(" << i+1 << "," << j+1 << ")";
          
        }
      }
      cout << endl;
    }
  
  
    


  }
}