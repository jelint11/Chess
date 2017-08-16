/// \file
/// \brief  Main function
/// \return an integer 0 upon exit success

#include "ChessInterface.h"

using namespace std; 
int main() {

bool whiteturn=true;
int state;
ChessBoard board;
string mode;
system("clear");
while(1)
{
  cout<<"For NEWGAME type N or for LOADGAME type L."<<endl;
  cin>>mode;
  if(mode.compare("L") == 0 || mode.compare("l") == 0) 
  {
    while(1)
    {
      cout<<"Type name of your SAVEFILE"<<endl;
      cin>>mode;
      if(board.setloadedBoard(whiteturn,mode)) break;
      
    }
    break;  
  }  
  else if(mode.compare("N") == 0 || mode.compare("n") == 0)
  {
    board.setnewBoard();
    break;
  }
  cout<<"Invalid input!"<<endl;
}

ChessInterface gui;   
   
while(1)
{
  gui.drawBoard();
  gui.updateBoard(board);
  gui.refreshScreen();
  state=board.doMove(gui.readInput(whiteturn),whiteturn);
  if(state == 1) 
  {
    whiteturn=!whiteturn;
    if (board.isCheck(board.findKing(whiteturn),whiteturn))
    {
      if(board.isCheckmate(whiteturn))
      {
        if(whiteturn) gui.printMessage(1,0,5,"Checkmate! BLACK player win.");
        else gui.printMessage(1,0,5,"Checkmate! WHITE player win.");
        break;
      }  
      else gui.printMessage(1,0,5,"Check!");
    }  
    else if(board.isStalemate(whiteturn))
    {
      gui.printMessage(1,0,5,"Stalemate! Game is drawn.");
      break;
    }          
  } 
  else if(state == 0) gui.printMessage(1,0,5,"Invalid move-Try it again!");
  else if(state == 2) gui.printMessage(1,0,5,"Game saved!");
  else if(state == 3) gui.printMessage(1,0,5,"Error-saving game failed!");
  else 
  {
    gui.printMessage(1,0,5,"Bye!");
    break;
  }
  
}

gui.drawBoard();
gui.updateBoard(board);
gui.refreshScreen();
getch();
  

return 0;
	
}

