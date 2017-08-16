/// \file
/// \brief  Header for ChessInterface.cpp

#include <ncurses.h>
#include "ChessBoard.h"
#include <stdio.h>
#include <ctype.h>

//!  Draws game elements at terminal screen. It's GUI. 
/*! Draws game board and prints messages about game state. */
class ChessInterface
{
  public:
         //! A konstructor.
         /*! Sets ncurses screen, makes color pairs and divides screen to game elements. */
	     ChessInterface();
	     
	     //! A destructor.
        ~ChessInterface();
        
         //!  Draws square of board each in one window. 
         void drawBoard();
         
         //!  Draws pieces to proper square.
         /*! \param b board with pieces which is drawed. */ 
         void updateBoard(const ChessBoard & b );
         
         //! Reads users input from keyboard until it is valid and then return it.
         /*! \param turn represents player who is on turn.*/ 
         char * readInput(bool turn);
         
         //! Refreshes screens.
         void refreshScreen();
         
         //! Prints messages for players about game state.
         /*!
         \param x shifts x chars to left.
         \param y shifts y chars down.
         \param colorpair sets color of text
         \param msg holds content of message
         */ 
         void printMessage(int x,int y,int colorpair,const char * msg);
         
  private:
         //! Checks if input is valid.
         bool isValid()const;    
  
         /** displays board squares */
	     WINDOW ** windows;
	     
	     /** storage for usage input */
	     char * m_input;
	     
	     /** represent window for terminal where program prints messages */
	     WINDOW * terminal;
};
