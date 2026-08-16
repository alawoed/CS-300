# Project One: Runtime and Memory Analysis

## Runtime Assumptions

Let `n` represent the number of courses. The ABCU curriculum has a bounded number of prerequisite references per course, so total prerequisite-token processing grows proportionally with `n`. Menu actions and the print/search menu operations are excluded from the loading analysis. Each ordinary pseudocode line has cost 1; a function-call line has the running time of that function.

## Worst-Case File Loading and Course Creation

| Applies To | Code Line / Operation | Cost | Number of Executions | Total |
|---|---|---:|---:|---:|
| Shared | Open file for reading | 1 | 1 | 1 |
| Shared | Initialize empty parsed course vector | 1 | 1 | 1 |
| Shared | Check for another line | 1 | n | n |
| Shared | Read next line | 1 | n | n |
| Shared | Split line and trim tokens | 1 | n | n |
| Shared | Check token count and required fields | 1 | n | n |
| Shared | Create Course object | 1 | n | n |
| Shared | Assign course number, title, and prerequisite vector | 1 | n | n |
| Shared | Process prerequisite tokens | 1 | n | n |
| Shared | Check and append prerequisite token | 1 | n | n |
| Shared | Append Course to parsed collection | 1 | n | n |
| Shared | Iterate through courses during prerequisite validation | 1 | n | n |
| Shared | Iterate through prerequisite references | 1 | n | n |
| Shared | Scan possible courses for matching prerequisite | 1 | n² | n² |
| Shared | Compare course number to prerequisite number | 1 | n² | n² |

The shared parsing and prerequisite-validation process is therefore **O(n²)** in the worst case because prerequisite validation may scan the course collection repeatedly.

### Vector

| Operation | Cost | Number of Executions | Total |
|---|---:|---:|---:|
| Call shared file parsing/validation | O(n²) | 1 | O(n²) |
| Store the parsed vector | 1 | 1 | 1 |

**Worst-case loading runtime: O(n²)**

Looking only at insertion/storage after parsing, adding the courses to the vector is linear, but the required validation step makes the complete loading process O(n²).

### Hash Table

| Operation | Cost | Number of Executions | Total |
|---|---:|---:|---:|
| Call shared file parsing/validation | O(n²) | 1 | O(n²) |
| Iterate through courses and compute hash | 1 | n | n |
| Walk collision chain in the worst case | n | n | n² |

**Worst-case loading runtime: O(n²)**

A hash table normally provides very fast insertion and lookup, but in the worst case every key can collide into the same bucket. Separate chaining then behaves like a linear list, producing an O(n²) worst-case insertion term across all courses.

### Binary Search Tree

| Operation | Cost | Number of Executions | Total |
|---|---:|---:|---:|
| Call shared file parsing/validation | O(n²) | 1 | O(n²) |
| Iterate through courses | 1 | n | n |
| Duplicate check / insertion path in a skewed tree | n | n | n² |

**Worst-case loading runtime: O(n²)**

A reasonably shaped binary search tree performs insertion efficiently, but an unbalanced tree can become skewed. In that worst case, each insertion may require traversing most of the existing tree.

## Data-Structure Evaluation

| Structure | Find One Course | Ordered Course List | Memory | Advantages | Disadvantages |
|---|---|---|---|---|---|
| Vector | O(n) | O(n log n) sort + O(n) print | O(n) | Simple storage, low overhead, easy to load and iterate | Exact lookup is linear and ordered output requires a separate sort |
| Hash Table | Average O(1), worst O(n) | O(n log n) sort + O(n) print | O(n + b), where `b` is the number of buckets | Fastest typical exact lookup; separate chaining handles collisions | No natural order; courses must be collected and sorted; bucket/chain overhead |
| Binary Search Tree | Average O(log n), worst O(n) | O(n) in-order traversal | O(n) | In-order traversal directly produces alphanumeric order; typical lookup is efficient | An unbalanced tree can degrade to linear lookup and deeper recursion |

## Recommendation

I recommend the **binary search tree** for the ABCU advising program. Although the required prerequisite validation makes the complete loading process O(n²) for all three designs, the advisor's two main operations favor the tree after the data is loaded. An in-order traversal prints every course in alphanumeric order in O(n) time without a separate sorting step, while a reasonably shaped tree finds an individual course in O(log n) time on average.

A hash table is stronger for average exact lookup, but it does not maintain course order and therefore requires the courses to be collected and sorted before printing the full schedule. A vector has less structural overhead, but individual course searches are linear and ordered output requires sorting. Considering both required advisor tasks together, the binary search tree provides the best overall fit.