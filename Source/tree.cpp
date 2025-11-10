#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Logfile.h"
#include "utils.h"
#include "tree.h"
#include "verify.h"
#include "dump.h"

Tree_t* Tree_Ctor(void) {

    TreeNode_t* root = Node_Ctor("Neizvestno chto");
    
    SAFE_CALLOC(tree, 1, Tree_t)

    tree->root = root;
    
    Node_Verify(tree->root);
    
    ONDEBUG( DUMP_AFTER(tree) )

    return tree;
}

TreeErr_t Tree_Dtor(Tree_t* tree) {
    assert(tree);

    ONDEBUG( DUMP_BEFORE(tree) )

    if ( ! tree) {
        fprintf(stderr, "Node_Dtor: NULL-pointer to TreeNode_t\n");
        return EC_NULL_POINTER;
    }

    Node_Verify(tree->root);
    Node_Dtor(tree->root);

    free(tree);

    return END_WITH_SUC;
}

TreeNode_t* Node_Ctor(TreeElem_t data) {

    SAFE_CALLOC(node, 1, TreeNode_t)

    node->data  = data;
    node->left  = NULL;
    node->right = NULL;

    Node_Verify(node);
    return node;
}

TreeErr_t Node_Dtor(TreeNode_t* node) {
    assert(node);
    Node_Verify(node);

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

int Is_Leaf_Node(TreeNode_t* node) {
    assert(node);
    Node_Verify(node);

    if (node->left  == NULL && 
        node->right == NULL )
    return IS_LEAF;

    return NOT_LEAF;
}