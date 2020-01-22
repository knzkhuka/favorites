#include<bits/stdc++.h>
using namespace std;

template<class T,class F>
struct segtree{
  int n;
  T e;
  F f;
  std::vector<T> dat;

  segtree(){}
  segtree(int sz,T _e,F _f):e(_e),f(_f){
    n = 1;
    while(n<=sz)n<<=1;
    dat.resize(2*n,e);
  }
  segtree(std::vector<T> const& v,T _e,F _f):e(_e),f(_f){
    build(v);
  }
  void build(std::vector<T> const& v){
    n = 1;
    int sz = v.size();
    while(n<=sz)n<<=1;
    dat.resize(2*n,e);
    for(int i=0;i<sz;++i){
      dat[i+n] = v[i];
    }
    for(int i=n-1;i>0;--i){
      dat[i] = f(dat[i<<1],dat[i<<1|1]);
    }
  }
  void set(int p,T v){
    for(dat[p+=n]=v;p>1;p>>=1){
      dat[p>>1] = f(dat[p],dat[p^1]);
    }
  }
  void increment(int p){
    for(dat[p+=n]=1;p>1;p>>=1){
      dat[p>>1] = f(dat[p],dat[p^1]);
    }
  }
  T query(int l,int r){
    T res = e;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1){
      if(l&1){
        res = f(res,dat[l]);
        l++;
      }
      if(r&1){
        r--;
        res = f(res,dat[r]);
      }
    }
    return res;
  }
  T operator[](int k){
    return query(k,k+1);
  }
};

vector<int64_t> frac;

signed main(){

  // https://atcoder.jp/contests/abc150/tasks/abc150_c

  int n;
  cin>>n;
  frac.resize(n+1);
  frac[0] = frac[1] = 1;
  for(int64_t i=2;i<=n;++i)frac[i]=frac[i-1]*i;
  vector<int64_t> a(n),b(n);
  for(auto& ai:a)cin>>ai;
  for(auto& bi:b)cin>>bi;

  auto get = [](vector<auto> const& a){
    int n = a.size();
    auto sum = [](auto a,auto b){return a+b;};
    segtree<int64_t,decltype(sum)> seg(n+1,0,sum);

    auto k = 0;
    for(auto i=0;i<n;++i){
      auto t = seg.query(0,a[i]);
      k += (a[i]-t-1)*frac[n-i-1];
      seg.increment(a[i]);
    }
    return k;
  };

  cout<<abs(get(a)-get(b))<<endl;

}
