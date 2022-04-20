#include <iostream>
#include <stdexcept>
#include <vector>

template<typename T, size_t S = 1>
class Container
{
public:
    Container(void)
    {
        m_Ptr = static_cast<T*>(malloc(S * sizeof(T)));
        if(!m_Ptr) throw std::bad_alloc();
    }

    ~Container()
    {
        m_Ptr = nullptr;
        if(m_Ptr) free(m_Ptr);
    }
    
    size_t Size() const
    {
        return m_Size;
    }

    T &operator[](size_t idx)
    {
        if(idx >= m_Size) throw std::out_of_range("Index is out of bounds");
        return m_Ptr[idx];
    }


    void operator=(T arr[])
    {
        for(size_t i = 0; i < m_Size; ++i)
        {
            m_Ptr[i] = arr[i];
        }
    }

    void Resize(size_t newSize)
    {
        if(m_Ptr)
        {
            if(newSize)
            {
                m_Ptr = static_cast<T*>(realloc(m_Ptr, newSize * sizeof(T)));
            }
        }
        else if(m_Size)
        {
            m_Ptr = static_cast<T*>(malloc(newSize * sizeof(T)));
        }
        else throw std::bad_alloc();

        m_Size = newSize;
    }

    template<typename __T, size_t __S>
    friend std::ostream &operator<<(std::ostream &out, const Container<__T, __S> &other);

private:
    size_t m_Size = S;
    T *m_Ptr = nullptr;
};

template<typename T, size_t S>
std::ostream &operator<<(std::ostream &out, const Container<T, S> &other)
{
    out << '{';
    for(size_t i = 0; i < other.m_Size - 1; ++i)
    {
        std::cout <<  other.m_Ptr[i] << ", ";
    }
    std::cout << other.m_Ptr[other.m_Size - 1] << "}";

    return out;
}

int main(void)
{
    Container<int, 7> container; 

    for(int i = 0; i < container.Size(); ++i)
    {
        container[i] = 2*i;
    }

    std::cout << container << std::endl;

    return EXIT_SUCCESS;
}