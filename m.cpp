// brute---------------------------------------------
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

// Brute force approach using two-pass evaluation
int evaluateBruteForce(string s) {
    // Map words to string representations
    unordered_map<string, string> wordToSym = {
        {"zero", "0"}, {"one", "1"}, {"two", "2"}, {"three", "3"}, {"four", "4"},
        {"five", "5"}, {"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"},
        {"plus", "+"}, {"minus", "-"}, {"times", "*"}, {"divided_by", "/"}
    };

    stringstream ss(s);
    string token;
    vector<string> parsedTokens;

    // Convert string tokens to symbols/digits
    while (ss >> token) {
        if (wordToSym.count(token)) {
            parsedTokens.push_back(wordToSym[token]);
        }
    }

    // Pass 1: Handle '*' and '/'
    vector<string> pass1;
    for (int i = 0; i < parsedTokens.size(); i++) {
        if (parsedTokens[i] == "*" || parsedTokens[i] == "/") {
            int prevVal = stoi(pass1.back());
            pass1.pop_back();
            int nextVal = stoi(parsedTokens[i + 1]);
            i++; // skip next operand

            int res = 0;
            if (parsedTokens[i - 1] == "*") res = prevVal * nextVal;
            else res = prevVal / nextVal;

            pass1.push_back(to_string(res));
        } else {
            pass1.push_back(parsedTokens[i]);
        }
    }

    // Pass 2: Handle '+' and '-'
    int result = stoi(pass1[0]);
    for (int i = 1; i < pass1.size(); i += 2) {
        string op = pass1[i];
        int val = stoi(pass1[i + 1]);
        if (op == "+") result += val;
        else if (op == "-") result -= val;
    }

    return result;
}




//optimal---------------------------------------------------------------


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

int solve(string inputStr) {
    // Mapping words to digit values
    unordered_map<string, int> wordToNum = {
        {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
        {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
    };

    // Mapping words to operator symbols
    unordered_map<string, char> wordToOp = {
        {"plus", '+'}, {"minus", '-'}, {"times", '*'}, {"divided_by", '/'}
    };

    stringstream ss(inputStr);
    string word;
    
    stack<int> st;
    char lastOp = '+'; // Default operation for the first number

    while (ss >> word) {
        // Case 1: If current token is a number word
        if (wordToNum.find(word) != wordToNum.end()) {
            int num = wordToNum[word];

            if (lastOp == '+') {
                st.push(num);
            } 
            else if (lastOp == '-') {
                st.push(-num);
            } 
            else if (lastOp == '*') {
                int topVal = st.top();
                st.pop();
                st.push(topVal * num);
            } 
            else if (lastOp == '/') {
                int topVal = st.top();
                st.pop();
                st.push(topVal / num);
            }
        } 
        // Case 2: If current token is an operator word
        else if (wordToOp.find(word) != wordToOp.end()) {
            lastOp = wordToOp[word];
        }
    }

    // Accumulate the calculated numbers from the stack
    int finalResult = 0;
    while (!st.empty()) {
        finalResult += st.top();
        st.pop();
    }

    return finalResult;
}

int main() {
    string inputStr = "eight divided_by two plus three";
    
    int result = solve(inputStr);
    cout << "Output: " << result << endl; // Expected output: 7

    return 0;
}
