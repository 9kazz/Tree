#ifndef DUMP_H
#define DUMP_H

#include <stdio.h>

#include "Logfile.h"
#include "utils.h"
#include "tree.h"

#define SHAPE   "shape = Mrecord, "
#define STYLE   "style = \"filled\", "

                /*COLORS*/

#define BRIGHT_GREEN    "\"#C0FFC0\""                
#define BRIGHT_RED      "\"#FFC0C0\""
#define BRIGHT_BLUE     "\"#C0C0FF\""
#define BRIGHT_YELLOW   "\"#ffff94ff\""
#define YELLOW          "\"#cdcd00ff\""

const int MAX_DUMP_INFO_LEN = 256;

#define DUMP_BEFORE(tree)                                                                                                                        \
    {                                                                                                                                            \
    static char dump_info_str[MAX_DUMP_INFO_LEN] = {0};                                                                                          \
    snprintf(dump_info_str, MAX_DUMP_INFO_LEN, "Before <span style = \"color: blue;\"> %s </span> in %s:%d", __func__, __FILE__, __LINE__);      \
    Graphic_Dump_Node(tree, dump_info_str);                                                                                                              \
    }
    
#define DUMP_AFTER(tree)                                                                                                                         \
    {                                                                                                                                            \
    static char dump_info_str[MAX_DUMP_INFO_LEN] = {0};                                                                                          \
    snprintf(dump_info_str, MAX_DUMP_INFO_LEN, "AFTER <span style = \"color: blue;\"> %s </span> in %s:%d", __func__, __FILE__, __LINE__);       \
    Graphic_Dump_Node(tree, dump_info_str);                                                                                                              \
    }


TreeErr_t Dump_Node_preorder (const TreeNode_t* node, FILE* output_file);
TreeErr_t Dump_Node_postorder(const TreeNode_t* node, FILE* output_file);
TreeErr_t Dump_Node_inorder  (const TreeNode_t* node, FILE* output_file);

TreeErr_t Graphic_Dump_Node     (const Tree_t*     tree, const char* dump_info);
TreeErr_t Print_Tree_to_Graphviz(const Tree_t*     tree, FILE* output_file);
TreeErr_t Print_Node_to_Graphviz(const TreeNode_t* node, FILE* output_file);
TreeErr_t Dump_Node_to_HTML     (const TreeNode_t* node, const char* image_file_name, const char* dump_info);

#endif