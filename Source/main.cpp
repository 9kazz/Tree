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

    Tree_t* tree = Tree_Ctor("10");

    Node_Add(tree, "3");
    Node_Add(tree, "5");
    Node_Add(tree, "12");
    Node_Add(tree, "7");
    Node_Add(tree, "20");
    Node_Add(tree, "2");
    
    Graphic_Dump_Node(tree->root);

    Tree_Dtor(tree);

    atexit(Logfile_close);

    return 0;
}