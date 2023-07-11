//
//  Student.h


#ifndef __Final_project__Student__
#define __Final_project__Student__

#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
  string student_id;
  string full_name;
  string phone_num;
  string birth_day;
  
public:
  // DEFAULT CONSTRUCTOR
  Student  ();
  Student  (string, string, string, string);
  ~Student (){}
  
  // MUTATOR
  void _set_studentID (string &);
  void _set_fullName  (string &);
  void _set_phoneNum  (string &);
  void _set_birthDay  (string &);
  
  // ACCESSOR
  string _get_studentID () const;
  string _get_fullName  () const;
  string _get_phoneNum  () const;
  string _get_birthDay  () const;
  
  
  //*~~~*~~~*~~~*~~~*~~~*~~~*
  //  OVERLOAD << OPERATOR //
  //*~~~*~~~*~~~*~~~*~~~*~~~*
  friend ostream& operator << (ostream &, Student &);
};

#endif /* defined(__Final_project__Student__) */
