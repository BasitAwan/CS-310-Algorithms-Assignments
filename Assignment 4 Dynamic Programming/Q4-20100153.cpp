/* the recurrence relation is T(n,m) = T(n+1,m)+T(m+1,n). n is the size of the first string and m is the size of the second string
The complexity of the alogritm is O(m+n), There are m+n subproblems and it takes O(1) time to compute each of them.

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




int main() {
  string first="";
  string second= "";
  string third ="";
  string filename;
  // cout << "Enter name of the file please:";
  // cin >> filename;
  filename= "test.txt";
  ifstream myfile(filename.c_str());

  bool check = false;
  int counter = 0;
  if (myfile.is_open()) {
  	getline(myfile,first);
  	getline(myfile,second);
  	getline(myfile,third);
  }
  int **match= new int*[first.length()+1];
  for (int i = 0; i < first.length()+1; ++i)
  {
  	match[i]= new int[second.length()+1];
  	for (int j = 0; j < second.length()+1; ++j)
  	{
  		match[i][j]=0;
  	}
  }

  for (int i = 0; i < first.length()+1; ++i)
  {
  	for (int j = 0; j < second.length()+1; ++j)
  	{
  		if (i==0 && j==0)
  		{
  			match[i][j]=1;
  		}
  		else if (j==0)
  		{
  			if (first[i-1]==third[i-1])
  			{
  				match[i][j]=match[i-1][j];
  			}
  		}
  		else if (i==0)
  		{
  			if (second[j-1]==third[j-1])
  			{
  				match[i][j]=match[i][j-1];
  			}
  		}
  		else if(first[i-1]==third[i+j-1])
  		{
  			if (second[j-1]==third[i+j-1])
  			{
  				match[i][j]= max(match[i][j-1],match[i-1][j]);
  			}
  			else
  			{

  				match[i][j]=match[i-1][j];
  			}
  		}
  		else if(second[j-1]==third[i+j-1])
  		{
  			if (first[i-1]==third[i+j-1])
  			{
  				match[i][j]= max(match[i][j-1],match[i-1][j]);
  			}
  			else
  			{
  				match[i][j]=match[i][j-1];
  			}
  		}
  	}
  }

  

	int i = first.length();
	int j = second.length();
	if (match[i][j]!=1)
	{
		cout << "INVALID" << endl;
		return 0;
	}
	cout << "VALID" << endl;
	string temp="";
	vector<string> v;
	bool firstString = true;
	int location= third.length()-1;
	while(i!=-1 || j!=-1)
	{
		if (i==0)
		{
			if (temp.length()>0)
			{
				v.push_back("S1"+temp);	
			}
			firstString=false;
			temp= "";
			break;
		}

		else if (match[i-1][j]==1 && first[i-1]==third[location] && firstString)
		{
			temp= first[i-1]+temp;
			i = i-1;
			location--;
		}
		else if (firstString)
		{
			// cout << third[location]<< endl;

			if (temp.length()>0)
			{
				v.push_back("S1"+temp);	
			}
			firstString=false;
			temp= "";
		}
		else if(match[i][j-1]==1 && second[j-1]==third[location] && !firstString)
		{
			temp= second[j-1]+temp;
			j = j-1;
			location--;
		}
		else if (!firstString)
		{

			if (temp.length()>0)
			{
				v.push_back("S2"+temp);	
			}
			firstString=true;
			temp= "";
		}
	}

	for (int i = v.size()-1; i >-1; --i)
	{
		cout<< v[i] << " ";
	}

   

  return 0;
}