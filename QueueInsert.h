#pragma once

#include <mutex>
#include <vector>

struct Node
{
    int value;
    Node* next;
    std::unique_ptr<std::mutex> node_mutex;
};

class FineGrainedQueue
{
public:
    FineGrainedQueue();
    ~FineGrainedQueue();
    void insertIntoMiddle(int value, int pos);

    Node* getHead() const
    {
        return head;
    }

private:
    Node* head;
    std::mutex queue_mutex;
};
