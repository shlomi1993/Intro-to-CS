#include <stdlib.h>
#include <assert.h>
#include "result.h"
#include "genericBinTree.h"

/***************************
* Name: Shlomi Ben Shushan *
* ID: *********            *
* Group: 01 - CS           *
* Assignment: 5			   *
***************************/

// This struct defines a Binary Tree.
struct BinTree {
    Ptr val;
    struct BinTree* left;
    struct BinTree* right;
    BinTreeFunctions funcs;
};

// This function returns 1 if the BinTree is empty, 0 otherwise.
static int isEmpty(BinTree* root) {
    if (root == NULL) {
        return 1;
    }
    if (root->val == NULL) {
        return 1;
    }
    return 0;
}

// This function initializes a BinTree.
BinTree* createBinTree(BinTreeFunctions funcs) {
    BinTree* root = malloc(sizeof(BinTree));
    if (root == NULL) {
        return NULL;
    }
    root->funcs = funcs;
    root->val = NULL;
    root->left = NULL;
    root->right = NULL;
    return root;
}

// This function finds and element in the BinTree.
BinTree* findInBinTree(BinTree* root, Ptr val) {
    if (isEmpty(root)) {
        return NULL;
    }
    if (root->funcs.compare(root->val, val) > 0) {
        return findInBinTree(root->left, val);
    }
    if (root->funcs.compare(root->val, val) < 0) {
        return findInBinTree(root->right, val);
    }
    return root;
}

// This function creates a copy of the value in the root and returns a pointer to it.
Ptr createCopyOfValueInRoot(BinTree* root) {
    if (root == NULL) {
        return NULL;
    }
    Ptr ptr = root->funcs.allocate();
    root->funcs.copy(ptr, root->val);
    return ptr;
}

// This function recursively returns the number of elements in the BinTree.
int sizeOfBinTree(BinTree* root) {
    if (isEmpty(root)) {
        return 0;
    }
    return 1 + sizeOfBinTree(root->left) + sizeOfBinTree(root->right);
}

// This function is a BinTree destructor -- free memory.
void destroyBinTree(BinTree* root) {
    if (root == NULL) {
        return;
    }
    destroyBinTree(root->left);
    destroyBinTree(root->right);
    root->funcs.destroy(root->val);
    free(root);
}

// This function add a new element to the BinTree.
Result addToBinTree(BinTree* root, Ptr val) {
    if (root == NULL) {
        return FAILURE;
    }
    if (root->val == NULL) {
        root->val = root->funcs.allocate();
        if (root->val == NULL) {
            return MEM_ERROR;
        }
        root->funcs.copy(root->val, val);
        return SUCCESS;
    }
    if (root->funcs.compare(root->val, val) > 0) {
        if (root->left != NULL) {
            return addToBinTree(root->left, val);
        }
        root->left = createBinTree(root->funcs);
        if (root->left == NULL) {
            return MEM_ERROR;
        } else {
            root->left->val = root->funcs.allocate();
            if (root->left->val == NULL) {
                destroyBinTree(root->left);
                return MEM_ERROR;
            }
            root->funcs.copy(root->left->val, val);
            return SUCCESS;
        }
    }
    if (root->funcs.compare(root->val, val) < 0) {
        if (root->right != NULL) {
            return addToBinTree(root->right, val);
        }
        root->right = createBinTree(root->funcs);
        if (root->right == NULL) {
            return MEM_ERROR;
        } else {
            root->right->val = root->funcs.allocate();
            if (root->right->val == NULL) {
                destroyBinTree(root->right);
                return MEM_ERROR;
            }
            root->funcs.copy(root->right->val, val);
            return SUCCESS;
        }
    }
    return FAILURE;
}

// This function creates a BinTree from given arrays.
BinTree* createBinTreeFromArr(BinTreeFunctions funcs, Ptr arr[], int size) {
    BinTree* root = createBinTree(funcs);
    if (root == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        Result result = addToBinTree(root, arr[i]);
        if (result != SUCCESS) {
            destroyBinTree(root);
            return NULL;
        }
    }
    return root;
}

static int arr_from_tree_pre_order(BinTree* root, Ptr arr[], int size, int last);
static Result remove_from_arr(BinTreeFunctions funcs, Ptr arr[], int size, Ptr val);

// This function removes an element from a BinTree.
Result removeFromBinTree(BinTree** rootPtr, Ptr val) {
    assert(rootPtr != NULL);
    BinTree* root = *rootPtr;
    if (!findInBinTree(root, val)) {
        return FAILURE;
    }
    int size = sizeOfBinTree(root);
    Ptr* arr = malloc(size * sizeof(Ptr));
    if (arr == NULL) {
        return MEM_ERROR;
    }
    int last = arr_from_tree_pre_order(root, arr, size, -1);
    assert(last == size - 1);

    Result result = remove_from_arr(root->funcs, arr, size, val);
    assert(result == SUCCESS);

    BinTree* new_root = createBinTreeFromArr(root->funcs, arr, size-1);
    for (int i = 0; i < size-1; i++) {
        root->funcs.destroy(arr[i]);
    }
    free(arr);

    if (new_root == NULL) {
        return MEM_ERROR;
    }

    destroyBinTree(*rootPtr);
    *rootPtr = new_root;
    return SUCCESS;
}

// This is a pre-order printer function.
void printPreOrder(BinTree* root) {
    if (isEmpty(root)) {
        return;
    }
    root->funcs.print(root->val);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

// This is an in-order printer function.
void printInOrder(BinTree* root) {
    if (isEmpty(root)) {
        return;
    }
    printInOrder(root->left);
    root->funcs.print(root->val);
    printInOrder(root->right);
}

// This is a post-order printer function.
void printPostOrder(BinTree* root) {
    if (isEmpty(root)) {
        return;
    }
    printPostOrder(root->left);
    printPostOrder(root->right);
    root->funcs.print(root->val);
}

static int arr_from_tree_pre_order(BinTree* root, Ptr arr[], int size, int last) {
    if (root == NULL) {
        return last;
    }
    int i = last + 1;
    assert(i < size);
    arr[i] = root->funcs.allocate();
    root->funcs.copy(arr[i], root->val);
    last = arr_from_tree_pre_order(root->left, arr, size, i);
    return arr_from_tree_pre_order(root->right, arr, size, last);
}

static Result remove_from_arr(BinTreeFunctions funcs, Ptr arr[], int size, Ptr val) {
    int val_idx = -1;
    for (int i = 0; i < size; i++) {
        if (funcs.compare(arr[i], val) == 0) {
            val_idx = i;
            break;
        }
    }
    if (val_idx == -1) {
        return FAILURE;
    }
    funcs.destroy(arr[val_idx]);
    for (int i = val_idx; i < size - 1; i++) {
        arr[i] = arr[i+1];
    }
    arr[size-1] = NULL;
    return SUCCESS;
}
