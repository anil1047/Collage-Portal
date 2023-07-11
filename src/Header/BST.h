//
//  BST.h
//  Final_project
//
//  Created by YIEN LIN, TRUC HUYNH on 6/19/14.
//  Copyright (c) 2014 YIEN LIN, TRUC HUYNH. All rights reserved.
//

#ifndef __Final_project__BST__
#define __Final_project__BST__

#include <iostream>
#include <iomanip>
#include "Header/Data.h"

using namespace std;



class BST
{
private:
  
  struct BST_Node
  {
    Student *data;     // The value in this node
    BST_Node *left;    // To point to the left node
    BST_Node *right;   // To point to the right node
  };
  
  BST_Node *root;        // root of the tree
  int count;             // number of nodes in the tree
  
public:
  // Constructor
  BST();
  
  // Destructor
  ~BST();
  
  // Binary Tree operations
  void     insert   (Student *);
  Student* remove   (string);
  bool     search   (string, Student *&) const;
  
  // Print tree operations
  void      pretty_print    (ostream &)    const;
  void      _inOrder_print  (ostream &)    const;
  int       get_count       ()             const { return count; }
  BST_Node* get_root        ()                   { return root; }
  
private:
  BST_Node* _search         (string)                          const;
  BST_Node* _remove         (BST_Node *, string, Student *&);
  void      _destroy        (BST_Node *);
  void      _pretty_print   (BST_Node *, int, ostream &)      const;
  BST_Node* _get_successor  (BST_Node *)                      const;
  void      _r_inOrder      (BST_Node *, ostream &)           const;
};

#endif /* defined(__Final_project__BST__) */
