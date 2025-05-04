// Copyright 2022 NNTU-CS
#ifndef TPQUEUE_H
#define TPQUEUE_H

#include <stdexcept>

template <typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& d) : data(d), next(nullptr) {}
  };

  Node* head;

 public:
  TPQueue() : head(nullptr) {}

  ~TPQueue() {
    while (head) {
      Node* tmp = head;
      head = head->next;
      delete tmp;
    }
  }

  void push(const T& value) {
    Node* newNode = new Node(value);
    if (!head || value.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
      return;
    }
    Node* current = head;
    while (current->next && current->next->data.prior >= value.prior) {
      current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
  }

  T pop() {
    if (!head)
      throw std::runtime_error("Queue is empty");
    Node* tmp = head;
    T result = head->data;
    head = head->next;
    delete tmp;
    return result;
  }
};

#endif  // TPQUEUE_H
