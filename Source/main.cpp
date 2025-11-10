#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Logfile.h"
#include "utils.h"
#include "tree.h"
#include "dump.h"
#include "akinator.h"

#define DATA(node)  node->data
#define LEFT(node)  node->left
#define RIGHT(node) node->right

FILE* Logfile = fopen("Logfile.htm", "w");

void Logfile_close(void) {
    fclose(Logfile);
}
 
int main() {
    assert(Logfile);

    Tree_t* tree = Tree_Ctor();

    DATA(tree->root) = "Zhivotnoye";
    
    TreeNode_t* poltorashka = Node_Ctor("Poltorashka");
    TreeNode_t* vedet_matan = Node_Ctor("Vedet matan");
    RIGHT(tree->root) = vedet_matan;
    LEFT(tree->root)  = poltorashka;

    TreeNode_t* petrovich = Node_Ctor("Petrovich");
    TreeNode_t* vasya     = Node_Ctor("Vasya");
    RIGHT(vedet_matan) = vasya; 
    LEFT(vedet_matan)  = petrovich;

    Create_new_node_aki(vasya);

    // Akinator_main_aki(tree);
    // printf("%s\n", DATA(tree->root));
    // printf("%s\n", DATA(LEFT(tree->root)));
    // printf("%s\n", DATA(LEFT(poltorashka)));
    // printf("%s\n", DATA(RIGHT(poltorashka)));


    Graphic_Dump_Node(tree, "akinator");
    Tree_Dtor(tree);

    atexit(Logfile_close);

    return 0;
}