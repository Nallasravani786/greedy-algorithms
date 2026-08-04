//optimal-----------------
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <stack>

using namespace std;

int solve(string s) {
    unordered_map<string, int> units = {
        {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
        {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
        {"ten", 10}, {"eleven", 11}, {"twelve", 12}, {"thirteen", 13},
        {"fourteen", 14}, {"fifteen", 15}, {"sixteen", 16}, {"seventeen", 17},
        {"eighteen", 18}, {"nineteen", 19}
    };

    unordered_map<string, int> tens = {
        {"twenty", 20}, {"thirty", 30}, {"forty", 40}, {"fifty", 50},
        {"sixty", 60}, {"seventy", 70}, {"eighty", 80}, {"ninety", 90}
    };

    unordered_map<string, char> ops = {
        {"plus", '+'}, {"minus", '-'}, {"times", '*'}, {"divided_by", '/'}
    };

    stringstream ss(s);
    string word;
    
    stack<int> st;
    char lastOp = '+';
    int currentNum = 0;

    auto processNum = [&](int num, char op) {
        if (op == '+') {
            st.push(num);
        } else if (op == '-') {
            st.push(-num);
        } else if (op == '*') {
            int topVal = st.top();
            st.pop();
            st.push(topVal * num);
        } else if (op == '/') {
            int topVal = st.top();
            st.pop();
            st.push(topVal / num);
        }
    };

    while (ss >> word) {
        if (ops.count(word)) {
            // Apply operation for completed number
            processNum(currentNum, lastOp);
            currentNum = 0;
            lastOp = ops[word];
        } else if (units.count(word)) {
            currentNum += units[word];
        } else if (tens.count(word)) {
            currentNum += tens[word];
        } else if (word == "hundred") {
            currentNum = (currentNum == 0 ? 1 : currentNum) * 100;
        }
    }

    // Process the final remaining number
    processNum(currentNum, lastOp);

    // Sum stack contents
    int result = 0;
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }

    return result;
}

int main() {
    // Example: (100 / 20) + 23 = 5 + 23 = 28
    string inputStr = "one hundred divided_by twenty plus twenty three";
    
    int result = solve(inputStr);
    cout << "Output: " << result << endl; // Output: 28

    return 0;
}
