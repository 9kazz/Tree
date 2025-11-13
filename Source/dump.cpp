#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Logfile.h"
#include "disk.h" 
#include "utils.h"
#include "tree.h"
#include "verify.h"
#include "dump.h"

TreeErr_t Graphic_Dump_Node(const Tree_t* tree, const char* dump_info) {
    assert(tree);

    static size_t dump_num = 1;

    static const size_t    MAX_STR_LEN  = 256;
    char image_name_str   [MAX_STR_LEN] = {0};
    char create_image_CMD [MAX_STR_LEN] = {0};

    SAFE_SNPRINTF(image_name_str, MAX_STR_LEN, "dump_files/image_%d.png", dump_num); 

    SAFE_FOPEN(graphviz_file, "dump_files/graphviz.txt", "w")

    Print_Tree_to_Graphviz(tree, graphviz_file);

    fclose(graphviz_file);

    SAFE_SNPRINTF(create_image_CMD, MAX_STR_LEN, "dot -Tpng dump_files/graphviz.txt -o %s", image_name_str);

    system(create_image_CMD);

    Dump_Node_to_HTML(tree->root, image_name_str, dump_info);

    ++dump_num;

    return END_WITH_SUC;
}

TreeErr_t Print_Tree_to_Graphviz(const Tree_t* tree, FILE* output_file) {
    assert(tree);
    assert(output_file);

    fprintf(output_file, "digraph Tree {\n");
    fprintf(output_file, "\trankdir = TB;\n");
    fprintf(output_file, "\tnode [" SHAPE STYLE " fillcolor = " BRIGHT_GREEN ", color = darkgreen, width = 1, height = 1];\n");
    fprintf(output_file, "\tedge [color = \"darkgreen\"];\n\n");

    Print_Node_to_Graphviz(tree->root, output_file);

    fprintf(output_file, "\n}\n");

    return END_WITH_SUC;
}

TreeErr_t Print_Node_to_Graphviz(const TreeNode_t* node, FILE* output_file) {
    assert(node);
    assert(output_file);

    static int node_rank = 0;
    ++node_rank;

    if (node->left){
        Print_Node_to_Graphviz(node->left, output_file);
    } if (node->right) {
        Print_Node_to_Graphviz(node->right, output_file);
    }

    if ( Is_Leaf_Node( (TreeNode_t*) node) == IS_LEAF ) {
        fprintf(output_file, "\tnode_%d [label = \" { %s | rank = %d | anc = %p | ptr = %p | {<left> 0 | <right> 0}}\", rank = %d]\n", node, node->data, node->rank, node->parent, node, node_rank);
    } else {
        fprintf(output_file, "\tnode_%d [label = \" { %s | rank = %d | anc = %p | ptr = %p | {<left> yes | <right> no}}\", rank = %d]\n", node, node->data, node->rank, node->parent, node, node_rank);
    }

    if (node->left) {
        fprintf(output_file, "\tnode_%d: <left> -> node_%d [dir = both]\n", node, node->left);
    } if (node->right) {
        fprintf(output_file, "\tnode_%d: <right> -> node_%d [dir = both]\n", node, node->right);
    }
    
    --node_rank;
    return END_WITH_SUC;
}

TreeErr_t Dump_Node_to_HTML(const TreeNode_t* node, const char* image_file_name, const char* dump_info) {
    assert(node);

    fprintf(Logfile, "<pre>\n");
        fprintf(Logfile, "\t<h2> Dump of tree (%s): </h2>\n", dump_info);

    fprintf(Logfile, "<h3>Preorder: ");
    Dump_Node_preorder(node, Logfile);

    fprintf(Logfile, "\n<h3>Image:</h3>\n");
    fprintf(Logfile, "\t<img src = %s width = \"600\" height = \"600\">\n\n", image_file_name);

    fprintf(Logfile, "</pre>");

    return END_WITH_SUC;
}

// TreeErr_t Dump_disk_buffer (char* disk_buffer, size_t cur_pos, size_t size_of_file) {
//     assert(disk_buffer);

//     fprintf(Logfile, "<h1>Dump of disk_buffer\n");

//     fprintf(Logfile, "<span style = \"color: grey;\">");

//     for (size_t pos = 0; pos < cur_pos; pos++)
//         fprintf(Logfile, "%c", disk_buffer[pos]);

//     fprintf(Logfile, "</span>");

//     fprintf(Logfile, "<span style = \"color: orange;\">%d</span>", disk_buffer[cur_pos]);

//     fprintf(Logfile, "<span style = \"color: blue;\">");
    
//     for (size_t pos = cur_pos + 1; pos < size_of_file; pos++)
//         fprintf(Logfile, "%c", disk_buffer[pos]);

//     fprintf(Logfile, "</span>");

//     fprintf(Logfile, "</h1>\n");

//     return END_WITH_SUC;
// }

TreeErr_t Dump_disk_buffer (char* disk_buffer, size_t cur_pos, size_t size_of_file) {
    assert(disk_buffer);

    fprintf(stdout, "\"");

    for (size_t pos = 0; pos < cur_pos; pos++) {
        if (disk_buffer[pos] == '\0') fprintf(stdout, T_RED "0" T_RESET);
        else                          fprintf(stdout, T_GREY "%c" T_RESET, disk_buffer[pos]);
    }

    if (disk_buffer[cur_pos] == '\0') fprintf(stdout, T_RED "0" T_RESET);
    else                          fprintf(stdout, T_BG_YELLOW "%c" T_RESET, disk_buffer[cur_pos]);
    
    for (size_t pos = cur_pos + 1; pos < size_of_file; pos++) {
        if (disk_buffer[pos] == '\0') fprintf(stdout, T_RED "0" T_RESET);
        else                          fprintf(stdout, T_BRIGHT_BLUE "%c" T_RESET, disk_buffer[pos]);
    }

    fprintf(stdout, "\"\n");

    return END_WITH_SUC;
}