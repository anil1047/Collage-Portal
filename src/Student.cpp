//
//  Student.cpp


#include "Header/Student.h"

/**
 *  CONSTRUCTOR
 */
Student::Student()
{
  student_id = full_name = phone_num = birth_day = "";
}

/**
 *  OVERLOAD CONSTRUCTOR
 */
Student::Student(string id, string name, string pNum, string bDay)
{
  student_id = id;
  full_name  = name;
  phone_num  = pNum;
  birth_day  = bDay;
}

/**
 *  MUTATOR MEMBER FUNCTIONS
 *  PROVIDE METHOD TO LET USER TO ASSIGN THE STORING ATTRIBUTES(STATUS)
 *
 *  @param  - NONE
 *  @return - VOID
 */
void Student::_set_studentID (string &id)
{
  student_id = id;
}
void Student::_set_fullName  (string &name)
{
  full_name = name;
}
void Student::_set_phoneNum  (string &pNum)
{
  phone_num = pNum;
}
void Student::_set_birthDay  (string &bDay)
{
  birth_day = bDay;
}

/**
 *  ACCESSOR MEMBER FUNCTIONS
 *  PROVIDE METHOD TO LET USER TO ACCESS THE STORING ATTRIBUTES(STATUS)
 *
 *  @param  - NONE
 *  @return - DEPENDS ON WHAT KIND OF DATA TYPE
 */
string Student::_get_studentID () const
{
  return student_id;
}
string Student::_get_fullName  () const
{
  return full_name;
}
string Student::_get_phoneNum  () const
{
  return phone_num;
}
string Student::_get_birthDay  () const
{
  return birth_day;
}

/**
 *-----------------------------------------------------------------------------*
 * FUNCTION MEMBER FUNCTION : operator << ()                                   *
 * PRE-CONDITION            : right(STUDENT OBJECT) HAS VALUES AND HAD BEEN    *
 *                            PROPERLY DECLARED                                *
 * POST-CONDITION           : NOTHING CHANGED                                  *
 * PARAMETER                : right(Student &)                                 *
 * REFERENCE PARAMETER      : out(ostream &)                                   *
 * RETURN VALUE             : ostream &                                        *
 *-----------------------------------------------------------------------------*
 * OVERLOADING OPERATOR << AND PRINT EVERY VARIABLES INSIDE THE INFORMATION    *
 * ABSTRACT DATA TYPE                                                          *
 *-----------------------------------------------------------------------------*
 */
ostream& operator << (ostream &out, Student &right)
{
  out << "STUDENT ID   : " << right.student_id << endl;
  out << "FULL NAME    : " << right.full_name  << endl;
  out << "PHONE NUMBER : " << right.phone_num  << endl;
  out << "BIRTH YEAR   : " << right.birth_day  << endl;
  
  return out;
}
