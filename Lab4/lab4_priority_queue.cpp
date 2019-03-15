// Jonathan Chen 20722167 && Aman Mathur 20710307
// April 1st, 2019
// SYDE 223 Lab #4
#include "lab4_priority_queue.h"

using namespace std;

// PURPOSE: Parametric constructor
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
    heap = new TaskItem*[n_capacity+1];
    size = 0;
    capacity = n_capacity;
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
    //Missing something maybe
    delete [] heap;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
    return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
    return size == 0;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
    return size == capacity;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
    for (int i = 0; i < size; i++) {
        cout << "Priority #: " << heap[i]->priority << endl;
    }
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
    if (empty())
        return TaskItem(-1, "NULL");
    else
        return *heap[1];
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
    if (size == capacity)
        return false;

    if (empty()) {
        heap[1] = new TaskItem(val);
    } else {
        int i = size+1;
        heap[i] = new TaskItem(val);
        while (i > 1 && heap[i/2]->priority < heap[i]->priority) {
            TaskItem * tmp = heap[i];
            heap[i] = heap[i/2];
            heap[i/2] = tmp;
            i /= 2;
        }
    }
    size++;
    return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
    if (empty())
        return false;
    else {
        TaskItem *dequeued = heap[1];
        heap[1] = heap[size];
        heap[size] = dequeued;
        size--;

        int i = 1;

        while (i < size) {
            TaskItem *max = new TaskItem(0, "N/A");
            if (heap[i*2] <= heap[i*2+1]) {
                max = heap[i*2+1];
            } else {
                max = heap[i*2];
            }
            if (heap[i]->priority < max->priority) {
                TaskItem *tmp = heap[i];
                heap[i] = max;
                heap[i / 2] = tmp;
                i *= 2;
            } else {
                return true;
            }
        }
    }
    return true;
}
