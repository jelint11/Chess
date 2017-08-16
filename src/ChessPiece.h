/// \file
/// \brief  Header for ChessPiece.cpp

#include "ChessPos.h"
#include <set>

using namespace std;

class ChessBoard;

//!  Represents Chesspiece. It is parent of all types of pieces. 
class ChessPiece  
{
  public:    
             //! A konstructor.
	         ChessPiece(bool white,int x,int y);
	         
	         //! A destructor.
	 virtual ~ChessPiece();
	         
	         //! Returns true if piece is white false otherwise.
	         bool isWhite()const;
	         
	         //! Check if pos is in set of possible moves.
	         /*! \param pos tested position. */
	         bool isValid(const ChessPos & pos)const;
	         
	         //! Sets position to piece
	         /*!  \param pos setted position.*/
	         void setPos(const ChessPos & pos);
	         
	         //! Returns position of piece.
	         ChessPos getPiecePos()const;
	         
	         //! Returns all possible positions where piece can go.
	         set<ChessPos> getValidPos()const;
	         
	         //! Abstract method.
	 virtual char getType()const = 0;
	 
	         //! Abstract method;
	 virtual void setvalidDest(const ChessBoard & b) = 0;
	 
  protected:
  
    /** Represents color of piece. */
	bool m_white;
	
	/** Represents position of piece. */
	ChessPos * m_pos;
	
	/** Represents all possible positions where piece can go. */
	set<ChessPos> m_dest;
};

//! Inherrited from ChessPiece.Represents Pawn.
class Pawn :public ChessPiece  
{
  public:
             //! A konstructor.
	         Pawn(bool white,int x,int y);
	         
	         //! Returns type P.
	 virtual char getType()const;
	 
	         //! Finds all possible positions where piece can go and store them.  
	         /*! \param b board where is piece. */   
	 virtual void setvalidDest(const ChessBoard & b);
	 
	         //! Returns true if pawn moved two square forward last turn.
             bool movedlastTurn()const;
     
             //! Sets m_moved at value moved 
             /*! \param moved setted value to moved*/    
	         void setlastTurn(bool moved);
	         
  protected:
  
     /** Represents pawn moved two square forward last turn. */
	 bool m_moved;
};

//! Inherrited from ChessPiece.Represents Rock.
class Rock :public ChessPiece  
{
  public:
             //! A konstructor.
	         Rock(bool white,int x,int y);
	         
	         //! Returns type P.
	 virtual char getType()const;
	 
	         //! Finds all possible positions where piece can go and store them.  
	         /*!\param b board where is piece. */
	 virtual void setvalidDest(const ChessBoard & b);
	 
	         //! Returns true if piece was dragged.
	         bool isDragged()const;
	 
	         //! Sets dragged to true;
	         void setDrag();

  protected:
     /** Represents piece was dragged */
	 bool m_dragged;
};

//! Inherrited from ChessPiece.Represents King.
class King :public ChessPiece  
{
  public:    
             //! A konstructor.
	         King(bool white,int x,int y);
	         
	         //! Returns type K.
	 virtual char getType()const;
	         
	         //! Finds all possible positions where piece can go and store them.  
	         /*! \param b board where is piece. */
	 virtual void setvalidDest(const ChessBoard & b);
	 
	 		 //! Returns true if piece was dragged.
	 		 bool isDragged()const;
	 
		     //! Sets dragged to true;
             void setDrag();
     
  protected:
     /** Represents piece was dragged */
	 bool m_dragged;
};

//! Inherrited from ChessPiece.Represents Qeen.
class Qeen :public ChessPiece  
{
  public:    
             //! A konstructor.
	         Qeen(bool white,int x,int y);
	         
	         //! Returns type Q.
	 virtual char getType()const;
	         
	         //! Finds all possible positions where piece can go and store them.  
	         /*! \param b board where is piece.*/
	 virtual void setvalidDest(const ChessBoard & b);
    
  protected:
	
};

//! Inherrited from ChessPiece.Represents Bishop.
class Bishop :public ChessPiece  
{
  public:    
             //! A konstructor.
	         Bishop(bool white,int x,int y);
	         
	         //! Returns type B.
	 virtual char getType()const;
	 
	         //! Finds all possible positions where piece can go and store them.  
	         /*! \param b board where is piece.*/
	 virtual void setvalidDest(const ChessBoard & b);
   
  protected:
	
};

//! Inherrited from ChessPiece.Represents Knight.
class Knight :public ChessPiece  
{
  public:    
             //! A konstructor.
	         Knight(bool white,int x,int y);
	         
	         //! Returns type H. 
	 virtual char getType()const;
	         
	         //! Finds all possible positions where piece can go and store them.  
	         /*! \param b board where is piece.*/ 
	 virtual void setvalidDest(const ChessBoard & b);
   
  protected:
	
};

