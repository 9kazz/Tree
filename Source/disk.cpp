#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

#include "Logfile.h"
#include "utils.h"
#include "disk.h"
#include "tree.h"
#include "verify.h"
#include "dump.h"
#include "akinator.h"

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

Tree_t* Create_Tree_from_disk(const char* input_file_name) {
    assert(input_file_name);

    SAFE_FOPEN(disk_file, input_file_name, "r")

    DiskBuf_t* disk_buf = Create_tree_buf_from_disk(disk_file);

    size_t cur_pos = 0;

    TreeNode_t* root = Create_Node_from_disk(&cur_pos, disk_buf);
    
    SAFE_CALLOC(tree, 1, Tree_t)

    DISK(tree) = disk_buf;
    
    ROOT(tree) = root;

    return tree;   
}

TreeNode_t* Create_Node_from_disk(size_t* cur_pos, DiskBuf_t* disk_buf) {
    assert(cur_pos);
    assert(disk_buf);

    const int NIL_LEN = strlen("nil");

    static int rank = -1;
    rank++ ;    

    char* buffer     = disk_buf->buffer;
    size_t disk_size = disk_buf->size;

    ONDEBUG( Dump_disk_buffer(disk_buf->buffer, *cur_pos, disk_buf->size); )

    *cur_pos += skip_space(buffer, disk_size, *cur_pos);
    
    if (buffer[*cur_pos] == '(') 
    {
        TreeNode_t* new_node = Node_Ctor_empty();
        (*cur_pos)++ ;

        DATA(new_node) = Read_Node_Name_from_disk(cur_pos, disk_buf);
        RANK(new_node) = rank;

        LEFT(new_node) = Create_Node_from_disk(cur_pos, disk_buf);
        if( LEFT(new_node) ) 
            PARENT(LEFT(new_node)) = new_node;

        RIGHT(new_node) = Create_Node_from_disk(cur_pos, disk_buf);
        if( RIGHT(new_node) )
            PARENT(RIGHT(new_node)) = new_node;
        
        (*cur_pos)++ ;

        rank-- ;
        return new_node;
    }

    else if ( Is_nil(*cur_pos, disk_buf) ) 
    {
        (*cur_pos) += NIL_LEN;
        *cur_pos += skip_space(buffer, disk_size, *cur_pos);
        rank-- ;
        return NULL;
    }

    fprintf(stderr, "%s in %s:%d: Unknown symbol in buffer: %c (ANSI: %d) in position: %d\n", __func__, __FILE__, __LINE__, buffer[*cur_pos], buffer[*cur_pos], *cur_pos);
    return NULL;
}

TreeElem_t Read_Node_Name_from_disk(size_t* cur_pos, DiskBuf_t* disk_buf) {
    assert(cur_pos);
    assert(disk_buf);
    
    char* buffer     = disk_buf->buffer;
    size_t disk_size = disk_buf->size;

    *cur_pos += skip_space(buffer, disk_size, *cur_pos);
    char* start_of_str = buffer + (*cur_pos);

    size_t node_name_len = 0;

    int sscanf_check = sscanf(start_of_str, " \"%*[^\"]\"%n", &node_name_len);
    // if (sscanf_check == EOF || sscanf_check == 0)
    //     fprintf(stderr, "Warning: sscanf returned %d in %s: %s:%d\n", sscanf_check, __func__, __FILE__, __LINE__);

    *cur_pos += node_name_len;

    *( buffer + (*cur_pos) - 1) = '\0';

    return start_of_str + 1;
}

DiskBuf_t* Create_tree_buf_from_disk(FILE* input_file) {
    assert(input_file);

    SAFE_CALLOC(disk, 1, DiskBuf_t)

    struct stat file_info;

    int file_descriptor = fileno(input_file);

    SAFE_FSTAT(file_descriptor, &file_info)

    size_t size_of_file = file_info.st_size;

    SAFE_CALLOC(tree_buf, size_of_file, char)    

    SAFE_FREAD(tree_buf, sizeof(char), size_of_file, input_file)
    
    disk->buffer = tree_buf;
    disk->size   = size_of_file;

    return disk;
}

int Is_nil(size_t cur_pos, DiskBuf_t* disk_buf) {
    assert(disk_buf);

    char* buffer = disk_buf->buffer;

    if( buffer[cur_pos]   == 'n' &&
        buffer[++cur_pos] == 'i' &&
        buffer[++cur_pos] == 'l' )
    {
        return IS_NIL;
    }

    return NOT_NIL;

}

TreeErr_t Dump_Node_preorder(const TreeNode_t* node, FILE* output_file) {
    assert(node);

    fprintf(output_file, "(");

    fprintf(output_file, "\"%s\"", node->data);

    if (Is_Leaf_Node( (TreeNode_t*) node ) == IS_LEAF)
        fprintf(output_file, " nil nil");

    if (node->left)
        Dump_Node_preorder(node->left, output_file);

    if (node->right)
        Dump_Node_preorder(node->right, output_file);

    fprintf(output_file, ")");

    return END_WITH_SUC;
}   