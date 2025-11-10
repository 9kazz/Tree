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
#define ROOT(tree)  tree->root

FILE* Logfile = fopen("Logfile.htm", "w");

void Logfile_close(void) {
    fclose(Logfile);
}
 
int main() {
    assert(Logfile);

    SAFE_FOPEN(output_file, "dump_files/disk.txt", "w")

    Tree_t* tree = Tree_Ctor();

    SAFE_CALLOC(zhivotnoe, strlen("Zhivotnoe") + 1, char)
    strcpy(zhivotnoe, "Zhivotnoe");

    free(DATA(ROOT(tree)));

    DATA(ROOT(tree))            = zhivotnoe;
    TreeNode_t* poltorashka     = Node_Ctor("Poltorashka");
    TreeNode_t* vedet_matan     = Node_Ctor("Vedet matan");
    TreeNode_t* petrovich       = Node_Ctor("Petrovich");
    TreeNode_t* neizvestno_chto = Node_Ctor("Neizvestno_chto");

    LEFT(ROOT(tree))   = poltorashka;
    RIGHT(ROOT(tree))  = vedet_matan;
    LEFT(vedet_matan)  = petrovich;
    RIGHT(vedet_matan) = neizvestno_chto;

    Akinator_main_aki(tree);

    Graphic_Dump_Node(tree, "akinator");
    
    Dump_Node_preorder(ROOT(tree), output_file);

    Tree_Dtor(tree);

    fclose(output_file);
    atexit(Logfile_close);

    return 0;
}