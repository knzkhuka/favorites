#include<bits/stdc++.h>
using namespace std;

template<class T>
struct culsum_2D {
  int h,w;
  vector<vector<T>> sum;
  culsum_2D(vector<vector<T>>const& a){
    h = a.size();
    w = a[0].size();
    sum.resize(h+1,vector<T>(w+1));
    for(int i=0;i<h;++i)
      for(int j=0;j<w;++j)
        sum[i+1][j+1] = a[i][j];
    for(int i=0;i<h;i++)
      for(int j=0;j<w;j++)
        sum[i+1][j+1] += sum[i+1][j]+sum[i][j+1]-sum[i][j];
  }
  T get(int sy,int sx,int ty,int tx){
    assert(0<=sy&&0<=sx);
    assert(ty<=h&&tx<=w);
    assert(sy<=ty&&sx<=tx);
    return sum[ty][tx]-sum[ty][sx]-sum[sy][tx]+sum[sy][sx];
  }
};

//https://atcoder.jp/contests/abc159/tasks/abc159_e

#define rep(i,n) for(int i=0;i<(n);++i)

signed main(){

  int h,w,k;
  cin>>h>>w>>k;
  vector<string> s(h);
  for(auto& si:s)cin>>si;

  vector<vector<int>> a(h,vector<int>(w));
  rep(i,h)rep(j,w){
    a[i][j] = (s[i][j]=='1');
  }
  culsum_2D<int> sum(a);

  int ans = 1<<28;
  for(int b=0;b<(1<<(h-1));++b){
    bitset<11> bit(b);
    vector<int> s;
    s.emplace_back(0);
    rep(i,h)if(bit[i])s.emplace_back(i+1);
    s.emplace_back(h);
    int res = bit.count();
    int px = 0;
    int n = s.size();
    for(int x=1;x<=w;++x){
      int tmp = 0;
      rep(i,n-1){
        tmp = max(tmp,sum.get(s[i],px,s[i+1],x));
      }
      if(tmp<=k)continue;
      if(abs(x-px)==1){
        res = 1<<28;
        break;
      }
      res++;
      px = x-1;
    }
    ans = min(ans,res);
  }
  cout<<(ans)<<endl;

}