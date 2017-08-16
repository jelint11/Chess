/// \file
/// \brief  Implements ChessPos 
 
//!  Represents position on the board 
class ChessPos  
{
  public:
    //! A constructor.
	ChessPos(int row, int col):m_Row(row),m_Col(col){}
	
	//! A destructor.
   ~ChessPos(){}
   
    //! Return row.
	int getRow()const{return m_Row;}
	
	//! Return column.
	int getCol()const{return m_Col;} 
	
	//! Set row and column to any position .
    /*!
      \param row will be set.
      \param col will be set.
    */
	void setPos(int row, int col) 
	{
	  m_Row=row;
	  m_Col=col;
	} 
	
	//! Overloaded operator < .
	friend bool operator< (const ChessPos & lpos, const ChessPos & rpos)
    {
      if(lpos.m_Row != rpos.m_Row) return lpos.m_Row < rpos.m_Row;
      else return lpos.m_Col < rpos.m_Col;
    }
    
    //! Overloaded operator == .
	bool operator==(const ChessPos & rpos) 
	{
    return (m_Row == rpos.m_Row && m_Col == rpos.m_Col);
    }
 
  private:
  
    /** number of row */
	int m_Row; 
	
	/** number of col */
	int m_Col; 
};
