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

bool findnum(treenode *root, int value){
    if (root == NULL){
        return false;
    }
    if (root->data == value){
        return true;
    }
    if (root->data < value){
        return findnum(root->left, value);
    } else {
        return findnum(root->right, value);
    }
}

bool freetree(treenode *root){
    if (root == NULL){
        return true;
    }
    freetree(root->right);
    freetree(root->left);
    free(root);
    return true;
}

treenode* returnmin(treenode *root){
    if (root == NULL){
        return NULL;
    }
    if (root->left == NULL){
        return root;
    }
    return returnmin(root->left);
}

bool deletenode(treenode **rootptr, int value){
    if (*rootptr == NULL){
        return false;
    }
    if ((*rootptr)->data == value){
        // Case 1: No children
        if ((*rootptr)->left == NULL && (*rootptr)->right == NULL){
            free(*rootptr);
            *rootptr = NULL;
            return true;
        }
        // Case 2: Left child only
        if ((*rootptr)->left == NULL){
            treenode *temp = (*rootptr)->right;
            free(*rootptr);
            *rootptr = temp;
            return true;
        }
        // Case 3: Right child only
        if ((*rootptr)->right == NULL){
            treenode *temp = (*rootptr)->left;
            free(*rootptr);
            *rootptr = temp;
            return true;
        }
        // Case 4: Two children
        treenode* lowestmin = returnmin((*rootptr)->left);
        (*rootptr)->data = lowestmin->data;
        deletenode(&((*rootptr)->left), lowestmin->data);
        return true;
    }

    if (value < (*rootptr)->data){
        return deletenode(&((*rootptr)->left), value);
    } else {
        return deletenode(&((*rootptr)->right), value);
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