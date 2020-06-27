//
// Created by zyl on 2020/6/27.
//

#include "algorithm.h"


/**********************************************************************/
/*
 * KMP (Knuth Morris Pratt) algorithm
 *      Pattern search, first generate a LPS (Longest Prefix Suffix) list,
 * */
/**********************************************************************/
vector<int> LPS(const string &pat) {
    vector<int> lps(pat.size(), 0);
    int len = 0, i = 1;
    while  (i < pat.size()) {
        if (pat[len] == pat[i]) {
            len++;
            lps[i] = len;
            i++;
        } else if (len > 0) {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar to search the step
            len = lps[len - 1];
        } else {
            lps[i] = 0;
            i++;
        }
    }
    return lps;
}

vector<int> KMP(const string& txt, const string& pat) {
    vector<int> lps = LPS(pat);
    vector<int> res;
    int i, j = 0;
    while (i < txt.size()) {
        if (txt[i] == pat[j]) {
            i++;
            j++;
            if (j == pat.size()) res.push_back(i - j);
        } else if (j != 0) {
            j = lps[j - 1];
        } else {
            j = 0;
            i++;
        }
    }
    return res;
}