#pragma once

#include <cassert>
#include <vector>

namespace edit {

	//		Fixed-Size Overwriting Stack
	
	template <class T>
	class FSOStack {
	public:
		FSOStack(size_t capacity)
			: m_capacity(capacity)
			, m_size(0)
			, m_bottom(0)
			, m_top(0)
		{
			assert(capacity >= 1);

			// Fill with T's default value but keeping the size to zero.
			m_items.reserve(m_capacity);
			for (size_t i = 0; i < m_capacity; i++) {
				m_items.push_back(T());
			}
		}

		size_t capacity() const { return m_capacity; }
		size_t size() const { return m_size; }
		bool empty() const { return size() == 0; }
		bool full() const { return size() == capacity(); }

		// Top returns a reference to the top item.
		// PRECONDITIONS
		//	!Empty()
		const T& top() const
		{
			assert(!empty());

			return m_items[m_top];
		}

		// Push adds an item at the top of the stack.
		// If the stack is full, the bottom item is overwritten.
		void push(const T &x)
		{
			// 1. Update indices and size
			if (full()) {
				increment(m_top);
				increment(m_bottom);
			}
			else if (empty()) {
				m_size = 1;
			}
			else {
				increment(m_top);
				++m_size;
			}

			// 2. Insert
			m_items[m_top] = x;
		}

		// Pop removes the top element if the stack is not empty.
		// Does nothing if the stack is empty.
		void pop()
		{
			if (empty()) {
				return;
			}

			if (size() > 1) {
				decrement(m_top);
			}

			--m_size;
		}

	private:
		void increment(size_t &i)
		{
			i = (i + 1) % capacity();
		}

		void decrement(size_t &i)
		{
			if (0 == i) {
				i = capacity() - 1;
			}
			else {
				--i;
			}
		}

	private:
		std::vector<T>	m_items;
		size_t			m_capacity;
		size_t			m_size;// current number of items
		size_t			m_bottom;
		size_t			m_top;
	};
}