#include "heap.hpp"

// TODO huffman
node* huffman_code(Heap* heap) {
    while (heap->size() != 1) {
        node* T1 = heap->removeMin();
        node* T2 = heap->removeMin();
        
        node* n = new node(' ', T1->weight + T2->weight);
        n->left = T1;
        n->right = T2;
        T1->parent = n;
        T2->parent = n;
        
        heap->insert(n);
    }
    
    return heap->removeMin();
}