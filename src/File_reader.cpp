//
//  File_reader.cpp


#include "Header/File_reader.h"

/**
 *  + File_reader::File_reader()    CONSTRUCTOR
 */
File_reader::File_reader()
{
  input_file   = "";
  delete_count = 0;
}

/**
 *  + File_reader::_set_input_file
 *  ASSIGN INPUT FILE NAME TO THE ATTRIBUTE
 *
 *  @param  in(const string)  - INPUT FILE NAME
 *  @return                   - VOID
 */
void File_reader::_set_input_file(const string in)
{
  input_file = in;
}

/**
 *  + File_reader::_get_vector
 *  PROVIDE THE ADDRESS OF VECTOR
 *
 *  @param      - NONE
 *  @return     - VOID
 */
vector<Data *>* File_reader::_get_vector()
{
  return &list;
}

/**
 *  + File_reader::_get_vectorSize
 *  PROVIDE THE SIZE OF THE VECTOR, USING STATIC CAST TO CONVERT UNSIGNED INT
 *  (FROM size() FUNCTION) TO INT
 *
 *  @param      - NONE
 *  @return     - integer
 */
int File_reader::_get_vectorSize() const
{
  return (static_cast<int>(list.size()));
}

/**
 *  + File_reader::_insert_toVector
 *
 */
bool File_reader::_insert_toVector(Data *newSdt)
{
  // VALIDATION FOR DUPLICATION
  string target_id = newSdt->_get_studentObj()->_get_studentID();
  
  for(int i=delete_count; i<list.size(); i++){
    if(list[i]->_get_studentObj()->_get_studentID() == target_id){
      return false;
    }
  }
  
  // PUSH INTO VECTOR
  list.push_back(newSdt);
  return true;
}



/**
 *-----------------------------------------------------------------------------*
 * FUNCTION MEMBER FUNCTION : _parsing_input_file()                            *
 * PRE-CONDITION            : NONE                                             *
 * POST-CONDITION           : INPUT FILE READ AND VECTOR IS POPULATED          *
 * PARAMETER                : NONE                                             *
 * REFERENCE PARAMETER      : NONE                                             *
 * RETURN VALUE             : bool                                             *
 *-----------------------------------------------------------------------------*
 * THE INPUT FILE IS IN CSV FILE TYPE(COMMA SEPARATED VALUES). THEREFORE, THE  *
 * PARSING PART WILL HAVE TO SECTIONS : FIRST, READING LINE BY LINE, THIS STEP *
 * WILL GIVE US A STRING. THEN, SECONDLY, PASS STRING INTO AN istringstream    *
 * OBJECT AND USING getline READ ALL DATA(SEPARATED BY COMMA). AFTER THESE TWO *
 * SECTIONS, WE WILL HAVE ALL THE DATA WE NEED TO BUILD A STUDENT CLASS OBJECT *
 * THEN, WE DYNAMICALLY ALLOCATE A BLOCK OF MEMORY FOR STUDENT CLASS OBJECT,   *
 * AND THEN, WE PUSH A POINTER WHICH POINTS TO THIS NEWLY BUILT STUDENT CLASS  *
 * OBJECT INTO A VECTOR FOR LATER USAGE. CLOSE FILE WHEN THERE IS NO MORE      *
 * INPUT DATA IN THE INPUT FILE.                                               *
 *-----------------------------------------------------------------------------*
 */
bool File_reader::_parsing_input_file()
{
  string input_str, temp;
  ifstream inputFile(input_file.c_str());
  if(inputFile.fail()){
    return false;
  }
  else{
    while(getline(inputFile, input_str)){
      Student *sdt = new Student;
      int counter = 0;
      std::istringstream inStr_buffer(input_str);
      while(getline(inStr_buffer, temp, ',')){
        if(counter == 0){
          sdt->_set_studentID(temp);
        }
        else if(counter == 1){
          sdt->_set_fullName(temp);
        }
        else if(counter == 2){
          sdt->_set_phoneNum(temp);
        }
        else{
          sdt->_set_birthDay(temp);
        }
        counter++;
      } // END FOR LOOP
      
      Data *tempData = new Data(sdt);
      list.push_back(tempData);
    } // END WHILE LOOP
    inputFile.close();
  }
  
  return true;
}

/**
 *  + File_reader::_lazy_deletion
 *  WHEN USER REQUESTS TO DELETE A STUDENT, THIS MEMBER FUNCTION WILL FIND
 *  THE RIGHT NODE AND SWITCH ITS FLAG TO FALSE AND THEN SWAP THAT NODE TO
 *  THE FIRST HALF OF THE VECTOR
 *
 *  @param  del_node(string &)  - TARGET STUDENT OBJECT TO BE DELTED
 *  @return                     - VOID
 */
void File_reader::_lazy_deletion(string &del_node)
{
  for(int i=delete_count; i<list.size(); i++){
    if(list[i]->_get_studentObj()->_get_studentID() == del_node){
      // FOUND A MATCH
      list[i]->_switch_flag();
      Data *temp = list[delete_count];
      list[delete_count] = list[i];
      list[i] = temp;
      temp = NULL;
      delete_count++;
      
      cout << "[DELETION MADE]" << endl;
      return;
    } // END IF STATEMENT
  } // END FOR LOOP
  
  cout << "[NO DELETION MADE]" << endl;
  return;
}

/**
 *  + File_reader::_show_deleted_students
 *  DISPLAY DELETED STUDENT(S)
 *
 *  @param      - NONE
 *  @return     - VOID
 */
void File_reader::_show_deleted_students(ostream &os) const
{
  if(delete_count == 0){
    os << "[NO DELETION OCCURED SO FAR]" << endl;
  }
  else{
    for(int i=0; i<delete_count; i++){
      os << *list[i]->_get_studentObj() << endl;
    } // END FOR LOOP
  }
}

/**
 *  + File_reader::_resotre_deletion
 *  RETREAT DELETED STUDENT
 *
 *  @param  restoreStudent(string &)  - THE STUDENT OBJECT THAT NEEDS TO BE
 #                                      RESTORED FROM DELETION
 *  @return                           - VOID
 */
Data * File_reader::_restore_deletion(string &restoreStudent)
{
  Data *reStudent = NULL;
  for(int i=0; i<delete_count; i++){
    if(list[i]->_get_studentObj()->_get_studentID() == restoreStudent){
      // MATCH FOUND
      reStudent = list[i];
      list[i]->_switch_flag();
      delete_count--;
      Data *temp = list[delete_count];
      list[delete_count] = list[i];
      list[i] = temp;
      
      cout << "[STUDENT RETREATED]" << endl;
      return reStudent;
    } // END IF STATEMENT
  } // END FOR LOOP
  
  cout << "[STUDENT RETREATING FAIL]" << endl;
  return reStudent;
}

/**
 *  + File_reader::_display_contents_in_vector
 *  DISPLAY STUDENT DATA
 *
 *  @param  os	- (ostream &)
 *  @return      - VOID
 */
void File_reader::_display_contents_in_vector(ostream &os)
{
  for(int i=delete_count; i<list.size(); i++){
    if(!list[i]->_get_flag()){
      Student *sdt_out = list[i]->_get_studentObj();
      os << sdt_out->_get_studentID() << ",";
      os << sdt_out->_get_fullName()  << ",";
      os << sdt_out->_get_phoneNum()  << ",";
      os << sdt_out->_get_birthDay()  << "\n";
    }
  } // END FOR LOOP
}

/**
 *  + File_reader::_get_delete_count
 *  RETURNS THE DELETE_COUNT
 *
 *  @param    	- NONE
 *  @return     - INTEGER
 */
int File_reader::_get_delete_count() const
{
  return delete_count;
}

/**
 *  + File_reader::_get_data
 *  SEARCH FOR THE GIVEN ID IN THE DATABASE
 *  RETURN THE ADDRESS IF FOUND.
 *  OTHERWISE, RETURN NULL
 *
 *  @param    	- NONE
 *  @return      - Data*
 */
Data *File_reader::_get_data(string &id)
{
  for(int i = delete_count; i<list.size(); i++){
    if(list[i]->_get_studentObj()->_get_studentID() == id){
      return list[i];
    } // END IF
  } // END FOR LOOP
  return NULL;
}
