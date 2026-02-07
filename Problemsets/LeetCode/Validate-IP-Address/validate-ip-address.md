# 🌐 Validate IP Address | String Parsing + Format Validation (O(n)) — C++

---

## 🧠 Intuition

An IP address can either be:

- **IPv4**
- **IPv6**
- Or **Neither**

Each version follows strict formatting rules. Instead of mixing validation logic, we classify the input based on its delimiter:

- If it contains `.` → attempt **IPv4** validation  
- If it contains `:` → attempt **IPv6** validation  

This keeps the logic clean and ensures proper edge-case handling.

---

## 🚀 Approach

### 🔹 IPv4 Validation

An IPv4 address must:

- Contain exactly **4 segments**
- Segments separated by `.`
- Each segment:
  - Length between **1 and 3**
  - Contains only digits `0–9`
  - Numeric value between **0 and 255**
  - Must not contain leading zeros (except `"0"`)

Validation Steps:

1. Reject early if:
   ```
   - Starts or ends with '.'
   - Contains ".." (empty segment)
   ```
2. Split using `.`
3. Ensure segment count equals 4
4. For each segment:
   - Not empty
   - No leading zero (unless length is 1)
   - All characters are digits
   - Integer value within `[0, 255]`

If all checks pass → return `"IPv4"`.

---

### 🔹 IPv6 Validation

An IPv6 address must:

- Contain exactly **8 segments**
- Segments separated by `:`
- Each segment:
  - Length between **1 and 4**
  - Contains only hexadecimal characters:
    - `0–9`
    - `a–f`
    - `A–F`
- Leading zeros are allowed
- The compressed format `"::"` is not allowed in this problem

Validation Steps:

1. Reject early if:
   ```
   - Starts or ends with ':'
   - Contains "::"
   ```
2. Split using `:`
3. Ensure segment count equals 8
4. Validate each segment for valid hexadecimal characters

If all checks pass → return `"IPv6"`.

If neither validation succeeds → return `"Neither"`.

---

## ⏱ Complexity

### Time Complexity
- Splitting the string: `O(n)`
- Validating segments: `O(n)`

Overall: **O(n)**

### Space Complexity
- Storage for segments (maximum 4 or 8): `O(1)`

Overall: **O(1)**

---

## 💻 Code

```cpp
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string validIPAddress(string queryIP) {

        // Try IPv4
        if (queryIP.find('.') != string::npos) {

            if (queryIP.front() == '.' || queryIP.back() == '.' || 
                queryIP.find("..") != string::npos)
                return "Neither";

            vector<string> v;
            stringstream ss(queryIP);
            string token;

            while (getline(ss, token, '.')) {
                v.push_back(token);
            }

            if (v.size() != 4) return "Neither";

            for (int i = 0; i < 4; i++) {

                if (v[i].empty() || v[i].size() > 3)
                    return "Neither";

                if (v[i].size() > 1 && v[i][0] == '0')
                    return "Neither";

                for (char c : v[i]) {
                    if (!isdigit(c))
                        return "Neither";
                }

                int num = stoi(v[i]);
                if (num < 0 || num > 255)
                    return "Neither";
            }

            return "IPv4";
        }

        // Try IPv6
        else if (queryIP.find(':') != string::npos) {

            if (queryIP.front() == ':' || queryIP.back() == ':' || 
                queryIP.find("::") != string::npos)
                return "Neither";

            vector<string> v;
            stringstream ss(queryIP);
            string token;

            while (getline(ss, token, ':')) {
                v.push_back(token);
            }

            if (v.size() != 8) return "Neither";

            for (int i = 0; i < 8; i++) {

                if (v[i].empty() || v[i].size() > 4)
                    return "Neither";

                for (char c : v[i]) {
                    if (!(
                        (c >= '0' && c <= '9') ||
                        (c >= 'a' && c <= 'f') ||
                        (c >= 'A' && c <= 'F')
                    )) {
                        return "Neither";
                    }
                }
            }

            return "IPv6";
        }

        return "Neither";
    }
};
```

---

## 📌 Key Takeaways

- Classify input based on delimiter before validation.
- Carefully handle edge cases (leading/trailing delimiters, empty segments).
- Use `stringstream` for clean splitting.
- Strict validation prevents partial parsing errors.
- Each segment is validated exactly once → linear time complexity.

---
