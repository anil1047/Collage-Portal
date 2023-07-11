//
//  File_reader.h


#ifndef __Final_project__File_reader__
#define __Final_project__File_reader__

#include <iostream>
#include "Header/Data.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class File_reader
{
private:
  vector<Data *> list;
  string input_file;
  int delete_count;
  
public:
  File_reader  ();
  ~File_reader (){}
  
  vector<Data *>* _get_vector();
  
  void   _set_input_file              (const string);
  bool   _parsing_input_file          ();
  int    _get_vectorSize              ()              const;
  
  bool   _insert_toVector             (Data *);
  Data * _get_data                    (string &);
  void   _lazy_deletion               (string &);
  void   _show_deleted_students       (ostream &)     const;
  Data * _restore_deletion            (string &);
  int    _get_delete_count            ()              const;
  void   _display_contents_in_vector  (ostream &);
};

#endif /* defined(__Final_project__File_reader__) */
