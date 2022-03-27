#ifndef ALGORITHM_CONTAINER_LIST
#define ALGORITHM_CONTAINER_LIST
// implementation of doubly linked list
#include<iterator>


namespace algorithm::container {

	template<typename VALUE>
	struct list_node {
		VALUE value;
		list_node<VALUE>* next;
		list_node<VALUE>* prev;
	};

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
		explicit list() { list_size = 0, head = nullptr, tail = nullptr; }
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
		void merge(const list<V>&, bool) = delete; // not implemented
		void sort() = delete; // not implemented
	};


	// list member implementatoins
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
}

#endif // !ALGORITHM_CONTAINER_LIST
