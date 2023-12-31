#pragma once

#include <initializer_list>
#include <exception>

namespace nstl {

class LinkedListOutOfBounds : std::exception {
public:
    const char* what() const noexcept  {
        return "LinkedListOutOfBounds exception thrown";
    }
};

template<typename T>
class singly_linked_list {
public:
    singly_linked_list()
            : m_head(nullptr), m_tail(nullptr), m_size(0) {}
    // implement this correctly
    singly_linked_list(std::initializer_list<T> values)
            : singly_linked_list() {
        for (auto& value : values)
            this->append(value);
    }

    void append(const T& value) {
        node* new_tail = new node(value);
        if (!m_head) {
            m_head = m_tail = new_tail;
        } else {
            m_tail->next = new_tail;
            m_tail = new_tail;
        }
        ++m_size;
    }

    T pop() {
        node* curr = m_head;
        for (int i = 0; i != m_size - 2; ++i)
            curr = curr->next;
        T value = curr->next->value;
        delete curr->next;
        curr->next = nullptr;
        --m_size;
        return value;
    }

    void insert(const T& value, size_t position)  {
        if (position > m_size)
            throw LinkedListOutOfBounds();

        auto newNode = new node(value);
        if (!position) {
            if (!m_head) {
                m_head = m_tail = newNode;
            } else {
                newNode->next = m_head;
                m_head = newNode;
            }
        } else {
            if (position == m_size) {
                m_tail->next = newNode;
                m_tail = newNode;
            } else {
                node* curr = m_head;
                for (int i = 0; i != position - 1; ++i)
                    curr = curr->next;
                newNode->next = curr->next;
                curr->next = newNode;
            }
        }
        ++m_size;
    }

    void remove(size_t position) {
        if (!m_size || position > m_size - 1)
            throw LinkedListOutOfBounds();

        if (!position) {
            if (!m_head) {
                m_head = m_tail = nullptr;
            } else {
                node* oldHead = m_head;
                m_head = m_head->next;
                delete oldHead;
            }
        } else {
            node* curr = m_head;
            for (int i = 0; i != position - 1; ++i)
                curr = curr->next;
            node* newNext = curr->next->next;
            delete curr->next;
            curr->next = newNext;
        }
        --m_size;
    }

    void reverse() {
        node* prev = nullptr;
        node* curr = m_tail = m_head;
        node* next;
        do {
            next = curr->next;  // keeps track of the next node to traverse to
            curr->next = prev;  // flips the current node's link from curr->next to curr->prev
            prev = curr;        // keeps track of the previous node for use in the next iteration
        } while ((curr = next) != nullptr);
        m_head = prev;
    }

    size_t size() const { return m_size; }

    T& at(size_t position) const {
        if (position > m_size - 1)
            throw LinkedListOutOfBounds();

        node* curr = m_head;
        for (int i = 0; i != position; ++i)
            curr = curr->next;
        return curr->value;
    }

    T& operator[](size_t i) const { return at(i); }

    template<typename Func>
    void traverse(Func&& func) {
        if (!m_head) return;
        node* curr = m_head;
        do {
            func(curr->value);
        } while ((curr = curr->next) != nullptr);
    }
private:
    struct node {
        node(const T& value, node* next = nullptr)
                : value(value), next(next) {}
        T value;
        node* next;
    };
    node* m_head, *m_tail;
    size_t m_size;
};

template<typename T>
class doubly_linked_list {
public:
    doubly_linked_list()
            : m_head(nullptr), m_tail(nullptr), m_size(0) {}
    doubly_linked_list(std::initializer_list<T> values)
            : doubly_linked_list() {
        for (auto& value : values)
            this->append(value);
    }

    void append(const T& value) {
        node* new_tail = new node(value);
        if (!m_head) {
            m_head = m_tail = new_tail;
        } else {
            m_tail->next = new_tail;
            new_tail->prev = m_tail;
            m_tail = new_tail;
        }
        ++m_size;
    }

    T pop() {
        T value = m_tail->value;
        node* new_tail = m_tail->prev;
        new_tail->next = nullptr;
        delete m_tail;
        m_tail = new_tail;
        --m_size;
        return value;
    }

    void insert(const T& value, size_t position)  {
        if (position > m_size)
            throw LinkedListOutOfBounds();

        auto newNode = new node(value);
        if (!position) {
            if (!m_head) {
                m_head = m_tail = newNode;
            } else {
                newNode->next = m_head;
                m_head->prev = newNode;
                m_head = newNode;
            }
        } else {
            if (position == m_size) {
                m_tail->next = newNode;
                newNode->prev = m_tail;
                m_tail = newNode;
            } else {
                node* curr;
                if (position >= m_size / 2) {
                    curr = m_tail;
                    for (int i = m_size - 1; i != position; --i)
                        curr = curr->prev;
                    curr->prev->next = newNode;
                    newNode->prev = curr->prev;
                    curr->prev = newNode;
                    newNode->next = curr;
                } else {
                    curr = m_head;
                    for (int i = 0; i != position - 1; ++i)
                        curr = curr->next;
                    curr->next->prev = newNode;
                    newNode->next = curr->next;
                    curr->next = newNode;
                    newNode->prev = curr;
                }
            }
        }
        ++m_size;
    }
    void remove(size_t position) {
        if (!m_size || position > m_size - 1)
            throw LinkedListOutOfBounds();

        if (!position) {
            if (!m_head->next) {
                m_head = m_tail = nullptr;
            } else {
                node* oldHead = m_head;
                m_head = m_head->next;
                m_head->prev = nullptr;
                delete oldHead;
            }
        } else {
            if (position == m_size - 1) {
                node* newTail = m_tail->prev;
                newTail->next = nullptr;
                delete m_tail;
                m_tail = newTail;
            } else {
                node* curr;
                if (position >= m_size / 2) {
                    curr = m_tail;
                    for (int i = m_size - 1; i != position + 1; --i)
                        curr = curr->prev;
                    node* newPrev = curr->prev->prev;
                    newPrev->next = curr;
                    delete curr->prev;
                    curr->prev = newPrev;
                } else {
                    curr = m_head;
                    for (int i = 0; i != position - 1; ++i)
                        curr = curr->next;
                    node* newNext = curr->next->next;
                    newNext->prev = curr;
                    delete curr->next;
                    curr->next = newNext;
                }
            }
        }
        --m_size;
    }

    void reverse() {
        node* tmp;
        node* curr = m_tail = m_head;
        do {
            tmp = curr->prev;
            curr->prev = curr->next;
            curr->next = tmp;
        } while ((curr = curr->prev) != nullptr);
        m_head = tmp->prev;
    }

    size_t size() const { return m_size; }

    T& at(size_t position) const  {
        if (position > m_size - 1)
            throw LinkedListOutOfBounds();

        node* curr;
        if (position >= m_size / 2) {
            curr = m_tail;
            for (int i = m_size - 1; i != position; --i)
                curr = curr->prev;
        } else {
            curr = m_head;
            for (int i = 0; i != position; ++i)
                curr = curr->next;
        }
        return curr->value;
    }

    T& operator[](size_t i) const { return at(i); }

    template<typename Func>
    void traverse(Func&& func) {
        if (!m_head) return;
        node* curr = m_head;
        do {
            func(curr->value);
        } while ((curr = curr->next) != nullptr);
    }

    template<typename Func>
    void rtraverse(Func&& func) {
        if (!m_tail) return;
        node* curr = m_tail;
        do {
            func(curr->value);
        } while ((curr = curr->prev) != nullptr);
    }
private:
    struct node {
        node(const T& value, node* prev = nullptr, node* next = nullptr)
                : value(value), prev(prev), next(next) {}
        T value;
        node* prev, *next;
    };
    node* m_head, *m_tail;
    size_t m_size;
};

}  // nstl
