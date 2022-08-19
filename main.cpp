#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdarg>

template<typename T, size_t S = 0>
class Container
{
public:
    Container(void)
    {
        if(m_Size)
        {
            m_Ptr = static_cast<T*>(malloc(sizeof(T) * m_Size));
        }

		for(size_t i = 0; i < m_Size; ++i)
		{
			m_Ptr[i] = 0;
		}
    }

	Container(size_t size)
	{
		m_Size = size;

		if(m_Size)
        {
            m_Ptr = static_cast<T*>(malloc(sizeof(T) * m_Size));
        }

		for(size_t i = 0; i < m_Size; ++i)
		{
			m_Ptr[i] = 0;
		}
	}

    ~Container()
    {
        if(m_Ptr) free(m_Ptr);
    }
    
    size_t Size() const
    {
        return m_Size;
    }
	
	T &operator[](int64_t _idx) const
    {
		if(_idx < 0) _idx = (m_Size - 1) - ~(_idx);
		if(_idx >= m_Size) throw std::out_of_range("Index is out of bounds");

        return *(m_Ptr + _idx);
    }
	
	T &operator[](int64_t _idx)
    {
		if(_idx < 0) _idx = (m_Size - 1) - ~(_idx);
		if(_idx >= m_Size) throw std::out_of_range("Index is out of bounds");

        return *(m_Ptr + _idx);
    }
	
    void Append(const T &_element)
    {
        m_Size++;
        Resize(m_Size);
        m_Ptr[m_Size - 1] = _element;
    }

    T Pop(void)
    {
        m_Size--;
        T tmp = m_Ptr[m_Size];
        Resize(m_Size);
    
        return tmp;
    }

    void Clear(void)
    {
        m_Size = 0;
        Resize(m_Size);
    }

    void BubbleSort(void)
    {
        for(size_t i = 0; i < m_Size; i++)
        {
            for(size_t j = 0; j < m_Size - i - 1; j++)
            {
                if(m_Ptr[j] > m_Ptr[j + 1])
                {
                    T tmp = (*this)[j];
                    (*this)[j] = (*this)[j + 1];
                    (*this)[j + 1] = tmp;
                }
            }
        }
    }

    T Max(void)
    {
        T max = (*this)[0];
        for(size_t i = 0; i < m_Size; ++i)
        {
            if((*this)[0] > max) max = (*this)[i];
        }

        return max;
    }

    T Min(void)
    {
        T min = (*this)[0];
        for(size_t i = 0; i < m_Size; ++i)
        {
            if((*this)[i] < min) min = (*this)[i];
        }

        return min;
    }

	Container<T> Slice(size_t start, size_t end, size_t step)
	{
		Container<T> __tmp;
		for(size_t i = start; i < end; i += step)
		{
			__tmp.Append((*this)[i]);
		}
		
		return __tmp;
	}

	Container<T> Slice(int32_t end)
	{
		Container<T> __tmp;
		for(size_t i = 0; i < end; ++i)
		{
			__tmp.Append((*this)[i]);
		}

		return __tmp;
	}

	Container<T> Slice(int32_t start, int32_t end)
	{
		Container<T> __tmp;
		for(size_t i = start; i < end; ++i)
		{
			__tmp.Append((*this)[i]);
		}

		return __tmp;
	}

protected:
    size_t m_Size = S;
    T *m_Ptr = nullptr;

    void Resize(size_t _newSize)
    {
        if(m_Ptr)
        {
            if(_newSize)
            {
                m_Ptr = static_cast<T*>(realloc(m_Ptr, _newSize * sizeof(T)));
            }
        }
        else if(m_Size)
        {
            m_Ptr = static_cast<T*>(malloc(_newSize * sizeof(T)));
        }

        else throw std::bad_alloc();

        m_Size = _newSize;
    }
};

template<typename T, size_t S>
std::ostream &operator<<(std::ostream &out, const Container<T, S> &other)
{
    if(other.Size())
    {
        out << "{";
        for(size_t i = 0; i < other.Size()- 1; ++i)
        {
            std::cout <<  other[i] << ", ";
        }
        std::cout << other[other.Size() - 1] << "}";
    }

    else out << "";

    return out;
}

int main(void)
{
	Container<float, 10> container;

	for(size_t i = 0; i < container.Size(); ++i)
	{
		container[i] = i + 1 + 0.33f;
	}

	std::cout << container << std::endl;
	container.BubbleSort();
	std::cout << container.Slice(0, container.Size(), 3) << std::endl;

	return EXIT_SUCCESS;
}
