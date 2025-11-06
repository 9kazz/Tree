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

    TreeNode_t* node1 = Node_Ctor("10", NULL, NULL);
    Tree_t tree = {.root = node1};

    Node_Add(&tree, "3");
    Node_Add(&tree, "5");
    Node_Add(&tree, "12");
    Node_Add(&tree, "7");
    Node_Add(&tree, "20");
    Node_Add(&tree, "2");
    
    Graphic_Dump_Node(tree.root);

    Node_Dtor(tree.root);

    atexit(Logfile_close);

    return 0;
}