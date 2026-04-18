#include <cstdlib>

struct node {
    node* parent;
    int keys[4];
    node** children = (node**)calloc(5, sizeof(node*));
    int size = 0;

    void insertKeyAt(int num, int index) {
        for (int i = size; i > index; i--) {
            keys[i] = keys[i-1];
        }
        keys[index] = num;
        size++;
    }

    bool contains(int num) {
        for (int i = 0; i < size; i++) {
            if (keys[i] == num) {
                return true;
            }
        }
        return false;
    }
};