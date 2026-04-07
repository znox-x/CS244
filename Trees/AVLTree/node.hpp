#pragma once

struct node {
    node* parent;
    int elem;
    node* left;
    node* right;

    int depth() {
        if (!parent) {
            return 0;
        }

        return 1 + parent->depth();
    }

    int height() {
        if (!left && !right) {
            return 1;
        }
        
        int l = left ? left->height() : 0;
        int r = right ? right->height() : 0;

        return 1 + (l > r ? l : r);
    }
};