//
//  Hash_Table.h


#ifndef __Final_project__Hash_Table__
#define __Final_project__Hash_Table__

#include <iostream>
#include <iomanip>
#include "Header/Data.h"


const int DEFAULT_BUCKET_SIZE = 3;

// ADT - INDICATES EACH ELEMENT IN HASH TABLE
struct hash_bucket
{
  int      occupied_bucket;
  Student *bucket[DEFAULT_BUCKET_SIZE];
};  // END STRUCT

class Hash_Table
{
private:
  int tableSize;
  int occupied_count;
  int full_bucket_count;
  int valid_count;
  int overflow_count;
  int delete_count;
  int collision_count;
  
  hash_bucket *hashTable;
  
  int          _get_prime_number (int);
  unsigned int _get_hashKey      (const string &);
  
  void _show_bucket              (const hash_bucket &, ostream &, int &);
  void _show_bucket_prettyPrint  (const hash_bucket &, ostream &);
  void _reHashing                ();
  
public:
  Hash_Table  (int);
  ~Hash_Table ();
  
  void      _add_to_table                (Student *, ostream &);
  void      _show_tableContent           (ostream &);
  void      _show_hash_table_prettyPrint (ostream &);
  bool      _search_by_studentID         (string &, Student *&);
  Student * _delete_node                 (string &);
  
  // TESTING
  void _display_hashTable_status (ostream &);
  int _get_count                 ();
  
  hash_bucket *_get_hashTable_ptr    () const;
  int          _get_tableSize        () const;
  int          _get_occupiedCount    () const;
  int          _get_full_bucketCount () const;
};

#endif /* defined(__Final_project__Hash_Table__) */
