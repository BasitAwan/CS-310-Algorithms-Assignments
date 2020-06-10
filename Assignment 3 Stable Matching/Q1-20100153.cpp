/*
in this task I have used stable matching algorithm to get the best match for each plane and airport
and I have also implement a restricted array to see if the match is restricted or not. The stable 
stable matching algorithm essentially goes to every preference from best to worst and asks if they
wanna join, if they don't it moves on to next, if the prefers also prefer this airport than it says 
okay and the pair it was already paired with gets unpaired.
Because each plane looks for matches in each airport the running time is o(n2)

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
  string line;
  string filename;
  cout << "Enter name of the file please:";
  cin >> filename;
  ifstream myfile(filename.c_str());
  int **teamPref;
  int *teamMatch;
  int *siteMatch;
  bool check = false;
  int number = 999999;
  int counter = 0;
  if (myfile.is_open()) {
    while (check || myfile >> line) {
      if (check) {
        check = false;
      }
      if (counter > number) {
        break;
      }
      if (line[0] == 'n') {
        myfile >> line;
        number = stoi(line);
        teamPref = new int *[number];
        for (int i = 0; i < number; ++i)
          teamPref[i] = new int[number];

        teamMatch = new int[number];
        siteMatch = new int[number];
        for (int i = 0; i < number; ++i) {

          teamMatch[i] = -1;
          siteMatch[i] = -1;
          for (int j = 0; j < number; ++j) {
            teamPref[i][j] = 0;
          }
        }
      } else if (line[line.length() - 1] == ':') {
        if (counter >= number * 2) {
          while (myfile >> line) {
            string extract = "";
            for (int i = 1; i < line.length(); ++i) {
              if (line[i] == ',') {
                break;
              }
              extract = extract + line[i];
            }
            int planeNum = stoi(extract);
            extract = "";
            myfile >> line;
            for (int i = 1; i < line.length(); ++i) {
              if (line[i] == ',') {
                break;
              }
              extract = extract + line[i];
            }
            int airNum = stoi(extract);

            restricted[planeNum - 1][airNum - 1] = 1;
          }

          check = false;
        } else {
          int counter2 = 0;
          string extract = "";
          myfile >> line;
          while (line[line.length() - 1] != ':') {
            for (int i = 1; i < line.length(); ++i) {
              if (line[i] == ',') {
                break;
              }
              extract = extract + line[i];
            }
            if (counter >= number) {
              airPref[counter % number][counter2] = stoi(extract) - 1;
            } else {
              planePref[counter][counter2] = stoi(extract) - 1;
            }
            extract = "";
            if (!(myfile >> line)) {
              break;
            }
            counter2++;
          }
          check = true;
          counter++;
        }
      }
    }
  }
  while (true) {
    check = false;
    for (int i = 0; i < number; ++i) {
      if (airMatch[i] == -1) {
        check = true;
        for (int j = 0; j < number; ++j) {
          int x = airPref[i][j];
          if (restricted[x][i] == 1) {
            break;
          }
          if (planeMatch[x] == -1) {
            planeMatch[x] = i;
            airMatch[i] = x;
            break;
          } else {

            int temp = planeMatch[x];
            for (int k = 0; k < number; ++k) {
              if (planePref[x][k] == temp) {
                break;
              } else if (planePref[x][k] == i) {
                cout << temp << "," << i << "," << planePref[x][k] << endl;
                airMatch[temp] = -1;
                planeMatch[x] = i;
                airMatch[i] = x;
                break;
              }
            }
          }
          if (airMatch[i] != -1) {
            break;
          }
        }
      }
    }
    if (check == false) {
      break;
    }
  }
  for (int i = 0; i < number; ++i) {
    cout << "A" << i + 1 << " "
         << "P" << airMatch[i] + 1 << ",";
  }
  cout << endl;

  return 0;
}