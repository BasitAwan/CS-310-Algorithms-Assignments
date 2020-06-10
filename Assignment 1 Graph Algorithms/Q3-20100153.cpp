/* I used an adjancy matrix in this task, I implemented something similar to djikstra algorithm, through comparasion of 
value coming from nodes and keeping the minimum one. Then I took the user's input and compared distance from A to B and then the 
sum of distances from A to X and X to B. I couldn't get the code to print a path though.


*/
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <set> 
#include <fstream>
#include <list> 
#include <stack>

using namespace std;

class Graph
{
	public:
	int num;
	int edge[100][100];

	Graph()
	{
		num = 1;
		
	}
	Graph(int number)
	{
		num = number;
		// int** edge = new int*[num];
		// for(int i = 0; i < num; ++i)
		//    	edge[i] = new int[num];


		for (int i = 0; i < num; ++i)
		{
			for (int j = 0; j < num; ++j)
			{
				edge[i][j]=0;
			}
		}
	}
	void printGraph()
	{
		for (int i = 0; i < num; ++i)
		{ 

	        cout << i << ':'; 
	  
	        for (int j=0 ; j<num ; j++ ) 
	        {
	            cout << j << ";" << edge[i][j] << ", "; 
	        }
	        cout << endl; 
    	}
	}
	void addEdge(int src, int dest, int w) 
	{

		edge[src][dest]=w;

	} 
	int helper(int src, int dest, int visited[])
	{
		int min=99999999;
		visited[src]=1;
		cout << src << " " << dest << endl;
		if (src==dest)
		{
			return 0;
		}
		for (int i = 0; i < num; ++i)
		{
			if (edge[src][i]!=0 && visited[i]==0)
			{
				 int x = helper(i,dest,visited)+ edge[src][i];
				 cout << x << endl;
				 if (x<min)
				 {
				 	min = x;
				 }

			}
		}
		return min;
	}

	// 
	int findmin(int src, int dest)
	{
		int min=999999999;
		int visited[num];
		for (int i = 0; i < num; ++i)
		{
			visited[i]=0;
		}
		for (int i = 0; i < num; ++i)
		{
			if (edge[src][i]!=0 )
			{
				 int x = helper(i,dest,visited)+ edge[src][i];
				 if (x<min)
				 {
				 	min = x;
				 }

			}
			for (int j = 0; j < num; ++j)
			{
				visited[j]=0;
			}

		}
		return min;
	}

	
};

int main()
{
	string line;
	string filename;
	cout << "Enter name of the file please:";
	cin >> filename;
  	ifstream myfile (filename.c_str());
  	Graph* graph;
  	bool check = false;
  	int number=999999;
  	int count = 0;
  	if (myfile.is_open())
  	{
  		while(check || myfile>> line)
  		{
  			if (count>number)
  			{
  				break;
  			}
  			count++;
  			if (check)
  			{
  				check==false;
  			}
  			if (line[0]=='n')
  			{
  				myfile>> line;
  				number =stoi(line);
   				graph = new Graph(number);


  			}
  			else if (line[line.length()-1]==':')
  			{
  				string extract = "";
  				for (int i = 1; i < line.length()-1; ++i)
  				{
  					extract = extract + line[i];
  				}

  				int src= stoi(extract);
  				extract="";
  				myfile>> line;

  				while(line[line.length()-1]!=':')
  				{

  					string dest;
  					for (int i = 1; i < line.length(); ++i)
	  				{
	  					if (line[i]==';')
	  					{
	  						dest = extract;
	  						extract="";
	  						++i;
	  					}
	  					if (line[i]==',')
	  					{
	  						break;
	  					}
	  					extract = extract + line[i];
	  				}

	  				int d = stoi(dest);
  					int w = stoi(extract) ;
  					extract="";

  					graph->addEdge(src,d,w);
  					if (!(myfile>> line))
  					{
  						break;
  					}
  					

  				}
  				check =true;

  			}

  		}

  	}
  	int a,b,x;
  	cout << "Please Enter A,B,X with spaces:";
  	cin>>a;
  	cin>>b;
  	cin>>x;
  	int normal = graph->findmin(a,b);
  	int divert = graph->findmin(a,x) + graph->findmin(x,b);
  	if (normal*1.2>divert)
  	{
  		cout<< "DIstance is less than 120%" << endl;
  		cout << "length of path A to B is " << normal << "whereas length of path A to B via X is " << divert;
  		return 0;
  	}
  	else
  	{
  		cout<< "DIstance is more than 120%" << endl;
  		cout << "length of path A to B is " << normal << "whereas length of path A to B via X is " << divert;
  		return 0;
  	}

}






// string helper1(int src, int dest, int visited[])
	// {
	// 	int min=99999999;
	// 	visited[src]=1;
	// 	string final ="";
	// 	if (src==dest)
	// 	{
	// 		return "";
	// 	}
	// 	for (int i = 0; i < num; ++i)
	// 	{
	// 		if (edge[src][i]!=0 && visited[i]==0)
	// 		{
	// 			 int x = helper(i,dest,visited)+ edge[src][i];
	// 			 string y =  helper1(i,dest,visited);
	// 			 cout << x << endl;
	// 			 if (x<min)
	// 			 {
	// 			 	final = "L->" +to_string(i) + y;
	// 			 	min = x;

	// 			 }

	// 		}
	// 	}
	// 	return final;
	// }
	// string findPath(int src, int dest)
	// {
	// 	int min=999999999;
	// 	int visited[num];
	// 	string final ="";
	// 	for (int i = 0; i < num; ++i)
	// 	{
	// 		visited[i]=0;
	// 	}
	// 	for (int i = 0; i < num; ++i)
	// 	{
	// 		if (edge[src][i]!=0)
	// 		{
	// 			 int x = helper(i,dest,visited)+ edge[src][i];
	// 			 string y = helper1(i,dest,visited);
	// 			 cout << x << endl;
	// 			 if (x<min)
	// 			 {
	// 			 	final = y;
	// 			 	min = x;

	// 			 }

	// 		}
	// 	}
	// 	return final;
	// }