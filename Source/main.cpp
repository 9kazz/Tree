#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Logfile.h"
#include "utils.h"
#include "tree.h"
#include "dump.h"
#include "akinator.h"
#include "disk.h" 

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

    SAFE_FOPEN(disk_output_file, "dump_files/disk_output.txt", "w")

    // Tree_t* tree = Tree_Ctor();

    // SAFE_CALLOC(zhivotnoe, strlen("Zhivotnoe") + 1, char)
    // strcpy(zhivotnoe, "Zhivotnoe");

    // free(DATA(ROOT(tree)));

    // DATA(ROOT(tree))            = zhivotnoe;
    // TreeNode_t* poltorashka     = Node_Ctor("Poltorashka");     
    // TreeNode_t* vedet_matan     = Node_Ctor("Vedet matan");     
    // TreeNode_t* petrovich       = Node_Ctor("Petrovich");       
    // TreeNode_t* neizvestno_chto = Node_Ctor("Neizvestno_chto"); 

    // LEFT(ROOT(tree))   = poltorashka;
    // RIGHT(ROOT(tree))  = vedet_matan;
    // LEFT(vedet_matan)  = petrovich;
    // RIGHT(vedet_matan) = neizvestno_chto;

    // Graphic_Dump_Node(tree, "akinator");

    // Akinator_main_aki(tree);

    // Graphic_Dump_Node(tree, "akinator");
    
    // Dump_Node_preorder(ROOT(tree), disk_output_file);

    // Graphic_Dump_Node(tree, "akinator");

    // Tree_Dtor(tree);
    

    Tree_t* tree_from_disk = Create_Tree_from_disk("disk_input.txt");

    // TreeNode_t* petrovich = LEFT(RIGHT(ROOT(tree_from_disk)));
    
    Graphic_Dump_Node(tree_from_disk, "akinator");

    TreeNode_t* petr = Find_Node_in_tree(ROOT(tree_from_disk), "Petrovich");
    TreeNode_t* neizv = Find_Node_in_tree(ROOT(tree_from_disk), "Baraban");
    TreeNode_t* common = Find_common_node(petr, neizv); 
    Node_Difference_aki(tree_from_disk, petr, neizv);
    // Node_Definition_aki(petr, ROOT(tree_from_disk));
    Tree_Dtor(tree_from_disk);

    fclose(disk_output_file);
    atexit(Logfile_close);

    return 0;
}