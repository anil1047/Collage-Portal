//
//  Heap.cpp


#include "Header/Heap.h"

/**
 *  OVERLOAD CONSTRUCTOR
 */
Heap::Heap(int size)
{
  count   = 0;
  arrSize = size*2;
  first_zero_index = 0;
  
  // DYNAMICALLY ALLOCATE AN ARRAY
  heap_arr = new Data *[arrSize];
  for(int i=0; i<arrSize; i++){
    heap_arr[i] = NULL;
  }
}

/**
 *  DESTRUCTOR
 */
Heap::~Heap()
{
  delete[] heap_arr;
  heap_arr = NULL;
  count    = 0;
  arrSize  = 0;
  first_zero_index = 0;
}

/**
 *  - Heap::_resize
 *  RESIZING THE HEAP ARRAY IF IT RAN OUT OF SPACE
 *
 *  @param    - NONE
 *  @return   - VOID
 */
void Heap::_resize()
{
  if(count == (arrSize-1)){
    int newSize  = 2 *arrSize;
    // DECLARE A TEMP ARRAY
    Data **temp_arr = new Data *[newSize];
    for(int i=0; i<arrSize; i++){
      temp_arr[i] = heap_arr[i];
    } // END FOR LOOP
    
    delete[] heap_arr;
    heap_arr = temp_arr;
    temp_arr = NULL;
  }
}

/**
 *  + Heap::_push
 *  INSERT FUNCTION FOR HEAP CLASS, TAKE AN ADDRESS OF A DATA OBJECT
 *  AND STORE IT INTO HEAP ARRAY
 *
 *  @param  newObj(Data *)  - A POINTER THAT HOLDS THE ADDRESS OF A DATA OBJECT
 *  @return                 - BOOLEAN VALUE(TURE : INSERT DONE, FALSE : FAIL)
 */
bool Heap::_push(Data *newObj)
{
  _resize();
  
  if(newObj->_get_searchCount() == 0){
    heap_arr[count] = newObj;
    count++;
  }
  else{
    heap_arr[count] = heap_arr[first_zero_index];
    count++;
    
    heap_arr[first_zero_index] = newObj;
    _re_heap_up(first_zero_index);
    first_zero_index++;
  }
  return true;
}

/**
 *  - Heap::_re_heap_up
 *  IF THE CHILD ELEMENT HAS A GREATER VALUE THEN SWAP THE PARENT AND THE CHILD
 *  KEEP SWAPING UNTIL THE PARENT IS GREATER THAN CHILD
 *
 *  @param  child_index(int)  - CHILD ELEMENT'S INDEX
 *  @return                   - VOID
 */
void Heap::_re_heap_up(int child_index)
{
  int parent_index = 0;
  Data *temp       = NULL;
  
  // CHECK IF THE CHILD INDEX EQUALS TO 0
  if(child_index > 0){
    // GET PARENT INDEX
    parent_index = (child_index - 1) / 2;
    if(heap_arr[parent_index]->_get_searchCount() <
       heap_arr[child_index]->_get_searchCount()){
      temp = heap_arr[parent_index];
      heap_arr[parent_index] = heap_arr[child_index];
      heap_arr[child_index]  = temp;
      
      // RECURSION CALL
      _re_heap_up(parent_index);
    }
    else{
      return;
    }
  }
  else if(child_index == 0){
    // CHILD INDEX EQUALS TO ZERO - NO PARENT
    return;
  }
  else{
    // CHILD INDEX IS NEGATIVE NUMBER
    cout << "[ERROR] : RE-HEAP-UP, CHILD INDEX FAILED" << endl;
    return;
  }
}

/**
 *  - Heap::_re_heap_down
 *  IF THE PARENT ELEMENT HAS SMALLER VALUE THAN THE CHILD'S VALUE, THEN SWAP
 *  THEM, KEEP SWAPPING UNTIL THE PARENT ELEMENT IS GRATER THAN BOTH CHILD
 *
 *  @param  parent_index(int) - INDEX THAT INDICATES PARENT NODE
 *  @return                   - VOID
 */
void Heap::_re_heap_down(int parent_index)
{
  Data *temp      = NULL;
  int left_child  = parent_index * 2 + 1;
  int right_child = parent_index * 2 + 2;
  int index = 0;
  
  // FIND THE CHILD HAS GREATER VALUE
  if(left_child < count && count < arrSize){
    if(right_child >= count){
      // ONLY ONE CHILD(LEFT)
      index = left_child;
    }
    else{ // TWO CHILDREN
      // COMPARE WHICH ONE IS LARGER
      if(heap_arr[left_child]->_get_searchCount() >=
         heap_arr[right_child]->_get_searchCount()){
        index = left_child;
      } // END IF
      else{
        index = right_child;
      } // END ELSE
    } // END FINDING GREATEST CHILD
    
    // SEE IF WE NEED TO SWAP THE VALUES
    if(heap_arr[parent_index]->_get_searchCount() <
       heap_arr[index]->_get_searchCount()){
      temp = heap_arr[parent_index];
      heap_arr[parent_index] = heap_arr[index];
      heap_arr[index] = temp;
      
      // CALL RE-HEAP-DOWN AGAIN
      _re_heap_down(index);
    }
  }
  return;
}

/**
 *  + Heap::_pop
 *  DELETE THE ROOT ELEMENT, AND USE RE-HEAP-DOWN TO MAKE THE HEAP ARRAY 
 *  MAINTAIN AS MAXHEAP ARRAY
 *
 *  @param  cpObj(Data *&)  - THE POINTER THAT COPYS THE DELETED ELEMENT
 *  @return                 - BOOLEAN VALUE
 */
bool Heap::_pop(Data *&cpObj)
{
  if(count == 0){ // EMPTY ARRAY
    cpObj = NULL;
    return false;
  }
  else{
    cpObj             = heap_arr[0];
    heap_arr[0]       = heap_arr[first_zero_index-1];
    heap_arr[first_zero_index-1] = heap_arr[count-1];
    //delete heap_arr[count-1];
    heap_arr[count-1] = NULL;
    count--;
    first_zero_index--;
    
    _re_heap_down(0);
    return true;
  }
}

/**
 *  + Heap::_update_rank
 *  UPDATING THE NODE THAT HAD JUST BEEN SEARCHED
 *
 *  @param  student_id(string)  - STUDENT ID NUMBER
 *  @return                     - VOID
 */
void Heap::_update_rank(string student_id)
{
  Data *temp = NULL;
  // FIND THE SPECIFIC ELEMENT
  for(int i=0; i<count; i++){
    if(heap_arr[i]->_get_studentObj()->_get_studentID() == student_id){
      if(i > first_zero_index){
        // FIRST SWAP TARGET WITH THE FIRST ELEMENT WHICH HAS ZERO COUNT
        temp = heap_arr[first_zero_index];
        heap_arr[first_zero_index] = heap_arr[i];
        heap_arr[i] = temp;
        temp = NULL;
        
        // RE-HEAP-UP FROM THE LAST ELEMENT WHICH HAS NONE-ZERO SEARCH COUNT
        _re_heap_up(first_zero_index);
        first_zero_index++;
      }
      else if(i == first_zero_index){
        _re_heap_up(first_zero_index);
        first_zero_index++;
      }
      else{ // MATCHED STUDENT OBJECT HAD BEEN SEARCHED
        _re_heap_up(i);
      }
    } // ENF IF
  }
}

/**
 *  + Heap::_show_topTen
 *  DISPLAYING TOP TEN SEARCH STUDENTS IN HEAP ARRAY
 *
 *  @param  os(ostream &) - OSTREAM REFERENCE OBJECT
 *  @return               - VOID
 */
void Heap::_show_topTen(ostream &os)
{
  if(first_zero_index == 0){
    os << "NO SEARCH HAD BEEN MADE SO FAR" << endl;
    return;
  }
  const int topTen = 10;
  
  vector<Data *> temp_storage;
  Data *temp = NULL;
  int boundry = 0;
  (first_zero_index > topTen) ? boundry = topTen : boundry = first_zero_index;
  for(int i=0; i<boundry; i++){
    if(_pop(temp)){
      if(temp->_get_searchCount() != 0){
        os << "Student ID: " << temp->_get_studentObj()->_get_studentID()
           << "  | Search times: " << temp->_get_searchCount();
        (temp->_get_flag()) ?
        os << "  | status : deleted.\n" :
        os << "  | status : available.\n";
      }
      temp_storage.push_back(temp);
    } // END IF
  } // END FOR LOOP
  
  // PUSH ELEMENTS BACK
  for(auto i : temp_storage){
    _push(i);
  }
}
