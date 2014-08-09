#include <iostream>
#include <string>
#include <bitset>

using namespace std;

// returns 0 or 1 depending on the value of the bit in the string at given position (bitnr, bitnr = 0 is first bit, etc)
int getBit(const string& str, int bitnr) {
	int placeCharacter = bitnr / 8;
	int placeBit = bitnr % 8;
	
	int compare = 1;
	compare <<= (7 - placeBit);
	
	return (str[placeCharacter] & compare) == 0 ? 0 : 1;
}

class BinaryTrie;

class Node {
	friend class BinaryTrie;
private:
	Node* left;
	Node* right;
public:
	Node() : left(0), right(0) { }
	
	virtual bool isLeaf() {
		return false;
	}
};

class Leaf : public Node {
	friend class BinaryTrie;
private:
	string key;
public:
	Leaf(const string& key) : key(key) { }
	
	virtual bool isLeaf() {
		return true;
	}
};

class BinaryTrie {
private:
	Node* root;
public:
	BinaryTrie() : root(0) { }
	
	void insert(const string& key) {
		insert(key, root, 0);
	}
	
	bool contains(const string& key) {
		return contains(key, root, 0);
	}
	
	void inorder(void (*callback) (const string& key)) {
		inorder(callback, root);
	}
private:
	void insert(const string& key, Node*& node, int level) {
		if(node == 0)
			node = new Leaf(key);
		else {
			if(node->isLeaf()) {
				Leaf* leaf = (Leaf*) node;
				node = new Node();
				
				if(getBit(leaf->key, level) == 0)
					node->left = leaf;
				else
					node->right = leaf;
			}
			
			if(getBit(key, level) == 0)
				insert(key, node->left, level + 1);
			else
				insert(key, node->right, level + 1);
		}
	}
	
	bool contains(const string& key, Node* node, int level) {
		if(node == 0)
			return false;
		else if(node->isLeaf()) {
			if(((Leaf*) node)->key == key)
				return true;
			else
				return false;
		} else if(getBit(key, level) == 0)
			return contains(key, node->left, level + 1);
		else
			return contains(key, node->right, level + 1);
	}
	
	void inorder(void (*callback) (const string& key), Node* node) {
		if(node == 0)
			return;
		else if(node->isLeaf())
			callback(((Leaf*) node)->key);
		else {
			inorder(callback, node->left);
			inorder(callback, node->right);
		}
		
	}
};

void print(const string& str) {
	cout << str << " ";
}

int main() {
	
	BinaryTrie trie;
	trie.insert("a");
	trie.insert("b");
	trie.insert("c");
	trie.insert("d");
	trie.insert("e");
	trie.insert("f");
	trie.insert("g");
	
	cout << trie.contains("a") << endl;
	cout << trie.contains("c") << endl;
	cout << trie.contains("g") << endl;
	
	cout << trie.contains("aardappel") << endl;
	cout << trie.contains("h") << endl;
	
	trie.inorder(&print);
	

	return 0;
}