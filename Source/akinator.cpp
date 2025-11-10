#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Logfile.h"
#include "utils.h"
#include "tree.h"
#include "dump.h"
#include "akinator.h"
#include "verify.h"

#define DATA(node)  node->data
#define LEFT(node)  node->left
#define RIGHT(node) node->right

#define STRINGIFY(str) #str
#define FORMAT_WITH_LIM(max_len, type) "%" STRINGIFY(max_len) type
    
TreeErr_t Akinator_main_aki(Tree_t* tree) {
    assert(tree);

    FILE* output_file = stdout;

    int final_user_answer = 0;

    TreeNode_t* final_node = Ask_and_Answer_until_leaf_aki(tree->root);

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

    RIGHT(final_node) = new_node_No;
    LEFT(final_node)  = new_node_Yes;
    free(DATA(final_node));
    DATA(final_node)  = difference;

    #undef MAX_NEW_NODE_DATA_LEN
    #undef MAX_DIFFERENCE_LEN

    return END_WITH_SUC;
}

TreeNode_t* Ask_and_Answer_until_leaf_aki(TreeNode_t* node) {
    assert(node);
    Node_Verify(node);

    int user_answer = 0;

    static TreeNode_t* cur_node = node;

    Ask_Question_aki(cur_node);

    if ( Is_Leaf_Node(cur_node) == IS_LEAF)
        return cur_node;

    user_answer = Read_Answer_aki(cur_node);

    if (user_answer == ANS_YES)  
        cur_node = LEFT(cur_node);

    else if (user_answer == ANS_NO)
       cur_node = RIGHT(cur_node);

    return Ask_and_Answer_until_leaf_aki(cur_node);
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