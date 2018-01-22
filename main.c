#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    unsigned int count;
    const char *word;
    struct node *left;
    struct node *right;
} Node;

static const char SPACE = 32;


Node *createLeaf(char *word) {
    struct node *leaf = (Node *) malloc(sizeof(Node));
    leaf->word = malloc(sizeof(word));
    strcpy(leaf->word, word);
    leaf->count = 1;
    leaf->left = NULL;
    leaf->right = NULL;
    return leaf;
}


void insertWord(Node *leaf, char *word) {
    if (searchWord(leaf, word)) {
        return;
    }
    if (leaf == NULL)
        leaf = createLeaf(word);

    else if (strcmp(word, leaf->word) < 0) {
        if (leaf->left != NULL)
            insertWord(leaf->left, word);
        else
            leaf->left = createLeaf(word);

    } else if (strcmp(word, leaf->word) > 0) {
        if (leaf->right != NULL)
            insertWord(leaf->right, word);
        else
            leaf->right = createLeaf(word);
    }
}

int searchWord(Node *node1, char *word) {
    if (node1 == 0)
        return 0;

    if (strcmp(word, node1->word) == 0) {
        ++node1->count;
        return 1;
    } else if (strcmp(word, node1->word) < 0)
        searchWord(node1->left, word);

    else if (strcmp(word, node1->word) > 0)
        searchWord(node1->right, word);
}

/*
 Given a binary search tree, print out
 its data elements in increasing
 sorted order.
*/
void printTree(Node *node) {
    if (node == NULL) return;

    printTree(node->left);
    printf("\n%s: %d", node->word, node->count);
    printTree(node->right);
}

void deleteTree(Node *node) {
    if (node == NULL) return;

    deleteTree(node->left);
    deleteTree(node->right);
    free(node->word);
    node->word = NULL;
    free(node);
    node = NULL;
}

Node *buildTree( Node *node1) {
    char word[22];
    unsigned int i = 0;
    char letter;


    FILE *file = fopen("/home/yushitosh/CLionProjects/msl-clang-001/input01.txt", "r");
    if (file == NULL) {
        printf("Error! File cannot be opened");
        exit(1);
    }



    while (fgetc(file)!=EOF) {
        letter = fgetc(file);
        switch (letter) {
            case 32: {
                char temp[i + 1];
                int size = i;
                strncpy(temp, word, size);
                temp[size] = '\n';
                if (node1 != 0)
                    insertWord(node1, temp);
                else
                    node1 = createLeaf(temp);

                i = 0;
                break;
            }
            default: {
                word[i] = letter;
                ++i;
            }
        }
    }
    fclose(file);
}

int main(int argc, char **argv) {

//    Node *root = createLeaf("one");
//    insertWord(root, "go");
//    insertWord(root, "two");
//    insertWord(root, "three");
//    insertWord(root, "two");
//    insertWord(root, "three");

//    deleteTree(root);
    Node *root = 0;


    buildTree(root);


    exit(0);
}