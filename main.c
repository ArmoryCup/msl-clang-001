#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    unsigned int count;
    char *word;
    struct node *left;
    struct node *right;
} Node;

const char SPACE = 32;
const char NULL_CHARACTER = '\0';
FILE *file_write = 0;

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


void deleteTree(Node *node) {
    if (node == NULL) return;

    deleteTree(node->left);
    deleteTree(node->right);
    free(node->word);
    node->word = NULL;
    free(node);
    node = NULL;
}

Node *buildTree(FILE *file) {
    char word[22];
    unsigned int i = 0;
    char letter;
    Node *node1 = NULL;;


    if (file == NULL) {
        printf("Error! File cannot be opened");
        exit(1);
    }


    do {
        letter = fgetc(file);
        if (letter == SPACE || letter == '\n') {

            char temp[i + 1];
            strncpy(temp, word, i);
            temp[i] = NULL_CHARACTER;

            if (node1 != 0)
                insertWord(node1, temp);
            else
                node1 = createLeaf(temp);

            i = 0;
        } else {
            word[i] = letter;
            ++i;
        }

    } while (letter != '\n');

    fclose(file);

    return node1;
}

char insertCurrentWord(char *word, const int size) {
    char temp[size + 1];
    strncpy(temp, word, size);
    temp[size] = '\n';
    return temp;
}

void generateOutput(Node *root) {
    if (root == NULL) return;

    generateOutput(root->left);
    fprintf(file_write, "\n%s: %d", root->word, root->count);
    generateOutput(root->right);


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

int main(int argc, char **argv) {

    FILE *file_read = fopen("/home/yushitosh/CLionProjects/msl-clang-001/input01.txt", "r");
    file_write = fopen("/home/yushitosh/CLionProjects/msl-clang-001/myoutput01.txt", "w");

    Node *root = 0;
    root = buildTree(file_read);

    generateOutput(root);
    fclose(file_write);
    deleteTree(root);
    exit(0);
}