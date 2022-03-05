#ifndef ALGORITHM_RED_BLACK_TREE
#define ALGORITHM_RED_BLACK_TREE
#include<algorithm>


// 1. root is black
// 2. nil is black
// 3. child nodes of red are black
// 4. every path to nil node have the same number of black nodes
namespace algorithm::rbtree {

	enum class Color : char { RED, BLACK }; // 1 byte enum

	template<typename K, typename V>
	struct node{
		K key;
		V value;
		Color color;
		node* parent;
		node* left;
		node* right;
	};

	template<typename K, typename V> // comprison operator < for type K should be implemented
	class RedBlackTree {
	private:
		node<K, V>* root; // root. parent is nil
		node<K, V>* nil; // nil node

	public:
		explicit RedBlackTree();
		RedBlackTree(const RedBlackTree&) = delete;
		RedBlackTree& operator=(const RedBlackTree&) = delete;
		~RedBlackTree();
		node<K, V>* find_node(K key) const; // returns a pointer to the node or nullptr(key not found)
		void rb_insert(K key, V value);
		void rb_delete(K key);
		void rb_delete_all_nodes(); // deallocates all nodes
		void show_tree() const; // displays the tree info
		
	private:
		node<K, V>* find_node(K key, node<K, V>* current) const; // helper function
		void left_rotation(node<K, V>* x); // rotate the subtree around current to the left
		void right_rotation(node<K, V>* y); // rotate to the right
		void rb_insert_self_balance(node<K, V>* current); // perform self balancing
		node<K, V>* rb_min(node<K, V>* current) const; // find the minimum node from the subtree of current
		void rb_transplant(node<K, V>* x, node<K, V>* y); // replace x with y
		void rb_delete_self_balance(node<K, V>* current); // perform self balancing
		void rb_delete_all_nodes(node<K,V>* current); // helper functoin
		void show_tree(node<K, V>* current, int node_num = 0) const; // helper function. root = 0
	};
}

#endif // !ALGORITHM_RED_BLACK_TREE
