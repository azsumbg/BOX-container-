#pragma once

unsigned char BOX_Ok{ 0b00000000 };
unsigned char BOX_invalid_element{ 0b00000001 };
unsigned char BOX_invalid_index{ 0b00000010 };
unsigned char BOX_invalid_base{ 0b00000100 };
unsigned char BOX_not_valid{ 0b00001000 };
unsigned char BOX_increased{ 0b00010000 };
unsigned char BOX_decreased{ 0b00100000 };

namespace box
{
	template<typename T> class BOX
	{
	private:
		T* m_base_ptr{ nullptr };
		size_t max_container_size{ 0 };

		size_t push_back_position{ 0 };

	public:
		BOX(size_t max_lenght, T* init_value = nullptr) :max_container_size{ max_lenght }, m_base_ptr{ new T[max_lenght] }
		{
			if (init_value)
			{
				for (size_t i = 0; i < max_lenght; ++i)*(m_base_ptr + i) = *init_value;
				push_back_position = max_container_size;
			}
		}

		BOX(size_t max_lenght, T init_value) :max_container_size{ max_lenght }, m_base_ptr{ new T[max_lenght] }
		{
			for (size_t i = 0; i < max_lenght; ++i)*(m_base_ptr + i) = init_value;
			push_back_position = max_container_size;
		}

		BOX(BOX&& other) :m_base_ptr{ other.m_base_ptr }
		{
			max_container_size = other->m_base_ptr;
			push_back_position = other->push_back_position;

			other = nullptr;
		}

		~BOX()
		{
			if (m_base_ptr)delete[] m_base_ptr;
		}

		size_t capacity() const
		{
			return max_container_size;
		}

		size_t size() const
		{
			return push_back_position;
		}

		unsigned char is_valid() const
		{
			if (!m_base_ptr)return BOX_not_valid;
			else return BOX_Ok;
		}

		T back() const
		{
			if (push_back_position > 0)
				return *(m_base_ptr + push_back_position - 1);

			return *m_base_ptr;
		}
		unsigned char  init(T* element)
		{
			if (m_base_ptr && element)
			{
				if (max_container_size > 1)
					for (size_t ind = 0; ind < max_container_size; ++ind)
						*(m_base_ptr + ind) = *element;
				else *m_base_ptr = *element;

				return BOX_Ok;
			}

			if (!element)return BOX_invalid_element;

			return BOX_invalid_base;
		}

		unsigned char push_back(T* element)
		{
			if (!element)return BOX_invalid_element;

			if (m_base_ptr)
			{
				if (push_back_position + 1 <= max_container_size)
				{
					*(m_base_ptr + push_back_position) = *element;
					++push_back_position;

					return BOX_Ok;
				}
				else
				{
					T* temp_ptr = new T[max_container_size + 1];

					for (size_t i = 0; i < max_container_size; ++i)
						*(temp_ptr + i) = *(m_base_ptr + i);

					*(temp_ptr + max_container_size) = *element;

					delete[] m_base_ptr;
					m_base_ptr = temp_ptr;

					++max_container_size;
					++push_back_position;

					return BOX_increased;
				}
			}

			return BOX_invalid_base;
		}
		unsigned char push_front(T* element)
		{
			if (!element)return BOX_invalid_element;

			if (m_base_ptr)
			{
				*m_base_ptr = *element;
				return BOX_Ok;
			}

			return BOX_invalid_base;
		}
		
		unsigned char push_back(T element)
		{
			if (m_base_ptr)
			{
				if (push_back_position + 1 <= max_container_size)
				{
					*(m_base_ptr + push_back_position) = element;
					++push_back_position;

					return BOX_Ok;
				}
				else
				{
					T* temp_ptr = new T[max_container_size + 1];

					for (size_t i = 0; i < max_container_size; ++i)
						*(temp_ptr + i) = *(m_base_ptr + i);

					*(temp_ptr + max_container_size) = element;

					delete[] m_base_ptr;
					m_base_ptr = temp_ptr;

					++max_container_size;
					++push_back_position;

					return BOX_increased;
				}
			}

			return BOX_invalid_base;
		}
		unsigned char push_front(T element)
		{
			if (m_base_ptr)
			{
				*m_base_ptr = element;
				return BOX_Ok;
			}

			return BOX_invalid_base;
		}

		unsigned char erase(size_t index)
		{
			if (index < 0 || index >= max_container_size)return BOX_invalid_index;

			T* temp_ptr = new T[max_container_size - 1];

			for (size_t i = 0; i < max_container_size - 1; ++i)
			{
				if (i < index) *(temp_ptr + i) = *(m_base_ptr + i);
				else *(temp_ptr + i) = *(m_base_ptr + i + 1);
			}
			delete[] m_base_ptr;
			m_base_ptr = temp_ptr;

			--max_container_size;
			--push_back_position;

			return BOX_decreased;
		}

		T operator[] (size_t index)
		{
			if (index < 0 || index >= max_container_size) return T{};

			if (!m_base_ptr)return T{};

			return *(m_base_ptr + index);
		}
		unsigned char operator() (size_t index, T* element)
		{
			if (index < 0 || index >= max_container_size)return BOX_invalid_index;

			if (!element)return BOX_invalid_element;

			if (!m_base_ptr)return BOX_invalid_base;

			*(m_base_ptr + index) = *element;

			return BOX_Ok;
		}
		unsigned char operator() (size_t index, T element)
		{
			if (index < 0 || index >= max_container_size)return BOX_invalid_index;

			if (!m_base_ptr)return BOX_invalid_base;

			*(m_base_ptr + index) = element;

			return BOX_Ok;
		}
	};
}