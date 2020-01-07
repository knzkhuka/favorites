#include<bits/stdc++.h>
using namespace std;

template<class T>
vector<T> slide_min(vector<T> const& v,int k){
  vector<T> mins;
  deque<int> deq;
  int n = v.size();
  for(int i=0;i<n;++i){
    if(i>=k)mins.emplace_back(v[deq.front()]);
    if(deq.front()+k<=i)deq.pop_front();
    while(!deq.empty() && v[i]<v[deq.back()]){
      deq.pop_back();
    }
    deq.emplace_back(i);
  }
  mins.emplace_back(v[deq.front()]);
  return mins;
}

signed main(){

  int n,k;
  cin>>n>>k;
  vector<int> a(n);
  for(auto& ai:a)cin>>ai;
  for(auto&& x:slide_min(a,k))cout<<x<<" ";
  cout<<endl;

}