#ifndef ALGORITHM_CONTAINER_STACK
#define ALGORITHM_CONTAINER_STACK
#ifndef ALGORITHM_CONTAINER_QUEUE
#include"queue.h"
#endif
// linked list implementation of stack


namespace algorithm::container {

	template<typename T>
	class stack {
	private:
		QueueStackNode<T>* head;
		unsigned stack_size;
	public:
		stack();
		stack(const stack<T>& other);
		stack<T>& operator=(const stack<T>& other);
		~stack();
		T& top() const; // calling top() while empty() causes an error
		bool empty() const;
		unsigned size() const;
		void push(T data); // this implementation call copy consturctor twice on user objects
		void pop();
		void clear();
		void swap(stack<T>& other);
	};


	// implementatinos

	template<typename T>
	stack<T>::stack() {

		head = nullptr;
		stack_size = 0;
	}

	template<typename T>
	stack<T>::stack(const stack<T>& other) {

		auto current = other.head;
		if (current == nullptr) head = nullptr;
		while (current != nullptr) {
			push(current->data);
			current = current->next;
		}
		stack_size = other.stack_size;
	}

	template<typename T>
	stack<T>& stack<T>::operator=(const stack<T>& other) {

		if (&other != this) {
			clear();
			auto current = other.head;
			if (current != nullptr) head = nullptr;
			while (current != nullptr) {
				push(current->data);
				current = current->next;
			}
			stack_size = other.stack_size;
		}
	}

	template<typename T>
	stack<T>::~stack() { clear(); }

	template<typename T>
	T& stack<T>::top() const { return head->data; }

	template<typename T>
	bool stack<T>::empty() const { return (stack_size == 0) ? true : false; }

	template<typename T>
	unsigned stack<T>::size() const { return stack_size; }
	
	// this implementation calls copy constructor twice
	template<typename T>
	void stack<T>::push(T data) {

		auto new_node = new QueueStackNode<T>{ data, head };
		head = new_node;
		stack_size++;
	}

	template<typename T>
	void stack<T>::pop() {

		if (!empty()) {
			auto temp = head;
			head = head->next;
			delete temp;
			stack_size--;
		}
	}

	template<typename T>
	void stack<T>::clear() { while (!empty()) pop(); }

	template<typename T>
	void stack<T>::swap(stack<T>& other) {

		if (&other != this) {
			auto temp = head;
			head = other.head;
			other.head = temp;

			auto tmp = other.stack_size;
			other.stack_size = stack_size;
			stack_size = tmp;
		}
	}
}

#endif // !ALGORITHM_CONTAINER_STACK
