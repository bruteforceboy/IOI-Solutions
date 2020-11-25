#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, T, P;
  cin >> N >> T >> P;
  int arr[N][T];
  int point[T];
  for (int i = 0; i < T; i++)
    point[i] = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < T; j++) {
      cin >> arr[i][j];
      if (arr[i][j] == 0)
        point[j]++;
    }
  }
  vector<pair<int, pair<int, int>>>rank;
  for (int i = 0; i < N; i++) {
    int score = 0;
    int solved = 0;
    for (int j = 0; j < T; j++) {
      if (arr[i][j] == 1) {
        ++solved;
        score += point[j];
      }
    }
    rank.push_back(make_pair(score, make_pair(solved, i)));
  }
  sort(rank.begin(), rank.end());
  reverse(rank.begin(), rank.end());
  for (int i = 0; i < rank.size(); i++) {
    // while score and solved are equal
    int count = 1;
    int j = i;
    while (rank[j + 1].first == rank[j].first && rank[j + 1].second.first == rank[j].second.first) {
      ++count;
      ++j;
    }
    if (count > 0) {
      sort(rank.begin() + i, rank.begin() + i + count);
      i = j;
    }
  }
  for (int i = 0; i < rank.size(); i++) {
    int id = rank[i].second.second;
    if (id == P - 1)
      cout << rank[i].first << " " << i + 1 << endl;
  }
}
