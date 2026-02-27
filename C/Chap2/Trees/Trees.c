#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct treenode {
    int data;
    struct treenode *left;
    struct treenode *right;
} treenode;


treenode *createnode(int value){
    treenode *result = malloc(sizeof(treenode));
    if (result != NULL){
        result->left = NULL;
        result->right = NULL;
        result->data = value;
    }
    return result;
}

void printtab(int a){
    for(int i = 0; i < a; i++){
        printf("\t");
    }
}


void printtree_rec(treenode *root, int level){
    if (root == NULL){
        printtab(level);
        printf("---empty---\n");
        return;
    }
    printtab(level);
    printf("value = %d\n", root->data);
    printtab(level);
    printf("left\n");
    printtree_rec(root->left, level+1);
    printtab(level);
    printf("right\n");
    printtree_rec(root->right, level+1);
}

void printtree(treenode *root) {
    printtree_rec(root, 0);
}

bool insertnumber(treenode **rootptr, int value){
    if (*rootptr == NULL){
        (*rootptr) = createnode(value);
        return true;
    }
    if ((*rootptr)->data == value){
        printf("value already exists");
        return false;
    }
    if (value < (*rootptr)->data){
        return insertnumber(&((*rootptr)->left), value);
    } else {
        return insertnumber(&((*rootptr)->right), value);
    }
}

int main(){
    // Create root node
    treenode *root = createnode(1);
    
    // Create left and right children
    root->left = createnode(2);
    root->right = createnode(3);
    
    // Create grandchildren
    root->left->left = createnode(4);
    root->left->right = createnode(5);
    
    // Print the tree
    printf("Tree structure: ");
    printtree(root);
    printf("\n");
    
    return 0;
}