#include <iostream>
#include <string>
#include <cctype>

struct Process {
    std::string id;
    int priority;

    Process(const std::string& id, int priority) : id(id), priority(priority) {}
};

class PriorityQueue {
private:
    Process** heap;
    int capacity;
    int size;

    void resize(int newCapacity) {
        Process** newHeap = new Process*[newCapacity];
        for (int i = 0; i < size; ++i) {
            newHeap[i] = heap[i];
        }
        delete[] heap;
        heap = newHeap;
        capacity = newCapacity;
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index]->priority > heap[parentIndex]->priority)
                std::swap(heap[index], heap[parentIndex]);
            else
                break;
            index = parentIndex;
        }
    }

    void heapifyDown(int index) {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int maxIndex = index;

        if (leftChildIndex < size && heap[leftChildIndex]->priority > heap[maxIndex]->priority)
            maxIndex = leftChildIndex;
        if (rightChildIndex < size && heap[rightChildIndex]->priority > heap[maxIndex]->priority)
            maxIndex = rightChildIndex;

        if (maxIndex != index) {
            std::swap(heap[index], heap[maxIndex]);
            heapifyDown(maxIndex);
        }
    }

public:
    PriorityQueue() : capacity(5), size(0) {
        heap = new Process*[capacity];
    }

    void addProcess(const std::string& id, int priority) {
        if (size == capacity)
            resize(2 * capacity);

        heap[size] = new Process(id, priority);
        heapifyUp(size);
        size++;
    }

    void removeProcess() {
        if (size == 0) {
            std::cout << "EMPTY" << std::endl;
            return;
        }

        std::cout << heap[0]->id << std::endl;
        delete heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
    }

    void peekProcess() {
        if (size == 0) {
            std::cout << "EMPTY" << std::endl;
            return;
        }

        std::cout << heap[0]->id << std::endl;
    }

    ~PriorityQueue() {
        for (int i = 0; i < size; ++i) {
            delete heap[i];
        }
        delete[] heap;
    }
};

int main() {
    PriorityQueue pq;

    std::string command, id;
    int priority;

    do {
        std::cin >> command;
        if (command == "ADD") {
            std::cin >> id >> priority;
            pq.addProcess(id, priority);
        } else if (command == "REMOVE") {
            pq.removeProcess();
        } else if (command == "PEEK") {
            pq.peekProcess();
        }
    } while (command != "EXIT" && !std::cin.eof());
}
