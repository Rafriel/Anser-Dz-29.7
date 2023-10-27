#include <iostream>
#include <thread>
#include "QueueInsert.h"

int main()
{
    FineGrainedQueue queue;
    for (int i = 0; i < 10; i++)
    {
        queue.insertIntoMiddle(i, i);
    }

    std::vector<std::thread> threads;
    threads.reserve(7);
    for (int i = 0; i < 7; i++) {
        threads.emplace_back([&queue, i]() {
            queue.insertIntoMiddle(100 * (i + 1), 5 + i);
            });
    }
    threads.emplace_back([&queue]() {
        queue.insertIntoMiddle(1000, 40);
        });

    for (auto& thread : threads) {
        thread.join();
    }

    Node* current = queue.getHead();

    while (current != nullptr)
    {
        std::cout << current->value << " ";
        current = current->next;
    }

    return 0;
}
