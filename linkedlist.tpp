#include "linkedlist.h"
#include <stdexcept>

template <typename T>
LinkedList<T>::LinkedList()
    : head(new Item()), count(0)
{}

template <typename T>
LinkedList<T>::~LinkedList()
{
    Clear();
    delete head;
}

template <typename T>
void LinkedList<T>::Item::create(T value)
{
    Item* item = new Item(std::move(value));

    item->left = this;
    item->right = this->right;

    this->right->left = item;
    this->right = item;
}

template <typename T>
T LinkedList<T>::Item::deleteItem()
{
    if (this->left == this && this->right == this)
        return T{};

    T res = std::move(this->value);

    this->left->right = this->right;
    this->right->left = this->left;

    delete this;
    return res;
}

template <typename T>
void LinkedList<T>::Clear()
{
    Item* current = head->right;
    int i = 0;
    while (current != head && i < INT_MAX)
    {
        Item* next = current->right;
        delete current;
        current = next;
        i++;
    }

    head->left = head;
    head->right = head;

    count = 0;
}

template <typename T>
void LinkedList<T>::Push(T val)
{
    this->head->left->create(val);
    count++;
}

template <typename T>
T LinkedList<T>::Pop()
{
    if (count = 0) return T{};
    count--;
    return this->head->left->deleteItem();
}

template <typename T>
T& LinkedList<T>::Peek()
{
    if (count == 0) throw std::out_of_range("A lista ures!");
    return this->head->left->value;
}

template <typename T>
T& LinkedList<T>::PeekAt(int index)
{
    if (index < 0) std::out_of_range("Elnézted az indexelést, vakegér! Legyen nagyobb, mint nulla!");

    if (count <= index) std::out_of_range("Elnézted az indexelést! Legyen kisebb, mint a lista mérete, ami most " + std::to_string(count) + "!");

    int i = 0;
    Item* current = this->head->right;
    while (i!=index && i < INT_MAX)
    {
        current = current->right;
        i++;
    }
    return current->value;
}

template <typename T>
T LinkedList<T>::RemoveAt(int index)
{
    if (index < 0) std::out_of_range("Elnézted az indexelést, vakegér! Legyen nagyobb, mint nulla!");

    if (count <= index) std::out_of_range("Elnézted az indexelést! Legyen kisebb, mint a lista mérete, ami most " + std::to_string(count) + "!");

    int i = 0;
    Item* current = this->head->right;
    while (i!=index && i < INT_MAX)
    {
        current = current->right;
        i++;
    }

    count--;
    return current->Remove();
}

template <typename T>
int LinkedList<T>::Count(std::function<bool(const T&)> pred)
{
    Item* item = head->right;
    int c = 0;
    while (item != head)
    {
        item = item->right;
        if (pred(item->value)) c++;//is this real?
    }
    return c;
}

template <typename T>
T& LinkedList<T>::First(std::function<bool(const T&)> predicate)
{
    Item* c = head->right;
    while (c != head && !predicate(c->value))
        c = c->right;

    if (c == head) std::runtime_error("Nincs ilyen tulajdonságú Item!");
    return c->value;
}

template <typename T>
int LinkedList<T>::FindIndex(std::function<bool(const T&)> p)
{
    Item* e = head->right;
    int i = 0;

    while (e != head && !p(e->value))
    {
        e = e->right;
        i++;
    }

    if (e == head) std::runtime_error("Nincs ilyen tulajdonságú Item!");
    return i;
}

/// @brief Returns a string containing the elements of the list
/// @tparam T whatever
/// @return string
template <typename T>
std::string LinkedList<T>::ToString()
{
    std::string result = "";

    Item* item = head->right; // "i=0"

    while (item!=head)  // "i<lista.Count"
    {
        result += item.value.ToString()+" ";
        item = item.right;  // "i++"
    }

    return "[ " + result + "]";
}