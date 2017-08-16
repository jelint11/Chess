/// \file
/// \brief  Implementation of Chess GUI

#include "ChessInterface.h"

ChessInterface::ChessInterface()
{
  initscr();
  start_color();
  clear();
  keypad(stdscr, TRUE);
  init_pair(1, COLOR_BLACK, COLOR_GREEN);
  init_pair(2, COLOR_WHITE, COLOR_YELLOW);
  init_pair(3, COLOR_BLACK, COLOR_YELLOW);
  init_pair(4, COLOR_WHITE, COLOR_GREEN);
  init_pair(5, COLOR_RED, COLOR_BLACK);
  windows = new WINDOW*[64];
  terminal = newwin(5, 30, 3, 55);
  m_input = new char[6];
}


ChessInterface::~ChessInterface()
{
  for(int i=0;i<64;i++)  delwin(windows[i]);
  delete [] windows;
  delwin(terminal);
  delete [] m_input;
  endwin();
}


void ChessInterface::drawBoard()
{
  for(int i=0;i<64;i++)
  {
    windows[i] = newwin(3, 5, 2+3*(i/8), 5+5*(i%8));
    if((i+i/8)%2) wbkgd( windows[i], COLOR_PAIR(1));
    else  wbkgd( windows[i], COLOR_PAIR(2));
  }
  for(int i=8;i>0;i--)
  {
    mvwaddch(stdscr, 27-3*i, 3, 48+i);
    mvwaddch(stdscr, 27-3*i, 46, 48+i);
    mvwaddch(stdscr, 1, 47-5*i, 73-i);
    mvwaddch(stdscr, 26, 47-5*i, 73-i);
  }
}


void ChessInterface::updateBoard(const ChessBoard & b )
{
  int pair;
   
  for (int i=0;i<64;i++)
  {
    if(!b.isEmpty(i))
    {
      if((i+i/8)%2 && b.isWPiece(i)) pair=4;
      else if (b.isWPiece(i)) pair=2;
      else if ((i+i/8)%2) pair=1;
      else pair=3;
      wattron(windows[i],COLOR_PAIR(pair) | A_BOLD);
      mvwaddch(windows[i],1,2,b.getPieceType(i) );
      wattroff(windows[i],COLOR_PAIR(pair) | A_BOLD);
    } 
  }
}

bool ChessInterface::isValid()const
{
  if ( strncmp(m_input, "quit", 4*sizeof(char)) == 0) return true;
  if ( strncmp(m_input, "save", 4*sizeof(char)) == 0) return true;
  if ( m_input[0] < 97 || m_input[0] > 104 ) return false;
  if ( m_input[1] < 48 || m_input[1] > 56   ) return false;
  if ( m_input[2] != 32   ) return false;
  if ( m_input[3] < 97 || m_input[3] > 104 ) return false;
  if ( m_input[4] < 48 || m_input[4] > 56   ) return false;
  return true;
}


void ChessInterface::refreshScreen()
{
  refresh();
  for (int i=0;i<64;i++) wrefresh(windows[i]); 
}


char * ChessInterface::readInput(bool turn)
{
  if(turn) mvwprintw(terminal,2,0,"WHITE: Type your move");
  else mvwprintw(terminal,2,0,"BLACK: Type your move");
  mvwgetnstr(terminal,3,5,m_input,5 );
  m_input[0]=tolower(m_input[0]);
  m_input[3]=tolower(m_input[3]);
  while(!isValid())
  {
    wclear(terminal);
    wattron(terminal,COLOR_PAIR(5) | A_BOLD);
    wprintw(terminal,"Invalid input-Try it again!");
    wattroff(terminal,COLOR_PAIR(5) | A_BOLD);
    if(turn) mvwprintw(terminal,2,0,"WHITE: Type your move");
    else mvwprintw(terminal,2,0,"BLACK: Type your move");
    mvwgetnstr(terminal,3,5,m_input,5 );
  }
  wclear(terminal);
  wrefresh(terminal);
  return m_input;
  
}


void ChessInterface::printMessage(int x,int y,int colorpair,const char * msg)
{
  wclear(terminal);
  wattron(terminal,COLOR_PAIR(colorpair) | A_BOLD);
  mvwprintw(terminal,x,y,msg);
  wattroff(terminal,COLOR_PAIR(colorpair) | A_BOLD); 
  wrefresh(terminal);
}



