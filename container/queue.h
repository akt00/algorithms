#ifndef ALGORITHM_CONTAINER_QUEUE
#define ALGORITHM_CONTAINER_QUEUE
// linked list implementation of queue


namespace algorithm::container {

	// this node is used for queue and stack
	template<typename T>
	struct QueueStackNode {
		T data;
		QueueStackNode<T>* next;
	};

	template<typename T>
	class queue {
	private:
		QueueStackNode<T>* head; // out
		QueueStackNode<T>* tail; // in
		unsigned queue_size;
	public:
		queue();
		queue(const queue<T>& arg);
		queue& operator=(const queue<T>& arg);
		~queue();
		const QueueStackNode<T>& front() const;
		const QueueStackNode<T>& back() const;
		bool empty() const; // calling top() while empty() causes an error
		unsigned size() const;
		void push(T data);
		void pop();
		void clear();
	};

	template<typename T>
	queue<T>::queue() {
		head = nullptr;
		tail = nullptr;
		queue_size = 0;
	}

	template<typename T>
	queue<T>::queue(const queue<T>& arg) {
		clear();
		auto current = arg.head;
		while (current != nullptr) {
			push(current->data);
			current = current->next;
		}
	}

	template<typename T>
	queue<T>& queue<T>::operator=(const queue<T>& arg) {
		if (&arg != this) {
			clear();
			auto current = arg.head;
			while (current != nullptr) {
				push(current->data);
				current = current->next;
			}
		}
	}

	template<typename T>
	queue<T>::~queue() {
		clear();
	}

	template<typename T>
	const QueueStackNode<T>& queue<T>::front() const {
		return *head;
	}

	template<typename T>
	const QueueStackNode<T>& queue<T>::back() const {
		return *tail;
	}

	template<typename T>
	bool queue<T>::empty() const {
		return (queue_size > 0) ? true : false;
	}

	template<typename T>
	unsigned queue<T>::size() const {
		return queue_size;
	}

	template<typename T>
	void queue<T>::push(T data) {
		auto temp = new QueueStackNode<T>{ data, nullptr };
		if (tail == nullptr) {
			head = temp;
			tail = head;
		}
		else {
			tail->next = temp;
			tail = tail->next;
		}
		queue_size++;
	}

	template<typename T>
	void queue<T>::pop() {
		if (empty() == false) {
			auto temp = head;
			if (head == tail) { // avoid dangling pointer
				head = nullptr;
				tail = nullptr;
			}
			else {
				head = head->next;
			}
			queue_size--;
			delete temp;
		}
	}

	template<typename T>
	void queue<T>::clear() {
		while (empty() == false) {
			pop();
		}
	}
}

#endif // !ALGORITHM_CONTAINER_QUEUE
