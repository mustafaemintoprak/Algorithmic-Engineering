#include <vector>
#include <unordered_map>

using namespace std;

class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};

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
