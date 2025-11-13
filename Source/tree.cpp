#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Logfile.h"
#include "utils.h"
#include "tree.h"
#include "verify.h"
#include "dump.h"

#define DATA(node)      node->data
#define LEFT(node)      node->left
#define RIGHT(node)     node->right
#define PARENT(node)    node->parent
#define IS_ALLOC(node)  node->is_alloc
#define RANK(node)      node->rank
#define ROOT(tree)      tree->root
#define DISK(tree)      tree->disk
#define DISK_BUF(tree)  tree->disk->buffer
#define DISK_SIZE(tree) tree->disk->size

Tree_t* Tree_Ctor() {

    TreeNode_t* root = Node_Ctor("Neizvestno chto");
    
    SAFE_CALLOC(tree, 1, Tree_t)

    ROOT(tree) = root;
    DISK(tree) = NULL;

    ONDEBUG( Node_Verify(ROOT(tree)); )
    
    ONDEBUG( DUMP_AFTER(tree) )

    return tree;
}

TreeErr_t Tree_Dtor(Tree_t* tree) {
    assert(tree);

    // ONDEBUG( DUMP_BEFORE(tree) ) 

    if ( ! tree) {
        fprintf(stderr, "Node_Dtor: NULL-pointer to TreeNode_t\n");
        return EC_NULL_POINTER;
    }

    Node_Verify(ROOT(tree));
    Node_Dtor(ROOT(tree));

    if ( DISK(tree) ) {
        free(DISK_BUF(tree));
        free(DISK(tree));
    }

    free(tree);

    return END_WITH_SUC;
}

TreeNode_t* Node_Ctor(TreeElem_t data) {

    SAFE_CALLOC(node, 1, TreeNode_t)

    TreeElem_t data_aloc = strdup(data);
    
    DATA(node)  = data_aloc;

    LEFT(node)     = NULL;
    RIGHT(node)    = NULL;
    PARENT(node)   = NULL;

    RANK(node)     = 0;
    IS_ALLOC(node) = ALLOC;

    ONDEBUG( Node_Verify(node); )
    return node;
}

TreeNode_t* Node_Ctor_empty(void) {

    SAFE_CALLOC(node, 1, TreeNode_t)

    DATA(node)     = NULL;
    LEFT(node)     = NULL;
    RIGHT(node)    = NULL;
    PARENT(node)   = NULL;

    RANK(node)     = 0;
    IS_ALLOC(node) = STATIC;

    ONDEBUG( Node_Verify(node); )
    return node;
}

TreeErr_t Node_Dtor(TreeNode_t* node) {
    assert(node);
    ONDEBUG( Node_Verify(node); )

    if ( ! node) {
        fprintf(stderr, "Node_Dtor: NULL-pointer to TreeNode_t\n");
        return EC_NULL_POINTER;
    }

    if (LEFT(node))
        Node_Dtor(LEFT(node));
    
    if (RIGHT(node))
        Node_Dtor(RIGHT(node));

    if (IS_ALLOC(node) == ALLOC)
        free(DATA(node));

    free(node);

    return END_WITH_SUC;
}

int Is_Leaf_Node(TreeNode_t* node) {
    assert(node);
    ONDEBUG( Node_Verify(node); )

    if (LEFT(node)  == NULL && 
        RIGHT(node) == NULL )
    return IS_LEAF;

    return NOT_LEAF;
}

TreeNode_t* Find_Node_in_tree (TreeNode_t* node, const char* finding_data) {
    assert(node);
    assert(finding_data);

    TreeNode_t* found_node = NULL;

    if (Is_Leaf_Node(node)) 
    {
        if (strcmp( DATA(node), finding_data) == 0) 
            return node;

        return NULL;
    }

    if ( LEFT(node) ) 
    {
        found_node = Find_Node_in_tree( LEFT(node), finding_data);

        if (found_node != NULL)
            return found_node;
    }


    if ( RIGHT(node) ) 
    {
        found_node = Find_Node_in_tree( RIGHT(node), finding_data);

        if (found_node != NULL)
            return found_node;
    }

    return NULL;
}