#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string validIPAddress(string queryIP) {

        // Try IPv4
        if (queryIP.find('.') != string::npos) {

            // reject leading/trailing dot, and double dots
            if (queryIP.front() == '.' || queryIP.back() == '.' || queryIP.find("..") != string::npos)
                return "Neither";

            vector<string> v;
            stringstream ss(queryIP);
            string token;

            while (getline(ss, token, '.')) {
                v.push_back(token);
            }

            if (v.size() != 4) return "Neither";

            for (int i = 0; i < 4; i++) {

                if (v[i].empty() || v[i].size() > 3) return "Neither";
                if (v[i].size() > 1 && v[i][0] == '0') return "Neither";

                for (char c : v[i]) {
                    if (!isdigit(c)) return "Neither";
                }

                int num = stoi(v[i]);
                if (num < 0 || num > 255) return "Neither";
            }

            return "IPv4";
        }

        // Try IPv6
        else if (queryIP.find(':') != string::npos) {

            // reject leading/trailing colon, and double colons (:: not allowed)
            if (queryIP.front() == ':' || queryIP.back() == ':' || queryIP.find("::") != string::npos)
                return "Neither";

            vector<string> v;
            stringstream ss(queryIP);
            string token;

            while (getline(ss, token, ':')) {
                v.push_back(token);
            }

            if (v.size() != 8) return "Neither";

            for (int i = 0; i < 8; i++) {

                if (v[i].empty() || v[i].size() > 4) return "Neither";

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
