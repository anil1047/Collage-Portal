//
//  Controller_Mngr.cpp
 
// ********************************************************
// CONTROLLER MANAGER
// Controller_Mngr.h
//

// The controller manager is the interface of the database.
// It has access to all data structures in the database
// (vector which stores data, and the BST and Hash Tables
//  and heap which point to the data in the vectors).
//
// _task_Mngr will prompt a menu to the user from which
// that user can add or remove data, search for data,
// display the hash table, display the students by sorted
// key, display the BST, display most frequently searched
// students, display hash table stats, write to output
// file, display deleted student, and restore deleted
// student
// ********************************************************

#include "Header/Controller_Mngr.h"

/**
 *	+	Controller_Mngr::Controller_Mngr()
 *
 *	Constructor
 *	Create an instance of file reader class, then it sets the file name
 *	in that class by calling the method, and it calls the the reader method
 *	to read data into the vector
 *	After that, it creates a new Binary Search Tree and Hash table
 *
 *	@ param: none
 *	@ return: void
 */
Controller_Mngr::Controller_Mngr()
{
  fReader = new File_reader();
  fReader->_set_input_file(INPUT_FILE);
  
  while(!fReader->_parsing_input_file()){
    fReader->_set_input_file(_read_fileName_fromUsr());
  }
  
  bsTree  = new BST();
  hTable  = new Hash_Table(fReader->_get_vectorSize());
  heapArr = new Heap(fReader->_get_vectorSize());
  
  _initialization();
  
  /*
  if(fReader->_parsing_input_file()){
    bsTree = new BST();
    hTable = new Hash_Table(fReader->_get_vectorSize());
  }
  else
	  fReader->_set_input_file(_read_fileName_fromUsr());
  
  _initialization();
   */
}

/**
 *  - Controller_Mngr::_initialization()
 *
 *  Logic : Initialize BST & Hash Table
 *
 *  @ param: none
 *  @ return: void
 */
void  Controller_Mngr::_initialization()
{
  vector<Data *> *pList = fReader->_get_vector();
  
  for (auto i : *pList){
    bsTree->insert(i->_get_studentObj());
    hTable->_add_to_table(i->_get_studentObj(), std::cout);
    heapArr->_push(i);
  }
  
  pList = NULL;
}

/**
 *	+	Controller_Mngr::~Controller_Mngr()
 *
 *	Destructor
 *	Delete the Hash Table,
 *	Binary Search Tree,
 *	File read instance
 *
 *	@ param: none
 *	@ return: void
 */
Controller_Mngr::~Controller_Mngr()
{
  delete bsTree;
  delete hTable;
  delete heapArr;
  delete fReader;
}



/**
 *	-	Controller_Mngr::_read_fileName_fromUsr()
 *
 *	Logic : Promt a user to enter a file name
 *			if the program could not the default file.
 *			Then return the file name
 *
 *	@ param: none
 *	@ return: string
 */
string Controller_Mngr::_read_fileName_fromUsr()
{
  string file_name;
  
  cout << "[ERROR] : FAILED TO READ DEFAULT INPUT FILE." << endl;
  cout << "          PLEASE PROVIDE ANOTHER INPUT FILE." << endl;
  cout << "--------------------------------------------" << endl;
  cout << "WHAT IS THE NAME OF NEW INPUT FILE (INCLUDE FILE FORMAT) ?" << endl;
  cin >> file_name;
  
  return file_name;
}



// HELPER MEMBER FUNCTIONS
// *************************************************************************
// HELPER MEMBER FUNCTIONS


/**
 *	-	Controller_Mngr::_greetingMsg()
 *
 *	Logic : Print the greeting message
 *
 *	@ param: none
 *	@ return: string
 */
void Controller_Mngr::_greetingMsg()
{
  cout << "\nSTUDENT DATABASE";
  cout << "PLEASE CHOOSE FROM THE MENU BELOW:" << endl << endl;
}


/**
 *	-	Controller_Mngr::_farewellMsg()
 *
 *	Print the farewell message
 *
 *	@ param: none
 *	@ return: string
 */
void Controller_Mngr::_farewellMsg()
{
  cout << "\nThank you for using thie program. Have a good day!" << endl;
}


/**
 *	-	Controller_Mngr::_read_usrInput(char &usrInput)
 *
 *	Logic : Ask the user to enter a choice for an action
 *			and validate it
 *
 *	@ param: usrInput: char &
 *	@ return: bool
 */
bool Controller_Mngr::_read_usrInput(char &usrInput)
{
  const string question_prompt =
  "What operation do you want to perform? (M - Menu, Q - Quit) : ";
  
  bool flag_choice = true;
  
  // START - DO-WHILE
  do{
    cout << question_prompt;
    // READ ONLY ONE char
    cin.get(usrInput);
    // GET RID OF SPACES, NEWLINE CHARACTERS, TABS
    while(usrInput == '\n' || usrInput == ' ' || usrInput == '\t'){
      cin.get(usrInput);
    }
    cin.ignore(80, '\n');
    
    // CHANGE TO UPPER CASE
    usrInput = _change_to_upper(usrInput);
    
    // VALIDATE INPUT
    flag_choice = _usr_validation(usrInput);
    
    // INVALID MESSAGE
    if(!flag_choice){
      cout << "[INVALID] Invalid input! Please try again!\n";
      cout << "(You can always enter 'M' or 'm' to display menu!\n";
      cout << endl;
    }
    
  } while(!flag_choice);  // END - DO-WHILE
  
  return flag_choice;
}


/**
 *	-	Controller_Mngr::_read_sdtID_from_usr(string &sdt_id)
 *
 *	Logic : Ask the user to enter a valid student ID as a number
 *			and convert it into a string
 *
 *	@ param: sdt_id : string &
 *	@ return: bool
 */
bool Controller_Mngr::_read_sdtID_from_usr(string &sdt_id)
{
  const string INVALID_MSG = "Invalid input! Please try again? ";
  const string ASK_MSG = "Please enter a student ID (Q to QUIT): ";
  string string_num;
  
  cout << ASK_MSG;
  
  // While the string is not Q or not within ID range
  while ((!(std::cin >> string_num)
          || atoi(string_num.c_str()) >= 100000000 || atoi(string_num.c_str()) < 10000000)
         && string_num != "Q" && string_num != "q") {
    std::cin.clear();
    std::cin.ignore(80, '\n');
    cout << INVALID_MSG << endl;
    cout << ASK_MSG;
  }
  
  if (string_num == "Q" || string_num == "q")
    return false;
  
  std::cin.ignore(80, '\n');
  
  sdt_id = string_num;
  // CONVERT INTEGER VARIABLE TO STRING OBJECT
  //sdt_id = to_string(num);
  
  return true;
}
/**
 *	Controller_Mngr::_read_sdt_Input_from_usr( sdt_name:string &, aspect:string ,
 *												low : int, high : int)
 *	Logic : Simple Validation User Input
 *
 *	param @	sdt_name : string &		-	Contain the value of user input
 *	param @	aspect	: string		-	Contain the name of the value to prompt user.
 *	param @	low		: int			-	Determine the Lowest character to get input
 *	param @ high	: int			-	Determine the highest character to get input
 */
bool Controller_Mngr::_read_sdt_Input_from_usr(string &sdt_name,
                                               string aspect,
                                               unsigned int low,
                                               unsigned int high)
{
	// Data field:
	const string INVALID_MSG = "Invalid input! Please try again!";
	const string ASK_MSG ="Please enter "+ aspect +" of the student (Q to QUIT): ";
  
	cout << ASK_MSG;
	while (getline(cin, sdt_name),
         (sdt_name.length() < low || sdt_name.length() > high) &&
         sdt_name != "Q") {
		// CLEAR THE CIN BUFFER
		std::cin.clear();
		cin.ignore(80, '\n');
		cout << INVALID_MSG << endl;
		cout << " \tThe "   << aspect << " should contain more than or equal to "
    << low   << " \n\tBut less than or equal to "
    << high  << " characters.\n";
		cout	<< ASK_MSG;
	};
  
  if (sdt_name == "Q")
    return false;
  
	return true;
}	//	end definition.

/**
 *	-	Controller_Mngr::_change_to_upper(char letter)
 *
 *	Logic : Change the received parameter into upper case
 *
 *	@ param: letter : char
 *	@ return: bool
 */
char Controller_Mngr::_change_to_upper(char letter)
{
  letter = toupper(letter);
  return letter;
}


/**
 *	-	Controller_Mngr::_usr_validation(char usrChoice)
 *
 *	Logic : Check if the given choice is in the range
 *
 *	@ param: usrChoice : char
 *	@ return: bool
 */
bool Controller_Mngr::_usr_validation(char usrChoice)
{
  // USING SWITCH STATEMENT TO CHECK IF USER CHOICE IS VALID
  switch(usrChoice){
      // IF NO MATCH FOUND, IT WILL "FALL-THROUGH" TO THE DEFAULT
    case 'A': return true;
    case 'D': return true;
    case 'S': return true;
    case 'H': return true;
    case 'K': return true;
    case 'I': return true;
    case 'F': return true;
    case 'X': return true;
    case 'Y': return true;
    case 'U': return true;
    case 'W': return true;
    case 'M': return true;
    case 'Q': return true;
    default: return false;
  }
}

/**
 *	MAIN METHOD - ALL "MANAGER METHOD"
 *	-	Controller_Mngr::_menu()
 *
 *	A, D, S, H, K, I, F, X, W, M, Q
 *	Logic : Display the menu choices
 *
 *	@ param: none
 *	@ return: void
 */

void Controller_Mngr::_menu() const
{
  cout.setf(ios::left);
  cout << FRAME                                                   << endl;
  cout << "# (A) "                                                << setw(71)
  << "Add new data"                                  << " #" << endl;
  cout << "# (D) "                                                << setw(71)
  << "Delete data"                                   << " #" << endl;
  cout << "# (S) "                                                << setw(71)
  << "Search by the primary key"                     << " #" << endl;
  cout << "# (H) "                                                << setw(71)
  << "Print entire hash table"                       << " #" << endl;
  cout << "# (K) "                                                << setw(71)
  << "List data in sorted key sequence"              << " #" << endl;
  cout << "# (I) "                                                << setw(71)
  << "Print indented binary search tree"             << " #" << endl;
  cout << "# (F) "                                                << setw(71)
  << "Display the most frequently searched student"  << " #" << endl;
  cout << "# (X) "                                                << setw(71)
  << "Show statistics of hash table"                 << " #" << endl;
  cout << "# (W) "                                                << setw(71)
  << "Write to output file"                          << " #" << endl;
  cout << "# (Y) "                                                << setw(71)
  << "Display deleted student"                       << " #" << endl;
  cout << "# (U) "                                                << setw(71)
  << "Restore deleted student"                       << " #" << endl;
  cout << "# (M) "                                                << setw(71)
  << "Show menu"                                     << " #" << endl;
  cout << "# (Q) "                                                << setw(71)
  << "Quit program"                                  << " #" << endl;
  cout << FRAME                                                   << endl;
}

/**
 *	-	Controller_Mngr::_deleted_display()
 *
 *	Logic : Print data of deleted students
 *			by calling the method in the File Reader class
 *
 *	@ param: none
 *	@ return: void
 */
void Controller_Mngr::_deleted_display()
{
  cout << MSG_FRAME;
  cout << "* " << setw(64) << left
  << "You have chosen to display deleted students." << "*";
  cout << MSG_FRAME;
  fReader->_show_deleted_students(cout);
  
  cout << MSG_FRAME;
}

/**
 *	-	Controller_Mngr::_restore_Mngr()
 *
 *	Logic : Restore the deleted students
 *			by calling the method in the File Reader class
 *			and inserting them into the BST & Hash table
 *
 *	@ param: none
 *	@ return: void
 */
void Controller_Mngr::_restore_Mngr()
{
  cout << MSG_FRAME;
  cout << "* " << setw(64) << left
  << "You have chosen to restore a deleted student." << "*";
  cout << MSG_FRAME;
  
  if(fReader->_get_delete_count()){
    string sdt_id;
    if(_read_sdtID_from_usr(sdt_id)){
      Data *reStudent = fReader->_restore_deletion(sdt_id);
      if(reStudent){  // STUDENT ID IN DELETED LIST
        bsTree->insert(reStudent->_get_studentObj());
        hTable->_add_to_table(reStudent->_get_studentObj(), cout);
        cout << "Deleted student has been restored." << endl;
      }
      reStudent = NULL;
    }
    else{
      cout << "You have chosen to not restore a deleted student." << endl;
    }
  }
  else{
    cout << "The deleted list currently is empty." << endl;
  }
  
  cout << MSG_FRAME;
}

/**
 *	-	Controller_Mngr::_task_Mngr()
 *
 *	Logic : The body of the object. It displays the greeting,
 *	menu, and it calls the appropiate method based on user's choice
 *
 *	@ param: none
 *	@ return: void
 */
void Controller_Mngr::_task_Mngr()
{
  char task;
  bool exit_flag = true;
  
  _greetingMsg();
  _menu();
  while(exit_flag&&_read_usrInput(task)){
    switch(task){
      case 'A':	_addMngr                ();          break;		// A
        
      case 'D':	_remove_Mngr            ();          break;		// D
        
      case 'S':	_searchMngr             ();          break;		// S
        
      case 'H':	_table_displayMngr      ();          break;		// H
        
      case 'K':	_display_sortedKey_Mngr ();          break;		// K
        
      case 'I':	_tree_displayMngr       ();          break;		// I
        
      case 'F': _frequency_Mngr         ();          break;		// I
        
      case 'X':	_statistics_Mngr        ();          break;		// X
        
      case 'Y': _deleted_display        ();          break;		// Y
        
      case 'U':	_restore_Mngr           ();          break;		// U
        
      case 'W':	_write_Mngr             ();          break;		// W
        
      case 'M':	_menu_Mngr              ();          break;		// M
        
      case 'Q':	_quit_Mngr              (exit_flag); break;		// Q
        
      default: cout << "[ERROR] task_mngr - switch STATEMENT \n";
    } // END SWITCH
  } // END WHILE
  _frequency_Mngr();
  
  _farewellMsg();
}

/**
 *	-	Controller_Mngr::_searchMngr()
 *
 *	Logic : Get the student id from the user to search it in the database,
 *	Call the private method to search infrormation about the student
 *	Display a message if this student is not in the database
 *
 *	@ param: none
 *	@ return: void
 */
void Controller_Mngr::_searchMngr()
{
  string stu_id;
  Data*  data_found;
  
  cout << MSG_FRAME;
  cout << "* " << setw(64) << left
  << "You have chosen to search a student by a student ID." << "*";
  cout << MSG_FRAME;
  cout << "\n\tTo search please enter the Student ID (8 characters):\n";
  
  if(_read_sdtID_from_usr(stu_id)){
    cout << endl;
    if(_find_and_display(stu_id, data_found)){
      ++(*data_found); // Update search_count for data
      heapArr->_update_rank(data_found->_get_studentObj()->_get_studentID());
    }
    else{
      cout << "The database does not contain this student ID.";
    }
  }
  else{
    cout << "You have chosen to quit searching for a student.";
  }
  cout << MSG_FRAME;
}

/**
 *	-	Controller_Mngr::_find_and_display(string student_ID, Data*& temp)
 *
 *	Logic : Search for the given student ID in the BST & Hash Table
 *			and display the data, returning true.
 *			Otherwise, return false
 *
 *	@ param: student_ID - string,  temp - Data*&
 *	@ return: bool
 */
bool Controller_Mngr::_find_and_display(string student_ID, Data*& temp)
{
  time_t timer;
  double t_tree = 0;
  double t_hash = 0;
  double t_vect = 0;
  
  bool hash_flag = false;
  
  Student *target = NULL; // will be outputted for search
  
  timer = clock();
  if(bsTree->search(student_ID, target)){
    timer  = clock() - timer;
    t_tree = static_cast<double>(timer)/CLOCKS_PER_SEC;
    timer = clock();
    if(hTable->_search_by_studentID(student_ID, target)){
      timer  = clock() - timer;
      t_hash = static_cast<double>(timer)/CLOCKS_PER_SEC;
    }
    else
      hash_flag = true; //
    timer  = clock();
    temp   = fReader->_get_data(student_ID);
    timer  = clock() - timer;
    t_vect = static_cast<double>(timer)/CLOCKS_PER_SEC;
    
    cout << "Student found: " << endl;
    cout << *target;
    cout << "---------------------------------------" << endl;
    cout << "TIME ELAPSED" << endl;
    cout << "[BST]        : " << fixed << t_tree << " sec" << endl;
    cout << "[Hashing]    : ";
    if (!hash_flag)
      cout << fixed << t_hash << " sec" << endl;
    else
      cout << "N/A - Student not in hash table (full bucket)." << endl;
    cout << "[Vector]     : " << fixed << t_vect << " sec" << endl;
    return true;
  }
  
  return false;
}

/**
 *	-	Controller_Mngr::_table_displayMngr()
 *
 *	Logic : Call the private method to display
 *	the content of the hash table
 *
 *	@ param: none
 *	@ return: void
 */
void Controller_Mngr::_table_displayMngr()	{
  cout << MSG_FRAME;
  cout << "* " << setw(64) << left
  << "You have chosen to display entire hash table." << "*";
  cout << MSG_FRAME;
  //hTable->_show_tableContent(cout);	// Call hashtable member func
  hTable->_show_hash_table_prettyPrint(cout);
}

/**
 *	-	Controller_Mngr::_display_sortedKey_Mngr()
 *
 *	Logic : Call the private method to display
 *	the content of the hash table in sorted order
 *
 *	@ param: none
 *	@ return: void
 */
void Controller_Mngr::_display_sortedKey_Mngr()	{
  cout << MSG_FRAME;
  cout << "* " << setw(64) << left
  << "You have chosen to display students in sorted student ID sequence."
  << "*";
  cout << MSG_FRAME;
  //hTable->_show_hash_table_prettyPrint(cout);	// Call hashtable member func
  bsTree->_inOrder_print(cout);
}

/**
 *	-	Controller_Mngr::_tree_displayMngr()
 *
 *	Logic : Call the private method to display
 *	the Binary Search Tree
 *
 *	@ param: none
 *	@ return: void
 */
void Controller_Mngr::_tree_displayMngr()	{
	cout << MSG_FRAME;
	cout << "* " << setw(64) << left
  << "You have chosen to display the binary search tree." << "*";
  cout << MSG_FRAME;
	bsTree->pretty_print(cout);
}

/**
 *	-	Controller_Mngr::_statistics_Mngr()
 *
 *	Logic : Call the private method to display statistics
 *	about the hash table
 *
 *	@ param: none
 *	@ return: void
 */
void Controller_Mngr::_statistics_Mngr()
{
  cout << MSG_FRAME;
  cout << "* " << setw(64) << left
  << "You have chosen to show the statistics about the hash table." << "*";
  cout << MSG_FRAME;
  hTable->_display_hashTable_status(cout);			// Calling hash member func
  
  cout << MSG_FRAME;
}

/**
 *	+	Controller_Mngr::_write_Mngr()	: void
 *
 *	Simple Call :
 *		+	  _writeout_helper(): void
 */
void Controller_Mngr::_write_Mngr()
{
  cout << MSG_FRAME;
  cout << "* " << setw(64) << left
  << "You have chosen to wrtie database to an output file." << "*";
  cout << MSG_FRAME;
  _writeout_helper();			// Call this to write to output file...
  
  cout << MSG_FRAME;
}


/**
 *	-	Controller_Mngr::_menu_Mngr()
 *
 *	Logic : Call the private method to show the menu
 *
 *	@ param: none
 *	@ return: void
 */
void Controller_Mngr::_menu_Mngr()
{
  cout << MSG_FRAME;
  cout << "* " << setw(64) << left
  << "You have chosen to show menu." << "*";
  cout << MSG_FRAME;
  
  _menu();		// Call Menu here...
  
  cout << MSG_FRAME;
}


/**
 *	-	Controller_Mngr::_quit_Mngr(bool &exit_flag)
 *
 *	Logic : Change the received parameter to false and return it
 *	to quit the program
 *
 *	@ param: exit_flag: bool &
 *	@ return: bool
 */

bool Controller_Mngr::_quit_Mngr(bool &exit_flag)
{
	exit_flag = false;
  string file_name = OUTPUT_FILE;
  cout << MSG_FRAME;
  cout << "* " << setw(64) << left
  << "You have chosen to quit the program." << "*";
  cout << MSG_FRAME;
  
  // AUTO - WRITE TO OUTPUT FILE
  ofstream outFile;
	outFile.open(file_name.c_str());
  while (!outFile){
    cin.clear();
    cin.ignore(80, '\n');
    cout << "Problem opening output file.\n";
    cout << "Please provide a file to output data to: ";
    cin >> file_name;
    outFile.open(file_name.c_str());
  }
  
  fReader->_display_contents_in_vector(outFile);
  cout << "Data written to " << file_name << endl;
  
  outFile.close();
  
  return exit_flag;
}

/**
 *	-	Controller_Mngr::_frequency_Mngr()
 *
 *	Logic : Display the heap with the most frequently request
 *
 *	@ param: none
 *	@ return: void
 */
void Controller_Mngr::_frequency_Mngr()
{
  // testing
  //heapArr->_display();
  
  cout << MSG_FRAME;
  cout << "* " << setw(64) << left
  << "You have chosen to show students by the most searched frequency." << "*";
  cout << MSG_FRAME;
  cout << "\n\tSEARCH HISTORY TABLE (HIGHEST TO LOWEST # OF SEARCHES)\n\n";
  cout << MSG_FRAME;
  
  heapArr->_show_topTen(cout);
  cout << endl;
}

/*
 *	+	Controller_Mngr::_remove_Mngr()	: void
 *
 *	Call :
 *					_read_sdtID_from_usr(stu_id : string)
 *					_delete_Data(stu_id : string ,stu_delete : Student*)
 *
 */
void Controller_Mngr::_remove_Mngr()
{
  string stu_id ;
  Data* stu_delete = NULL;
  
  cout << MSG_FRAME;
  cout << "* " << setw(64) << left
  << "You have chosen to delete a student in database." << "*";
  cout << MSG_FRAME;
  cout << "\n\tTo delete please enter the Student ID (8 characters):\n\n";
  
	//Validate user input
  if(_read_sdtID_from_usr(stu_id))	{
    if (!_delete_Data(stu_id, stu_delete))		//Call this to delete
      cout << "Student not found, try again?\n";
  }
	else{
    cout << "You have chosen to not delete a student.";
  }
	cout << MSG_FRAME;
  stu_delete = NULL;
}

/**
 *	-	Controller_Mngr::_delete_Data(string student_ID,Data* _Student)
 *
 *	Logic : Delete data from the Hash Table & BST
 *
 *	@ param: student_ID - string, _Student - Data*
 *	@ return: bool
 */
bool Controller_Mngr::_delete_Data(string student_ID,Data* _Student)
{
	bool flag_tree,  flag_table;
  Student *del_from_BST  = bsTree->remove(student_ID);
  Student *del_from_Hash = hTable->_delete_node(student_ID);
  
  if(del_from_BST == del_from_Hash && del_from_Hash && del_from_BST){
    cout << "Deleted the student object from both Binary Search Tree and the ";
    cout << "Hash Table." << endl;
    flag_tree = flag_table = true;
    fReader->_lazy_deletion(student_ID);
  }
  else if(del_from_BST && !del_from_Hash){
    cout << "Deleted the student object from Binary Search Tree but failed to ";
    cout << "find the student object in Hash Table" << endl;
    flag_tree  = true;
    flag_table = false;
    fReader->_lazy_deletion(student_ID);
  }
  else if(!del_from_BST && del_from_Hash){
    cout << "Deleted the student object from Hash Table but failed to find the ";
    cout << "student object in the BST" << endl;
    flag_tree  = false;
    flag_table = true;
    fReader->_lazy_deletion(student_ID);
  }
  else{
    cout << "Failed to delete the student object in both the Binary Search Tree";
    cout << " and Hash Table" << endl;
    flag_tree = flag_table = false;
  }
  del_from_BST  = NULL;
  del_from_Hash = NULL;
	return (flag_tree || flag_table);
}

/*	SET OF WRITE METHOD:
 *
 *	+	 Controller_Mngr::_writeout_helper()	: void
 *
 *	Call member function :
 *	+	Controller_Mngr::_write_to_outFile(ostream &outputFile)	: bool
 *		To write the data to output
 */
void  Controller_Mngr::_writeout_helper()
{
	ofstream outFile;
  string file_name = OUTPUT_FILE; // default output file
	outFile.open(file_name.c_str());
  while (!outFile){
    cin.clear();
    cin.ignore(80, '\n');
    cout << "Problem opening output file.\nPlease provide a file to output data to: ";
    cin >> file_name;
    outFile.open(file_name.c_str());
  }
  
  fReader->_display_contents_in_vector(outFile);
  cout << "Write successful!";
  
  outFile.close();
}

/**
 *	-	Controller_Mngr::_addMngr()
 *
 *	Logic : Call the private method to add new data
 *
 *	@ param: none
 *	@ return: void
 */
void Controller_Mngr::_addMngr()
{
  cout << MSG_FRAME;
  cout << "* " << setw(64) << left
  << "You have chosen to add a new student to the database" << "*";
  cout << MSG_FRAME;
  
  Student* new_stu = _new_student();
  if (new_stu) {
    _read_student_info(new_stu);	// Add new Student here
    cout << "New student successfully added!";
  }
  else
    cout << "You have chosen to not create a new student.";
  
  cout << MSG_FRAME;
}

/**
 *	-	Controller_Mngr::_read_student_info(Student* new_sdt)
 *
 *	Logic : Insert the given student data into the Vector, BST, and Hash table
 *
 *	@ param: new_sdt - Student*
 *	@ return: void
 */
void Controller_Mngr::_read_student_info(Student* new_sdt)
{
  Data *newData = new Data(new_sdt);
  if(fReader->_insert_toVector(newData)){
    bsTree->insert(newData->_get_studentObj());
    hTable->_add_to_table(newData->_get_studentObj(),cout);
    heapArr->_push(newData);
  }
  else{
    cout << endl;
    cout << "********************************************" << endl;
    cout << "*  Student ID already exists,  Try again?  *" << endl;
    cout << "********************************************" << endl;
  }
}


/**
 *	-	Controller_Mngr::_new_student()
 *
 *	Logic : Allocate a new student
 *
 *	@ param: none
 *	@ return: Student
 */
Student* Controller_Mngr::_new_student()
{
	string student_id,full_name,phone_num,birthday;
  
  // If student decides to quit on any of the following input,
  // return NULL
	if (!(_read_sdtID_from_usr(student_id)))
    return NULL;
	if (!(_read_sdt_Input_from_usr(full_name,"full name", 3 , 20)))
    return NULL;
	if (!(_read_sdt_Input_from_usr(phone_num,"phone number", 8, 12)))
    return NULL;
	if (!(_read_sdt_Input_from_usr(birthday,"birthyear", 4, 4)))
    return NULL;
  
  // Allocate a new student
	Student *stu = new Student(student_id, full_name, phone_num, birthday);
  // Return the newly allocated student
	return stu;
}
