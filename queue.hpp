#include <list>
#include <iostream>

using namespace std;
using namespace cop4530;

template<typename T>
Queue<T>::Queue()
{
}

template<typename T>
Queue<T>::~Queue()
{

}

template<typename T>
Queue<T>::Queue(const Queue & rhs)
{
        list<T> container(rhs.container);
}

template<typename T>
Queue<T>::Queue(const Queue && rhs)
{
        list<T> container(move(rhs.container));
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue & rhs)
{
        container = rhs.container;
        return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue && rhs)
{
        container = move(rhs.container);
        return *this;
}

template<typename T>
void Queue<T>::print()
{
auto itr=container.begin();
for (;itr!=container.end();++itr)
    {cout <<*itr<<' ';}
cout <<"\n";
}

template<typename T>
T& Queue<T>::back()
{
        return container.back();
}

template<typename T>
const T& Queue<T>::back()const
{
        return container.back();
}


template<typename T>
bool Queue<T>::empty() const
{
        return container.empty();
}

template<typename T>
T& Queue<T>::front()
{
        return container.front();
}
template<typename T>
const T& Queue<T>::front() const
{
        return container.front();
}

template<typename T>
void Queue<T>::pop()
{
        container.pop_front();
}

template<typename T>
void Queue<T>::push(const T& val)
{
        container.push_back(val);
}

template<typename T>
void Queue<T>::push(T&& val)
{
        container.push_back(move(val));
}

template<typename T>
int Queue<T>::size()
{
        return container.size();
}
template<typename T>
T& Queue<T>::front()
{
        return container.front();
}


