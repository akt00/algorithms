#include"rbtree.h"

using namespace algorithm::rbtree;


template<typename K, typename V>
RedBlackTree<K, V>::RedBlackTree() {

	this->nil = new node<K, V>({}, {}, rbtree::Color::BLACK, {}, {}, {});
	root = this->nil;
}

template<typename K, typename V>
RedBlackTree<K, V>::~RedBlackTree() {

	this->rb_delete_all_nodes();
	delete this->nil;
}
template<typename K, typename V>
node<K, V>* RedBlackTree<K, V>::find_node(K key) const {

	return this->find_node(key, this->root);
}

template<typename K, typename V>
node<K, V>* RedBlackTree<K, V>::find_node(K key, node<K, V>* current) const {

	if (current == this->nil) {
		return nullptr;
	}
	else if (current->key == key) {
		return current;
	}
	else {
		if (key < current->key) return this->find_node(key, current->left);
		else return this->find_node(key, current->right);
	}
}


template <typename K, typename V>
void RedBlackTree<K, V>::rb_insert(K key, V value) {

	auto newNode = new node<K, V>{key, value, Color::RED, this->nil, this->nil, this->nil};
	auto parent = this->nil;
	auto current = this->root;

	// loop until current reaches NIL
	while (current != this->nil) {
		parent = current;
		if (newNode->key < current->key) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	newNode->parent = parent; 

	if (parent == this->nil) { // root
		this->root = newNode;
	}
	else if (newNode->key < parent->key) { // left node
		parent->left = newNode;
	}
	else { // right node
		parent->right = newNode;
	}

	rb_insert_self_balance(newNode);
}

// x.parent.left/right, x.right, x.parent, y.left, y.parent, b.parent
template<typename K, typename V>
void RedBlackTree<K, V>::left_rotation(node<K, V>* x) {

	auto y = x->right;
	x->right = y->left; // x.right
	if (y->left != this->nil) {
		y->left->parent = x; // b.parent
	}
	y->parent = x->parent; // y.parent
	if (x->parent->left == x) { // x.parent.left/right
		x->parent->left = y;
	}
	else {
		x->parent->right = y; 
	}
	y->left = x; // y.left
	x->parent = y; // x.parent
}

// y.parent.left/right, y.parent, y.left, x.parent, x.right, b.parent
template<typename K, typename V>
void RedBlackTree<K,V>::right_rotation(node<K, V>* y) {

	auto x = y->left;
	y->left = x->right; // y.left
	if (x->right != this->nil) {
		x->right->parent = y; // b.parent
	}
	x->parent = y->parent; // y.parent
	if (x->parent == this->nil) {
		this->root = x;
	}
	else if (y->parent->left == y) { // y.parent.left.right
		y->parent->left = x;
	}
	else {
		y->parent->right = x;
	}
	x->right = y; // x.right
	y->parent = x; // y.parent
}

// 1. root red: change root to black at the end
// 2. uncle is red: recolor, uncle, parent, and grandparent
// 3. uncle is black & triangle: rotate left/right around parent
// 4. uncle is black & line: rotate left/right around parent, and recolor parent and grandparent 
template<typename K, typename V>
void RedBlackTree<K, V>::rb_insert_self_balance(node<K, V>* current) {

	// while parent is red
	while (current->parent->color == Color::RED) { 
		if (current->parent == current->parent->parent->left) { // if parent is left node
			auto uncle = current->parent->parent->right;
			if (uncle->color == Color::RED) { // uncle is red
				current->parent->color = Color::RED;
				uncle->color = Color::BLACK;
				current->parent->parent->color = Color::RED;
				current = current->parent->parent;
			}
			else { // uncle is black
				if (current == current->parent->right) { // triangle
					current = current->parent;
					this->left_rotation(current);
				}
				current->parent->color = Color::BLACK;
				current->parent->parent->color = Color::RED;
				this->right_rotation(current->parent->parent);
			}
		}
		else { // if parent is right node
			auto uncle = current->parent->parent->left;
			if (uncle->color == Color::RED) { // uncle is red
				current->parent->color = Color::RED;
				uncle->color = Color::BLACK;
				current->parent->parent->color = Color::RED;
				current = current->parent->parent;
			}
			else { // uncle is black
				if (current == current->parent->left) { // triangle
					current = current->parent;
					this->right_rotation(current);
				}
				current->parent->color = Color::BLACK;
				current->parent->parent->color = Color::RED;
				this->left_rotation(current->parent->parent);
			}
		}
	}
}

template<typename K, typename V>
node<K, V>* RedBlackTree<K, V>::rb_min(node<K, V>* current) const {

	while (current != this->nil) {
		current = current->left;
	}
	return current;
}

template<typename K, typename V>
void RedBlackTree<K, V>::rb_transplant(node<K, V>* x, node<K, V>* y) {

	if (x->parent == this->nil) { // x is root
		this->root = y;
	}
	else if (x == x->parent->left) { // x is a left node
		x->parent->left = y;
	}
	else { // x is a right node
		x->parent->right = y;
	}
	y->parent = x->parent;
}

// x: y's right child
// y: min node from target.right
template<typename K, typename V>
void RedBlackTree<K, V>::rb_delete(K key) {

	auto target = this->find_node(key);
	if (target == nullptr) return;
	
	auto y = target;
	auto y_original_color = y->color;
	node<K, V>* x;
	if (target->left == this->nil) { // left is nil
		x = target->right;
		this->rb_transplant(target, target->right); // transplant right node to target
	}
	else if (target->right == this->nil) { // right is nil
		x = target->left;
		this->rb_transplant(target, target->left); // transplant left node to target
	}
	else {
		y = this->rb_min(target->right); // find min node from right node
		y_original_color = y->color;
		x = y->right;
		if (y->parent == target) { // y is child of target
			x->parent = y;
		}
		else {
			this->rb_transplant(y, y->right);
			y->right = target->right;
			y->right->parent = y;
		}
		this->rb_transplant(target, y);
		y->left = target->left;
		y->left->parent = y;
		y->color = target->color;
	}
	if (y_original_color == Color::BLACK) { // deleted node is black -> perform balancing
		this->rb_delete_self_balance(x);
	}
}

template<typename K, typename V>
void RedBlackTree<K, V>::rb_delete_self_balance(node<K, V>* current) {
	auto temp = current; // deallocates this node at the end

	while ((current != this->root) && (current->color == Color::BLACK)) {
		if (current == current->parent->left) {
			auto w = current->parent->right;
			if (w->color == Color::RED) {
				w->color = Color::BLACK;
				current->parent->color = Color::RED;
				this->left_rotation(current->parent);
				w = current->parent->right;
			}
			if ((w->left->color == Color::BLACK) && (w->right->color == Color::BLACK)) {
				w->color = Color::RED;
				current = current->parent;
			}
			else {
				if (w->right->color == Color::BLACK) {
					w->left->color = Color::BLACK;
					w->color = Color::RED;
					this->right_rotation(w);
					w = current->parent->right;
				}
				w->color = current->parent->color;
				current->parent->color = Color::BLACK;
				w->right->color = Color::BLACK;
				this->left_rotation(current->parent);
				current = this->root;
			}
		}
		else { // opposite
			auto w = current->parent->left;
			if (w->color == Color::RED) {
				w->color = Color::BLACK;
				current->parent->color = Color::RED;
				this->right_rotation(current->parent);
				w = current->parent->left;
			}
			if ((w->right->color == Color::BLACK) && (w->left->color == Color::BLACK)) {
				w->color = Color::RED;
				current = current->parent;
			}
			else {
				if (w->left->color == Color::BLACK) {
					w->right->color = Color::BLACK;
					w->color = Color::RED;
					this->left_rotation(w);
					w = current->parent->left;
				}
				w->color = current->parent->color;
				current->parent->color = Color::BLACK;
				w->left->color = Color::BLACK;
				this->right_rotation(current->parent);
				current = this->root;
			}
		}
	}

	current->color = Color::BLACK;
	delete temp;
}

// set root to nil
template<typename K, typename V>
void RedBlackTree<K, V>::rb_delete_all_nodes() {

	this->rb_delete_all_nodes(this->root);
}

template<typename K, typename V>
void RedBlackTree<K, V>::rb_delete_all_nodes(node<K, V>* current) {

	if (current != this->nil) {
		this->rb_delete_all_nodes(current->left);
		this->rb_delete_self_balance(current->right);
		delete current;
	}
	if (current = this->root) this->root = this->nil;
}

template<typename K, typename V>
void RedBlackTree<K, V>::show_tree() const {

	this->show_tree(this->root);
}

template<typename K, typename V>
void RedBlackTree<K, V>::show_tree(node<K, V>* current, int node_num) const {

	if (current != this->nil) {
		show_tree(current->left, node_num * 2 + 1);
		auto color = (current->color == Color::RED) ? "RED" : "BLACK";
		std::cout << "key = " << current->key << " node_num = " << node_num
			<< " node_color = " << color << std::endl;
		show_tree(current->right, node_num * 2 + 2);
	}
}

// explicit instanciation
template algorithm::rbtree::RedBlackTree<int, int>;
