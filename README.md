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

Below are tables with the measurement results of individual operations in *nanoseconds*. The results in the tables are the average operation time per element. Measurements were taken across different table capacities (N) and various Load Factors (1%, 50%, 99%) to simulate best, average, and worst case scenarios.

### Adding elements (Insert)
| N (Capacity) | Load Factor | Custom Hash | djb2 Hash | Polynomial Hash | Stupid Hash
| :--- | :--- | :--- | :--- | :--- | :--- |
| **1000** | 1% | 3010 | 2190 | 2240 | 2310 |
| | 50% | 2959.8 | 2330.8 | 2136.4 | 2164.2 |
| | 99% | 2835.15 | 2268.08 | 2125.45 | 2353.94 |
| **10000** | 1% | 2956 | 2297 | 2191 | 2284 |
| | 50% | 2932.88 | 2339.82 | 2265.76 | 3836.5 |
| | 99% | 2896.47 | 2316.01 | 2124.68 | 2652.14 |
| **100000** | 1% | 2872.1 | 2353.1 | 2066.1 | 2199.6 |
| | 50% | 2907.45 | 2348.75 | 2124.5 | 2175.74 |
| | 99% | 2866.1 | 2352.85 | 2126.96 | 2372.57 |
| **1000000** | 1% | 2977.89 | 2390.43 | 2190.74 | 2262.09 |
| | 50% | 2988.18 | 2383.21 | 2174.78 | 2248.72 |
| | 99% | 3005.03 | 2405.05 | 2174.92 | 2452.2 |

### Removing elements (Remove)
| N (Capacity) | Load Factor | Custom Hash | djb2 Hash | Polynomial Hash | Stupid Hash |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **1000** | 1% | 2320 | 1770 | 1720 | 2180 |
| | 50% | 2589.6 | 1794.6 | 1425.2 | 5714.8 |
| | 99% | 2196.46 | 1663.43 | 1707.47 | 11330.5 |
| **10000** | 1% | 2180 | 1648 | 1665 | 3152 |
| | 50% | 2336.14 | 1712.84 | 1585.72 | 43271 |
| | 99% | 2504.02 | 1707.71 | 1561.4 | 89677.6 |
| **100000** | 1% | 2689.2 | 2135.9 | 1480.9 | 11628.2 |
| | 50% | 2348.54 | 2092.99 | 1649.4 | 407094 |
| | 99% | 2553.39 | 1762.04 | 1599.02 | 1320380 |
| **1000000** | 1% | 2333.73 | 1730.26 | 1541.49 | 84134 |
| | 50% | 2893.96 | 1781.01 | 1611.43 | > 5 minutes |
| | 99% | 3636.29 | 1812.68 | 1656.13 | > 5 minutes |

### Time Complexity of all operations

| Operation | Best Case (Low Load/Good Hash) | Average Case (Mid Load) | Worst Case (High Load/Bad Hash) |
| :--- | :--- | :--- | :--- |
| **Adding an element** | ***O(1)*** | ***O(1)*** | ***O(1)*** |
| **Removing an element** | ***O(1)*** | ***O(1)*** | *O(N)* |
| **Searching for an element** | ***O(1)*** | ***O(1)*** | *O(N)* |

#### Hash Table Architecture Summary
The measurements are a direct result of the Hash Table's architecture. A hash table uses an array of pointers to store data. When an operation is being done the key is passed through a hashing function, which mathematically calculates the exact memory index in constant time ***O(1)***. 
In this implementation, when two different strings produce the same index it is solved by method called **Chaining**. Each spot in hash table (index) is the `head` of a Singly Linked List. Therefore inserting a new element is always ***O(1)*** because when collision occurs we add an element to the beggining of linked list. This operation is not influenced by the load factor of hash table.

Removing elements require traversing the list at the given index. When the **Load Factor is low (e.g., 1%)**, collisions are extremely rare, resulting in instant ***O(1)*** complexity. At a **moderate Load Factor (50%)**, chains are still very short, maintaining near-constant time. As the **Load Factor approaches 100% (99%)**, the likelihood of collisions significantly increases. If the hash function fails to distribute data evenly, the table degrades into long linked lists, causing the computational complexity of the `remove()` operation to drop towards linear ***O(N)***. To illustrate the worst case scenario better there is another hash function called `Stupid Hash` which returns 0 for every value. As you can see in the table above it dramatically decreases performance to the said ***O(n)***.

#### Hash Functions Summary
The efficiency of removal operations heavily relies on the chosen hash function, especially at high Load Factors (99%). 
Standard algorithms like **djb2** and **Polynomial Hash** use prime numbers and bitwise operations to ensure a uniform distribution of elements across all available indexes, keeping chains short even when the table is nearly full. 
Custom algorithms that rely on simple addition or non-prime multiplication often fail to avoid mathematical patterns. This leads to clustering leaving many indexes empty while creating massive chains in others, which dramatically increases the average time of the `remove()` operation as the Load Factor grows.