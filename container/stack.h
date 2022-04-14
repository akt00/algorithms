#ifndef ALGORITHM_CONTAINER_STACK
#define ALGORITHM_CONTAINER_STACK
// linked list implementation of stack


namespace algorithm::container {

	template<typename T>
	class stack {
	private:
		QueueStackNode<T>* head;
		unsigned stack_size;
	public:
		stack();
		stack(const stack<T>&);
		stack<T>& operator=(const stack<T>&);
		const QueueStackNode<T>& top() const; // calling top() while empty() causes an error
		bool empty() const;
		unsigned size() const;
		void push(T data);
		void pop();
		void clear();
		void swap(stack<T>& other);
	};

	template<typename T>
	stack<T>::stack() {
		head = nullptr;
		stack_size = 0;
	}

	template<typename T>
	stack<T>::stack(const stack<T>& other) {
		clear();
		auto current = other.head;
		while (current != nullptr) {
			push(current->data);
			current = current->next;
		}
	}

	template<typename T>
	stack<T>& stack<T>::operator=(const stack<T>& other) {
		if (&other != this) {
			clear();
			auto current = other.head;
			while (current != nullptr) {
				push(current->data);
				current = current->next;
			}
		}
	}

	template<typename T>
	const QueueStackNode<T>& stack<T>::top() const {
		return *head;
	}

	template<typename T>
	bool stack<T>::empty() const {
		return (stack_size > 0) ? true : false;
	}

	template<typename T>
	unsigned stack<T>::size() const {
		return stack_size;
	}

	template<typename T>
	void stack<T>::push(T data) {
		auto new_node = new QueueStackNode<T>{ data, head };
		head = new_node;
		stack_size++;
	}

	template<typename T>
	void stack<T>::pop() {
		if (empty() != false) {
			auto temp = head;
			head = head->next;
			delete temp;
			stack_size--;
		}
	}

	template<typename T>
	void stack<T>::clear() {
		while (empty() == false) {
			pop();
		}
	}

	template<typename T>
	void stack<T>::swap(stack<T>& other) {
		if (&other != this) {
			auto temp = head;
			head = other.head;
			other.head = temp;
		}
	}
}

#endif // !ALGORITHM_CONTAINER_STACK
