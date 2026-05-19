#include <iostream>
#include <string>
using namespace std;

struct node {
	char ch;
	int weight;
	node *left, *right, *parent;

	node(char c, int w) : ch(c), weight(w), left(nullptr), right(nullptr), parent(nullptr) {};

	// TODO getCode
	string getCode() {
	    if (!parent)    return "";
	    
	    if (this == parent->left) {
	        return parent->getCode() + "0";
	    } else {
	        return parent->getCode() + "1";
	    }
	}
};