/* THe matching algorithm is the very similar as in the previous one just during matching the time
of team reached at location is put into consideration, if a team has a lesser time then it gets to
go to the location and the other has to search again, also the preference in this goes from highest 
index to lowest
the running time again is O(n2) */



#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

using namespace std;
struct teamTime
{
  int team;
  int time;
};

int main() {
  string line;
  string filename;
  cout << "Enter name of the file please:";
  // cin >> filename;
  filename = "test.txt";
  ifstream myfile(filename.c_str());
  int **teamPref;
  teamTime *siteMatch;
  int *teamMatch;
  bool check = false;
  int number = 999999;
  int counter = 0;
  if (myfile.is_open()) {
    while (check || myfile >> line) {
      if (check) {
        check = false;
      }
      if (counter > number * 2) {
        break;
      }
      if (line[0] == 'n') {
        myfile >> line;
        number = stoi(line);
        teamPref = new int *[number];
        for (int i = 0; i < number; ++i)
          teamPref[i] = new int[number*2];
        teamMatch = new int[number];
        siteMatch = new teamTime[number];
        for (int i = 0; i < number; ++i) {

          teamMatch[i] = -1;
          siteMatch[i].team = -1;
          siteMatch[i].time = -1;
          for (int j = 0; j < number*2; ++j) {
            teamPref[i][j] = -1;
           
          }
        }
      } else if (line[line.length() - 1] == ':') {
        string extract = "";
        myfile >> line;
        int counter2 = 0;
        while (true) {
          for (int i = 1; i < line.length(); ++i) {
            if (line[i] == ',') {

              if (extract=="") {
                
              } else {
                teamPref[counter][counter2] = stoi(extract) - 1;

              }
              extract = "";
              
              counter2++;
            }
            else if (line[i]=='L' || line[i]=='-'){

            }
            else {
              extract = extract + line[i];
              
            }
            
          }
          if (extract=="") {
            
          } else {

            teamPref[counter][counter2] = stoi(extract) - 1;
          }
          extract="";
          if (counter2>=number*2-1) {

              break;
            }
        }
        check = true;
        counter++;
        
      }
    }
  }
  while (true) {
    check = false;
    for (int i = 0; i < number; ++i) {
      if (teamMatch[i] == -1) {
        check = true;
        for (int j = number*2-1; j >=0; --j) {
          int x = teamPref[i][j];
          if (x != -1 && siteMatch[x].team == -1) {
            siteMatch[x].team = i;
            siteMatch[x].time = j;
            teamMatch[i] = x;
            break;
          } else if (x!= -1 && siteMatch[x].time>j) {
            int temp = siteMatch[x].team;
            siteMatch[x].team = i;
            siteMatch[x].time = j;
            teamMatch[i]= x;
            teamMatch[temp] = -1;
            break;
            
            
          }
        }
      }
    }
    if (check == false) {
      break;
    }
  }
  cout << "Final Destinations: " ;
  for (int i = 0; i < number; ++i) {
    cout << "L" << i + 1 << " "
         << "T" << siteMatch[i].team + 1 << ",";
  }
  cout << endl;

  // for (int i = 0; i < number; ++i)
  // {
  //   for (int j = 0; j < number*2; ++j)
  //   {
  //     cout<< teamPref[i][j] +1  << ", ";
  //   }
  //   cout << endl;
  // }

  return 0;
}