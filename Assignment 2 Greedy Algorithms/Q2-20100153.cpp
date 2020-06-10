/* In the algorithm, the first step is filling the tank to the full. 
Then move to next destination and decrease fuel accordingly. In station check if tank has
 capacity to go to the next station if it does move to next station. If it does not fill tank 
 until capacity to reach next station, fill tank so that it reaches hospital or if hospital 
distance is more than max capacity then fill it up full. Repeat until hospital is reached.
I just used an integar array to store the station distances 
The running time of the algorithm is O(n) as it goes through all the stations once*/



#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <set> 
#include <fstream>
#include <list> 
#include <stack>

using namespace std;





int main()
{
	string line;
	string filename;
	cout << "Enter name of the file please:";
	cin.getline(filename);
	ifstream myfile (filename.c_str());
  int tank = 0;
	int rate = 0;
  int fill =0;
  int n=0;
  int *station;
  int hospital;
	if (myfile.is_open())
	{
		myfile >> line;
    myfile >> tank;
    myfile >> line;
    myfile >> rate;
    myfile >> line;
    myfile >> fill;
    myfile >> line;
    myfile >> n;
    station = new int[n+1];
    for (int i = 0; i < n; ++i)
    {
      myfile >> line;
      myfile >> station[i];
    }

    myfile >> line;
    myfile >> hospital;
    station[n]=hospital;

  
  
    int petrol=tank;
    int totalTime = 0;
    string output = "";
    for (int i = 0; i < n+1; ++i)
    {
      int dist;
      if (i>0)
      {
        dist =station[i]-station[i-1];
      }
      else
      {

        dist = station[i];
      }
      petrol = petrol - rate*dist;
      hospital=hospital-dist;
      cout << hospital << endl;

      if (hospital<0)
      {
        break;
      }
      else if ((petrol/rate)>=(station[i+1]-station[i]))
      {
        
        continue;
      }
      else
      {

        int required= (station[i+1]-station[i])*rate;
        int max = tank - petrol;
        int time=0;
        if (required>max)
        {
          time = time + max*fill;
          petrol = petrol + max;

          
        }
        else
        {
          time = time + required*fill;
          petrol = petrol + required;

        }
        totalTime = totalTime + time;
        output = output + 'L' + to_string((i+1)) + " "+ to_string(time) + ", ";
      }

    }
    cout << output << endl;
    cout << "Total Time: " << totalTime << endl;


  }
}