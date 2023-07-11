//
//  Hash_Table.cpp


#include "Header/Hash_Table.h"

/**
 * CONSTRUCTOR
 *-----------------------------------------------------------------------------*
 * PRIVATE MEMBER FUNCTION : Hash_Table()                                      *
 * PRE-CONDITION           : tSize HAD BEEN ASSIGNED WITH POSITIVE VALUE       *
 * POST-CONDITION          : THE HASH TABLE HAD BEEN INITIALIZED               *
 * PARAMETER               : tSize(int)                                        *
 * REFERENCE PARAMETER     : NONE                                              *
 * RETURN VALUE            : NONE                                              *
 *-----------------------------------------------------------------------------*
 * FIRST GET PRIME NUMBER FROM PRIVATE MEMBER FUNCTION _get_prime_number, THEN *
 * ASSIGN IT TO tableSize. AND ASSIGN ZERO TO THE REST OF int ATTRIBUTES. THE  *
 * LAST STEP IS TO DYNAMICALLY ALLOCATE AN ARRAY WITH SIZE (tableSize), AND    *
 * INITIALIZE THE STRUCT hash_bucket WITH NULL VALUE AND ZERO.                 *
 *-----------------------------------------------------------------------------*
 */
Hash_Table::Hash_Table(int tSize)
{
  tableSize = _get_prime_number(tSize);
  occupied_count = 0;
  full_bucket_count = 0;
  
  // NOT SURE
  valid_count = overflow_count = delete_count = collision_count = 0;
  
  hashTable = new hash_bucket[tableSize];
  for(int i = 0; i < tableSize; i++){
    hashTable[i].occupied_bucket = 0;
    for(int j = 0; j < DEFAULT_BUCKET_SIZE; j++){
      hashTable[i].bucket[j] = NULL;
    } // END INNER FOR LOOP
  } // END OUTER FOR LOOP
} // END CONSTRUCTOR

/**
 * DESTRUCTOR
 *-----------------------------------------------------------------------------*
 * PRIVATE MEMBER FUNCTION : ~Hash_Table()                                     *
 * PRE-CONDITION           : NONE                                              *
 * POST-CONDITION          : DYNAMICALLY ALLOCATED ARRAY WILL BE DELETED       *
 * PARAMETER               : NONE                                              *
 * REFERENCE PARAMETER     : NONE                                              *
 * RETURN VALUE            : NONE                                              *
 *-----------------------------------------------------------------------------*
 * SIMPLY JUST DE-ALLOCATED THE MEMORY WE DYNAMICALLY ALLOCATED EARLIER        *
 *-----------------------------------------------------------------------------*
 */
Hash_Table::~Hash_Table()
{
  delete[] hashTable;
}

/**
 * PRIVATE MEMBER FUNCTIONS
 */

/**
 *-----------------------------------------------------------------------------*
 * PRIVATE MEMBER FUNCTION : _get_prime_number                                 *
 * PRE-CONDITION           : size HAD BEEN ASSIGNED WITH VALUE                 *
 * POST-CONDITION          : THE RETURN VALUE WILL BECOME NEW TABLE SIZE       *
 * PARAMETER               : size(int)                                         *
 * REFERENCE PARAMETER     : NONE                                              *
 * RETURN VALUE            : num(int)                                          *
 *-----------------------------------------------------------------------------*
 * TESTING NUMBER WILL BE DIVIDED BY ALL NUMBERS FROM 1 TO TESTING NUMBER, AT  *
 * THE SAME TIME, COUNTING THE SCENARIO THAT THE REMAINDER OF DIVISION EQUALS  *
 * TO 0. IF THE NUMBER OF THE COUNT EQUALS TO TWO, THEN THE TESTING NUMBER IS  *
 * A PRIME NUMBER. THEREFORE, RETURN IT. IF THE COUNT IS NOT EQUAL TO TWO,     *
 * TESTING THE NEXT FOLLOWING NUMBER.                                          *
 *-----------------------------------------------------------------------------*
 */
int Hash_Table::_get_prime_number(int size)
{
  int num = size * 2;
  while(true){
    int count = 0;
    for(int i = 1; i <= num; i++){
      if(num%i == 0){
        count++;
      }
    } // END FOR LOOP
    if(count == 2){ // IS A PRIME NUMBER
      return num;
    }
    else{
      num++;
    }
    
  } // END WHILE LOOP
}

/**
 *-----------------------------------------------------------------------------*
 * PRIVATE MEMBER FUNCTION : _get_hashKey()                                    *
 * PRE-CONDITION           : idNum HAS BEEN ASSIGNED A VALID VALUE             *
 * POST-CONDITION          : A HASH KEY WILL BE GENERATED                      *
 * PARAMETER               : idNum(string &)                                   *
 * REFERENCE PARAMETER     : NONE                                              *
 * RETURN VALUE            : A VALUE(HASH KEY)(unsigned int)                   *
 *-----------------------------------------------------------------------------*
 * I TRIED TO PRACTICE THE BITWISE OPERATORS. THIS HASH FUNCTION IS INVENTED   *
 * BY THOMAS WANG. THIS METHOND CAN EFFICIENTLY AND EVEN-RANDOMLY SPREAD KEYS  *
 *-----------------------------------------------------------------------------*
 */
unsigned int Hash_Table::_get_hashKey(const string &idNum)
{
  unsigned int address = static_cast<unsigned int>(atoi(idNum.c_str()));
  
  int first_half  = address     / 10000;
  int second_half = address     % 10000;
  int first_f     = first_half  / 100;
  int second_f    = first_half  % 100;
  int first_s     = second_half / 100;
  int second_s    = second_half % 100;
  
  address = (first_f + second_f + first_s + second_s) *
  (first_half + second_half);
  
  return address % tableSize;
}

/**
 *-----------------------------------------------------------------------------*
 * PRIVATE MEMBER FUNCTION : _show_bucket()                                    *
 * PRE-CONDITION           : hBucket HAS AT LEAST ONE STUDENT POINTER          *
 * POST-CONDITION          : NOTHING CHANGED                                   *
 * PARAMETER               : hBucket(const hash_bucket &), out(ostream &)      *
 * REFERENCE PARAMETER     : counter(int &)                                    *
 * RETURN VALUE            : void                                              *
 *-----------------------------------------------------------------------------*
 * SIMEPLY PRINT OUT ALL STUDENT OBJECT IN THE BUCKET                          *
 *-----------------------------------------------------------------------------*
 */
void Hash_Table::_show_bucket(const hash_bucket &hBucket,
                              ostream &out, int &counter)
{
  for(int i = 0; i < hBucket.occupied_bucket; i++){
    out << "[" << setw(3) << counter << "] : ";
    out << hBucket.bucket[i]->_get_studentID() << " - ";
    out << hBucket.bucket[i]->_get_fullName()  << endl;
    counter++;
  }
}

/**
 *-----------------------------------------------------------------------------*
 * PRIVATE MEMBER FUNCTION : _show_bucket_prettryPrint()                       *
 * PRE-CONDITION           : hBucket HAS AT LEAST ONE STUDENT POINTER          *
 * POST-CONDITION          : NOTHING CHANGED                                   *
 * PARAMETER               : hBucket(const hash_bucket &), out(ostream &)      *
 * REFERENCE PARAMETER     : NONE                                              *
 * RETURN VALUE            : void                                              *
 *-----------------------------------------------------------------------------*
 * SIMEPLY PRINT OUT ALL STUDENT OBJECT IN THE BUCKET, PRINT EMPTY STRING IF   *
 * THE POINTER IN BUCKET IS POINTING TO NULL                                   *
 *-----------------------------------------------------------------------------*
 */
void Hash_Table::_show_bucket_prettyPrint(const hash_bucket &hBucket,
                                          ostream &out)
{
  string location = "Location ";
  for(int i = 0; i < DEFAULT_BUCKET_SIZE; i++){
    // THE FOLLOWING STATEMENT IS DETERMINING IF INDENTION NECCESSARY
    (i == 0) ? out << setw(3)  << right << location << i << " : "
    : out << setw(31) << right << location << i << " : ";
    
    // CHECK IF IT'S EMPTY
    if(hBucket.bucket[i] != NULL){
      out << hBucket.bucket[i]->_get_studentID() << " - ";
      out << hBucket.bucket[i]->_get_fullName()  << endl;
    }
    else{
      out << "" << endl;
    }
  }
}

/**
 * PUBLIC MEMBER FUNCTION
 */

/**
 *-----------------------------------------------------------------------------*
 * PRIVATE MEMBER FUNCTION : _add_to_table()                                   *
 * PRE-CONDITION           : sdt_in HOLDS VALID ADDRESS OF A STUDENT OBJECT    *
 *                           out STORES A VALID OSTREAM OBJECT                 *
 * POST-CONDITION          : EITHER HASH TABLE GET ONE MORE ELEMENT OR AN      *
 *                           OBJECT GOT DUMPED                                 *
 * PARAMETER               : sdt_in(Student *), out(ostream &)                 *
 * REFERENCE PARAMETER     : NONE                                              *
 * RETURN VALUE            : void                                              *
 *-----------------------------------------------------------------------------*
 * FIRST, GET THE HASH KEY THAT CORRESPONDING TO THE STUDENT ID NUMBER. THEN,  *
 * CHECK IS THE SPECIFIC BUCKET(ACCORDING TO HASH KEY) FULL OR NOT. IF IT IS   *
 * FULL, THEN PROMPT THE MESSAGE AND THEN DUMP THE DATA. IF IT IS NOT FULL,    *
 * THEN, INSERT INTO BUCKET.                                                   *
 *-----------------------------------------------------------------------------*
 */
void Hash_Table::_add_to_table(Student *sdt_in, ostream &out)
{
  unsigned int hashKey =
  _get_hashKey(sdt_in->_get_studentID());
  
  if(hashTable[hashKey].occupied_bucket == DEFAULT_BUCKET_SIZE){// FULL BUCKET
    out << endl;
    out << "--------------------------------------------------------" << endl;
    out << "[BUCKET FULL - " << hashKey << " ] : DUMPING INPUT!"      << endl;
    out << sdt_in->_get_studentID()                                   << endl;
    out << "--------------------------------------------------------" << endl;
    out << endl;
    
    overflow_count++;
  }
  else{ // BUCKET IS NOT FULL
    if(hashTable[hashKey].occupied_bucket == 0){  // EMPTY BUCKET
      hashTable[hashKey].bucket[0] = sdt_in;
      occupied_count++;
      hashTable[hashKey].occupied_bucket++;
    }
    else{ // BUCKET IS NOT EMPTY NOR FULL
      hashTable[hashKey].bucket[hashTable[hashKey].occupied_bucket] = sdt_in;
      if(hashTable[hashKey].occupied_bucket == 2){  // WILL BE FULL
        hashTable[hashKey].occupied_bucket++; // INCREMENT TO 3
        full_bucket_count++;
      }
      else{ // STILL NOT FULL
        hashTable[hashKey].occupied_bucket++;
      }
      collision_count++;
    } // END OUTER IF-ELSE STATEMENT
    valid_count++;
  }
}

/**
 *-----------------------------------------------------------------------------*
 * PRIVATE MEMBER FUNCTION : _show_tableContent()                              *
 * PRE-CONDITION           : out STORES A VALID OSTREAM OBJECT                 *
 * POST-CONDITION          : NOTHING CHANGED                                   *
 * PARAMETER               : out(ostream &)                                    *
 * REFERENCE PARAMETER     : NONE                                              *
 * RETURN VALUE            : void                                              *
 *-----------------------------------------------------------------------------*
 * ITERATE WHOLE TABLE AND PRINT ALL THE STUDENT OBJECTS                       *
 *-----------------------------------------------------------------------------*
 */
void Hash_Table::_show_tableContent(ostream &out)
{
  int counter = 1;
  for(int i = 0; i < tableSize; i++){
    if(hashTable[i].occupied_bucket != 0){  // IF THE BUCKET IS NOT EMPTY
      _show_bucket(hashTable[i], out, counter);
    }
  } // END FOR LOOP
}

/**
 *-----------------------------------------------------------------------------*
 * PRIVATE MEMBER FUNCTION : _show_hash_table_prettyPrint()                    *
 * PRE-CONDITION           : out STORES A VALID OSTREAM OBJECT                 *
 * POST-CONDITION          : NOTHING CHANGED                                   *
 * PARAMETER               : out(ostream &)                                    *
 * REFERENCE PARAMETER     : NONE                                              *
 * RETURN VALUE            : void                                              *
 *-----------------------------------------------------------------------------*
 * SIMPLY PRINT THE BUCKET NUMBER AND CALL ANOTHER PRIVATE MEMBER FUNCTION TO  *
 * PRINT OUT THE CONTENTS OF THAT BUCKET                                       *
 *-----------------------------------------------------------------------------*
 */
void Hash_Table::_show_hash_table_prettyPrint(ostream &out)
{
  for(int i = 0; i < tableSize; i++){
    out << "[BUCKET - " << setw(3) << i << " ] : ";
    _show_bucket_prettyPrint(hashTable[i], out);
  }
}

/**
 *-----------------------------------------------------------------------------*
 * PRIVATE MEMBER FUNCTION : _search_by_studentID()                            *
 * PRE-CONDITION           : id(string &) IS VALID                             *
 * POST-CONDITION          : IF FOUND, copy_sdt OCCUPIED WITH STUDENT INFO     *
 *                           IF NOT FOUND, copy_sdt NOT OCCUPIED               *
 * PARAMETER               : id(string &)                                      *
 * REFERENCE PARAMETER     : copy_sdt(Student *&)                              *
 * RETURN VALUE            : bool                                              *
 *-----------------------------------------------------------------------------*
 * FIND MATCH, RETURN TRUE IF FOUND, ELSE, RETURN FALSE                        *
 *-----------------------------------------------------------------------------*
 */
bool Hash_Table::_search_by_studentID(string &id, Student *&copy_sdt)
{
  unsigned int hashKey = _get_hashKey(id);
  
  if(hashTable[hashKey].occupied_bucket != 0){
    for(int i = 0; i < hashTable[hashKey].occupied_bucket; i++){
      if(hashTable[hashKey].bucket[i]){
        if(hashTable[hashKey].bucket[i]->_get_studentID() == id){
          copy_sdt = hashTable[hashKey].bucket[i];
          return true;
        } // END IF
      } // END IF
    } // END FOR LOOP
    return false;
  }
  else{
    return false;
  }
}

/**
 *-----------------------------------------------------------------------------*
 * PRIVATE MEMBER FUNCTION : _display_hashTable_status()                       *
 * PRE-CONDITION           : out STORES A VALID OSTREAM OBJECT                 *
 * POST-CONDITION          : NOTHING CHANGED                                   *
 * PARAMETER               : out(ostream &)                                    *
 * REFERENCE PARAMETER     : NONE                                              *
 * RETURN VALUE            : void                                              *
 *-----------------------------------------------------------------------------*
 * SIMPLY PRINT OUT THE STATUS OF THE HASH TABLE                               *
 *-----------------------------------------------------------------------------*
 */
void Hash_Table::_display_hashTable_status(ostream &out)
{
  out << "[HASH TABLE STATUS] : " << endl;
  out << "NUMBER OF VALID ELEMENTS IN TABLE : " << valid_count        << endl;
  out << "NUMBER OF DUMPED ELEMENTS         : " << overflow_count     << endl;
  out << "SIZE OF THE HASH TABLE            : " << tableSize          << endl;
  out << "NUMBER OF COLLISIONS              : " << collision_count    << endl;
  out << "NUMBER OF FULL BUCKETS            : " << full_bucket_count  << endl;
  out << "NUMBER OF OCCUPIED BUCKETS        : " << occupied_count     << endl;
  out << "LOAD FACTOR                       : "
  << setprecision(2) << fixed << showpoint
  << (occupied_count / static_cast<double>(tableSize)) * 100 << "%" << endl;
}

/**
 *-----------------------------------------------------------------------------*
 * PRIVATE MEMBER FUNCTION : _delete_node()                                    *
 * PRE-CONDITION           : id(string &) IS VALID                             *
 * POST-CONDITION          : IF FOUND, copy_sdt OCCUPIED WITH STUDENT INFO     *
 *                           AND DELETE FROM TABLE, IF NOT FOUND, copy_sdt NOT *
 *                           OCCUPIED                                          *
 * PARAMETER               : id(string &)                                      *
 * REFERENCE PARAMETER     : copy_sdt(Student &)                               *
 * RETURN VALUE            : Student *                                         *
 *-----------------------------------------------------------------------------*
 * FIND MATCH, DELETE THE MATCH AND RETURN TRUE IF FOUND, ELSE, RETURN FALSE   *
 *-----------------------------------------------------------------------------*
 */
Student *Hash_Table::_delete_node(string &sdt_id)
{
  Student *copy_sdt = NULL;
  unsigned int hashKey = _get_hashKey(sdt_id);
  
  if(hashTable[hashKey].occupied_bucket == 0){
    // NO MATCH
    return copy_sdt;
  }
  else{
    for(int i = 0; i < DEFAULT_BUCKET_SIZE; i++){
      if(hashTable[hashKey].bucket[i] &&
         hashTable[hashKey].bucket[i]->_get_studentID() ==
         sdt_id){
        // FOUND MATCH
        copy_sdt = hashTable[hashKey].bucket[i];
        hashTable[hashKey].bucket[i] = NULL;
        if(hashTable[hashKey].occupied_bucket == 1){
          hashTable[hashKey].occupied_bucket--;
          occupied_count--;
          delete_count++;
        }
        else{
          hashTable[hashKey].occupied_bucket--;
          delete_count++;
          int temp_index = hashTable[hashKey].occupied_bucket;
          if(i < temp_index){ // NEED TO SWAP
            hashTable[hashKey].bucket[i] =
            hashTable[hashKey].bucket[temp_index];
            hashTable[hashKey].bucket[temp_index] = NULL;
          } // END IF STATEMENT
        } // END IF-ELSE STATEMENT
        valid_count--;
      } // END IF STATEMENT - IF MATCH
    } // END FOR LOOP
    return copy_sdt; // NO MATCH FOUND
  } // END OUTER IF-ELSE STATEMENT - IF BUCKET EMPTY OR NOT
}

/**
 *  Hash_Table::_get_count
 *  THE HASH TALBE WOULD NOT KEEP TRACK THE TOTAL NUMBER OF ELEMENT COUNT
 *  ONLY CALCULATE IT WITH TABLE SIZE AND OCCUPIED BUCKET WHEN USER SENDS
 *  REQUESTS
 *
 *  @param  - NONE
 *  @return - INTEGER
 */
int Hash_Table::_get_count()
{
  int total_count = 0;
  for(int i=0; i<tableSize; i++){
    total_count += hashTable[i].occupied_bucket;
  } // END FOR LOOP
  return total_count;
}

/**
 *  ACCESSOR MEMBER FUNCTIONS
 *  PROVIDE METHOD TO LET USER TO ACCESS THE STORING ATTRIBUTES(STATUS)
 *
 *  @param  - NONE
 *  @return - DEPENDS ON WHAT KIND OF DATA TYPE
 */
hash_bucket *Hash_Table::_get_hashTable_ptr() const
{
  return hashTable;
}

int Hash_Table::_get_tableSize() const
{
  return tableSize;
}

int Hash_Table::_get_occupiedCount() const
{
  return occupied_count;
}

int Hash_Table::_get_full_bucketCount() const
{
  return full_bucket_count;
}

