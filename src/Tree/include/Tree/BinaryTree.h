#ifndef ALGO_BINARY_TREE_H
#define ALGO_BINARY_TREE_H

typedef struct TreeNode {
    void *obj;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct BSTree {
    struct TreeNode *root;
    int size;

    void (*destructor)(void *); // destructor to free the obj in TreeNode
    int (*comparator)(const void *, const void *);
} BSTree;


static TreeNode *TreeNode_new(void *obj);

/**
 * the caller is responsible to free the BSTree
 *
 * @param destructor
 * @return a pointer to BSTree
 */
BSTree *BSTree_new(void (*destructor)(void *),
                   int (*comparator)(void *, void *));

void BSTree_free(BSTree **tree);

void BSTree_add(BSTree *tree, void *obj);

static TreeNode *add(TreeNode *root, void *obj, int (*comparator)(void *, void *));

void BSTree_prefix_traversal(TreeNode *root, void(*callback)(void *));


#endif //ALGO_BINARY_TREE_H
