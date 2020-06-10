/* the algorithm I used first splits a 2d arrray board into 4 equal pieces and sees which piece has
the blank board and places a boomerang at the end of that piece it then continues to do that until the
size of the board is 2, in that case it places a bommerang around the piece. 
The reccurence relation is T(n) = 4T(n/4)
The runTime is log4(n) in other words O(log4n)
The time complexity is O(nlogn)
*/
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
int counter = 1;


void boardFiller(int row, int col, int startrow, int startCol, int size, int **board){
  if (size==2)
  {
    for (int i = startrow; i < startrow+2; ++i)
    {
      for (int j = startCol; j < startCol+2; ++j)
      {
        if (board[i][j]==0)
        {
          board[i][j]=counter;
        }
      }
      
    }
    counter++;
  }
  else
  {
    if (row<startrow+size/2)
    {
      if (col<startCol+size/2)
      {
        
        boardFiller(row,col,startrow,startCol,size/2, board);
        boardFiller(startrow+size/2,startCol+size/2,startrow+size/2,startCol+size/2,size/2, board);
        boardFiller((startrow+size/2)-1,startCol+size/2,startrow,startCol+size/2,size/2, board);
        boardFiller(startrow+size/2,startCol+size/2-1,startrow+size/2,startCol,size/2, board);
        board[startrow+size/2][startCol+size/2]= counter;
        board[(startrow+size/2)-1][startCol+size/2]= counter;
        board[startrow+size/2][(startCol+size/2)-1]= counter;
        counter++;



      }
      else
      {
        boardFiller(row,col,startrow,startCol+size/2,size/2 , board);
        boardFiller(startrow+size/2-1,startCol+size/2-1,startrow,startCol,size/2, board);
        boardFiller(startrow+size/2,startCol+size/2-1,startrow+size/2,startCol,size/2, board);
        boardFiller(startrow+size/2-1,startCol+size/2,startrow+size/2,startCol+size/2,size/2, board);
        board[startrow+size/2][startCol+size/2] = counter;
        board[startrow+size/2][startCol+size/2-1]= counter;
        board[startrow+size/2-1][startCol+size/2-1]= counter;
        counter++;
        


      }


    }
    else 
    {
      if (col<startCol+size/2)
      {
  cout << size << " " << row << " " << col <<  " " << "" << startrow << " " << startCol << " " << counter <<endl;

        boardFiller(row,col,startrow+size/2,startCol,size/2 , board);
        boardFiller(startrow+size/2,startCol+size/2,startrow+size/2,startCol+size/2,size/2, board);
        boardFiller(startrow+size/2-1,startCol+size/2,startrow,startCol+size/2,size/2, board);
        boardFiller(startrow+size/2-1,startCol+size/2-1,startrow,startCol,size/2, board);
        board[startrow+size/2][startCol+size/2]= counter;
        board[startrow+size/2-1][startCol+size/2]= counter;
        board[startrow+size/2-1][startCol+size/2-1]= counter;
        counter++;
        
      }
      else
      {
        boardFiller(row,col,startrow+size/2,startCol+size/2,size/2 , board);
        boardFiller(startrow+size/2,startCol+size/2,startrow+size/2,startCol+size/2,size/2, board);
        boardFiller(startrow+size/2-1,startCol+size/2,startrow,startCol+size/2,size/2, board);
        boardFiller(startrow+size/2-1,startCol+size/2-1,startrow,startCol,size/2, board);
        board[startrow+size/2][startCol+size/2] = counter;
        board[startrow+size/2-1][startCol+size/2]= counter;
        board[startrow+size/2-1][startCol+size/2-1]= counter;
        counter++;
        
      }
    }
  

  }
}

int main() {
  string line;
  string filename;
  cout << "Enter name of the file please:";
  // cin >> filename;
  filename = "test.txt";
  ifstream myfile(filename.c_str());
  int **board;
  int number = 999999;
  int row = -1;
  int col= -1;
  if (myfile.is_open()) {
    string line;
    myfile>> line;
    myfile >> number;
    myfile >> line;
    myfile >> row;
    myfile>>line;
    myfile>>col;
    board = new int*[number];
    for (int i = 0; i < number; ++i)
    {
      board[i]= new int[number];
    }
    for (int i = 0; i < number; ++i)
    {
      for (int j = 0; j < number; ++j)
      {
        board[i][j]=0;
      }
    }
    board[row][col] = -1;


  }
  boardFiller(row,col,0,0,number,board);


  for (int i = 0; i < number; ++i)
  {
    for (int j = 0; j < number; ++j)
    {
      if (board[i][j]==-1)
      {
        cout << -1<< "   ";
        continue;
      }
      cout<< static_cast<char>('A' - 1 + board[i][j]) << "   ";
    }
    cout << endl;
  }

  return 0;
}