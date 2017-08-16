/// \file
/// \brief  Header for ChessBoard.cpp

#include "ChessPiece.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <time.h> 
#include <unistd.h> 
using namespace std;  
#define DIMENSION 8

//!  ChessBoard represents game board. 
/*! This class is engine of all game. It provides all calculations.*/
class ChessBoard 
{
  public:
    
    //! A Constructor.
    /*! Makes two dimensional array of int and vector of pieces. */
	ChessBoard();
	
	//! A Destructor.
    ~ChessBoard();	
    
    //! Sets all pieces at their proper starting positions.
	void setnewBoard();
	
	//! Loads game from file.
	/*!
    \param turn if is true it is white turn else black turn.
    \param inFile contains name of source file.
    */
	bool setloadedBoard(bool & turn,const string & inFile);
	
	//! Returns true if square is empty false otherwise
	/*! \param square is number of square  */
    bool isEmpty(int square)const;
    
    //! Returns true if piece at square is white false otherwise
	/*! \param square is number of square  */
    bool isWPiece(int square)const;
    
    //! Returns type of piece
	/*! \param square is number of square  */
    char getPieceType(int square)const;
    
    //! Does move if is valid
	/*!
	Returns 0 if move is not valid, 1 if is valid, 2 if move is succesfull saved game 3 otherwise and 4 if is quitted game.
    \param input contains users input 
    \param turn if is true it is white turn
    */
    int doMove(const char * input,bool turn);
    
    //! Returns position of king
	/*!  \param color if is true return white king */
    ChessPos findKing(bool color)const;
    
    //! Returns true if is check false otherwise
	/*! 
    \param pos position which is tested on check
    \param turn if is true it is white turn
    */
    bool isCheck(const ChessPos & pos,bool turn)const;
    
    //! Returns true if is checkmate false otherwise
	/*!  \param turn if is true it is white turn*/
    bool isCheckmate(bool turn)const;
    
    //! Returns true if is stalemate false otherwise
	/*! \param turn if is true it is white turn */
    bool isStalemate(bool turn)const;
  private:
    
    //! Returns index of piece on square
	/*!  \param square is number of square */
    int  getSquare(int square)const;
    
    //! Returns true if is enpassant false otherwise
	/*! 
    \param from starting position
    \param to destinating position 
    */
    bool doEnpassant(const ChessPos & from,const ChessPos & to);
    
    //! Returns true if game is saved sucessfully
	/*! \param turn if is true it is white turn */
    bool saveGame(bool turn)const;
    
    //! Returns true if is castling false otherwise
	/*! 
    \param from starting position
    \param to destinating position 
    */
    bool doCastling(const ChessPos & from,const ChessPos & to);
    
    //! Promote pawn to qeen
	/*! \param number of pawn to promote*/
    void promotePawn(int number);
    
    //! Computes row and col coordinates from text input
	/*!  \param input contains user input  */
    ChessPos computePos(const char * input);
    
    //! Returns true if is doublecheck false otherwise
	/*! \param turn if is true it is white turn */
    bool isDoubleCheck(bool turn)const;
    
    //! Returns position of attacker who casuses check
	/*! 
    \param pos position which is checked
    \param turn if is true it is white turn
    */
    ChessPos getAttackerPos(const ChessPos & pos,bool turn)const;
    
    //! Returns positions which are between king and attacker and are possible for interpose
	/*! 
    \param kingpos position of king
    \param attackerpos position of attacker
    */
    set<ChessPos> getInterposePos(const ChessPos & kingpos,const ChessPos & attackerpos)const;
    
    /** two dimensional integer array -1 represents empty square otherwise index of piece */
	int ** board;
	
	/** vector of pieces */
	vector<ChessPiece*> pieces; 
};
