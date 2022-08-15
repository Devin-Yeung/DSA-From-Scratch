#include <Tree/BinaryTree.h>
#include <stdlib.h>
#include <stdio.h>

static TreeNode *TreeNode_new(void *obj) {
    if (obj == NULL) {
        // TODO: error handling
        return NULL;
    }

    TreeNode *node = malloc(sizeof(TreeNode));
    if (node == NULL) {
        // TODO: error handling
        return NULL;
    }
    node->obj = obj;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BSTree *BSTree_new(void (*destructor)(void *),
                   int (*comparator)(void *, void *)) {

    if (destructor == NULL || comparator == NULL) {
        // TODO: error handling
        return NULL;
    }

    BSTree *tree = malloc(sizeof(BSTree));
    if (tree == NULL) {
        // TODO: error handling
        return tree;
    }

    tree->size = 0;
    tree->destructor = destructor;
    tree->comparator = comparator;
    tree->root = NULL;
    return tree;
}

// helper method of BSTree free
static void free_subtree(TreeNode *root, void(*callback)(void *)) {
    if (root == NULL) return;
    free_subtree(root->left, callback);
    free_subtree(root->right, callback);
    // free the obj
    (*callback)(root->obj);
    // free the TreeNode
    free(root);
}

void BSTree_free(BSTree **tree) {
    BSTree * t = *tree;
    free_subtree(t->root, t->destructor);
    free(t);
    *tree = NULL;
}


static TreeNode *add(TreeNode *root, void *obj, int (*comparator)(void *, void *)) {
    if (root == NULL) return TreeNode_new(obj);
    int cmp = (*comparator)(obj, root->obj);
    if (cmp < 0) root->left = add(root->left, obj, comparator);
    else if (cmp > 0) root->right = add(root->right, obj, comparator);
    else; // do nothing, key already exists
//        root.size = 1 + size(root.left) + size(root.right);
    return root;
}

void BSTree_add(BSTree *tree, void *obj) {
    if (obj == NULL) return;
    tree->root = add(tree->root, obj, tree->comparator);
    tree->size += 1;
}

void BSTree_prefix_traversal(TreeNode *root, void(*callback)(void *)) {
    if (root == NULL || callback == NULL) return;
    BSTree_prefix_traversal(root->left, callback);
    BSTree_prefix_traversal(root->right, callback);
    (*callback)(root->obj);
}

void BSTree_postfix_traversal(TreeNode *root, void(*callback)(void *)) {
    if (root == NULL || callback == NULL) return;
    BSTree_postfix_traversal(root->left, callback);
    BSTree_postfix_traversal(root->right, callback);
    (*callback)(root);
}


