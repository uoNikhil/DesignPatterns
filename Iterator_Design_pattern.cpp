#include<iostream>
#include<vector>
#include <memory>
#include <sstream>
#include <iterator>

//T->Type of Individual element of Container ||   U->Pointer to Container
template<typename T, typename U>
class Iterator{
    typedef typename std::vector<T>::iterator iter_type;
public:
    Iterator(U* p_container):m_p_container(p_container)
    {
        m_itr = m_p_container->m_data.begin();
    }

    //Begin
    iter_type first()
    {
        return m_p_container->m_data.begin();
    }

    //isEnd
    bool isEnd()
    {
        return (m_itr == m_p_container->m_data.end());
    }
    //Current
    iter_type current()
    {
        return m_itr;
    }

    //Next
    void next()
    {
        m_itr++;
    }

private:
    // Iterator to Individual Element
    iter_type m_itr;
    // Pointer to Class
    U* m_p_container;
};

//Container<int> my_container;
template <typename T>
class Container{
    friend class Iterator<T,Container>;
public:
    Container(){}

    void add(T value)
    {
        m_data.emplace_back(value);
    }
    
    std::shared_ptr<Iterator<T,Container>> createIterator()
    {
        return std::make_shared<Iterator<T, Container>>(this);
    }

private:
    std::vector<T> m_data;
};

class CustomData
{
public:
    CustomData()
    {
        m_pair = {'a', 0};
    }
    CustomData(std::pair<char, int> pair)
    {
        m_pair = pair;
    }
    void setdata(std::pair<char, int> pair)
    {
        m_pair = pair;
    }

    std::pair<char, int> data()
    {
        return m_pair;
    }
private:
    std::pair<char, int> m_pair;
};


void clientCode()
{
    Container<int> my_container;
    for (int i=0;i<10;i++)
    {
        my_container.add(i);
    }

    auto itr = my_container.createIterator();
    std::stringstream ss;
    ss << "{ ";
    for (itr->first(); !itr->isEnd(); itr->next())
    {
        ss << *itr->current() << ", ";
    }
    ss << " }\n";
    std::cout << "Printing my_container : " << ss.str();
}

void clientCodeCustomCustomData()
{
    Container<CustomData> my_container;
    for (int i=0;i<10;i++)
    {
        CustomData data({char('a'+i), i});
        my_container.add(data);
    }

    auto itr = my_container.createIterator();
    std::stringstream ss;
    ss << "{ ";
    for (itr->first(); !itr->isEnd(); itr->next())
    {
        ss << "{" << itr->current()->data().first << ", " << itr->current()->data().second << "}, ";
    }
    ss << " }\n";
    std::cout << "Printing my_container : " << ss.str();
}

int main()
{
    clientCode();
    clientCodeCustomCustomData();
}