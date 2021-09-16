//Kushendra Ramrup
//CSCI 335
//Professor Raja
//Assignment r Question 2 Part C

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
#include "sequence_map.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// Comparable contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order

//int tree_count_recursive( )  --> Counts the amount of nodes in the tree
//int GetInternalPathLength ( )  --> Calculates the internal path length of a tree
//bool contains_bool_version( const Comparable & x) --> Just the original boolean contains func
//float AverageDepth()  --> calculates average depth of a tree

//The two double rotation functions have been edited to implement double rotations directly instead of calling the two single rotations.
//Name your modified implementation avl_tree_p2c.h.
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root{ nullptr }
      { }

    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );

        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    Comparable contains( const Comparable & x, int *var ) const
    {
        return contains( x, root , var);
    }

    Comparable contains( const Comparable & x , float &count) const
    {
        return contains( x, root , ++count);
    }
    bool contains_bool_version( const Comparable & x) const {
      return contains_bool_version (x, root);
    }


    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /*Counts the amount of nodes in a avl tree */
    int tree_count( ){
      return tree_count_recursive(root);
    }


    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    int remove( const Comparable & x , float & count)
    {
        remove( x, root, ++count );
    }

    /**
       * Prints average depth in a tree
      */
      double AverageDepth() {
        double nodes = tree_count();
        double length = Get_Internal_Path_Length(root);
        return length/nodes;
      }


  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }

        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    AvlNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else {
          t->element.Merge(x);
        }

        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else {
            t->element.Merge(x);
        }
        balance( t );
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    // void remove( const Comparable & x, AvlNode * & t )
    // {
    //     if( t == nullptr )
    //         return;   // Item not found; do nothing
    //
    //     if( x < t->element )
    //         remove( x, t->left );
    //     else if( t->element < x )
    //         remove( x, t->right );
    //     else if( t->left != nullptr && t->right != nullptr ) // Two children
    //     {
    //         t->element = findMin( t->right )->element;
    //         remove( t->element, t->right );
    //     }
    //     else
    //     {
    //         AvlNode *oldNode = t;
    //         t = ( t->left != nullptr ) ? t->left : t->right;
    //         delete oldNode;
    //     }
    //
    //     balance( t );
    // }

    /**
    * Internal method to remove from a subtree.
    * x is the item to remove.
    * t is the node that roots the subtree.
    * Set the new root of the subtree.
    */
    int remove( const Comparable & x, AvlNode * & t, float & recursive_calls )
    {
      if( t == nullptr )
        return 1;   // Item not found; do nothing

      if( x < t->element )
        return remove( x, t->left, ++recursive_calls );
      else if( t->element < x )
        return remove( x, t->right, ++recursive_calls );
      else if( t->left != nullptr && t->right != nullptr ) // Two children
      {
        t->element = findMin( t->right )->element;
        return remove( t->element, t->right, ++recursive_calls );
      }
      else
      {
        AvlNode *oldNode = t;
        t = ( t->left != nullptr ) ? t->left : t->right;
        delete oldNode;
      }

      balance( t );
      return recursive_calls;
    }


    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;

        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        } else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
	}
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    Comparable contains( const Comparable & x, AvlNode *t, int *recursive_count) const
    {
        if( t == nullptr )
            return Comparable("Not Found", "Not Found");
        else if( x < t->element ){
            recursive_count++;
            return contains( x, t->left , recursive_count);
          }
        else if( t->element < x ){
            recursive_count++;
            return contains( x, t->right , recursive_count);
          }
        else
            return t->element;    // Match
    }

    Comparable contains( const Comparable & x, AvlNode *t, float & count) const
    {
        if( t == nullptr )
            return Comparable("Not Found", "Not Found");
        else if( x < t->element ){
            count++;
            return contains( x, t->left , count);
          }
        else if( t->element < x ){
            count++;
            return contains( x, t->right , count);
          }
        else
            return t->element;    // Match
    }

    bool contains_bool_version( const Comparable & x, AvlNode *t ) const
{
    if( t == nullptr )
        return false;
    else if( x < t->element )
        return contains_bool_version( x, t->left );
    else if( t->element < x )
        return contains_bool_version( x, t->right );
    else
        return true;    // Match
}

/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

/*Recursively count the number of nodes in the avl tree
Does so from left child to right and adds root at the end*/
    int tree_count_recursive(const AvlNode *t) const{
      if (t == NULL){
        return 0;
      }
      else {
        return 1+ tree_count_recursive(t->left) + tree_count_recursive(t->right);
      }
    }

/*Find the depth of a node from root*/
  int depth_of_node(AvlNode *k, AvlNode *t){
    if (t == nullptr || k == t){
      return 0;
    }
    else if (k->element < t->element){
      return 1 + depth_of_node(k,t->left);
    }
    else {
      return 1 + depth_of_node(k,t->right);
    }
  }

/*Recursively find the internal path length of the tree
Does so by first making sure the node is not a nullptr
Then, if not it adds the node's level and ipl of the sbtrees to the total*/
    float Get_Internal_Path_Length(AvlNode *t) {
    if (t == nullptr)
        return 0;
    return (depth_of_node(t, root) + Get_Internal_Path_Length(t->left) + Get_Internal_Path_Length(t->right));
  }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }


    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
      AvlNode *k2 = k3->left->right;
    k3->left->right = k2->left;
    k2->left=k3->left;

    k3->left->height = (max( height( k3->left->left ), height( k3->left->right )) +1);
    k2->height = (max( height( k2->right), k3->left->height) +1);
    k3->left = k2;


    AvlNode *k1 = k3->left;
    k3->left = k1->right;
    k1->right=k3;

    k3->height = (max( height( k3->left ), height( k3->right)) +1);
    k1->height = (max( height( k2->left), k3->height) +1);
    k3 = k1;
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k3 )
    {
      AvlNode *k1 = k3->right->left;
    k3->right->left = k1->right;
    k1->right=k3->right;

    k3->right->height = (max( height( k3->right->left ), height( k3->right->right )) +1);
    k1->height = (max( height( k1->left), k3->right->height) +1);
    k3->right = k1;


    AvlNode *k2 = k3->right;
    k3->right = k2->left;
    k2->left=k3;

    k3->height = (max( height( k3->left ), height( k3->right)) +1);
    k2->height = (max( height( k2->right), k3->height) +1);
    k3 = k2;
    }
};

#endif
