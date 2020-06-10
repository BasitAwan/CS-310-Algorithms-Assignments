/* In this I used a struct probLength to sort the data according to the prob/length ratio but also
make sure that it remembers the original index. What I did was sort the racks according to their 
prob/length ratio and placed the highest one first. The sort function would dominate this algorithm 
and it was done in O(nlogn) hence the time complexity is O(nlogn)

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


struct probLength{
  double val;
  double index;
};


int main()
{
	string line;
	string filename;
	cout << "Enter name of the file please:";
	cin.getline(filename);
	ifstream myfile (filename.c_str());
  int n=0;
  double *len;
  double *prob;
  probLength* probLen;
	if (myfile.is_open())
	{

		myfile >> line;
    myfile >> n;
    prob = new double[n];
    len = new double[n];
    probLen = new probLength[n];
    myfile >> line;
    for (int i = 0; i < n; ++i)
    {

      myfile >> line;
      string extract="";
      for (int i = 0; i < sizeof(line)-1; ++i)
      {
        extract = extract + line[i];
      }
      len[i] = stod(extract);
    }

    myfile >> line;
    for (int i = 0; i < n; ++i)
    {
       myfile >> line;
       string extract="";
      for (int i = 0; i < sizeof(line)-1; ++i)
      {
        extract = extract + line[i];
      }
      prob[i] = stod(extract);
    }
    
    for (int i = 0; i < n; ++i)
    {
      probLen[i].val= prob[i]/len[i];
      probLen[i].index=i;
    }
    
    sort(probLen, probLen+n, [](probLength A, probLength B){return A.val> B.val;});

    for (int i = 0; i < n; ++i)
    {
      cout << "rack" << (probLen[i].index) +1 << " " ;
    }
    cout << endl;
    double expected = 0;
    for (int i = 0; i < n; ++i)
    {
      double sum = 0;
      for (int j = 0; j < i+1; ++j)
      {
        int ind = probLen[j].index;
        sum = sum + len[ind];
      }
      int ind = probLen[i].index;
      expected = expected + prob[ind]*sum;
    }

    cout << "Expected time: " << expected << endl; 
  
    


  }
}