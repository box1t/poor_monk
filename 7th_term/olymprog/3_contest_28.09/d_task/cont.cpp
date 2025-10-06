#include <bits/stdc++.h>

using namespace std;

/**
 * Calculates the minimum edit distance to make a string a palindrome.
 * 
 * Key insight: To make a string a palindrome, we need to make the first half
 * match the reverse of the second half. The minimum edit distance is the
 * number of mismatched character pairs when comparing from both ends.
 * 
 * @param word The input string
 * @return Minimum number of edit operations needed to make it a palindrome
 */
int getEditDistanceToPalindrome(const string& word) {
    int wordLength = word.length();
    int mismatchedPairs = 0;
    
    // Compare characters from both ends, moving towards the center
    for (int leftIndex = 0; leftIndex < wordLength / 2; leftIndex++) {
        int rightIndex = wordLength - 1 - leftIndex;
        
        // If characters don't match, we need one edit operation
        if (word[leftIndex] != word[rightIndex]) {
            mismatchedPairs++;
        }
    }
    
    return mismatchedPairs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int testCases;
    cin >> testCases;
    
    // Process each test case
    for (int testCase = 1; testCase <= testCases; testCase++) {
        string word;
        cin >> word;
        
        int editDistance = getEditDistanceToPalindrome(word);
        cout << editDistance << "\n";
    }
    
    return 0;
}
