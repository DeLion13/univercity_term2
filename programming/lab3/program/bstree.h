#pragma once

#include "strstrmap.h"

typedef struct __BinTree BinTree;
struct __BinTree 
{
   int  key;       
   StrStrMap * value;       
   BinTree * left;  
   BinTree * right; 
};


typedef struct __BSTree BSTree;
struct __BSTree {
    BinTree * root;  
    size_t size;       
};


void   BSTree_init       (BSTree * self);
void   BSTree_deinit     (BSTree * self);
BSTree * BSTree_alloc    (void);
void   BSTree_free       (BSTree * self);

size_t BSTree_size     (BSTree * self); 

int getKey(StrStrMap * value);  // there should be a function to get key from value

void   BSTree_insert   (BSTree * self, StrStrMap * value);  // add unique
bool   BSTree_lookup   (BSTree * self, int key);  // check for value with a key
StrStrMap * BSTree_search   (BSTree * self, int key);  // get the value for a key
StrStrMap * BSTree_delete   (BSTree * self, int key);  // delete the value for a key
void   BSTree_clear    (BSTree * node);       // delete all values

void printTree(BSTree * self);
void BinTree_print(BinTree * root, char pos, int lvl);