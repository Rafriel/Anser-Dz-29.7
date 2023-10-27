#include "QueueInsert.h"

FineGrainedQueue::FineGrainedQueue()
{
    head = nullptr;
}

FineGrainedQueue::~FineGrainedQueue()
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    // Create a new node with the given value.
    Node* new_node = new Node;
    new_node->value = value;
    new_node->next = nullptr;
    new_node->node_mutex = std::make_unique<std::mutex>();

    // Acquire a lock on the queue's mutex to protect the concurrent access to the queue.
    std::unique_lock<std::mutex> queue_lock(queue_mutex);

    Node* current = head;
    Node* previous = nullptr;
    int current_pos = 0;

    // Traverse the queue to find the insertion position.
    while (current_pos < pos && current != nullptr) {
        previous = current;
        current = current->next;
        current_pos++;
    }

    if (previous != nullptr) {
        std::unique_lock<std::mutex> current_lock(*(previous->node_mutex));
        if (current) {
            std::unique_lock<std::mutex> next_lock(*(current->node_mutex));
            new_node->next = current;
            previous->next = new_node;
        }
        else {
            previous->next = new_node;
        }
    }
    else {
        new_node->next = head;
        head = new_node;
    }
}
