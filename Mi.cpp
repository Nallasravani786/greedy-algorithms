#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

int calculate(string s) {
    stack<int> st;
    int currNum = 0;
    char lastOp = '+';
    int n = s.length();

    for (int i = 0; i < n; i++) {
        char ch = s[i];

        // Step 1: Form the current number
        if (isdigit(ch)) {
            currNum = currNum * 10 + (ch - '0');
        }

        // Step 2: Process operator or end of expression
        if ((!isdigit(ch) && !isspace(ch)) || i == n - 1) {
            if (lastOp == '+') {
                st.push(currNum);
            } else if (lastOp == '-') {
                st.push(-currNum);
            } else if (lastOp == '*') {
                int topVal = st.top();
                st.pop();
                st.push(topVal * currNum);
            } else if (lastOp == '/') {
                int topVal = st.top();
                st.pop();
                st.push(topVal / currNum);
            }

            // Reset for the next term
            lastOp = ch;
            currNum = 0;
        }
    }

    // Step 3: Accumulate stack results
    int finalResult = 0;
    while (!st.empty()) {
        finalResult += st.top();
        st.pop();
    }

    return finalResult;
}

int main() {
    string expr1 = "8 / 2 + 3";
    string expr2 = "100 / 20 + 23";

    cout << "Output 1: " << calculate(expr1) << endl; // Output: 7
    cout << "Output 2: " << calculate(expr2) << endl; // Output: 28

    return 0;
}
