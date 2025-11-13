#ifndef AKINATOR_H
#define AKINATOR_H

struct NodeDef_t {
    char* name;
    int   state;  
};

enum user_answers {
    ANS_NO    =  0,
    ANS_YES   =  1,
    ANS_INCOR = -1
};

enum statements {
    POS = 0,
    NEG = 1
};

TreeErr_t   Akinator_main_aki             (Tree_t* tree);

TreeErr_t   Create_new_node_aki           (TreeNode_t* final_node);
TreeNode_t* Ask_and_Answer_until_leaf_aki (TreeNode_t* node);
TreeErr_t   Ask_Question_aki              (TreeNode_t* node);
int         Read_Answer_aki               (TreeNode_t* node);

TreeNode_t* Node_Definition_aki           (TreeNode_t* node, TreeNode_t* node_to_stop);
TreeErr_t   Print_Definition              (NodeDef_t* node_buf, size_t way_len, FILE* output_file);

TreeNode_t* Node_Difference_aki           (Tree_t* tree,       TreeNode_t* node1, TreeNode_t* node2);
TreeNode_t* Find_common_node              (TreeNode_t* node1,  TreeNode_t* node2);
#endif