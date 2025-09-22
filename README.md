# SingleList

The `SingleList` class implements a **singly linked list** data structure that is dynamically resizable and allows insertion, deletion, and traversal of elements.

This is a **template class**, so it can store objects of any data type.

---

## Key Features

- **Template Class:** Can store any type of data using `SingleList<T>`.
- **Linked List:** Uses an internal `Node` structure with `data_` and `next_` pointers.
- **Iterator Support:** Provides both `iterator` and `const_iterator` for STL-style loops and algorithms.
- **Extensive Functionality:**
  - `push_front`, `pop_front`, `insert`, `insert_after`
  - `erase`, `erase_after`
  - `resize`, `clear`, `swap`
  - `splice`, `splice_after`
  - `merge`, `sort`, `reverse`, `unique`, `remove`
- **Comparison Operators:** `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Stream Operators:** `>>`, `<<` for input/output

---

## Usage Example

```cpp
#include "SingleList.hpp"
#include <iostream>

int main() {
    SingleList<int> list;

    // Insert elements
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    // Print the list
    std::cout << "List: " << list << std::endl; // { 1 2 3 }

    // Remove the first element
    list.pop_front();
    std::cout << "After pop_front: " << list << std::endl; // { 2 3 }

    // Merge another list
    SingleList<int> list2;
    list2.push_front(6);
    list2.push_front(5);
    list2.push_front(4);

    list.splice(list.begin(), list2);
    std::cout << "After splice: " << list << std::endl; // { 4 5 6 2 3 }

    // Reverse the list
    list.reverse();
    std::cout << "Reversed list: " << list << std::endl; // { 3 2 6 5 4 }

    return 0;
}
