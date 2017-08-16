/// \file
/// \brief  Implementation of pieces

#include "ChessBoard.h"

using namespace std;

ChessPiece::ChessPiece(bool white,int x, int y)
{
  m_white=white;
  m_pos=new ChessPos(x,y);
}


ChessPiece::~ChessPiece()
{
  delete m_pos;
}


bool ChessPiece::isWhite()const
{
  return m_white;
}

bool ChessPiece::isValid(const ChessPos & pos)const
{
  if(m_dest.find(pos) != m_dest.end() ) return true;
  else return false;
}

void ChessPiece::setPos(const ChessPos & pos)
{
  m_pos->setPos(pos.getRow(),pos.getCol());
}

set<ChessPos> ChessPiece::getValidPos()const
{
  return m_dest;
}

ChessPos ChessPiece::getPiecePos()const
{
  ChessPos tmp(m_pos->getRow(), m_pos->getCol());
  return tmp;
}



Pawn::Pawn(bool white,int x,int y):ChessPiece (white,x,y)
{
  m_moved=false;
}

bool Pawn::movedlastTurn()const
{
  return m_moved;
}

void Pawn::setlastTurn(bool moved)
{
  m_moved=moved;
}

char Pawn::getType()const
{
  return 'P';
}


void Pawn::setvalidDest(const ChessBoard & b )
{
  int square;
  m_dest.clear();
  if(m_pos->getRow() == -1 && m_pos->getCol() == -1) return;
  if(isWhite())
  {
  //first move
    square=DIMENSION*(m_pos->getRow()-2)+m_pos->getCol();
    if(m_pos->getRow()==DIMENSION-2 && b.isEmpty(square-DIMENSION) && b.isEmpty(square) )
     m_dest.insert(ChessPos(m_pos->getRow()-2, m_pos->getCol()) );
  //common move 
    square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol();
    if(b.isEmpty(square)) m_dest.insert(ChessPos(m_pos->getRow()-1, m_pos->getCol()) );
  //jump left
    if(m_pos->getCol()-1 >= 0)
    {
      square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol()-1;
      if(!b.isEmpty(square) &&!b.isWPiece(square)) m_dest.insert(ChessPos(m_pos->getRow()-1, m_pos->getCol()-1) );
    }  
  //jump right
    if(m_pos->getCol()+1 < DIMENSION)
    {
      square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol()+1;
      if(!b.isEmpty(square) && !b.isWPiece(square)) m_dest.insert(ChessPos(m_pos->getRow()-1, m_pos->getCol()+1) );
    }  
  }
  else
  {
  //first move
    square=DIMENSION*(m_pos->getRow()+2)+m_pos->getCol();
    if(m_pos->getRow()==1 && b.isEmpty(square-DIMENSION) && b.isEmpty(square) )
      m_dest.insert(ChessPos(m_pos->getRow()+2, m_pos->getCol()));
  //common move 
    square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol();
    if(b.isEmpty(square)) m_dest.insert(ChessPos(m_pos->getRow()+1, m_pos->getCol()) );
  //jump left
    if(m_pos->getCol()-1 >= 0)
    {
      square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol()-1;
      if(!b.isEmpty(square) && b.isWPiece(square)) m_dest.insert(ChessPos(m_pos->getRow()+1, m_pos->getCol()-1) );
    }  
  //jump right
    if(m_pos->getCol()+1 < DIMENSION)
    {
      square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol()+1;
      if(!b.isEmpty(square) && b.isWPiece(square)) m_dest.insert(ChessPos(m_pos->getRow()+1, m_pos->getCol()+1) );
    }  
  
  } 
 
}

Rock::Rock(bool white,int x,int y):ChessPiece (white,x,y)
{ 
  m_dragged=false;
}

bool Rock::isDragged()const
{
 return m_dragged;
}

void Rock::setDrag()
{
  m_dragged=true;
}

char Rock::getType()const
{
  return 'R';
}


void Rock::setvalidDest(const ChessBoard & b)
{
  int square,row,col;
  m_dest.clear();
  if(m_pos->getRow() == -1 && m_pos->getCol() == -1) return;
  
  row=m_pos->getRow()-1;//top
  square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol();
  while(row >= 0 && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(row,m_pos->getCol()));
    square -= DIMENSION;
    row--;
  }  
  if(row >= 0 && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(row,m_pos->getCol()) );
  
  row=m_pos->getRow()+1;//bottom
  square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol();
  while(row < DIMENSION && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(row,m_pos->getCol()));
    square += DIMENSION;
    row++;
  }  
  if(row < DIMENSION && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(row,m_pos->getCol()) );
     
  col=m_pos->getCol()-1;//left
  square=DIMENSION*m_pos->getRow()+m_pos->getCol()-1;
  while(col >= 0 && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(m_pos->getRow(),col));
    square--;
    col--;
  }  
  if(col >=0 && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(m_pos->getRow(), col) );
     
  col=m_pos->getCol()+1;//right
  square=DIMENSION*m_pos->getRow()+m_pos->getCol()+1;
  while(col < DIMENSION && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(m_pos->getRow(),col));
    square++;
    col++;
  }  
  if(col < DIMENSION && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(m_pos->getRow(), col) );
}


King::King(bool white,int x,int y):ChessPiece (white,x,y)
{
  m_dragged=false;
}

bool King::isDragged()const
{
 return m_dragged;
}

void King::setDrag()
{
  m_dragged=true;
}

char King::getType()const
{
  return 'K';
}


void King::setvalidDest(const ChessBoard & b)
{
  int square;
  m_dest.clear();
  if(m_pos->getRow() == -1 && m_pos->getCol() == -1) return; 
  if(m_pos->getRow()+1 < DIMENSION )
  {
    square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol();
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()+1, m_pos->getCol()) );
  } 
  
  if(m_pos->getRow()-1 >= 0 )
  {
    square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol();
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()-1, m_pos->getCol()) );
  } 
  
  if( m_pos->getCol()+1 < DIMENSION )
  {
    square=DIMENSION*(m_pos->getRow())+m_pos->getCol()+1;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow(), m_pos->getCol()+1) );
  } 
  
  if( m_pos->getCol()-1 >= 0 )
  {
    square=DIMENSION*(m_pos->getRow())+m_pos->getCol()-1;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow(), m_pos->getCol()-1) );
  } 
  
  if(m_pos->getRow()-1 >=0 && m_pos->getCol()-1 >=0 )
  {
    square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol()-1;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()-1, m_pos->getCol()-1) );
  } 
  
  if(m_pos->getRow()-1 >=0 && m_pos->getCol()+1 < DIMENSION )
  {
    square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol()+1;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()-1, m_pos->getCol()+1) );
  } 
  
  if(m_pos->getRow()+1 < DIMENSION && m_pos->getCol()+1 < DIMENSION )
  {
    square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol()+1;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()+1, m_pos->getCol()+1) );
  } 
  
  if(m_pos->getRow()+1 < DIMENSION && m_pos->getCol()-1 >=0 )
  {
    square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol()-1;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()+1, m_pos->getCol()-1) );
  } 
 
}


Qeen::Qeen(bool white,int x,int y):ChessPiece (white,x,y)
{

}


char Qeen::getType()const
{
  return 'Q';
}


void Qeen::setvalidDest(const ChessBoard & b)
{
  int square,row,col;
  m_dest.clear();
  if(m_pos->getRow() == -1 && m_pos->getCol() == -1) return;
  
  row=m_pos->getRow()-1;//top
  square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol();
  while(row >= 0 && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(row,m_pos->getCol()));
    square -= DIMENSION;
    row--;
  }  
  if(row >= 0 && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(row,m_pos->getCol()) );
  
  row=m_pos->getRow()+1;//bottom
  square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol();
  while(row < DIMENSION && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(row,m_pos->getCol()));
    square += DIMENSION;
    row++;
  }  
  if(row < DIMENSION && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(row,m_pos->getCol()) );
     
  col=m_pos->getCol()-1;//left
  square=DIMENSION*m_pos->getRow()+m_pos->getCol()-1;
  while(col >= 0 && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(m_pos->getRow(),col));
    square--;
    col--;
  }  
  if(col >=0 && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(m_pos->getRow(), col) );
     
  col=m_pos->getCol()+1;//right
  square=DIMENSION*m_pos->getRow()+m_pos->getCol()+1;
  while(col < DIMENSION && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(m_pos->getRow(),col));
    square++;
    col++;
  }  
  if(col < DIMENSION && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(m_pos->getRow(), col) );
  
  row=m_pos->getRow()-1;//top-left
  col=m_pos->getCol()-1;
  square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol()-1;
  while(row >= 0 && col >= 0 && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(row, col) );
    row--;
    col--;
    square -= (DIMENSION+1);
  }
  if(row >= 0 && col >= 0 && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(row, col) );
   
  row=m_pos->getRow()-1;//top-right
  col=m_pos->getCol()+1;
  square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol()+1;
  while(row >= 0 && col < DIMENSION && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(row, col) );
    row--;
    col++;
    square -= (DIMENSION-1);
  }
  if(row >= 0 && col < DIMENSION && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(row, col) ); 
   
  row=m_pos->getRow()+1;//bottom-left
  col=m_pos->getCol()-1;
  square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol()-1;
  while(row < DIMENSION && col >= 0 && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(row, col) );
    row++;
    col--;
    square += (DIMENSION-1);
  }
  if(row < DIMENSION && col >= 0 && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(row, col) );  
 
  row=m_pos->getRow()+1;//bottom-right
  col=m_pos->getCol()+1;
  square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol()+1;
  while(row < DIMENSION && col < DIMENSION && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(row, col) );
    row++;
    col++;
    square += (DIMENSION+1);
  }
  if(row < DIMENSION && col < DIMENSION && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(row, col) );  
   
}

Bishop::Bishop(bool white,int x,int y):ChessPiece (white,x,y)
{

}



char Bishop::getType()const
{
  return 'B';
}


void Bishop::setvalidDest(const ChessBoard & b)
{
  int square,row,col;
  m_dest.clear();
  if(m_pos->getRow() == -1 && m_pos->getCol() == -1) return;
  
  row=m_pos->getRow()-1;//top-left
  col=m_pos->getCol()-1;
  square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol()-1;
  while(row >= 0 && col >= 0 && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(row, col) );
    row--;
    col--;
    square -= (DIMENSION+1);
  }
  if(row >= 0 && col >= 0 && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(row, col) );
   
  row=m_pos->getRow()-1;//top-right
  col=m_pos->getCol()+1;
  square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol()+1;
  while(row >= 0 && col < DIMENSION && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(row, col) );
    row--;
    col++;
    square -= (DIMENSION-1);
  }
  if(row >= 0 && col < DIMENSION && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(row, col) ); 
   
  row=m_pos->getRow()+1;//bottom-left
  col=m_pos->getCol()-1;
  square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol()-1;
  while(row < DIMENSION && col >= 0 && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(row, col) );
    row++;
    col--;
    square += (DIMENSION-1);
  }
  if(row < DIMENSION && col >= 0 && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(row, col) );  
 
  row=m_pos->getRow()+1;//bottom-right
  col=m_pos->getCol()+1;
  square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol()+1;
  while(row < DIMENSION && col < DIMENSION && b.isEmpty(square) )
  {
    m_dest.insert(ChessPos(row, col) );
    row++;
    col++;
    square += (DIMENSION+1);
  }
  if(row < DIMENSION && col < DIMENSION && b.isWPiece(square) != isWhite()) m_dest.insert(ChessPos(row, col) );  
   
}  

Knight::Knight(bool white,int x,int y):ChessPiece (white,x,y)
{

}


char Knight::getType()const
{
  return 'H';
}


void Knight::setvalidDest(const ChessBoard & b)
{
  int square;
  m_dest.clear();
  if(m_pos->getRow() == -1 && m_pos->getCol() == -1) return;
  if(m_pos->getRow()+2 < DIMENSION && m_pos->getCol()+1 < DIMENSION )
  {
    square=DIMENSION*(m_pos->getRow()+2)+m_pos->getCol()+1;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()+2, m_pos->getCol()+1) );
  } 
  if(m_pos->getRow()+1 < DIMENSION && m_pos->getCol()+2 < DIMENSION )
  {
    square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol()+2;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()+1, m_pos->getCol()+2) );
  }  
  if(m_pos->getRow()+2 < DIMENSION && m_pos->getCol()-1 >= 0 )
  {
    square=DIMENSION*(m_pos->getRow()+2)+m_pos->getCol()-1;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()+2, m_pos->getCol()-1) );
  }  
  if(m_pos->getRow()+1 < DIMENSION && m_pos->getCol()-2 >= 0 )
  {
    square=DIMENSION*(m_pos->getRow()+1)+m_pos->getCol()-2;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()+1, m_pos->getCol()-2) );
  } 
  if(m_pos->getRow()-2  >= 0 && m_pos->getCol()+1 < DIMENSION )
  {
    square=DIMENSION*(m_pos->getRow()-2)+m_pos->getCol()+1;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()-2, m_pos->getCol()+1) );
  } 
  if(m_pos->getRow()-1  >= 0 && m_pos->getCol()+2 < DIMENSION )
  {
    square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol()+2;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()-1, m_pos->getCol()+2) );
  }
  if(m_pos->getRow()-1  >= 0 && m_pos->getCol()-2  >= 0 )
  {
    square=DIMENSION*(m_pos->getRow()-1)+m_pos->getCol()-2;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()-1, m_pos->getCol()-2) );
  }
  if(m_pos->getRow()-2  >= 0 && m_pos->getCol()-1  >= 0 )
  {
    square=DIMENSION*(m_pos->getRow()-2)+m_pos->getCol()-1;
    if(b.isEmpty(square) || b.isWPiece(square) != isWhite() ) m_dest.insert(ChessPos(m_pos->getRow()-2, m_pos->getCol()-1) );
  } 
   
}
