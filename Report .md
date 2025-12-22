# Optimizing Power Distribution in a Smart Electrical Grid Using Search Algorithms

## 1. Problem Description
Modern electrical grids must distribute limited power resources to multiple regions with different demands, priorities, and transmission costs. The challenge is to allocate electricity efficiently while respecting system constraints and minimizing overall cost.

In this project, we model a **Smart Electrical Grid Power Distribution** problem where a single power station supplies electricity to several regions (hospitals, factories, residential areas). 

### Region Characteristics:
* **Demand:** The amount of power required.
* **Priority:** Importance level (High, Medium, Low).
* **Transmission Cost:** Cost of delivering one unit of power.

### Objectives:
1. Total distributed power must not exceed station capacity.
2. High-priority regions are satisfied first.
3. Total transmission cost is minimized.

---

## 2. Algorithms Used

### 2.1 Breadth-First Search (BFS)
* **Pros:** Guarantees a feasible solution if it exists.
* **Cons:** High memory consumption; ignores cost/priority.
* **Purpose:** Baseline comparison.

### 2.2 Depth-First Search (DFS)
* **Pros:** Lower memory usage.
* **Cons:** No guarantee of optimality; can be inefficient.
* **Purpose:** Demonstrates limitations of uninformed search.

### 2.3 Uniform Cost Search (UCS)
* **Pros:** Guarantees an optimal solution based on cost.
* **Cons:** Slower than informed methods.
* **Purpose:** Finds the minimum-cost distribution.

### 2.4 Iterative Deepening Search (IDS)
* Iterative Deepening Search was not suitable for this problem due to the extremely large depth and exponential growth of the search space. 

### 2.5 A* Search
* **Pros:** Optimal and highly efficient.
* **Cons:** Requires a well-designed heuristic.
* **Purpose:** Best-performing algorithm for this problem.

### 2.6 Greedy Algorithm
* **Pros:** Very fast and simple.
* **Cons:** No global optimality guarantee.
* **Purpose:** try the algorithm that has the best desicion at the moment  .

### 2.7 Genetic Algorithm
* **Pros:** Scales well with problem size.
* **Cons:** Result is near-optimal, not always perfectly optimal.
* **Purpose:** Solves complex optimization effectively.

---

## 3. Heuristic Design

### A* Heuristic Function
$h(n) = \text{Remaining demand} * \text{min cost}$
* **Admissibility:** It never overestimates the cost, ensuring A* remains optimal.

### Greedy Heuristic
$\text{Score} = \frac{\text{Priority Weight}}{\text{Transmission Cost}}$
* Favors high importance and low cost but ignores future consequences.

---

## 4. Results & Comparison

| Algorithm | Prioritize High-Priority Regions | Minimize Total Cost | Overall Suitability |
| :--- | :--- | :--- | :--- |
| **BFS** | Not interested | Not optimal -> 340 | Very poor |
| **DFS** | Not interested | Not optimal -> 340 | Very poor |
| **UCS** | Depends on cost | Optimal -> 280 | Very good |
| **A\*** | Depends on heuristic | Optimal -> 280 | **Best choice** |
| **Greedy** | Sometimes | Not guaranteed -> 280 | Acceptable (fast) |
| **Genetic Algorithm** | Fitness weighted | Near optimal -> 140 | Good for large problems |

### Analysis:
* **A\*** achieved optimal results with the fewest node expansions.
* **UCS** found the optimal solution but was computationally heavier.
* **Genetic Algorithm** is best for large-scale systems where absolute optimality isn't feasible.

---

## 5. Conclusion
**A* search** is the most suitable algorithm for this problem, providing a balance of optimality and efficiency. For larger, more complex grids, the **Genetic Algorithm** offers a strong alternative.
