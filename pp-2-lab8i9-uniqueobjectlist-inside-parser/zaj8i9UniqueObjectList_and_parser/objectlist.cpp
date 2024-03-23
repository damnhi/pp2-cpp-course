#include <memory>
#include <stdexcept>
#include <utility>  // std::exchange()
#include "objectlist.h"
#include "object.h"



ObjectList::ObjectList() = default;
ObjectList::~ObjectList() {
//        while (head!= nullptr) {
//            struct Node *victim = head;
//            head = victim->next;
//            delete victim;
//        }
//        delete head;
    struct Node* current = head;
    int size = size_of_list;
    for(int i =0;  i< size ; i++) {
        struct Node *next = current->next;
        delete current;
        current = next;
    }

};

void ObjectList::push_front(value_type *newObject) {
    Node *new_node = new Node;

    auto* point_node = head;
    for (int i = 0; i < size_of_list; ++i) {
        if (*(point_node->data_) == *newObject){
            return;
        }
        else {
            point_node = point_node->next;
        }
    }

    ++size_of_list;
    new_node->data_ = newObject;

    //if head does not point to anything, we set head to new_node

    if (head == nullptr) {
        head = new_node;
        return;
    }

    new_node->next = head;
    head = new_node;
}

void ObjectList::pop_front() {
    if (size_of_list == 1){
        head = nullptr;
        size_of_list--;
        return;
    }
    if (size_of_list == 0){
        return;
    }
    struct Node* new_head = head;
    head = head->next;
    delete new_head;
    size_of_list--;
}

ObjectList::value_type &ObjectList::front() {
    return *head->data_;
}

void ObjectList::clear() {
    int size = size_of_list;
    for (int i = 0; i < size; ++i) {
        pop_front();
    }
}

void ObjectList::reverse() noexcept {
    if (size_of_list==0){
        return;
    }
    struct Node *next, *prev = nullptr, *current = head;

    for (int i = 0; i < size_of_list; ++i) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

ObjectList::iterator ObjectList::end() const{
    struct Node* ending_node = head;
    for (int i = 0; i < size_of_list; ++i) {
        ending_node = ending_node->next;
    }
    return {ending_node};
}

ObjectList::iterator ObjectList::begin() const {
    return {head};
}

void ObjectList::erase_after(ObjectList::iterator position) {
    if (size_of_list == 0 ||size_of_list==1 || position == this->end()) {
        return;
    }

    struct Node* temp = position->next;
    position->next = temp->next;
    delete temp;
    size_of_list--;
}

void ObjectList::erase(ObjectList::iterator position) {
    if (position==this->begin()){
        clear();
        return;
    }
    iterator current = begin();
    iterator prev = begin();
    while (current != position){
        prev= current;
        current++;

    }
    erase_after(prev);
}

ObjectList::ObjectList(const ObjectList &obj)  {
    iterator current_pos = obj.begin();
    //?
    while(current_pos != obj.end()){
        push_front(current_pos->data_);
        current_pos++;
    }
    reverse();
}

ObjectList::ObjectList(ObjectList &&other) {
    head = other.head;
    other.head = nullptr;
    size_of_list = other.size_of_list;
    other.size_of_list = 0;
}
