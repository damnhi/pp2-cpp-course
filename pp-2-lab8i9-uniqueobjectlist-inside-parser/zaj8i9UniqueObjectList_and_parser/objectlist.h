#pragma once

#include <cinttypes>  // std::size_t
#include <memory>  // std::unique_ptr (dla chętnych)
#include <set>


//#define UNIMPLEMENTED_OBJECT_LIST_CONSTRUCTOR_SIZE_EMPTY_METHODS
//#define UNIMPLEMENTED_PUSH_FRONT
//#define UNIMPLEMENTED_POP_FRONT
//#define UNIMPLEMENTED_FRONT
//#define UNIMPLEMENTED_CLEAR
//#define UNIMPLEMENTED_REVERSE // rozmowa kwalifikacyjna
//#define UNIMPLEMENTED_ITERATOR_METHODS_AT_LEAST_EMPTY
//#define UNIMPLEMENTED_ITERATORS
//#define UNIMPLEMENTED_ERASE_AFTER
//#define UNIMPLEMENTED_ERASE
//#define UNIMPLEMENTED_OBJECT_LIST_CONSTRUCTOR_SIZE_EMPTY_METHODS

class Object;


class ObjectList
{
private:
    struct Node{
        Object* data_;
        struct Node* next;

    };
    Node* head = nullptr;
    size_t size_of_list = 0;
//    std::set <std::unique_ptr<Object>> object_set;
public:
    using value_type = Object;
    ObjectList();
    ~ObjectList();

    ObjectList(const ObjectList& obj) ;
    ObjectList(ObjectList&& obj_list);
    ObjectList& operator=(const ObjectList& other) {

        if (this != &other) {
            clear();
            iterator current_pos = other.begin();
            while(current_pos != other.end()){
                push_front(current_pos->data_);
                current_pos++;
            }
            reverse();
        }

        return *this;
    }
    ObjectList& operator=(ObjectList&& other)
    {
        if (this != &other) {
            clear();
            head = other.head;
            size_of_list = other.size_of_list;
            other.size_of_list = 0;
            other.head = nullptr;
        }
        return *this;
    }

    size_t size() const{
        return size_of_list;
    }

    bool empty() const{
        if (size_of_list==0){
            return true;
        } else return false;
    }

    void clear();

    void reverse() noexcept;

    value_type& front();

    struct iterator
    {
        using type_of_val = struct Node;

        iterator(type_of_val* ptr) : m_ptr(ptr) {}

        Object& operator*() const { return *(m_ptr->data_); }
        type_of_val* operator->() { return m_ptr; }

        iterator& operator++(){
            m_ptr = m_ptr->next; return *this;
        };

        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; };

    private:
        type_of_val* m_ptr;
    };

    /**
     * @brief push_front
     * @param newObject
     * Wpierw sprawdzamy czy obiekt już jest w liście
     */
    void push_front(value_type* newObject);

    void pop_front();

    iterator begin() const;
    iterator end() const;

    void erase_after(iterator position);

    /// tego std::forward_list nie ma
    void erase(iterator position);

    /// dla chętnych, tego testy nie sprawdzają:
    ObjectList reverse_copy() const;

    /// dla chętnych, tego testy nie sprawdzają:
    void sort() noexcept;

protected:
    // TODO:
};
