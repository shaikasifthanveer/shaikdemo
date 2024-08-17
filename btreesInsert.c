#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 5 // Maximum degree of the B-tree

struct BTreeNode {
    int num_keys; // Number of keys currently in the node
    int keys[M-1]; // Array of keys
    struct BTreeNode *children[M]; // Array of child pointers
    bool is_leaf; // True if node is a leaf
};

// Function to create a new node
struct BTreeNode *createNode(bool is_leaf) {
	int i;
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->num_keys = 0;
    newNode->is_leaf = is_leaf;
    for (i = 0; i < M; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function to split a full child node
void splitChild(struct BTreeNode *parent, int index) {
    struct BTreeNode *child = parent->children[index];
    struct BTreeNode *newNode = createNode(child->is_leaf);
	int i;
    newNode->num_keys = M/2 - 1;

    // Move keys and children to the new node
    for (i = 0; i < M/2 - 1; i++) {
        newNode->keys[i] = child->keys[i + M/2];
    }

    if (!child->is_leaf) {
        for (i = 0; i < M/2; i++) {
            newNode->children[i] = child->children[i + M/2];
        }
    }

    child->num_keys = M/2 - 1;

    // Shift parent's children to make space for the new node
    for (i = parent->num_keys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }

    parent->children[index + 1] = newNode;

    // Shift parent's keys to insert the middle key from the child
    for (i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }

    parent->keys[index] = child->keys[M/2 - 1];
    parent->num_keys++;
}

// Function to insert a key into a non-full node
void insertNonFull(struct BTreeNode *node, int key) {
    int i = node->num_keys - 1;

    if (node->is_leaf) {
        // Insert key into the sorted order
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        // Find the child to insert the key
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        i++;

        if (node->children[i]->num_keys == M - 1) {
            // Split child if it's full
            splitChild(node, i);
            // Determine which of the two children is the new one
            if (node->keys[i] < key) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Function to insert a key into the B-tree
void insert(struct BTreeNode **root, int key) {
    struct BTreeNode *node = *root;

    if (node == NULL) {
        // Create a new root node
        *root = createNode(true);
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
    } else {
        if (node->num_keys == M - 1) {
            // Split the root if it's full
            struct BTreeNode *new_root = createNode(false);
            new_root->children[0] = node;
            splitChild(new_root, 0);
            *root = new_root;
        }
        insertNonFull(*root, key);
    }
}

// Function to traverse and print the B-tree in-order
void traverse(struct BTreeNode *root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->num_keys; i++) {
            traverse(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        traverse(root->children[i]);
    }
}

// Search node
int search(int val, struct BTreeNode *myNode){
	int i=0;
	while(i<myNode->num_keys && myNode->keys[i] < val)
		i++;
	if(myNode->keys[i] == val){
		printf("%d is found", val);
        return;
	}
	search(val,myNode->children[i]);
	return;
}

// Main function to test B-tree implementation
int main() {
    struct BTreeNode *root = NULL;
    int val, sear, i;
    char ch;
    for (i = 0; i < 100; i++) {
    	insert(&root, rand() % 500);
    }

    printf("In-order traversal of the B-tree: ");
    traverse(root);
    printf("\n");

    printf("Enter element to be searched: ");
    scanf("%d",&val);
    search(val, root);
    printf("\n");

    return 0;
}
