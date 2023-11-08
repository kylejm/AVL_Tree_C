
typedef struct _BSTNode{

    int value;
    struct _BSTNode *left;
    struct _BSTNode *right;
    int height;
} BSTNode;

int get_height(BSTNode const* root);    

int get_height_without_using_field(BSTNode* root);

int get_balance_score(BSTNode const* root);

void rotate_counter_clockwise(BSTNode** a_root);

void rotate_clockwise(BSTNode** a_root);

void balance_after_insert_in_left(int value, BSTNode** a_root);

void balance_after_insert_in_right(int value, BSTNode** a_root);

void insert(int value, BSTNode** a_root);

void free_tree(BSTNode** a_root);

void print_bst_nodes(BSTNode const* root);

void print_bst(BSTNode const* root, char const* label);

void update_height(BSTNode* root);

bool is_every_node_in_tree_avl_balanced(BSTNode const* root);


