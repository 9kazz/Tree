#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Logfile.h"
#include "utils.h"
#include "tree.h"
#include "verify.h"
#include "dump.h"

#define DATA(node)  node->data
#define LEFT(node)  node->left
#define RIGHT(node) node->right
#define ROOT(tree)  tree->root

Tree_t* Tree_Ctor() {

    TreeNode_t* root = Node_Ctor("Neizvestno chto");
    
    SAFE_CALLOC(tree, 1, Tree_t)

    ROOT(tree) = root;
    
    Node_Verify(ROOT(tree));
    
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

    Node_Verify(ROOT(tree));
    Node_Dtor(ROOT(tree));

    free(tree);

    return END_WITH_SUC;
}

TreeNode_t* Node_Ctor(TreeElem_t data) {

    const size_t MAX_NEW_NODE_DATA_LEN = 64;

    SAFE_CALLOC(node, 1, TreeNode_t)
    SAFE_CALLOC(data_aloc,  MAX_NEW_NODE_DATA_LEN + 1, char)

    strncpy(data_aloc, data, MAX_NEW_NODE_DATA_LEN);

    node->data  = data_aloc;
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

    if (LEFT(node))
        Node_Dtor(LEFT(node));
    
    if (RIGHT(node))
        Node_Dtor(RIGHT(node));

    free(DATA(node));
    free(node);

    return END_WITH_SUC;
}

int Is_Leaf_Node(TreeNode_t* node) {
    assert(node);
    Node_Verify(node);

    if (LEFT(node)  == NULL && 
        RIGHT(node) == NULL )
    return IS_LEAF;

    return NOT_LEAF;
}