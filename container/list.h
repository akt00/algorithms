#ifndef ALGORITHM_CONTAINER_LIST
#define ALGORITHM_CONTAINER_LIST
// implementation of doubly linked list
#include<iterator>
#include<functional>
#include<iostream>

namespace algorithm::container {

	// node for linked list
	template<typename VALUE>
	struct list_node {
		VALUE value;
		list_node<VALUE>* next;
		list_node<VALUE>* prev;
	};

	// doubly linked list class
	// either operator< must be implemented for custom objects or custom comparator must be provided if merge or sort operation are used
	template<typename V>
	class list {
	public:
		// forward iterator
		class list_iterator {
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = V;
			using pointer = V*;
			using reference = V&;

			explicit list_iterator(list_node<V>* arg) : current_ptr(arg) {}
			list_iterator& operator=(const list_iterator& arg) { current_ptr = arg.current_ptr; return *this; }
			list_iterator& operator++() { if (current_ptr != nullptr) current_ptr = current_ptr->next; return *this; } // prefix ++
			list_iterator operator++(int) { list_iterator ret = *this; ++(*this); return ret; } // postfix ++
			reference operator*() { return current_ptr->value; }
			pointer operator->() { return &current_ptr->value; }
			friend bool operator==(const list_iterator& l, const list_iterator& r) {
				if (l.current_ptr == r.current_ptr) return true;
				return false;
			}
			friend bool operator!=(const list_iterator& l, const list_iterator& r) {
				if (l.current_ptr != r.current_ptr) return true;
				return false;
			}

		private:
			list_node<V>* current_ptr;
		};

	private:
		unsigned list_size; // number of nodes in list
		list_node<V>* head; // pointer to the head node
		list_node<V>* tail; // pointer to the tail node

	public:
		list() { list_size = 0, head = nullptr, tail = nullptr; }
		list(const list<V>&);
		list& operator=(const list<V>&);
		~list() { clear(); }
		list_node<V>* front() const { return head; }
		list_node<V>* back() const { return tail; }
		list_iterator begin() const { return list_iterator(head); } // return iterator
		list_iterator end() const { return list_iterator(nullptr); } // return end of iterator
		bool empty() const { return (list_size == 0) ? true:false; }
		unsigned size() const { return list_size; }
		void push_front(V);
		void push_back(V);
		void pop_front();
		void pop_back();
		void clear();
		template<typename Comparator = std::less<>>
		void merge(list<V>&, Comparator comp = {}); // merge another list. the input list will be destroyed upon completion of merging.
		template<typename Comparator = std::less<>>
		void sort(Comparator comp = {});// performs merge sort
		// merge implementation is based on https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/
	private: // helper functions
		template<typename Comparator = std::less<>>
		auto merge_sort(list_node<V>* head, Comparator comp = {}) -> decltype(head);
		auto split(list_node<V>* head) -> decltype(head);
		template<typename Comparator = std::less<>>
		auto merge_nodes(list_node<V>* left, list_node<V>* right, Comparator comp = {}) -> decltype(head);
	};


	// list method implementatoins
	template<typename V>
	list<V>::list(const list<V>& arg) {
		list_size = 0;
		head = nullptr;
		tail = nullptr;
		for (auto i = arg.begin(); i != arg.end(); i++) {
			this->push_back(*i);
		}
	}

	template<typename V>
	list<V>& list<V>::operator=(const list<V>& arg) {
		if (arg != this) {
			this->clear();
			for (auto i = arg.begin(); i != arg.end(); i++) {
				this->push_back(*i);
			}
		}
	}

	template<typename V>
	void list<V>::push_front(V value) {
		list_node<V>* new_node = new list_node<V>{ value, nullptr, nullptr };
		if (head == nullptr) {
			head = new_node;
			tail = new_node;
		}
		else {
			head->prev = new_node;
			new_node->next = head;
			head = new_node;
		}
		list_size++;
	}

	template<typename V>
	void list<V>::push_back(V value) {
		list_node<V>* new_node = new list_node<V>{ value, nullptr, nullptr };
		if (tail == nullptr) {
			head = new_node;
			tail = new_node;
		}
		else {
			tail->next = new_node;
			new_node->prev = tail;
			tail = new_node;
		}
		list_size++;
	}

	template<typename V>
	void list<V>::pop_front() {
		if (head != nullptr) {
			auto temp = head;
			if (head->next == nullptr) {
				head = nullptr;
				tail = nullptr;
			}
			else {
				head = head->next;
				head->prev = nullptr;
			}
			list_size--;
			delete temp;
		}
	}

	template<typename V>
	void list<V>::pop_back() {
		if (tail != nullptr) {
			auto temp = tail;
			if (tail->prev == nullptr) {
				head = nullptr;
				tail = nullptr;
			}
			else {
				tail = tail->prev;
				tail->next = nullptr;
			}
			list_size--;
			delete temp;
		}
	}

	template<typename V>
	void list<V>::clear() {
		while (!this->empty()) {
			pop_back();
		}
	}

	template<typename V>
	template<typename Comparator>
	void list<V>::merge(list<V>& arg,  Comparator comp) {

		auto current1 = head;
		auto current2 = arg.head;
		decltype(head) newHead = nullptr;
		decltype(tail) newTail = nullptr;
		this->list_size = 0;

		while (current1 != nullptr && current2 != nullptr) {
			list_size++;
			if (comp(current1->value, current2->value) == true) {
				if (newHead == nullptr) {
					newHead = current1;
					newTail = current1;
				}
				else {
					newTail->next = current1;
					current1->prev = newTail;
					newTail = newTail->next;
				}
				current1 = current1->next;
			}
			else {
				if (newHead == nullptr) {
					newHead = current2;
					newTail = current2;
				}
				else {
					newTail->next = current2;
					current2->prev = newTail;
					newTail = newTail->next;
				}
				current2 = current2->next;
			}
		}

		while (current1 != nullptr) {
			list_size++;
			if (newHead == nullptr) {
				newHead = current1;
				newTail = current1;
			}
			else {
				newTail->next = current1;
				current1->prev = newTail;
				newTail = newTail->next;
			}
			current1 = current1->next;
		}

		while (current2 != nullptr) {
			list_size++;
			if (newHead == nullptr) {
				newHead = current2;
				newTail = current2;
			}
			else {
				newTail->next = current2;
				current2->prev = newTail;
				newTail = newTail->next;
			}
			current2 = current2->next;
		}

		head = newHead;
		tail = newTail;

		arg.head = nullptr;
		arg.tail = nullptr;
		arg.list_size = 0;
	}

	template<typename V>
	template<typename Comparator>
	void list<V>::sort(Comparator comp) {

		head = merge_sort(head, comp);
		if (head == nullptr) tail = nullptr;
		else {
			auto current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			tail = current;
		}
	}
	// break down the list nodes into a single node and merge them
	template<typename V>
	template<typename Comparator>
	auto list<V>::merge_sort(list_node<V>* head, Comparator comp) -> decltype(head) {

		if (head == nullptr || head->next == nullptr) return head;

		auto rightHead = split(head);
		head = merge_sort(head);
		rightHead = merge_sort(rightHead);
		return merge_nodes(head, rightHead, comp);
	}

	template<typename V>
	auto list<V>::split(list_node<V>* head) -> decltype(head) {

		auto fast = head;
		auto slow = head;
		while (fast->next != nullptr && fast->next->next != nullptr) {
			fast = fast->next->next;
			slow = slow->next;
		}
		auto temp = slow->next;
		slow->next = nullptr;
		return temp;
	}

	template<typename V>
	template<typename Comparator>
	auto list<V>::merge_nodes(list_node<V>* left, list_node<V>* right, Comparator comp) -> decltype(head) {

		if (left == nullptr) return right;
		if (right == nullptr) return left;
		if (comp(left->value, right->value) == true) {
			left->next = merge_nodes(left->next, right, comp);
			left->next->prev = left;
			left->prev = nullptr;
			return left;
		}
		else {
			right->next = merge_nodes(left, right->next, comp);
			right->next->prev = right;
			right->prev = nullptr;
			return right;
		}
	}

	/*
	template<typename V>
	template<typename Comparator>
	void list<V>::merge_sort(list_node<V>* left, list_node<V>* right, Comparator comp) {

		std::cout << "left value = " << left->value << " right value = " << right->value << std::endl;
		if (left != right) {
			auto midNode = bidrectional_mid_finder(left, right);
			auto rightHead = midNode->next;
			std::cout << "mid node = " << midNode->value << std::endl;
			merge_sort(left, midNode, comp);
			merge_sort(midNode->next, right, comp);
			std::cout << "left = " << left->value << " right = " << right->value << std::endl;
			std::cout << "merge called...\n";
			merge_nodes(left, rightHead, right->next, comp);
		}
	}

	// test passed
	template<typename V>
	auto list<V>::bidrectional_mid_finder(list_node<V>* left, list_node<V>* right) -> decltype(head) const {

		while (left != right && left->next != right) {
			left = left->next;
			right = right->prev;
		}
		return left;
	}
	
	// might contain bugs
	// leftHead cannot be nullptr
	template<typename V>
	template<typename Comparator>
	void list<V>::merge_nodes(list_node<V>* leftHead, list_node<V>* rightHead, list_node<V>* rightEnd, Comparator comp) {

		std::cout << "leftHead = " << leftHead->value << " rightHead = " << rightHead->value << std::endl;
		if(rightEnd != nullptr) std::cout << " rightEnd = " << rightEnd->value << std::endl;
		
		auto currentLeft = leftHead;
		auto currentRight = rightHead;
		auto newHeadPrev = leftHead->prev;
		list_node<V>* newHead = nullptr;
		list_node<V>* newTail = newHead;
		rightHead->prev->next = nullptr; // set the end of left list to nullptr
		if (rightEnd != nullptr) rightEnd->prev->next = nullptr; // set the end of right list to nullptr

		while (currentLeft != nullptr && currentRight != nullptr) {
			if (comp(currentLeft->value, currentRight->value) == true) {
				if (newHead == nullptr) {
					newHead = currentLeft;
					newTail = currentLeft;
				}
				else {
					newTail->next = currentLeft;
					currentLeft->prev = newTail;
					newTail = newTail->next;
				}
				currentLeft = currentLeft->next;
			}
			else {
				if (newHead == nullptr) {
					newHead = currentRight;
					newTail = currentRight;
				}
				else {
					newTail->next = currentRight;
					currentRight->prev = newTail;
					newTail = newTail->next;
				}
				currentRight = currentRight->next;
			}
		}
		
		while (currentLeft != nullptr) {
			if (newHead == nullptr) {
				newHead = currentLeft;
				newTail = currentLeft;
			}
			else {
				newTail->next = currentLeft;
				currentLeft->prev = newTail;
				newTail = newTail->next;
			}
			currentLeft = currentLeft->next;
		}

		while (currentRight != nullptr) {
			if (newHead == nullptr) {
				newHead = currentRight;
				newTail = currentRight;
			}
			else {
				newTail->next = currentRight;
				currentRight->prev = newTail;
				newTail = newTail->next;
			}
			currentRight = currentRight->next;
		}

		newHead->prev = newHeadPrev;
		if (newHeadPrev != nullptr) newHeadPrev->next = newHead;
		newTail->next = rightEnd;
		if (rightEnd != nullptr) rightEnd->prev = newTail;

		std::cout << newHead->prev << " " << newHead->value << " " << newTail->value << " " << newTail->next->value << " exited...\n";
	}
	*/
}

#endif // !ALGORITHM_CONTAINER_LIST
