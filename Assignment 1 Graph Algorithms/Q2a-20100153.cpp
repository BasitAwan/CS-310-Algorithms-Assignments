/* In this task I tried to do a topological sort to keep the ones hated below, I used a stack to get least pointed
to inserted into the top as I think a stack was the best data structure for this problem. To figure out if it was cyclic 
I made a function similar to the one in the previous question which did dfs to look for itself and then I ran on all leaders.



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
	set<int> *edge;
	int num;
	Graph()
	{
		num = 1;
		edge = new set<int>[1];
	}
	Graph(int number)
	{
		num = number;
		edge = new set<int>[number];
	}
	void printGraph()
	{
		for (int i = 0; i < num; ++i)
		{ 

	        set<int> temp = edge[i]; 
	        cout << i << ':'; 
	  
	        for (auto itr = temp.begin(); itr != temp.end(); ++itr) 
	        {
	            cout << *itr << ","; 
	        }
	        cout << endl; 
    	}
	}
	void addEdge(int src, int dest) 
	{ 
	    edge[src].insert(dest); 
	} 

	void find_order(int lead, int visited[], stack <int> &Stack)
	{
		visited[lead]=1;
		for (auto i = edge[lead].begin();  i != edge[lead].end(); ++i)
		{
			if (visited[*i]==0)
			{
				find_order(*i,visited,Stack);
			}
		}

		Stack.push(lead);
		

	}
	string is_cyclic(int lead, int visited[], int current[] ){
		cout << lead << endl;
		if (visited[lead]==1)
		{
			current[lead]=0;
			return "NOPE";
		}
		else
		{
			visited[lead] = 1;
			current[lead]=1;
			for (auto i = edge[lead].begin();  i != edge[lead].end(); ++i)
			{
				if (visited[*i]==0)
				{
					string result = is_cyclic(*i,visited,current);
					if(result!="NOPE")
					{
						return "->L" + to_string(*i)+ result;
					}
				}
				else if (current[*i])
				{
					return "->L" + to_string(*i);
				}
			}
			current[lead]=0;
		}
		return"NOPE";
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
  					for (int i = 1; i < line.length(); ++i)
	  				{
	  					if (line[i]==',')
	  					{
	  						break;
	  					}
	  					extract = extract + line[i];
	  				}
  					int dest = stoi(extract) ;
  					extract="";
  					graph->addEdge(src,dest);
  					if (!(myfile>> line))
  					{
  						break;
  					}
  					

  				}
  				check =true;

  			}

  		}

  	}
  	graph->printGraph();
  	stack<int> Stack;
  	int visited[number];
  	int current[number];
  	for (int i = 0; i < number; ++i)
  	{
  		visited[i]=0;
  		current[i]=0;
  	}
  	string result= "NOPE";
  	for (int i = 0; i < number; ++i)
	{
		if(visited[i]==0)
		{
			string result =graph->is_cyclic(i,visited,current);
			if (result!="NOPE")
			{
				cout<< "NO" << endl << "L" << i <<  result << endl;
				return 0;
			}

		}
	}
	for (int i = 0; i < number; ++i)
  	{
  		visited[i]=0;
  	}
  	for (int i = 0; i < number; ++i)
	{
		if(visited[i]==0)
		{
			graph->find_order(i,visited,Stack);

		}
	}
  	while(!Stack.empty())
  	{
  		cout << "L" << Stack.top() << " ";
  		Stack.pop();
  	}
  	cout <<endl;

}