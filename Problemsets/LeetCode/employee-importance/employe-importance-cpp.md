# Employee Importance | DFS + Hash Map (O(n)) — C++

---

## 🧠 Intuition

The employee hierarchy forms a tree-like structure where each employee has an importance value and may have multiple subordinates.

To compute the total importance of a given employee, we must include:

- The employee’s own importance  
- The importance of all direct subordinates  
- The importance of all indirect subordinates  

Since this is a recursive hierarchical relationship, a **Depth-First Search (DFS)** traversal is a natural and efficient approach.

---

## 🚀 Approach

1. Build a hash map (`unordered_map`) that maps:

   ```
   employee id → Employee*
   ```

   This allows constant-time lookup of any employee.

2. Start a DFS from the given `id`.

3. For each employee:
   - Add their importance to a running total.
   - Recursively call DFS for each subordinate.
   - Accumulate the returned values.

Each employee is visited exactly once during traversal.

---

## ⏱ Complexity

### Time Complexity
- Building the hash map: `O(n)`
- DFS traversal: `O(n)`

Overall: **O(n)**

### Space Complexity
- Hash map storage: `O(n)`
- Recursion stack (worst case): `O(n)`

Overall: **O(n)**

---

## 💻 Code

```cpp
/*
Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
*/

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:

    unordered_map<int, Employee*> mp;

    int dfs(int id) {
        Employee* emp = mp[id];
        int total = emp->importance;

        for (int subId : emp->subordinates) {
            total += dfs(subId);
        }

        return total;
    }

    int getImportance(vector<Employee*> employees, int id) {

        for (Employee* emp : employees) {
            mp[emp->id] = emp;
        }

        return dfs(id);
    }
};
```

---

## 📌 Key Takeaways

- Convert hierarchical structures into graph traversal problems.
- Use `unordered_map` for constant-time ID lookup.
- DFS is ideal for recursive accumulation problems.
- Each node is visited exactly once → optimal linear complexity.

---
