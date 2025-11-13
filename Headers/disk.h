#ifndef DISK_H
#define DISK_H

#include <stdio.h>

#include "utils.h"
#include "tree.h"

enum is_nil {
    NOT_NIL = 0,
    IS_NIL  = 1
};

Tree_t*     Create_Tree_from_disk     (const char* input_file_name);

TreeNode_t* Create_Node_from_disk     (size_t* cur_pos, DiskBuf_t* buffer);
TreeElem_t  Read_Node_Name_from_disk  (size_t* cur_pos, DiskBuf_t* buffer);

DiskBuf_t*  Create_tree_buf_from_disk (FILE* input_file);

int         Is_nil (size_t cur_pos, DiskBuf_t* buffer);

TreeErr_t   Dump_Node_preorder (const TreeNode_t* node, FILE* output_file);

#endif