#ifndef TREE_H
#define TREE_H 

typedef char* TreeElem_t;
typedef int   TreeErr_t;

enum is_leaf_checking {
    IS_LEAF      = 1,
    NOT_LEAF     = 0
};

struct TreeNode_t {
    TreeElem_t  data;
    TreeNode_t* left;
    TreeNode_t* right;
};

struct Tree_t {
    TreeNode_t* root;
};

Tree_t*     Tree_Ctor(void);
TreeErr_t   Tree_Dtor(Tree_t* tree);

TreeNode_t* Node_Ctor(TreeElem_t  data);
TreeErr_t   Node_Dtor(TreeNode_t* node);

int         Is_Leaf_Node(TreeNode_t* node);

#endif