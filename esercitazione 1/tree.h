#ifndef TREE_H
#define TREE_H

typedef struct node{
  int key;
  struct node * p;
  struct node * left;
  struct node * right;
} * Node;

typedef struct tree {
  Node root;
} * Tree;

#endif