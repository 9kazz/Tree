#ifndef TREE_H
#define TREE_H 

typedef char* TreeElem_t;
typedef int   TreeErr_t;

struct TreeNode_t {
    TreeElem_t  data;
    TreeNode_t* left;
    TreeNode_t* right;
};

struct Tree_t {
    TreeNode_t* root;
};

Tree_t*     Tree_Ctor(TreeElem_t root_value);
TreeErr_t   Tree_Dtor(Tree_t* tree);

TreeNode_t* Node_Ctor(TreeElem_t  data);
TreeErr_t   Node_Dtor(TreeNode_t* node);

TreeNode_t* Node_Add(Tree_t* tree, TreeElem_t value);

int         Is_Leaf_Node(TreeNode_t* node);

#endif