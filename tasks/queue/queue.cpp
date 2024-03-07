#include "queue.h"

Node::Node(int32_t value, Node* next) : value(value), next(next) {
}

Queue::Queue() : front_(nullptr), tail_(nullptr), size_(0) {
}

void RemoveQueue(Node* node) {
    if (node != nullptr) {
        RemoveQueue(node->next);
        delete node;
    }
}

Queue::~Queue() {
    RemoveQueue(front_);
}

void Queue::Push(int32_t value) {
    Node* new_node = new Node(value, nullptr);
    if (tail_ == nullptr) {
        front_ = tail_ = new_node;
    } else {
        tail_ = tail_->next = new_node;
    }
    ++size_;
}

void Queue::Pop() {
    Node* new_front = front_->next;
    delete front_;
    front_ = new_front;
    --size_;
}

int32_t Queue::Front() const {
    return front_->value;
}

int32_t Queue::Size() const {
    return size_;
}

void Queue::Clear() {
    RemoveQueue(front_);
    front_ = tail_ = nullptr;
    size_ = 0;
}

bool Queue::Empty() const {
    return size_ == 0;
}