# Hash Table: Collision Resolution and Hash Functions Comparison

## Overview

Implementation of a Hash Table from scratch in **C++**, using the chaining method (Singly Linked Lists) for collision resolution. The project includes a performance comparison of three different hashing algorithms.

## Functionality 
* **Adding elements to the hash table** * **Removing elements from the hash table**
* **Dynamic memory allocation for custom table capacity**
* **Performance analysis of 3 hashing algorithms:**
  * Custom Hash (position-based character multiplication)
  * djb2 Hash (bitwise shifting and magic prime numbers)
  * Polynomial Rolling Hash (treating strings as mathematical polynomials)

## Computational complexity analysis

Below are tables with the measurement results of individual operations in *nanoseconds*. The results in the tables are the average operation time per element, measured during mass insertion and deletion at different load factors **1%, 50%, 99%**.

### Adding elements (Insert)
| Operation | N (Capacity) | Custom Hash | djb2 Hash | Polynomial Hash |
| :--- | :--- | :--- | :--- | :--- |
| **Insert** | 1000 |  |  |  |
| | 10000 |  |  |  |
| | 100000 |  |  |  |
| | 1000000 |  |  |  |

### Removing elements (Remove)
| Operation | N (Capacity) | Custom Hash | djb2 Hash | Polynomial Hash |
| :--- | :--- | :--- | :--- | :--- |
| **Remove** | 1000 |  |  |  |
| | 10000 |  |  |  |
| | 100000 |  |  |  |
| | 1000000 |  |  |  |

### Time Complexity of all operations

| Operation | Average Case (Good Hash Function) | Worst Case (High Collisions) |
| :--- | :--- | :--- |
| **Adding an element** | ***O(1)*** | ***O(1)*** |
| **Removing an element** | ***O(1)*** | *O(N)* |
| **Searching for an element** | ***O(1)*** | *O(N)* |

#### Hash Table Architecture Summary
The measurements are a direct result of the Hash Table's architecture. A hash table uses an array of pointers (buckets) to store data. When an operation is requested, the key (string) is passed through a hashing function, which mathematically calculates the exact memory index in constant time ***O(1)***. 
In this implementation, collisions (when two different strings produce the same index) are resolved using **Chaining**. Each bucket is the `head` of a Singly Linked List. Therefore, inserting a new element is always ***O(1)*** because it is simply attached to the beginning of the list at the calculated index.

However, searching and removing elements require traversing the list at the given index. In the Average Case (where data is uniformly distributed), chains are very short, resulting in ***O(1)*** complexity. In the Worst Case (e.g., a poor hash function that assigns all elements to a single index), the table degrades into a single linked list, and the computational complexity drops to linear ***O(N)***.

#### Hash Functions Summary
The efficiency of removal operations heavily relies on the chosen hash function. 
Standard algorithms like **djb2** and **Polynomial Hash** use prime numbers and bitwise operations to ensure a uniform distribution of elements across all available buckets, keeping chains extremely short even at high Load Factors. 
Custom algorithms that rely on simple addition or non-prime multiplication often fail to avoid mathematical patterns (like parity bias). This leads to clustering – leaving many buckets empty while creating massive chains in others, which dramatically increases the average time of the `remove()` operation.