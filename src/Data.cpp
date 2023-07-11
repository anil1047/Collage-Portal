//
//  Data.cpp


#include "Header/Data.h"

/**
 *  DEFAULT CONSTRUCTOR
 */
Data::Data()
{
  sdt = NULL;
  search_count = 0;
  delete_flag = false;
}

/**
 *  OVERLOAD CONSTRUCTOR
 *  TAKE AN INPUT(AN ADDRESS OF STUDENT OBJECT) AND ASSIGN IT TO THE
 *  ATTRIBUTE IN THE CLASS
 *
 *  @param  inStudent(Student *)  - AN ADDRESS OF STUDENT OBJECT
 */
Data::Data(Student *inStudent) : search_count(0), delete_flag(false)
{
  sdt = inStudent;
}

/**
 *  + Data::_switch_flag
 *  THE FUNCTION WOULD SWITCH THE BOOLEAN VALUE THAT THE FLAG HOLDS
 *  (TRUE -> FALSE, VICE VERSEA)
 *
 *  @param    - NONE
 *  @return   - VOID
 */
void Data::_switch_flag()
{
  if(delete_flag == false){
    delete_flag = true;
  }
  else{
    delete_flag = false;
  }
}

/**
 *  + Data::operator++
 *  OVERLOADED PRE-FIX OPERATOR
 */
Data& Data::operator++()
{
  this->search_count += 1;
  return *this;
}

/**
 *  ACCESSOR MEMBER FUNCTIONS
 *  PROVIDE ACCESSING METHOD FOR USER TO ACCESS THE STORING ATTRIBUTES
 *
 *  @param    - NONE
 *  @return   - DEPENDS ON DIFFERENT KIND OF DATA TYPES
 */
bool Data::_get_flag() const
{
  return delete_flag;
}

int Data::_get_searchCount() const
{
  return search_count;
}

Student *Data::_get_studentObj() const
{
  return sdt;
}
