#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "avl.h"

// Basic BST Operations

void insert(int value, BSTNode** a_root){

    // Assuming that we have a valid value inserted

    // If we have no root
    if (*a_root == NULL){
        *a_root = malloc(sizeof **a_root); // create a new node 
        **a_root = (BSTNode){.value = value, .height = 0, .left = NULL, .right = NULL}; // fill in the node
    }
    // Else recusrively call down to a valid placement
    else if (value < (*a_root) -> value){
        insert(value, &((*a_root)-> left)); // insert until we move into position
        update_height(*a_root); // update score so we can balance
        balance_after_insert_in_left(value,a_root); // balance if needed
    }
    else if (value > (*a_root) -> value){
        insert(value, &((*a_root) -> right));
        update_height(*a_root);
        balance_after_insert_in_right(value,a_root);
    }
    
}

void free_tree(BSTNode** a_root) {
    if(*a_root != NULL) {
        free_tree(&((*a_root) -> left));
        free_tree(&((*a_root) -> right));
        free(*a_root);
        *a_root = NULL;
    }
}

// Rotations

void balance_after_insert_in_left(int value, BSTNode** a_root){
    if (get_balance_score(*a_root) == 2){
        if (value < (*a_root) -> left -> value){
            // LL rotation
            rotate_clockwise(a_root);
        }
        else{
            // LR rotation
            rotate_counter_clockwise(&((*a_root) -> left));
            rotate_clockwise(a_root);
        }
    }
}

void balance_after_insert_in_right(int value, BSTNode** a_root){
    if (get_balance_score(*a_root) == -2){
        if (value > (*a_root) -> right -> value){
            // RR rotation
            rotate_counter_clockwise(a_root);
        }
        else{
            // RL rotation
            rotate_clockwise(&((*a_root) -> right));
            rotate_counter_clockwise(a_root);
        }
    }

}

// Balance

void rotate_counter_clockwise(BSTNode** a_root){
    BSTNode* old_root = *a_root;
    BSTNode* new_root = old_root -> right;
    old_root -> right = new_root -> left;
    new_root -> left = old_root;
    
    // Update
    *a_root = new_root;
    update_height(old_root);
    update_height(new_root);
}

void rotate_clockwise(BSTNode** a_root){
    BSTNode* old_root = *a_root;
    BSTNode* new_root = old_root -> left;
    old_root -> left = new_root -> right;
    new_root -> right = old_root;

    // Update
    *a_root = new_root;
    update_height(old_root);
    update_height(new_root);


}


// Metrics

/*
    Using postorder traversal to get the height of the left and right recursively

*/
void update_height(BSTNode* root) {
    int height_of_left  = get_height(root -> left);
    int height_of_right = get_height(root -> right);
    root -> height = 1 + (height_of_left > height_of_right ? height_of_left : height_of_right);
}

int get_balance_score(BSTNode const* root) {
    return get_height(root -> left) - get_height(root -> right);
}

int get_height(BSTNode const* root) {
    return root == NULL ? -1 : root -> height;
}

// Testing
void print_bst_nodes(BSTNode const* root) {
    if(root != NULL) {
        print_bst_nodes(root -> left);
        printf("[%d] ", root -> value);
        print_bst_nodes(root -> right);
    }
}

bool is_every_node_in_tree_avl_balanced(BSTNode const* root) {  // for testing
    if(root != NULL) {
        int balance_score = get_balance_score(root);
        return balance_score >= -1 && balance_score <= 1
            && is_every_node_in_tree_avl_balanced(root -> left)
            && is_every_node_in_tree_avl_balanced(root -> right);
    }
    else {
        return true;
    }
}

int get_height_without_using_field(BSTNode* root) {
    if(root == NULL) {
        return -1;
    }
    int height_of_left  = get_height_without_using_field(root -> left);
    int height_of_right = get_height_without_using_field(root -> right);
    return 1 + (height_of_left < height_of_right ? height_of_left : height_of_right);
}

void print_bst(BSTNode const* root, char const* label) {
    printf("%s", label);
    print_bst_nodes(root);
    printf("\n");
}


int main (){
        BSTNode* root = NULL;
    insert(4, &root);
    insert(2, &root);
    insert(6, &root);
    insert(1, &root);
    insert(3, &root);
    insert(5, &root);
    insert(7, &root);
    print_bst(root, "Inserted as 4 2 6 1 3 5 7: ");
    printf("Height: %d\n", get_height(root));
    printf("Height: %d\n", get_height_without_using_field(root));
    assert(is_every_node_in_tree_avl_balanced(root));
    free_tree(&root);

    insert(1, &root);
    insert(2, &root);
    insert(3, &root);
    insert(4, &root);
    insert(5, &root);
    insert(6, &root);
    insert(7, &root);
    print_bst(root, "Inserted as 1 2 3 4 5 6 7: ");
    printf("Height: %d\n", get_height(root));
    printf("Height: %d\n", get_height_without_using_field(root));
    assert(is_every_node_in_tree_avl_balanced(root));
    free_tree(&root);

    insert(7, &root);
    insert(6, &root);
    insert(5, &root);
    insert(4, &root);
    insert(3, &root);
    insert(2, &root);
    insert(1, &root);
    print_bst(root, "Inserted as 7 6 5 4 3 2 1: ");
    printf("Height: %d\n", get_height(root));
    printf("Height: %d\n", get_height_without_using_field(root));
    assert(is_every_node_in_tree_avl_balanced(root));
    free_tree(&root);

    return 0;
}