/// \file
/// \brief  Implementation of board


#include "ChessBoard.h"


ChessBoard::ChessBoard()
{
  board=new int*[DIMENSION];
  for(int i=0;i<DIMENSION;i++) board[i]=new int[DIMENSION];
}


ChessBoard::~ChessBoard()
{
  for(int i=0;i<DIMENSION;i++) delete [] board[i];
  delete [] board;
  for(vector<ChessPiece*>::iterator it=pieces.begin();it!=pieces.end();++it) delete *it;
}

bool ChessBoard::setloadedBoard(bool & turn,const string & inFile)
{
  const char * path="./examples/";
  string input;
  input += path;
  input += inFile.c_str();
  ifstream file(input.c_str(), ios::in); 
  stringstream iss;string data;
  int counter=0;int value;
  bool moved;
  
  
  if (!file.is_open())
  {
    cout<<"Error-Unknown file name."<<endl;
    return false;
  }
  
  pieces.push_back(new Rock(false,-1,-1));
  pieces.push_back(new Knight(false,-1,-1));
  pieces.push_back(new Bishop(false,-1,-1));
  pieces.push_back(new Qeen(false,-1,-1));
  pieces.push_back(new King(false,-1,-1));
  pieces.push_back(new Bishop(false,-1,-1));
  pieces.push_back(new Knight(false,-1,-1));
  pieces.push_back(new Rock(false,-1,-1));
  for(int i=0;i<DIMENSION;i++) pieces.push_back(new Pawn(false,-1,-1));
  for(int i=0;i<DIMENSION;i++) pieces.push_back(new Pawn(true,-1,-1));
  pieces.push_back(new Rock(true,-1,-1));
  pieces.push_back(new Knight(true,-1,-1));
  pieces.push_back(new Bishop(true,-1,-1));
  pieces.push_back(new Qeen(true,-1,-1));
  pieces.push_back(new King(true,-1,-1));
  pieces.push_back(new Bishop(true,-1,-1));
  pieces.push_back(new Knight(true,-1,-1));
  pieces.push_back(new Rock(true,-1,-1));
  
  getline(file,data);
  iss << data << endl;
  if(!(data.size() == 1 && data[0] > 47 && data[0] < 50))
  {
    cout<<"Error-File is damaged."<<endl;
    for(vector<ChessPiece*>::iterator it=pieces.begin();it!=pieces.end();++it) delete *it;
    return false;
  }  
  iss >> value ;
  if(value == 1) turn=true;
  else turn=false;
  
  while (getline(file,data))
  { 
    if(!(data.size() == 4 && ((data[0] > 47 && data[0] < 52 && data[1] > 47 && data[1] < 58 ) || (data[0]== '-' && data[1] == 49) ) 
    && data[2] == ' ' && (data[3]==48 || data[3]==49 )))
    {
      for(vector<ChessPiece*>::iterator it=pieces.begin();it!=pieces.end();++it) delete *it;
      cout<<"Error-File is damaged."<<endl;
      return false;
    }
    iss << data << endl;
    iss >> value >> moved;
    if( counter < 64 && data !="" && value < 32)
    {
      board[counter/DIMENSION][counter%DIMENSION]=value;
      if(value !=-1) pieces[value]->setPos(ChessPos(counter/DIMENSION,counter%DIMENSION));
      if(moved && value !=-1 && pieces[value]->getType() == 'P') dynamic_cast<Pawn*>(pieces[value])->setlastTurn(moved);
      else if(moved && value !=-1 && pieces[value]->getType() == 'K') dynamic_cast<King*>(pieces[value])->setDrag();
      else if(moved && value !=-1 && pieces[value]->getType() == 'R') dynamic_cast<Rock*>(pieces[value])->setDrag();   
      counter++;
    }
    else
    {
      for(vector<ChessPiece*>::iterator it=pieces.begin();it!=pieces.end();++it) delete *it;
      cout<<"Error-File is damaged."<<endl;
      return false;
    } 
    if(file.eof()) break;
  }
  file.close();
  if(counter != 64) 
  {
    for(vector<ChessPiece*>::iterator it=pieces.begin();it!=pieces.end();++it) delete *it;
    cout<<"Error-File is damaged."<<endl;
    return false;
  }	
  return true;

}

void ChessBoard::setnewBoard()
{
  for(int i=0;i<DIMENSION;i++) board[0][i]=i;
  for(int i=0;i<DIMENSION;i++) board[1][i]=8+i;
  for(int i=2;i<DIMENSION;i++)
  {
    for(int j=0;j<DIMENSION;j++) board[i][j]=-1;
  } 
  for(int i=0;i<DIMENSION;i++) board[6][i]=16+i;
  for(int i=0;i<DIMENSION;i++) board[7][i]=24+i;
  
  pieces.push_back(new Rock(false,0,0));
  pieces.push_back(new Knight(false,0,1));
  pieces.push_back(new Bishop(false,0,2));
  pieces.push_back(new Qeen(false,0,3));
  pieces.push_back(new King(false,0,4));
  pieces.push_back(new Bishop(false,0,5));
  pieces.push_back(new Knight(false,0,6));
  pieces.push_back(new Rock(false,0,7));
  for(int i=0;i<DIMENSION;i++) pieces.push_back(new Pawn(false,1,i));
  for(int i=0;i<DIMENSION;i++) pieces.push_back(new Pawn(true,6,i));
  pieces.push_back(new Rock(true,7,0));
  pieces.push_back(new Knight(true,7,1));
  pieces.push_back(new Bishop(true,7,2));
  pieces.push_back(new Qeen(true,7,3));
  pieces.push_back(new King(true,7,4));
  pieces.push_back(new Bishop(true,7,5));
  pieces.push_back(new Knight(true,7,6));
  pieces.push_back(new Rock(true,7,7));

}

int ChessBoard::getSquare(int square)const
{
  return board[square / DIMENSION][square % DIMENSION];
}

char ChessBoard::getPieceType(int square)const
{
  return pieces[getSquare(square)]->getType();
}

bool ChessBoard::isEmpty(int square)const 
{
  if(getSquare(square) == -1 ) return true;
  else return false;
}

bool ChessBoard::isWPiece(int square)const
{
  if(pieces[getSquare(square)]->isWhite() ) return true;
  else return false; 
}

void ChessBoard::promotePawn(int number)
{
  ChessPos tmp=pieces[number]->getPiecePos();
  bool color=pieces[number]->isWhite();
  vector<ChessPiece*>::iterator it=pieces.begin()+number;
  delete *it;
  pieces.erase(pieces.begin()+number);
  pieces.insert(pieces.begin()+number,new Qeen(color,tmp.getRow(),tmp.getCol()) );
}

bool ChessBoard::doCastling(const ChessPos & from,const ChessPos & to)
{
  
  int frompiece=board[from.getRow()][from.getCol()]; 
  int topiece=board[to.getRow()][to.getCol()];
  int col = ((from.getCol() < to.getCol()) ? from.getCol() : to.getCol());
  int dir = ((from.getCol() < to.getCol()) ? 1 : -1);
  if(pieces[frompiece]->getType() == 'K' && !dynamic_cast<King*>(pieces[frompiece])->isDragged() &&
     pieces[topiece]->getType() == 'R' && !dynamic_cast<Rock*>(pieces[topiece])->isDragged())
  {
     col++;
     while(col < to.getCol() || col < from.getCol())
     {
       if(board[from.getRow()][col] != -1) return false;
       col++;
     }
     for(int i=0;i<3;i++)
     {
       if(isCheck(ChessPos(from.getRow(),from.getCol()+i*dir),pieces[frompiece]->isWhite())) return false;    
     }
     pieces[frompiece]->setPos(ChessPos(from.getRow(),from.getCol()+2*dir));
     pieces[topiece]->setPos(ChessPos(to.getRow(),from.getCol()+dir));
   
     board[to.getRow()][to.getCol()]=-1;
     board[from.getRow()][from.getCol()]=-1;
     board[to.getRow()][from.getCol()+2*dir]=frompiece;
     board[from.getRow()][from.getCol()+dir]=topiece;
     for(int i=8;i<24;i++)
     {
        if(pieces[i]->getType() == 'P') dynamic_cast<Pawn*>(pieces[i])->setlastTurn(false); 
     }
     return true;
  }
  return false;
}

bool ChessBoard::doEnpassant(const ChessPos & from,const ChessPos & to)
{
  int dir;
  int course=to.getCol()-from.getCol();
  if(abs(course)!=1)return false;
  int frompiece=board[from.getRow()][from.getCol()]; 
  int neighbour=board[from.getRow()][from.getCol()+course];
  if(pieces[frompiece]->isWhite()) dir=-1;
  else dir=1;
  if(neighbour != -1 && pieces[neighbour]->getType() == 'P' && dynamic_cast<Pawn*>(pieces[neighbour])->movedlastTurn() 
  && from.getRow() == (to.getRow()-dir) && pieces[neighbour]->isWhite() != pieces[frompiece]->isWhite())
  {
    pieces[frompiece]->setPos(to);
    pieces[neighbour]->setPos(ChessPos(-1,-1));
    board[to.getRow()][to.getCol()]=board[from.getRow()][from.getCol()];
    board[from.getRow()][from.getCol()]=-1;
    board[from.getRow()][from.getCol()+course]=-1;
    if(isCheck(findKing(pieces[frompiece]->isWhite()),pieces[frompiece]->isWhite()))
    {
      pieces[frompiece]->setPos(from);
      pieces[neighbour]->setPos(ChessPos(from.getRow(),from.getCol()+course));
      board[from.getRow()][from.getCol()]=board[to.getRow()][to.getCol()];
      board[to.getRow()][to.getCol()]=-1;
      board[from.getRow()][from.getCol()+course]=neighbour;
      return false;
    }
    else
    {
      for(int i=8;i<24;i++)  if(pieces[i]->getType() == 'P') dynamic_cast<Pawn*>(pieces[i])->setlastTurn(false); 
      return true;
    } 
  }
  return false;
}

bool ChessBoard::saveGame(bool turn)const
{
  time_t rawtime;
  struct tm * timeinfo;
  ofstream output;
  const char* path = "./examples/";
  char buffer[10];
  string name;
 
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  strftime (buffer,10,"%X",timeinfo);
  name += path;
  name += buffer;
  output.open (name.c_str());
  if (output.is_open())
  {
    if(turn) output<<"1"<<endl;
    else output<<"0"<<endl;
    if (!output.good())
    {
      output.close();
      return false;
    }
  	    
    for(int i=0;i<64;i++)
    {
      if(board[i/DIMENSION][i%DIMENSION]!=-1 &&  board[i/DIMENSION][i%DIMENSION] < 10 )  output<<"0";
      output<<board[i/DIMENSION][i%DIMENSION];
      if(board[i/DIMENSION][i%DIMENSION]!=-1 )
      {
        if(pieces[board[i/DIMENSION][i%DIMENSION]]->getType() == 'P')
          output<<" "<<dynamic_cast<Pawn*>(pieces[board[i/DIMENSION][i%DIMENSION]])->movedlastTurn()<<endl;
        else if(pieces[board[i/DIMENSION][i%DIMENSION]]->getType() == 'K')
          output<<" "<<dynamic_cast<King*>(pieces[board[i/DIMENSION][i%DIMENSION]])->isDragged()<<endl;
        else if(pieces[board[i/DIMENSION][i%DIMENSION]]->getType() == 'R')
          output<<" "<<dynamic_cast<Rock*>(pieces[board[i/DIMENSION][i%DIMENSION]])->isDragged()<<endl;  
        else output<<" 0"<<endl;     
      }
      else output<<" 0"<<endl;
      if (!output.good())
      {
        output.close();
        return false;
      }
    }
    
  }
  else return false;
  output.close();
  return true;

}

int ChessBoard::doMove(const char * input,bool turn)
{
  if ( strncmp(input,"save", 4) == 0)
  {
    if(saveGame(turn)) return 2; 
    return 3; 
  }
  if ( strncmp(input,"quit", 4) == 0) return 4;
 
  int retmove;  
  ChessPos from=computePos(input);
  ChessPos to=computePos(input+3);
  int frompiece=board[from.getRow()][from.getCol()]; 
  int topiece=board[to.getRow()][to.getCol()];
  if(from==to || frompiece==-1 || turn != pieces[frompiece]->isWhite() ) return 0;
  if(topiece != -1 && pieces[frompiece]->isWhite() == pieces[topiece]->isWhite() && doCastling(from,to) ) return 1;
  if(pieces[frompiece]->getType() == 'P'&& topiece == -1 && doEnpassant(from,to)) return 1;
  pieces[frompiece]->setvalidDest(*this);
  if( pieces[frompiece]->isValid(to) ) 
  {
    pieces[frompiece]->setPos(to);
    if(topiece != -1) pieces[topiece]->setPos(ChessPos(-1,-1));
    retmove=board[to.getRow()][to.getCol()];
    board[to.getRow()][to.getCol()]=board[from.getRow()][from.getCol()];
    board[from.getRow()][from.getCol()]=-1;
    if(isCheck(findKing(turn),turn))
    {
      pieces[frompiece]->setPos(from);
      if(topiece != -1) pieces[topiece]->setPos(to);
      board[from.getRow()][from.getCol()]=board[to.getRow()][to.getCol()];
      board[to.getRow()][to.getCol()]=retmove;
      return 0;
    }
    topiece=board[to.getRow()][to.getCol()];
    if(pieces[topiece]->getType() == 'P' && (to.getRow()==0 || to.getRow()==7))
    {
      promotePawn(topiece);
    }
    if(pieces[topiece]->getType() == 'K') dynamic_cast<King*>(pieces[topiece])->setDrag();
    if(pieces[board[to.getRow()][to.getCol()]]->getType() == 'R') dynamic_cast<Rock*>(pieces[topiece])->setDrag();
    for(int i=8;i<24;i++)
    {
      if(pieces[i]->getType() == 'P') dynamic_cast<Pawn*>(pieces[i])->setlastTurn(false); 
    }
    if(pieces[topiece]->getType() == 'P' && abs(from.getRow()-to.getRow()) == 2) dynamic_cast<Pawn*>(pieces[topiece])->setlastTurn(true);
      
    return 1;
  } 
  else return 0;
  
}

ChessPos ChessBoard::computePos(const char * input)
{
  int x,y;
  x=7-(input[1]-49);
  y=input[0]-97;
  ChessPos pos(x,y);
  return pos;
}  

ChessPos ChessBoard::findKing(bool color)const
{
  if(color) return pieces[28]->getPiecePos();
  else return pieces[4]->getPiecePos();
}

ChessPos ChessBoard::getAttackerPos(const ChessPos & pos,bool turn)const
{
  int i;
  for( i=0;i<32;i++)
  {
    if(pieces[i]->isWhite() != turn )
    {
      pieces[i]->setvalidDest(*this);
      if(pieces[i]->isValid(pos)) break; 
    }
  }
  return pieces[i]->getPiecePos();
}

bool ChessBoard::isCheck(const ChessPos & pos,bool turn)const
{
  
  for(int i=0;i<32;i++)
  {
    if(pieces[i]->isWhite() != turn )
    {
      pieces[i]->setvalidDest(*this);
      if(pieces[i]->isValid(pos)) return true;
    }
  }
  return false;
}

bool ChessBoard::isDoubleCheck(bool turn)const
{
  int counter=0;
  for(int i=0;i<32;i++)
  {
    if(pieces[i]->isWhite() != turn )
    {
      pieces[i]->setvalidDest(*this);
      if(pieces[i]->isValid(findKing(turn))) counter++;
      if(counter > 1) return true; 
    }
  }
  return false;
}

set<ChessPos> ChessBoard::getInterposePos(const ChessPos & kingpos,const ChessPos & attackerpos)const
{
  set<ChessPos> positions;
  int newposrow,newposcol,direction;
  if(kingpos.getRow() == attackerpos.getRow())
  {
    newposcol = ((kingpos.getCol() < attackerpos.getCol()) ? kingpos.getCol() : attackerpos.getCol());
    newposcol++;
    while(newposcol < kingpos.getCol() || newposcol < attackerpos.getCol()) 
    {
      positions.insert(ChessPos(kingpos.getRow(),newposcol));
      newposcol++;
    }
  }
  else if(kingpos.getCol() == attackerpos.getCol())
  {
    newposrow = ((kingpos.getRow() < attackerpos.getRow()) ? kingpos.getRow() : attackerpos.getRow());
    newposrow++;
    while(newposrow < kingpos.getRow() || newposrow < attackerpos.getRow()) 
    {
      positions.insert(ChessPos(newposrow,kingpos.getCol()));
      newposrow++;
    }
  }
  else 
  {
    newposrow = ((kingpos.getRow() < attackerpos.getRow()) ? kingpos.getRow() : attackerpos.getRow());
    newposcol = ((kingpos.getRow() < attackerpos.getRow()) ? kingpos.getCol() : attackerpos.getCol());
    direction = ((newposcol < attackerpos.getCol()) ? 1 : -1);
    newposrow++;
    newposcol+=1*direction;
    while(newposrow < kingpos.getRow() || newposrow < attackerpos.getRow()) 
    {
      positions.insert(ChessPos(newposrow,newposcol));
      newposrow++;
      newposcol+=1*direction;
    }
  }

  return positions;
}

bool ChessBoard::isCheckmate(bool turn)const
{
  int number;
  int retmove;
  int i;
  
  if(turn) number=28;
  else number=4;
  pieces[number]->setvalidDest(*this);
  set<ChessPos> positions=pieces[number]->getValidPos();//can sidestep
  
  for (set<ChessPos>::const_iterator it=positions.begin(); it!=positions.end(); ++it)
  {
    if(!isCheck(*it,turn) && !isCheck(getAttackerPos(findKing(turn),turn),!turn)) return false;
  }
  if (isDoubleCheck(turn)) return true; //is doublecheck
  
  ChessPos from(-1,-1);
  ChessPos attacker=getAttackerPos(findKing(turn),turn);
  if (isCheck(attacker,!turn))  //can take attacker
  {
    for(i=0;i<32;i++)                
    {
      if(pieces[i]->isWhite() == turn )
      {
        pieces[i]->setvalidDest(*this);
        if(pieces[i]->isValid(attacker))
        {
          from=pieces[i]->getPiecePos();
          retmove=board[attacker.getRow()][attacker.getCol()];
          pieces[retmove]->setPos(ChessPos(-1,-1));
          pieces[i]->setPos(attacker);
          board[attacker.getRow()][attacker.getCol()]=board[from.getRow()][from.getCol()];
          board[from.getRow()][from.getCol()]=-1;
          if(!isCheck(findKing(turn),turn))
          {
            pieces[i]->setPos(from);
            pieces[retmove]->setPos(attacker);
            board[from.getRow()][from.getCol()]=board[attacker.getRow()][attacker.getCol()];
            board[attacker.getRow()][attacker.getCol()]=retmove;
            return false;
          }
          else 
          {
            pieces[i]->setPos(from);
            pieces[retmove]->setPos(attacker);
            board[from.getRow()][from.getCol()]=board[attacker.getRow()][attacker.getCol()];
            board[attacker.getRow()][attacker.getCol()]=retmove;
          }
        }
      }
    }  
  }
  
 
  for(i=0;i<32;i++)                // it is horse
  {
    if(pieces[i]->isWhite() != turn )
    {
      pieces[i]->setvalidDest(*this);
      if(pieces[i]->isValid(findKing(turn))) break;
    }
  }
  if(pieces[i]->getType() == 'H') return true;
  
  
  positions.clear();  //can be covered
  positions=getInterposePos(findKing(turn),getAttackerPos(findKing(turn),turn));
  for (set<ChessPos>::const_iterator it=positions.begin(); it!=positions.end(); ++it)
  {
    for(i=0;i<32;i++)  
    {
      pieces[i]->setvalidDest(*this);
      if( pieces[i]->isWhite() == turn && pieces[i]->isValid(*it) ) 
      {
        from=pieces[i]->getPiecePos();
        retmove=board[it->getRow()][it->getCol()];
        if(retmove != -1) pieces[retmove]->setPos(ChessPos(-1,-1));
        pieces[i]->setPos(*it);
        board[it->getRow()][it->getCol()]=board[from.getRow()][from.getCol()];
        board[from.getRow()][from.getCol()]=-1;
        if(!isCheck(findKing(turn),turn))
        {
          pieces[i]->setPos(from);
          if(retmove != -1) pieces[retmove]->setPos(*it);
          board[from.getRow()][from.getCol()]=board[it->getRow()][it->getCol()];
          board[it->getRow()][it->getCol()]=retmove;
          return false;
        }
        else 
        {
          pieces[i]->setPos(from);
          if(retmove != -1) pieces[retmove]->setPos(*it);
          board[from.getRow()][from.getCol()]=board[it->getRow()][it->getCol()];
          board[it->getRow()][it->getCol()]=retmove;
        }
      }  
    }
  }
                             
  return true;
}

bool ChessBoard::isStalemate(bool turn)const
{
  set<ChessPos> positions;
  int retmove;
  ChessPos from(0,0);
  
  for(int i=0;i<32;i++)  
  {
    pieces[i]->setvalidDest(*this);
    positions.clear();
    if( pieces[i]->isWhite() == turn ) 
    {
      positions=pieces[i]->getValidPos();   
      for (set<ChessPos>::const_iterator it=positions.begin(); it!=positions.end(); ++it)
      {
        if( pieces[i]->isValid(*it) ) 
        {
          from=pieces[i]->getPiecePos();
          retmove=board[it->getRow()][it->getCol()];
          if(retmove != -1) pieces[retmove]->setPos(ChessPos(-1,-1));
          pieces[i]->setPos(*it);
          board[it->getRow()][it->getCol()]=board[from.getRow()][from.getCol()];
          board[from.getRow()][from.getCol()]=-1;
          if(!isCheck(findKing(turn),turn))
          {
            pieces[i]->setPos(from);
            if(retmove != -1) pieces[retmove]->setPos(*it);
            board[from.getRow()][from.getCol()]=board[it->getRow()][it->getCol()];
            board[it->getRow()][it->getCol()]=retmove;
            return false;
          }
          else 
          {
            pieces[i]->setPos(from);
            if(retmove != -1) pieces[retmove]->setPos(*it);
            board[from.getRow()][from.getCol()]=board[it->getRow()][it->getCol()];
            board[it->getRow()][it->getCol()]=retmove;
          }
        }
      }    
    }
  }
    
  return true;
}
