struct node {
    node* parent;
    int elem;
    node* left = nullptr;
    node* right = nullptr;
    bool isRed;
};