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


TreeErr_t Dump_Node_preorder (const TreeNode_t* node, FILE* output_file);
TreeErr_t Dump_Node_postorder(const TreeNode_t* node, FILE* output_file);
TreeErr_t Dump_Node_inorder  (const TreeNode_t* node, FILE* output_file);

TreeErr_t Graphic_Dump_Node     (const TreeNode_t* node);
TreeErr_t Print_Node_to_Graphviz(const TreeNode_t* node, FILE* output_file);
TreeErr_t Dump_Node_to_HTML     (const TreeNode_t* node, const char* image_file_name);

#endif