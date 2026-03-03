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

treenode* findmin(treenode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

treenode* deletenode(treenode* root, int value) {
    if (root == NULL) {
        return NULL;
    }

    if (value < root->data) {
        root->left = deletenode(root->left, value); // Parent catches the return
    } 
    else if (value > root->data) {
        root->right = deletenode(root->right, value); // Parent catches the return
    } 
    
    else {
        // Case 1 & 2: 0 or 1 child
        if (root->left == NULL) {
            treenode* temp = root->right;
            free(root);
            return temp; 
        } 
        else if (root->right == NULL) {
            treenode* temp = root->left;
            free(root);
            return temp; 
        }
        treenode* temp = findmin(root->right);
        root->data = temp->data;
        root->right = deletenode(root->right, temp->data);
    }

    // Return the current pointer to keep the upper branches intact
    return root;
}

treenode *invertTree(treenode* root){
    if (root == NULL){
        return NULL;
    }
    treenode *temp = root->left;
    root->left = root->right;
    root->right = temp; 

    invertTree(root->left);
    invertTree(root->right);
    return root;
}

int search(treenode *root){
    if (root == NULL){
        return 0;
    }
    int right = search(root->right);
    int left = search(root->left);
    if (right > left){
        return right + 1;
    } else {
        return left + 1;
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