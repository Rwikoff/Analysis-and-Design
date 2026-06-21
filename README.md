# Analysis-and-Design
What was the problem you were solving?

The objective was to build an efficient advising assistance tool for ABCU’s Computer Science department. The core challenge was to design a system capable of parsing course data, managing complex prerequisite relationships, and providing fast, alphanumeric retrieval of the full course catalog for department advisors.

How did you approach the problem?

I approached this by first analyzing the runtime and memory implications of various data structures—vectors, hash tables, and trees. I learned that data structures are the foundation of performance; choosing the wrong structure can make a program scale poorly. I ultimately selected a Binary Search Tree (BST) because its structure keeps data naturally sorted, eliminating the need for expensive post-load sorting algorithms.

How did you overcome any roadblocks?

The primary hurdle was ensuring the CSV parsing handled edge cases—like trailing commas or varied line endings—without crashing. I overcame this by implementing a custom string-splitting helper function and a robust two-pass loading process that verified prerequisites against the catalog before finalizing the tree insertion.

How has your work expanded your approach to designing software?

This project shifted my focus toward "algorithmic thinking." I now consider the efficiency of a program before writing a single line of code. Designing the system architecture in Project One before implementation in Project Two taught me that thoughtful planning significantly reduces technical debt and debugging time later in the development cycle.

How has your work evolved your ability to write maintainable, readable, and adaptable code?

I have moved away from monolithic functions toward modular, object-oriented design. By encapsulating logic within a BinarySearchTree class and utilizing descriptive naming conventions, I’ve made my code much more readable. I now prioritize creating clean, reusable interfaces, ensuring that if requirements change, the code is adaptable enough to evolve without a total rewrite.

## Vector Runtime Analysis (Worst-Case)

Assumptions: n is the number of courses, and p is the average number of prerequisites per course. Validating prerequisites requires searching the entire unsorted vector, which takes O(n) time.

<img width="664" height="721" alt="Vector" src="https://github.com/user-attachments/assets/9b24f8cb-d851-443d-bb22-37c2788813e3" />

## Hash Table Runtime Analysis (Worst-Case)

Assumptions: n is the number of courses, and p is the average number of prerequisites. In the absolute worst-case scenario, every single course hashes to the exact same bucket, turning the Hash Table into a linked list where Insert and Search both take O(n) time.

<img width="643" height="686" alt="HashTable" src="https://github.com/user-attachments/assets/65920b52-f39f-4a98-ab05-766e936a1e7c" />

## Binary Search Tree Runtime Analysis (Worst-Case)

Assumptions: n is the number of courses, and p is the average number of prerequisites per course. Searching an unsorted list for validation takes O(n) time. Inserting into an unbalanced Binary Search Tree (where the input data is already perfectly sorted) takes O(n) time.

<img width="562" height="749" alt="BinarySearchTree" src="https://github.com/user-attachments/assets/91d11909-faf3-4352-b6d5-ae2684891bdb" />

## Evaluation

When evaluating the appropriate data structure for the advising program, vectors offer a highly advantageous approach for simple data loading. Because they are dynamic arrays, appending new course objects to the end of the list as the file is read operates in fast, constant time, or O(1). However, their primary disadvantage emerges when sorting is required. Vectors are inherently unsorted, meaning that to fulfill the advisors' requirement of printing the courses in alphanumeric order, the program must execute a separate sorting algorithm, such as QuickSort or MergeSort. This adds significant computational overhead, generally O(n log n), every single time the advisor requests the course list.

Hash tables provide exceptional speed for specific lookups, making them a strong candidate for searching individual courses. Finding a single course and its prerequisites operates in O(1) average time, making it the fastest option for single-item retrieval. The distinct disadvantage of this structure is that hash tables distribute data based on hash codes, resulting in completely unordered data. To print an alphanumeric catalog, the program would need to extract all keys into a temporary list, run a sorting algorithm on that list, and then iterate through it to print. This is a highly inefficient process for generating the required ordered output.

A binary search tree provides an excellent balance for this specific scenario. Lookups for individual courses operate efficiently in O(log n) average time. The most significant advantage, however, is that a binary search tree keeps the data naturally sorted during the insertion process. While the worst-case runtime for initially loading the data into a completely unbalanced tree is O(n2), the tree structure's natural organization is ultimately much more valuable for the program's primary goals.

Based on this analysis, I recommend using a binary search tree for the final C++ code implementation. The advising program’s ongoing operational requirements rely heavily on data retrieval and ordered output rather than constant data insertion. By using the course number as the node key, the requirement to print an alphanumerically ordered course catalog can be accomplished effortlessly using a simple in-order traversal, which operates in O(n) time. Unlike the vector and the hash table, the binary search tree completely eliminates the need to write and execute separate, computationally expensive sorting algorithms to meet the advisors' formatting requirements. This makes it the most elegant, balanced, and efficient solution for this specific scenario.
