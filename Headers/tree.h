#ifndef TREE_H
#define TREE_H 

typedef char* TreeElem_t;
typedef int   TreeErr_t;

typedef int   bool_t;

enum is_allocated {
    STATIC = 0,
    ALLOC  = 1
};

enum is_leaf_checking {
    IS_LEAF  = 1,
    NOT_LEAF = 0
};

enum subtree {
    LEFT_SON  = 0,
    RIGHT_SON = 1
};

struct TreeNode_t;
struct DiskBuf_t;
struct Tree_t;

struct TreeNode_t {
    TreeElem_t  data;
    TreeNode_t* left;
    TreeNode_t* right;
    TreeNode_t* parent;
    int         rank;
    bool_t      is_alloc; // 0 -- not allocated, 1 -- was allocated
};

struct DiskBuf_t {
    char*  buffer;
    size_t size;
};

struct Tree_t {
    TreeNode_t* root;
    DiskBuf_t*  disk;
};

Tree_t*     Tree_Ctor(void);
TreeErr_t   Tree_Dtor(Tree_t* tree);

TreeNode_t* Node_Ctor(TreeElem_t  data);
TreeNode_t* Node_Ctor_empty(void);
TreeErr_t   Node_Dtor(TreeNode_t* node);

int         Is_Leaf_Node(TreeNode_t* node);

TreeNode_t* Find_Node_in_tree (TreeNode_t* node, const char* finding_data);

#endif