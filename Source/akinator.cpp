#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Logfile.h"
#include "utils.h"
#include "tree.h"
#include "dump.h"
#include "dump.h"
#include "akinator.h"
#include "verify.h"

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

#define STRINGIFY(str) #str
#define FORMAT_WITH_LIM(max_len, type) "%" STRINGIFY(max_len) type
    
TreeErr_t Akinator_main_aki(Tree_t* tree) {
    assert(tree);

    FILE* output_file = stdout;

    int final_user_answer = 0;

    TreeNode_t* final_node = Ask_and_Answer_until_leaf_aki(ROOT(tree));

    Ask_Question_aki(final_node);
    final_user_answer = Read_Answer_aki(final_node);

    if (final_user_answer == ANS_YES) {
        fprintf(output_file, "Eto bylo neslozhno :)\n");

    } else if (final_user_answer == ANS_NO) {
        Create_new_node_aki(final_node);
        fprintf(output_file, "V sleduyushchiy raz ya obyazatel'no otgadayu ;)\n");
    }

    fprintf(output_file, "Spasibo za igru! Do novykh vstrech!\n");

    return END_WITH_SUC;
}

TreeErr_t Create_new_node_aki(TreeNode_t* final_node) {
    assert(final_node);
    Node_Verify(final_node);

    FILE* output_file = stdout;

    #define MAX_NEW_NODE_DATA_LEN  64
    #define MAX_DIFFERENCE_LEN    128

    SAFE_CALLOC(difference, MAX_DIFFERENCE_LEN + 1, char)
    char new_node_Yes_data[MAX_NEW_NODE_DATA_LEN + 1] = {0};

    fprintf(output_file, "Kogo vy imeli v vidu?\n");
    scanf( " " FORMAT_WITH_LIM(MAX_NEW_NODE_DATA_LEN, "[^\n]"), new_node_Yes_data);

    fprintf(output_file, "Chem %s otlichayetsya ot %s?\n", new_node_Yes_data, DATA(final_node));
    fprintf(output_file, "On... ");
    scanf( " " FORMAT_WITH_LIM(MAX_DIFFERENCE_LEN, "[^\n]"), difference);

    TreeNode_t* new_node_Yes = Node_Ctor(new_node_Yes_data);
    TreeNode_t* new_node_No  = Node_Ctor(DATA(final_node));

    RANK(new_node_Yes) = RANK(final_node) + 1;
    RANK(new_node_No) = RANK(final_node) + 1;

    RIGHT(final_node)  = new_node_No;
    LEFT(final_node)   = new_node_Yes;
    free(DATA(final_node));
    DATA(final_node)   = difference;

    PARENT(new_node_Yes)  = final_node;
    PARENT(new_node_No)   = final_node;

    #undef MAX_NEW_NODE_DATA_LEN
    #undef MAX_DIFFERENCE_LEN

    return END_WITH_SUC;
}

TreeNode_t* Ask_and_Answer_until_leaf_aki(TreeNode_t* node) {
    assert(node);
    Node_Verify(node);

    int user_answer = 0;

    TreeNode_t* cur_node = node;

    while (Is_Leaf_Node(cur_node) == NOT_LEAF) {

        Ask_Question_aki(cur_node);

        user_answer = Read_Answer_aki(cur_node);
    
        if (user_answer == ANS_YES)  
            cur_node = LEFT(cur_node);

        else if (user_answer == ANS_NO)
            cur_node = RIGHT(cur_node);
    }

    return cur_node;
}


TreeErr_t Ask_Question_aki(TreeNode_t* node) {
    assert(node);
    Node_Verify(node);

    FILE* output_file = stdout;

    fprintf(output_file, "%s?\n", node->data);
    fprintf(output_file, "yes/no\n\n");

    return END_WITH_SUC;
}

int Read_Answer_aki(TreeNode_t* node) {

    FILE* output_file = stdout;

    #define MAX_ANSWER_LEN 3

    char answer_str[MAX_ANSWER_LEN + 1] = {0};

    scanf(FORMAT_WITH_LIM(MAX_ANSWER_LEN, "s"), answer_str);
    
    #undef MAX_ANSWER_LEN

    if ( strcmp(answer_str, "yes") == 0) {
        return ANS_YES;

    } else if ( strcmp(answer_str, "no") == 0) {
        return ANS_NO;

    } else {
        fprintf(output_file, "Incorrect answer. Please, enter only \"yes\" or \"no\"\n");
        Ask_Question_aki(node);
    }

    return ANS_INCOR;
}   

TreeNode_t* Node_Definition_aki(TreeNode_t* node, TreeNode_t* node_to_stop) {
    assert(node_to_stop);
    assert(node);
    // Node_Verify(node);

    TreeElem_t  node_name_ptr = NULL;
    TreeNode_t* cur_node = node;

    const int NODE_BUF_SIZE = 128;
    SAFE_CALLOC(node_buf, NODE_BUF_SIZE, NodeDef_t)

    size_t way_len = 0;

    while (cur_node != node_to_stop) 
    {
        node_buf[way_len].name = cur_node->data;
        
        if (LEFT(PARENT(cur_node)) == cur_node)
            node_buf[++way_len].state = POS;
        else
            node_buf[++way_len].state = NEG;
        
        cur_node = PARENT(cur_node);
    }

    node_buf[way_len].name = cur_node->data;

    Print_Definition(node_buf, way_len, stdout);

    free(node_buf);

    return node_to_stop;
}

TreeErr_t Print_Definition(NodeDef_t* node_buf, size_t way_len, FILE* output_file) {
    assert(node_buf);
    assert(output_file);

    for (size_t i = way_len; i > 0; i--) 
    {
        if (node_buf[i].state == NEG)
            fprintf(output_file, "not %s", node_buf[i].name);
        else
            fprintf(output_file, "%s", node_buf[i].name);

        if (i != 1)
            fprintf(output_file, ", ");
    }

    fprintf(output_file, "\n");

    return END_WITH_SUC;
}

TreeNode_t* Node_Difference_aki(Tree_t* tree, TreeNode_t* node1, TreeNode_t* node2) {
    assert(tree);
    assert(node1);
    assert(node2);

    FILE* output_file = stdout;

    TreeNode_t* common_ancestor = Find_common_node(node1, node2);

    fprintf(output_file, "\"%s\" and \"%s\" same at: ", DATA(node1), DATA(node2));
    Node_Definition_aki(common_ancestor, ROOT(tree));

    fprintf(output_file, "\"%s\" as opposed to \"%s\": ", DATA(node1), DATA(node2));
    Node_Definition_aki(node2, common_ancestor);    

    fprintf(output_file, "\"%s\" as opposed to \"%s\": ", DATA(node2), DATA(node1));
    Node_Definition_aki(node1, common_ancestor);    

    return common_ancestor;
}

TreeNode_t* Find_common_node(TreeNode_t* node1, TreeNode_t* node2) {
    assert(node1);
    assert(node2);
    
    TreeNode_t* cur_node1 = node1;
    TreeNode_t* cur_node2 = node2;

    while (cur_node1 != cur_node2 && cur_node1 != NULL && cur_node2 != NULL) 
    {
        if ( RANK(cur_node1) < RANK(cur_node2) )
            cur_node2 = PARENT(cur_node2);

        else 
            cur_node1 = PARENT(cur_node1);
    }

    return cur_node1;
}