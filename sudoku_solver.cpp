#include<bits/stdc++.h>
using namespace std;

//declaring sudoku grid and auxillary spaces for optimizations
vector<vector<int>> grid(9, vector<int>(9));
vector<vector<int>> row(9, vector<int>(10, 0));
vector<vector<int>> col(9, vector<int>(10, 0));
vector<vector<int>> box(9, vector<int>(10, 0));
bool isSolved = false;

//box index logic
int bi(int i, int j){
  return ((i/3)*3)+(j/3);
}

//for printing the sudoku once solution found
void print(vector<vector<int>> &grid){
  cout<<endl<<"******************"<<endl<<endl;
  for(int i = 0; i<9; i++){
    for(int j = 0; j<9; j++){
      if(j == 2 || j == 5){
        cout<<grid[i][j]<<'|';
      }
      else{
        cout<<grid[i][j]<<' ';
      }
    }cout<<endl;
    if(i == 2 || i == 5){
      for(int i = 0; i<=16; i++){
        cout<<'-';
      }cout<<endl;
    }
  }
}

//to check if we can place a number at x, y
bool canPlace(int i, int x, int y){
  return row[x][i] + col[y][i] + box[bi(x, y)][i] == 0;
}

//placing a number at x, y
void place(int i, int x, int y){
  row[x][i] = 1, col[y][i] = 1, box[bi(x, y)][i] = 1, grid[x][y] = i;
}

//removing a number from x, y
void remove(int i, int x, int y){
  row[x][i] = 0, col[y][i] = 0, box[bi(x, y)][i] = 0, grid[x][y] = 0;
}


//main solving function
void SudokuSolver(int x, int y){
//if the place in Sudoku is vacant
  if(grid[x][y] == 0){
    for(int i = 1; i<=9; i++){
      if(canPlace(i, x, y)){
        place(i, x, y);
        if(x == 8 && y == 8){
          print(grid);
          isSolved = true;
        }
        else if(y == 8) SudokuSolver(x+1, 0);
        else SudokuSolver(x, y+1);
        if(!isSolved) remove(i, x, y);
      }
    }
  }

//if the place is already filled
  else{
    if(x == 8 && y == 8){
      print(grid);
      isSolved = true;
    }
    else if(y == 8) SudokuSolver(x+1, 0);
    else SudokuSolver(x, y+1);
  }

}


int main(){
  cout<<"Enter the 9x9 puzzle:"<<endl;

  //Entering the Sudoku and Filling Aux spaces for memory optimizations
  for(int i = 0; i<9; i++){
    for(int j = 0; j<9; j++){
      cin>>grid[i][j];
      row[i][grid[i][j]] = 1;
      col[j][grid[i][j]] = 1;
      box[bi(i, j)][grid[i][j]] = 1;
    }
  }

  //calling the solving function
  SudokuSolver(0, 0);
  if(!isSolved) cout<<"Invalid Sudoku!!"<<endl;
  else cout<<endl<<"Sudoku Solved!!!"<<endl<<endl;
}
