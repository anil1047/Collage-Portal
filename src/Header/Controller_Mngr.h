//
//  Controller_Mngr.h



#ifndef __Final_project__Controller_Mngr__
#define __Final_project__Controller_Mngr__

// ********************************************************
// CONTROLLER MANAGER
// Controller_Mngr.h
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

#include <iostream>
#include "Header/Data.h"
#include "Header/Hash_Table.h"
#include "Header/Heap.h"
#include "Header/File_reader.h"
#include "Header/BST.h"
#include "time.h"
#include "math.h"
#include <string>
#include <vector>
#include <cstdlib> // atoi
#define FRAME "###############################################################################"
#define MSG_FRAME "\n*******************************************************************\n"
#define INPUT_FILE "/Users/yienlin/Desktop/C++/Re_Hashing/Re_Hashing/student_id_info.txt"

//const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "/Users/yienlin/Desktop/output.txt";

using namespace std;

class Controller_Mngr
{
private:
	BST         *bsTree;
	Hash_Table  *hTable;
	File_reader *fReader;
  Heap        *heapArr;
  
public:
	Controller_Mngr	 ();
	~Controller_Mngr ();
	
  void _task_Mngr	 ();
  
private:
  
	// BUILDING TREE, TABLE
	string _read_fileName_fromUsr	();
	void _initialization			();
  
	//	HELPER MEMBER FUNCTIONS	:
	bool _read_sdtName_from_usr		(string &);
	bool _read_sdtPhone_from_usr	(string &);
	bool _read_sdtBirth_from_usr	(string &);
	void _greetingMsg				      ();
	void _farewellMsg				      ();
	bool _read_usrInput				    (char &);
	char _change_to_upper			    (char);
	bool _usr_validation			    (char);
	bool _read_sdtID_from_usr		  (string &);
	bool _read_sdt_Input_from_usr	(string &, string, unsigned int, unsigned int);
  bool _delete_Data				      (string, Data *);
	bool _find_and_display			  (string, Data *&);
	void _writeout_helper			    ();
	void _read_student_info			  (Student *);
	Student* _new_student			    ();
	void _print_no_delete			    ();
	void _print_and_delete			  ();
  
	// MAIN METHOD METHOD:
	void _menu				            () const;
	void _addMngr			            ();                 // A
	void _remove_Mngr		          ();					        // D
	void _searchMngr		          ();					        // S
  void _frequency_Mngr			    ();					        // F
	void _table_displayMngr			  ();					        // H
	void _display_sortedKey_Mngr	();					        // K
	void _tree_displayMngr			  ();					        // I
	void _statistics_Mngr			    ();					        // X
	void _write_Mngr				      ();					        // W
	void _menu_Mngr					      ();					        // M
	bool _quit_Mngr					      (bool &exit_flag);	// Q
  void _deleted_display         ();                 // Y
  void _restore_Mngr            ();                 // U
};

#endif /* defined(__Final_project__Controller_Mngr__) */
