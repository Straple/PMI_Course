#include "stack.h"

Node::Node(int32_t value, Node* previous) : value(value), previous(previous) {
}

Stack::Stack() : head_(nullptr), size_(0) {
}

void RemoveStack(Node* node) {
    if (node != nullptr) {
        RemoveStack(node->previous);
        delete node;
    }
}

Stack::~Stack() {
    RemoveStack(head_);
}

void Stack::Push(int32_t value) {
    head_ = new Node(value, head_);
    ++size_;
}

void Stack::Pop() {
    Node* tmp = head_;
    head_ = head_->previous;
    delete tmp;
    --size_;
}

int32_t Stack::Top() const {
    return head_->value;
}

int32_t Stack::Size() const {
    return size_;
}

void Stack::Clear() {
    RemoveStack(head_);
    head_ = nullptr;
    size_ = 0;
}

bool Stack::Empty() const {
    return size_ == 0;
}