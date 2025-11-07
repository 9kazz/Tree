#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Logfile.h"
#include "utils.h"
#include "tree.h"
#include "verify.h"
#include "dump.h"

TreeErr_t Graphic_Dump_Node(const Tree_t* tree) {
    assert(tree);

    static size_t dump_num = 1;

    static const size_t MAX_DOT_CMD_LEN      = 256;
    char create_image_CMD [MAX_DOT_CMD_LEN] = {0};

    SAFE_FOPEN(graphviz_file, "dump_files/graphviz.txt", "w")

    Print_Tree_to_Graphviz(tree, graphviz_file);

    fclose(graphviz_file);

    SAFE_SNPRINTF(create_image_CMD, MAX_DOT_CMD_LEN, "dot -Tpng dump_files/graphviz.txt -o dump_files/image.png");

    system(create_image_CMD);

    Dump_Node_to_HTML(tree->root, "dump_files/image.png");

    ++dump_num;

    return END_WITH_SUC;
}

TreeErr_t Dump_Node_preorder(const TreeNode_t* node, FILE* output_file) {
    assert(node);

    fprintf(output_file, "(");

    fprintf(output_file, "%s", node->data);

    if (node->left)
        Dump_Node_preorder(node->left, output_file);

    if (node->right)
        Dump_Node_preorder(node->right, output_file);

    fprintf(output_file, ")");

    return END_WITH_SUC;
}

TreeErr_t Dump_Node_postorder(const TreeNode_t* node, FILE* output_file) {
    assert(node);

    fprintf(output_file, "(");

    if (node->left)
        Dump_Node_postorder(node->left, output_file);
    
    if (node->right)
        Dump_Node_postorder(node->right, output_file);
        
    fprintf(output_file, "%s", node->data);

    fprintf(output_file, ")");

    return END_WITH_SUC;
}

TreeErr_t Dump_Node_inorder(const TreeNode_t* node, FILE* output_file) {
    assert(node);

    fprintf(output_file, "(");

    if (node->left)
        Dump_Node_inorder(node->left, output_file);

    fprintf(output_file, "%s", node->data);

    if (node->right)
        Dump_Node_inorder(node->right, output_file);

    fprintf(output_file, ")");

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

    if (node->left)
        Print_Node_to_Graphviz(node->left, output_file);
        
    if (node->right)
        Print_Node_to_Graphviz(node->right, output_file);

    fprintf(output_file, "\tnode_%d [label = \" { %s | %p | {<left> %p | <right> %p}}\", rank = %d]\n", node, node->data, node, node->left, node->right, node_rank);

    if (node->left)
        fprintf(output_file, "\tnode_%d: <left> -> node_%d\n", node, node->left);

    if (node->right)
        fprintf(output_file, "\tnode_%d: <right> -> node_%d\n", node, node->right);

    --node_rank;
    return END_WITH_SUC;
}

TreeErr_t Dump_Node_to_HTML(const TreeNode_t* node, const char* image_file_name) {
    assert(node);

    fprintf(Logfile, "<pre>\n");
    fprintf(Logfile, "\t<h2> Dump of tree: </h2>\n");

    fprintf(Logfile, "<h3>Preorder: ");
    Dump_Node_preorder(node, Logfile);

    fprintf(Logfile, "\n\nPostorder:");
    Dump_Node_postorder(node, Logfile);

    fprintf(Logfile, "\n\nInorder:  ");
    Dump_Node_inorder(node, Logfile);
    fprintf(Logfile, "</h3>\n");

    fprintf(Logfile, "\n<h3>\tImage:</h3>\n");
    fprintf(Logfile, "\t<img src = %s width = \"400\" height = \"400\">\n\n", image_file_name);

    fprintf(Logfile, "</pre>");

    return END_WITH_SUC;
}