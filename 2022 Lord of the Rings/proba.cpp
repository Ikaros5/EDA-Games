#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef pair<int, int> P;
typedef vector<P> VP;

int main() {
   priority_queue <P, VP, greater<P>> q;
   q.push({1, 7});
   q.push({2, 7});
   q.push({1, 4});
   q.push({1, 1});
   q.push({2, 1});
   q.push({1, 6});
   q.push({2, 6});
   q.push({1, 3});
   q.push({1, 9});

   while(!q.empty()) {
      cout << q.top().first << " " << q.top().second << endl;
      q.pop();
   }
}