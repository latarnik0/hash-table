# Hash Table: Collision Resolution and Hash Functions Comparison

## Overview

Implementation of a Hash Table from scratch in **C++**, using the chaining method (Singly Linked Lists) for collision resolution. The project includes a performance comparison of three different hashing algorithms under various load factors.

## Functionality 
* **Adding elements to the hash table** * **Removing elements from the hash table**
* **Dynamic memory allocation for custom table capacity**
* **Performance analysis of 3 hashing algorithms:**
  * Custom Hash (position-based character multiplication)
  * djb2 Hash (bitwise shifting and magic prime numbers)
  * Polynomial Rolling Hash (treating strings as mathematical polynomials)

## Computational complexity analysis

Below are tables with the measurement results of individual operations in *nanoseconds*. The results in the tables are the average operation time per element. Measurements were taken across different table capacities (N) and various Load Factors (1%, 50%, 99%) to simulate best, average, and near-worst case scenarios.

### Adding elements (Insert)
| N (Capacity) | Load Factor | Custom Hash | djb2 Hash | Polynomial Hash |
| :--- | :--- | :--- | :--- | :--- |
| **1000** | 1% | | | |
| | 50% | | | |
| | 99% | | | |
| **10000** | 1% | | | |
| | 50% | | | |
| | 99% | | | |
| **100000** | 1% | | | |
| | 50% | | | |
| | 99% | | | |
| **1000000** | 1% | | | |
| | 50% | | | |
| | 99% | | | |

### Removing elements (Remove)
| N (Capacity) | Load Factor | Custom Hash | djb2 Hash | Polynomial Hash |
| :--- | :--- | :--- | :--- | :--- |
| **1000** | 1% | | | |
| | 50% | | | |
| | 99% | | | |
| **10000** | 1% | | | |
| | 50% | | | |
| | 99% | | | |
| **100000** | 1% | | | |
| | 50% | | | |
| | 99% | | | |
| **1000000** | 1% | | | |
| | 50% | | | |
| | 99% | | | |

### Time Complexity of all operations

| Operation | Best Case (Low Load/Good Hash) | Average Case (Mid Load) | Worst Case (High Load/Poor Hash) |
| :--- | :--- | :--- | :--- |
| **Adding an element** | ***O(1)*** | ***O(1)*** | ***O(1)*** |
| **Removing an element** | ***O(1)*** | ***O(1)*** | *O(N)* |
| **Searching for an element** | ***O(1)*** | ***O(1)*** | *O(N)* |

#### Hash Table Architecture Summary
The measurements are a direct result of the Hash Table's architecture. A hash table uses an array of pointers (buckets) to store data. When an operation is requested, the key (string) is passed through a hashing function, which mathematically calculates the exact memory index in constant time ***O(1)***. 
In this implementation, collisions (when two different strings produce the same index) are resolved using **Chaining**. Each bucket is the `head` of a Singly Linked List. Therefore, inserting a new element is always ***O(1)*** because it is simply attached to the beginning of the list at the calculated index, regardless of the Load Factor.

However, searching and removing elements require traversing the list at the given index. When the **Load Factor is low (e.g., 1%)**, collisions are extremely rare, resulting in instant ***O(1)*** complexity. At a **moderate Load Factor (50%)**, chains are still very short, maintaining near-constant time. As the **Load Factor approaches 100% (99%)**, the likelihood of collisions significantly increases. If the hash function fails to distribute data evenly, the table degrades into long linked lists, causing the computational complexity of the `remove()` operation to drop towards linear ***O(N)***.

#### Hash Functions Summary
The efficiency of removal operations heavily relies on the chosen hash function, especially at high Load Factors (99%). 
Standard algorithms like **djb2** and **Polynomial Hash** use prime numbers and bitwise operations to ensure a uniform distribution of elements across all available buckets, keeping chains short even when the table is nearly full. 
Custom algorithms that rely on simple addition or non-prime multiplication often fail to avoid mathematical patterns. This leads to clustering – leaving many buckets empty while creating massive chains in others, which dramatically increases the average time of the `remove()` operation as the Load Factor grows.