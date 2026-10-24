#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstddef>
#include <utility>

template <typename T>
class LinkedList
{
public:
    class Item
    {
        public:
            T value;
            Item* left;
            Item* right;

            template <typename... Args>
            explicit Item(Args&&... args)
                : value(std::forward<Args>(args)...),
                left(this),
                right(this)
            {
            }

            Item()
                : value{}, left(this), right(this)
            {
            }

            void create(T value);
            T deleteItem();
    };

    LinkedList();
    ~LinkedList();

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    void Clear();
    void Push(T val);
    T Pop();
    T& Peek();
    T& PeekAt(int index);
    T RemoveAt(int index);
    int Count(std::function<bool(const T&)> pred);
    T& First(std::function<bool(const T&)> predicate);
    int FindIndex(std::function<bool(const T&)> p);
    std::string ToString();

    Item* head;
    std::size_t count;
};

#include "linkedlist.tpp"

#endif