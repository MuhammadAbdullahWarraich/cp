/*
#include <bits/stdc++.h>
*/
///*
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <cstring>
//*/
bool DEBUG = false;
using namespace std;
int mapper(char ch) {
  if (ch == 'a') return 0;
  if (ch == 'e') return 1;
  if (ch == 'i') return 2;
  if (ch == 'o') return 3;
  if (ch == 'u') return 4;
  return -1;
}
void print_prefix_1(vector<int>& prefix_st) {
  string prefix = "";
  for (int i = prefix_st.size()-1; i >= 0; i--) {
    auto el = prefix_st[i];
    if (el == 0) prefix = "  " + prefix;
    else if (i+1 != prefix_st.size()) prefix = "| " + prefix;
    else if (el == 1) {
      prefix_st.pop_back();
      prefix_st.push_back(0);
      prefix = "|_" + prefix;
    } else {
      int val = prefix_st.back();
      prefix_st.pop_back();
      prefix_st.push_back(val-1);
      prefix = "|-" + prefix;
    }
  }
  cout << prefix;
}

vector<int> get_freqs(string str, int start, int end) {
  vector<int> f(5, 0);
  for (; start < end; start++) {
    assert(mapper(str[start]) != -1);
    f[mapper(str[start])] += 1;
  }
  return f;
}
int rec_func(string str, int start, int end, vector<int>& f, vector<vector<int>>& dp, vector<int>& prefix_st) {
  if (DEBUG) {
    print_prefix_1(prefix_st);
    cout << "\"";
    for (int i = start; i < end; i++) {
      cout << str[i];
    }
    cout << "\"\n";
  }
  if (end-start < 5) return 0;
  if (f[0] < 1 || f[1] < 1 || f[2] < 1 || f[3] < 1 || f[4] < 1) return 0;
  {
    auto dp_val = dp[start][end-1];
    if (dp_val != -1) return 0;
  }
  int ans = 1;
  int start_ch_mapped = mapper(str[start]), end_ch_mapped = mapper(str[end-1]);
  if (DEBUG) {
    int push_val = f[start_ch_mapped] > 1 ? 1 : 0;
    push_val += f[end_ch_mapped] > 1 ? 1 : 0;
    if (push_val > 0) prefix_st.push_back(push_val);
    else {
      while (prefix_st.size() > 0 && prefix_st.back() == 0) prefix_st.pop_back();
    }
  }
  if (f[start_ch_mapped] > 1) {
    f[start_ch_mapped] -= 1;
    int val = rec_func(str, start+1, end, f, dp, prefix_st);
    dp[start+1][end-1] = val;
    ans += val;
    f[start_ch_mapped] += 1;
  }
  if (f[end_ch_mapped] > 1) {
    f[end_ch_mapped] -= 1;
    int val = rec_func(str, start, end-1, f, dp, prefix_st);
    dp[start][end-2] = val;
    ans += val;
    f[end_ch_mapped] += 1;
  }
  return ans;
}
int foo(string str, int start, int end, vector<vector<int>>& dp) {
  vector<int> prefix_st;
  if (DEBUG) prefix_st.push_back(1);
  //cout << "foo called for: \"";
  //cout << "foo: \"";
  cout << "\"";
  for (int i = start; i < end; i++) {
    cout << str[i];
  }
  cout << "\"\n";
  auto f = get_freqs(str, start, end);
  return rec_func(str, start, end, f, dp, prefix_st);
}
int algo(string str) {
  int n = str.size();
  int start=0, end=0;
  vector<vector<int>> dp(n, vector<int>(n, -1));
  int ans = 0;
  for (int i = 0; i <= n; i++) {
    int mapped = i == n ? -1 : mapper(str[i]);
    if (mapped == -1) {
      end = i;
      if (start == end) {start = i+1; continue; }
      if (end-start < 5) { start = i+1; continue; }
      if (mapper(str[start]) == -1) { start++; end++; continue; }
      ans += foo(str, start, end, dp);
      start = i+1;
      end = i+1;
    } else {
      end++;
    }
  }
  return ans;
}

void test1() {
  string str = "aeiou";
  int ans = algo(str);
  assert(1 == ans);
}
void test2() {
  string str = "aebioudf";
  int ans = algo(str);
  assert(0 == ans);
}
void test3() {
  string str = "xaeiouax";
  int ans = algo(str);
  assert(3 == ans);
}
void test4() {
  string str = "aeiouaa";
  int ans = algo(str);
  assert(5 == ans);
}
void test5() {
  string str = "aaeiouua";
  int ans = algo(str);
  assert(7 == ans);
}
void test6() {
  string str = "aaeixyuaoiiieezwoaxueiaeiouua";
  int ans = algo(str);
  assert(16 == ans);
}
int main(int argc, char **argv) {
  if (argc == 1) DEBUG = false;
  else if (2 == argc && 0 == strcmp(argv[1], "debug")) DEBUG = true;
  else {
    cout << "Usage\nfor debugging: ./executable debug\n";
    cout << "for normal run: ./executable\n";
    exit(1);
  }
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  return 0;
}

