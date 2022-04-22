#include <iostream>
#include <stdexcept>
#include <vector>

template<typename T, size_t S = 0>
class Container
{
public:
    Container(void)
    {
        if(m_Size)
        {
            m_Ptr = static_cast<T*>(malloc(m_Size * sizeof(T)));
        }
    }

    ~Container()
    {
        if(m_Ptr) free(m_Ptr);
    }
    
    size_t GetSize() const
    {
        return m_Size;
    }

    T &operator[](size_t _idx)
    {
        if(_idx >= m_Size) throw std::out_of_range("Index is out of bounds");
        return m_Ptr[_idx];
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
                    T tmp = m_Ptr[j];
                    m_Ptr[j] = m_Ptr[j + 1];
                    m_Ptr[j + 1] = tmp;
                }
            }
        }
    }

    T Max(void)
    {
        T max = m_Ptr[0];
        for(size_t i = 0; i < m_Size; ++i)
        {
            if(m_Ptr[i] > max) max = m_Ptr[i];
        }

        return max;
    }

    T Min(void)
    {
        T min = m_Ptr[0];
        for(size_t i = 0; i < m_Size; ++i)
        {
            if(m_Ptr[i] < min) min = m_Ptr[i];
        }

        return min;
    }

    template<typename __T, size_t __S>
    friend std::ostream &operator<<(std::ostream &out, const Container<__T, __S> &other);

private:
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
    if(other.m_Size)
    {
        out << '{';
        for(size_t i = 0; i < other.m_Size - 1; ++i)
        {
            std::cout <<  other.m_Ptr[i] << ", ";
        }
        std::cout << other.m_Ptr[other.m_Size - 1] << "}";
    }

    else out << "";

    return out;
}

int main(void)
{
    Container<int32_t> container; 

    container.Append(7);
    container.Append(10);
    container.Append(1);
    container.Append(66);
    container.Append(8);
    container.Append(13);
    container.Append(11);
    container.Append(344);
    container.Append(999);
    container.Append(1111);
    container.Append(454);
    container.Append(16);
    container.Append(12);
    container.Append(100);
    container.Append(-1);
    container.Append(-112);
    container.Append(-1111);


    std::cout << container << std::endl;

    std::cout << container.Max() << std::endl;
    std::cout << container.Min() << std::endl;

    return EXIT_SUCCESS;
}