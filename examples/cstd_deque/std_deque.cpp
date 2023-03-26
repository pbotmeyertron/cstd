#include <iostream>
#include <deque>

int main() {
    // create an empty deque of integers
    std::deque<int> deq;

    // add some elements to the front of the deque
    deq.push_front(10);
    deq.push_front(20);
    deq.push_front(30);

    // add some elements to the back of the deque
    deq.push_back(40);
    deq.push_back(50);
    deq.push_back(60);

    // print the size of the deque
    std::cout << "Size of deque: " << deq.size() << std::endl;

    // print the first element of the deque
    std::cout << "First element: " << deq.front() << std::endl;

    // print the last element of the deque
    std::cout << "Last element: " << deq.back() << std::endl;

    // change the value of the second element
    deq[1] = 70;

    // print all the elements of the deque using iterator
    std::cout << "All elements: ";
    for (auto it = deq.begin(); it != deq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // remove the first element from the deque
    deq.pop_front();

    // remove the last element from the deque
    deq.pop_back();

    // print the size of the deque again
    std::cout << "Size of deque after pop_front() and pop_back(): " << deq.size() << std::endl;

    // clear the deque
    deq.clear();

    // print the size of the deque after clear()
    std::cout << "Size of deque after clear(): " << deq.size() << std::endl;

    return 0;
}
