#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Logfile.h"
#include "utils.h"
#include "tree.h"
#include "verify.h"

Tree_t* Tree_Ctor(TreeElem_t root_value) {

    TreeNode_t* root = Node_Ctor(root_value);
    
    SAFE_CALLOC(tree, 1, Tree_t)

    tree->root = root;
    
    ONDEBUG(Node_Verify(tree->root))

    return tree;
}

TreeErr_t Tree_Dtor(Tree_t* tree) {

    if ( ! tree) {
        fprintf(stderr, "Node_Dtor: NULL-pointer to TreeNode_t\n");
        return EC_NULL_POINTER;
    }

    ONDEBUG(Node_Verify(tree->root))
    Node_Dtor(tree->root);

    free(tree);

    return END_WITH_SUC;
}

TreeNode_t* Node_Ctor(TreeElem_t data) {

    SAFE_CALLOC(node, 1, TreeNode_t)

    node->data  = data;
    node->left  = NULL;
    node->right = NULL;

    ONDEBUG(Node_Verify(node))
    return node;
}

TreeErr_t Node_Dtor(TreeNode_t* node) {
    assert(node);
    ONDEBUG(Node_Verify(tree->root))

    if ( ! node) {
        fprintf(stderr, "Node_Dtor: NULL-pointer to TreeNode_t\n");
        return EC_NULL_POINTER;
    }

    if (node->left)
        Node_Dtor(node->left);
    
    if (node->right)
        Node_Dtor(node->right);

    free(node);

    return END_WITH_SUC;
}

TreeNode_t* Node_Add(Tree_t* tree, TreeElem_t value) {
    assert(tree);

    ONDEBUG(Node_Verify(tree->root))
    TreeNode_t* node_ptr = tree->root;

    while(node_ptr != NULL)
    {
        if ( atoi(value) <= atoi(node_ptr->data) )
        {
            if (node_ptr->left == NULL) 
            {
                node_ptr->left = Node_Ctor(value);
                return node_ptr->left;
            }

            else
                node_ptr = node_ptr->left;
        }

        else
        {
            if (node_ptr->right == NULL) 
            {
                node_ptr->right = Node_Ctor(value);
                return node_ptr->right;
            }

            else
                node_ptr = node_ptr->right;
        }
    }

    fprintf(stderr, "Node_Add: cannot to add new node\n");

    return NULL;
}

int Is_Leaf_Node(TreeNode_t* node) {
    assert(node);
    ONDEBUG(Node_Verify(tree->root))

    if (node->left  == NULL && 
        node->right == NULL )
    return IS_LEAF;

    return NOT_LEAF;
}