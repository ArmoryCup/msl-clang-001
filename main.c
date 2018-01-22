#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int count;
    const char *word;
    struct node *left;
    struct node *right;
} Node;

Node *root = 0;


Node *createLeaf(char *word) {
    struct node *leaf = (Node *) malloc(sizeof(Node));
    leaf->word = malloc(sizeof(word));
    strcpy(leaf->word, word);
    leaf->left = NULL;
    leaf->right = NULL;
    return leaf;
}

int buildTree(char *word) {
    if (root != 0)
        return 1;
    else {
        root = createLeaf(word);
        return 0;
    }


}

void insertWord(Node *leaf, const char *word) {
    if (leaf == NULL)
        leaf = createLeaf(word);

    else if (strcmp(word, leaf->word) < 0) {
        if (leaf->left != NULL)
            insertWord(leaf->left, word);
        else
            leaf->left = createLeaf(word);
    } else if (word > leaf->word) {
        if (leaf->right != NULL)
            insertWord(leaf->right, word);
        else
            leaf->right = createLeaf(word);
    }
}


int main(int argc, char **argv) {

//    Node *root = createLeaf("one");

//    insertWord(root, "go");
//    insertWord(root, "two");
//    insertWord(root, "three");



    char word[20];
    char c;
    FILE *input;
    input = fopen("/home/yushitosh/CLionProjects/msl-clang-001/input01.txt", "r");

    if (input == NULL) {
        printf("Error!");
        exit(1);
    }


    int i = 0;
    int wLengh = 0;
    while (1) {
        c = fgetc(input);
        switch (c) {
            case EOF:
                break;
            case 32: {
                char s[i+1];
                strncpy(s, word, i);
                i=0;
                break;
            }
            default: {
                word[i] = c;
                ++i;
            }
        }

    }
    fclose(input);


    exit(0);
}