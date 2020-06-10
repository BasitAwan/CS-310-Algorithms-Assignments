/* What I did is try to run bfs and alot alternate sides to neighbors. When I found two 
adjacent neighbors being which are going to have the same side, I called the cycle finder function
which found the path to the vertex that called it. I return that string. In the main function it checks 
if the string received was okay if it's not (the cyclic path was returned) it prints the string. if the 
string received is okay it takes the sides array sent in the function and first prints the function with side 
1 and then 2. Hence both boxes are made and if not possible the cycle printed. I used the queue data structure to
do bfs. To find the path i did a dfs until the same node was found. I also used sets to store edges, as they store require less storage





*/






#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <set> 
#include <fstream>
#include <list> 

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
	    edge[dest].insert(src); 
	} 
	string cycle_finder(int dest,int src, int visit[], int &times)
	{
		string result="NOPE";
		if (src==dest)
		{
			return "->C" + to_string(src);
			
		}
		visit[src]=1;
		times++;
		for (auto i = edge[src].begin();  i != edge[src].end(); ++i)
		{
			if (!visit[*i])
			{
				result = cycle_finder(dest,*i,visit,times);
			}
			if (result!="NOPE")
			{
				return "->C" + to_string(src)+ result;
			}
		}
		return "NOPE";
	}
	string find(int side[], list<int> queue)
	{
		
		if (queue.empty())
		{
			return "OK";
		}
		int chem = queue.front();
		queue.pop_front();

		for (auto i = edge[chem].begin();  i != edge[chem].end(); ++i)
		{
			if (side[*i]==0)
			{
				if (side[chem]==1)
				{
					side[*i]=2;
				}
				else
				{
					side[*i]=1;
				}
				queue.push_back(*i);
			}
			else
			{
				if (side[*i]==side[chem])
				{
					int visit[num];
					for (int i = 0; i < num; ++i)
					{
						visit[i]=0;
					}
					int times;
					return "C" + to_string(chem) + cycle_finder(chem,*i,visit,times);
					
				}
			}

		}
		string result = find(side,queue);
		if (result=="OK")
		{
			return "OK";
		}
		else
		{
			return  result;
		}

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
  	int sides[number];
  	for (int i = 0; i < number; ++i)
  	{
  		sides[i]=0;
  	}
  	sides[0]= 1;
  	list<int> queue;
  	queue.push_back(0);
  	string result = graph->find(sides,queue);
  	if (result=="OK")
  	{
  		cout<< "YES" << endl;
  		for (int i = 0; i < number; ++i)
  		{
  			if (sides[i]==1)
  			{
  				cout << "C" << i;
  			}
  		}
  		cout << endl;
  		for (int i = 0; i < number; ++i)
  		{
  			if (sides[i]==2)
  			{
  				cout << "C" << i;
  			}
  		}

  	}
  	else
  	{
  		cout<<"NO"<<endl <<  result << endl;
  	}



	return 0;
}