//
//  Heap.h


#ifndef __Final_project__Heap__
#define __Final_project__Heap__

#include <iostream>
#include <algorithm>
#include <vector>
#include "Header/Data.h"


class Heap
{
private:
  Data  **heap_arr;
  int    count;
  int    arrSize;
  int    first_zero_index;
  
  // RE-HEAP-UP & RE-HEAP-DOWN
  void _re_heap_up    (int);
  void _re_heap_down  (int);
  void _resize        ();
public:
  Heap  (int);
  ~Heap ();
  
  bool _push  (Data *);
  bool _pop   (Data *&);
  
  // UPDATE THE HEAP-ARRAY
  void _update_rank   (string);
  void _show_topTen   (ostream &);
};
#endif /* defined(__Final_project__Heap__) */
