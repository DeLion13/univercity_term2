#include "bstree.h"
#include "strstrmap.h"
#include "kvlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void   BSTree_init       (BSTree * self) {
    self -> root = NULL;
    self -> size = 0;
}

void   BSTree_free       (BSTree * self) {
    BSTree_deinit(self);
    free(self);
}

static void freeTree(BinTree * root) {
    if (root == NULL) return;
    
    if (root -> left) freeTree(root -> left);
    if (root -> right) freeTree(root->right);

    free(root);
}

void   BSTree_deinit     (BSTree * self) {
    if (self -> root != NULL) {
        freeTree(self -> root);
    }
    self -> root = NULL;
    self -> size = 0;
}

BSTree * BSTree_alloc    (void) {
    BSTree * self = malloc(sizeof(BSTree));
    BSTree_init(self);
    return self;
}

size_t BSTree_size     (BSTree * self) {
    return self -> size;
}

int getKey(StrStrMap * value) {
    return atoi(StrStrMap_get(value, "id"));
}

static void insert(BinTree * node, BinTree * newNode) {
    if (newNode->key == node->key) {
        fprintf(stderr, "`%i` Already exists\n", newNode->key);
        abort(); 
    }
    if (newNode->key < node->key) {
        if (node->left == NULL) {
            node->left = newNode; 
        }
        else {
            insert(node->left, newNode); 
        }
    } 
    else if (newNode->key > node->key) {
        if (node->right == NULL) {
            node->right = newNode; 
        }
        else {
            insert(node->right, newNode); 
        }
    }
}

void   BSTree_insert   (BSTree * self, StrStrMap * value) {
    BinTree * newNode = malloc(sizeof(BinTree));
    newNode -> key = getKey(value);
    newNode -> value = value;
    newNode -> left = NULL;
    newNode -> right = NULL;
    if (self->root == NULL) {
        self->root = newNode;
    }
    else {
        insert(self->root, newNode);
    }
    self -> size += 1;
}

static bool lookup(BinTree * node, int key) {
    if (node == NULL) return false;
    if (node -> key == key) return true;
    if (key < node -> key) return lookup(node -> left, key);
    if (key > node -> key) return lookup(node -> right, key);

    return false;
}

bool   BSTree_lookup   (BSTree * self, int key) {
    return lookup(self -> root, key);
}

static StrStrMap * search(BinTree * node, int key) 
{
    if (node == NULL) return NULL; 
    if (node -> key == key) return node -> value;
    if (key < node -> key) return search(node->left, key);
    if (key > node -> key) return search(node->right, key);

    return NULL;
}

StrStrMap * BSTree_search   (BSTree * self, int key) {
    return search(self -> root, key);
}

static BinTree * searchMin(BinTree * node) {
    if (node == NULL) return NULL; 
    if (node->left == NULL) return node;
    return searchMin(node->left); 
}

static StrStrMap * delete(BinTree * node, int key, BinTree * parent);

static void modifyTreeOnDelete(BinTree * node, BinTree * parent) {
    BinTree * replacementNode = NULL;
    if (node->left == NULL && node->right == NULL) {          // case A: no children
        replacementNode = NULL;  // nothing to replace with
    } else if (node->left == NULL || node->right == NULL) {   // case B: one child
        BinTree * child = (node->left != NULL) ? node->left : node->right;  // get a pointer to the child
        replacementNode = child;  // replace with it’s only child
    } else /* node->left != NULL && node->right != NULL */ {  // case C: two children
        BinTree * minNode = searchMin(node->right);  // find node with min value in right subtree
        StrStrMap * deletedValue = delete(node->right, minNode->key, node);  // remove and free min node by key
        BinTree * newMin = malloc(sizeof(BinTree));
        newMin -> key = getKey(deletedValue);
        newMin -> value = deletedValue;
        newMin->left = node->left;
        newMin->right = node->right;
        replacementNode = newMin;  // replace with the min node removed from it’s right subtree
    }
    if (parent->left == node) parent->left  = replacementNode;  // find node’s position as parent’s child
    else parent->right = replacementNode;
}


static StrStrMap * delete(BinTree * node, int key, BinTree * parent) {
   if (node == NULL) {
       fprintf(stderr, "Key `%i` not found on deletion\n", key);
       abort();
   }
   if      (key < node->key) return delete(node->left,  key, node);
   else if (key > node->key) return delete(node->right, key, node);
   else  /* key == node->key*/ {
       modifyTreeOnDelete(node, parent);
       StrStrMap * deletedValue = node->value;
       free(node);
       return deletedValue;
   }
}


StrStrMap * BSTree_delete(BSTree * self, int key) {
   BinTree fakeParent;  // to handle special root case
   fakeParent.left = self->root;
   StrStrMap * old = delete(self->root, key, &fakeParent);  // enter recursion
   self->root = fakeParent.left;
   return old;
}

static void clear(BinTree * node);

void   BSTree_clear    (BSTree * node) {
    if (node != NULL) {
        clear(node -> root);
    }
    node -> size = 0;
}

static void clear (BinTree *node) {
    if (node == NULL)
        return;
    clear(node->left);
    clear(node->right);

    free((char*)StrStrMap_get(node -> value,  "id"));
    free((char*)StrStrMap_get(node -> value,  "name"));
    free((char*)StrStrMap_get(node -> value,  "type"));
    free((char*)StrStrMap_get(node -> value,  "author"));
    StrStrMap_deinit(node -> value);
    free(node -> value);
    
}

void BinTree_printValueOnLevel(BinTree * node , char pos,int lvl) {
    for(int i=0; i<lvl; i++) {
        printf("....");
    }
    printf("||%c: ", pos);
    if(node == NULL) {
        printf("NULL\n");
    }
    else {
        printf(" %d\n", node -> key);
    }
    
}
void BinTree_print(BinTree * root, char pos, int lvl) {
    if(root != NULL && (root -> left != NULL || root -> right != NULL))
    BinTree_print(root -> right, 'R', lvl + 1);
    BinTree_printValueOnLevel(root, pos, lvl);
    if(root != NULL && (root -> left != NULL || root -> right != NULL))
    BinTree_print(root -> left, 'L', lvl + 1);
}

void printTree(BSTree * self) {
    BinTree_print(self -> root, '+', 0);
}