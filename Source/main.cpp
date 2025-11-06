#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Logfile.h"
#include "utils.h"
#include "tree.h"
#include "dump.h"

FILE* Logfile = fopen("Logfile.htm", "w");

void Logfile_close(void) {
    fclose(Logfile);
}
 
int main() {
    assert(Logfile);

    TreeNode_t* node3 = Node_Ctor(3, NULL, NULL);
    TreeNode_t* node4 = Node_Ctor(7, NULL, NULL);
    TreeNode_t* node2 = Node_Ctor(5, node3, node4);

    TreeNode_t* node6 = Node_Ctor(15, NULL, NULL);
    TreeNode_t* node5 = Node_Ctor(20, node6, NULL);

    TreeNode_t* node1 = Node_Ctor(10, node2, node5);

    Tree_t tree = {.root = node1};

    TreeNode_t* node7 = Node_Add(&tree, 40);

    Dump_Node_in_line(node1, stdout);
    
    Graphic_Dump_Node(node1);

    Node_Dtor(node1);
    Node_Dtor(node2);
    Node_Dtor(node3);
    Node_Dtor(node4);
    Node_Dtor(node5);
    Node_Dtor(node6);
    Node_Dtor(node7);

    atexit(Logfile_close);

    return 0;
}