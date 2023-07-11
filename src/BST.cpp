//
//  BST.cpp


#include "BST.h"

/**
 * BST for STUDENT INFORMATION DATABASE€
 */

/**
 * BST Constructor
 */
BST::BST()
{
	root = NULL;
	count = 0;
}

/**
 * Inserts data into the BST
 * @param student - data type to be inserted
 */
void BST::insert(Student *obj)
{
	BST_Node *newNode;
	BST_Node *pWalk;
	BST_Node *parent = NULL;
  
	// allocate the new node
	newNode = new BST_Node;
	newNode->data = obj;
	newNode->left = NULL;
	newNode->right = NULL;
  
	if (!root) // tree is empty
		root = newNode;
	else 
    
	{
		pWalk = root;
		while (pWalk)
		{
			parent = pWalk;
			if (obj->_get_studentID() <
          pWalk->data->_get_studentID())
				pWalk = pWalk->left;
			else
				pWalk = pWalk->right;
		}
    
		// insert the new node
		if (obj->_get_studentID() <
        parent->data->_get_studentID()) // no left child
			parent->left = newNode;
		else
			parent->right = newNode;
	}
	// Update node count
	count++;
}


/**
 * BST Destructor
 */
BST::~BST()
{
	if (root)
		_destroy(root);
}

/**
 * BST::_destroy
 * Traverses the BST in postorder and deletes every node in
 * the tree
 */
void BST::_destroy(BST_Node *root)
{
	if (root)
	{
		_destroy(root->left);
		_destroy(root->right);
		delete root;
	}
	return;
}


/**
 * BST::search
 * Searches a BST for a given target. Updates data when found,
 * returns true if found, false otherwise.
 * @param  target - search for target
 * @param  data   - pointer to be updated (address) of target found
 *                  unchanged if not found.
 * @return        - true if found, false if not found
 */
bool BST::search(string target, Student* &data) const
{
	BST_Node *found = _search(target);
	if (found != NULL) {
		data = found->data;
		return true;
	}
	return false;
}


/**
 * BST::_search
 * Locates the node that contains a given target
 * @param  target - search for target
 * @return        - returns a pointer if found
 */
BST::BST_Node* BST::_search(string target) const
{
	if (!root) // tree is empty
		return NULL;
  
	// tree is not empty
	BST_Node *pWalk = root;
	while (pWalk)
	{
		if (target < pWalk->data->_get_studentID())
			pWalk = pWalk->left;
		else
      if (target > pWalk->data->_get_studentID())
        pWalk = pWalk->right;
      else
        return pWalk; // found
	}
  
	return NULL; // not found
}


/**
 * BST::pretty_print
 * Calls a recursive function to print the tree
 */
void BST::pretty_print(ostream &out) const
{
	if (root)
		_pretty_print(root, 0, out);
}

/**
 * BST::_pretty_print
 * Recursively traverses the tree to print the data
 * as a sideways tree.
 *     Right - Print - Left
 * @param treeNode - incoming node to traverse
 * @param indent   - indent/spacing for printing tree
 */
void BST::_pretty_print(BST_Node* treeNode, int indent, ostream &out) const
{
	// Keep track of level to print
	static int level = 1;
  
	if (treeNode != NULL) {
		level++;
		_pretty_print(treeNode->right, indent + 8, out);
		level--;
		if (indent)
			out << setfill(' ') << setw(indent) << " ";
		out << level << ". "
    << treeNode->data->_get_studentID() << endl;
		level++;
		_pretty_print(treeNode->left, indent + 8, out);
		level--;
	}
}

/**
 * BST::remove
 * @param  target - target data to find for node removal
 * @return        - the address of the removed node's data
 *                  returns NULL if not found and deleted
 */
Student* BST::remove(string target)
{
	Student *save = NULL;
	_remove(root, target, save);
  
	return save;
}

/**
 * BST::_remove
 * Removes a node from the BST tree and returns the address of the
 * Student data of the removed node.
 *
 * In case of the removal of a parent node  with two children, its
 * successor (the data from the node which will replace it) will be
 * found from the largest data of the left subtree.
 *
 * @param  node   - current node to compare its data with target
 * @param  target - target data to find for node removal
 * @param  save   - address of Student to be updated if deleted,
 *                  NULL if not found
 * @return        - the address of a new child for a parent node
 *                  (target "parent" node is deleted, "grandchild"
 *                  node becomes "child" node)
 */
BST::BST_Node* BST::_remove(BST_Node *node, string target, Student *&save)
{
	if (node == NULL)
		return node;
  
	if (node->data->_get_studentID() == target) {
		save = node->data;
		BST_Node *return_val = NULL;
    
		if (node->left == NULL) {
			return_val = node->right;
			if (node == root)
				root = node->right;
			delete node;
			return return_val;
		}
		else if (node->right == NULL) {
			return_val = node->left;
			if (node == root)
				root = node->left;
			delete node;
			return return_val;
		}
		else {
			// Successor
			BST_Node *successor = _get_successor(node->left);
			// Move the data of the successor node to its new position,
			// and delete the old position (old node)
			node->left = _remove(node->left,
                           successor->data->_get_studentID(), node->data);
		}
	}
	else if (target < node->data->_get_studentID()) {
		node->left = _remove(node->left, target, save);
	}
	else {
		node->right = _remove(node->right, target, save);
	}
  
	return node;
}

/**
 * BST::get_successor
 * @param  node - left subtree node
 * @return      - left subtree's largest node
 */
BST::BST_Node* BST::_get_successor(BST_Node *node) const
{
	while (node->right != NULL)
		node = node->right;
	return node;
}

/**
 *
 */
void BST::_inOrder_print(ostream &os) const
{
  if(!root) {  // EMPTY TREE
    os << "Error! Can't not access the data. Something went wrong." << endl;
    return;
  }
  else{ // THERE ARE SOMETHING TO PRINT
    _r_inOrder(root, os);
  }
  os << endl;
}

/**
 *
 */
void BST::_r_inOrder(BST_Node *rt, ostream &out) const
{
  if(rt) {
    _r_inOrder(rt->left, out);
    // ACCESSING THE DATA OF THE TreeNode
    out << rt->data->_get_studentID() << " : ";
    out << rt->data->_get_fullName()  << endl;
    out << "-------------------------------------------" << endl;
    _r_inOrder(rt->right, out);
  }
}
