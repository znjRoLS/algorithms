//
// Created by rols on 4/22/17.
//

#include <unordered_map>
#include "kmp.h"

#define DEBUG 0
#define dout if (DEBUG) cout

// uses less memory in most cases (because this table is usually sparse)
#define USE_HASH_FOR_PARTIAL_MATCH true

int kmp(string haystack, string needle) {

    dout << "finding " << needle << " in " << haystack << endl;

#if USE_HASH_FOR_PARTIAL_MATCH
    unordered_map<int,int> partial_table;
    int i,m;
    //first check needle against itself and fill partial_table
    for(i = 1, m = 0; i < needle.size() - 1;) {
        if (needle[i] == needle[m]) {
            i ++;
            m ++;
            partial_table[i] = m;
        } else if (m > 0){
            m = partial_table[m];
        } else {
            i ++;
        }
    }

    for(pair<int,int> par : partial_table) {
        dout << par.first << " " << par.second << endl;
    }

    for (i = 0, m = 0; m+i < haystack.size();) {
        if (haystack[m+i] == needle[i]) {
            i ++;
            if (i == needle.size()) {
                return m;
            }
        } else if (i > 0) {
            if (partial_table.find(i) == partial_table.end()) {
                m = m + i;
                i = 0;
            } else {
                m = m + i - partial_table[i];
                i = partial_table[i];
            }
        } else {
            m ++;
        }
    }
    return -1;
#else

#endif


    return -1;
}

vector<int> kmp_all(string haystack, string needle) {
    vector<int> results;

    dout << "finding " << needle << " in " << haystack << endl;

#if USE_HASH_FOR_PARTIAL_MATCH
    unordered_map<int,int> partial_table;
    int i,m;
    //first check needle against itself and fill partial_table
    for(i = 1, m = 0; i < needle.size();) {
        if (needle[i] == needle[m]) {
            i ++;
            m ++;
            partial_table[i] = m;
        } else if (m > 0){
            m = partial_table[m];
        } else {
            i ++;
        }
    }

    for(pair<int,int> par : partial_table) {
        dout << par.first << " " << par.second << endl;
    }

    for (i = 0, m = 0; m+i < haystack.size();) {
        if (haystack[m+i] == needle[i]) {
            i ++;
            if (i == needle.size()) {
                results.push_back(m);
                if (partial_table.find(i) == partial_table.end()) {
                    m = m + i;
                    i = 0;
                } else {
                    m = m + i - partial_table[i];
                    i = partial_table[i];
                }
            }
        } else if (i > 0) {
            if (partial_table.find(i) == partial_table.end()) {
                m = m + i;
                i = 0;
            } else {
                m = m + i - partial_table[i];
                i = partial_table[i];
            }
        } else {
            m ++;
        }
    }

#else

#endif

    return results;
}