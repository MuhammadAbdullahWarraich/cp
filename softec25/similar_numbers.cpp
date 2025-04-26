#include <bits/stdc++.h>
using namespace std;
vector<int> get_factorials_array(int n) {
  vector<int> f(n+1);
  f[0] = 1;
  f[1] = 1;
  for (int i = 2; i <= n; i++) {
    f[i] = i * f[i-1];
  }
  return f;
}
int algo(string a, string b) {
  vector<int> f_a(10, 0), f_b(10, 0);
  for (int i = 0; i < a.size(); i++) f_a[(int)a[i] - '0']++;
  for (int i = 0; i < b.size(); i++) f_b[(int)b[i] - '0']++;
  int ans = -1;
  if (a[0] != '0' && b[0] != '0' && f_a == f_b) {
    //cout << "they are similar!\n";
    vector<int> factorial = get_factorials_array(a.size());
    int total = factorial[a.size()];
    for (int i = 0; i < 10; i++) {
      if (f_a[i] > 0) total /= f_a[i];
    }
    int invalid;
    if (f_a[0] == 0) invalid = 0;
    else {
      invalid = factorial[a.size() - 1];
      invalid /= (f_a[0] - 1);
      for (int i = 1; i < 10; i++) {
        if (f_a[i] > 0) invalid /= f_a[i];
      }
    }
    ans = total - invalid;
    //cout << ans << "\n";
  } else {
    //cout << "they aren't similar!\n";
    vector<int> factorial = get_factorials_array(b.size());
    int total = factorial[b.size()];
    for (int i = 0; i < 10; i++) {
      if (f_b[i] > 0) total /= f_b[i];
    }
    int invalid;
    if (f_b[0] == 0) invalid = 0;
    else {
      invalid = factorial[b.size() - 1];
      invalid /= (f_b[0] - 1);
      for (int i = 1; i < 10; i++) {
        if (f_b[i] > 0) invalid /= f_b[i];
      }
    }
    ans = total - invalid;
    //cout << ans << "\n";
  }
  return ans;
}
void test1() {
  string a = "0011";
  string b = "1100";
  assert(3 == algo(a, b));
}
void test2() {
  string a = "1100";
  string b = "1001";
  assert(3 == algo(a, b));
}
void test3() {
  string a = "1100";
  string b = "90801";
  auto fact = [](int n, auto& fact_ref) {
    if (n <= 1) return 1;
    return n * fact_ref(n-1, fact_ref); 
  };
  int answer = (fact(5, fact) / (2 * 1 * 1 * 1)) - (fact(5-1, fact) / (1 * 1 * 1 * 1));
  assert(answer == algo(a, b));
}
int main() {
  test1();
  test2();
  test3();
  return 0;
}
