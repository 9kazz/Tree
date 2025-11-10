#ifndef AKINATOR_H
#define AKINATOR_H


enum user_answers {
    ANS_NO    =  0,
    ANS_YES   =  1,
    ANS_INCOR = -1
};

TreeErr_t   Akinator_main_aki             (Tree_t* tree);

TreeErr_t   Create_new_node_aki           (TreeNode_t* final_node);
TreeNode_t* Ask_and_Answer_until_leaf_aki (TreeNode_t* node);
TreeErr_t   Ask_Question_aki              (TreeNode_t* node);
int         Read_Answer_aki               (TreeNode_t* node);


#endif