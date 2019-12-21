#include<bits/stdc++.h>
using namespace std;

// F := merge dat,dat
// G := lazy -> dat
// H := lazy -> lazy
template<class T,class F,class G,class H>
struct lazy_segment_tree{
  int n;
  vector<T> dat,lazy;
  T de,le;
  F f;
  G g;
  H h;

  lazy_segment_tree(){}
  lazy_segment_tree(int sz,F _f,G _g,H _h,T _de,T _le)
    :f(_f),g(_g),h(_h),de(_de),le(_le)
  {
    n = 1;
    while(n<=sz)n<<=1;
    dat.resize(2*n-1,de);
    lazy.resize(2*n-1,le);
  }
  lazy_segment_tree(vector<T> const& v,F _f,G _g,H _h,T _de,T _le)
    :f(_f),g(_g),h(_h),de(_de),le(_le)
  {
    int sz = v.size();
    n = 1;
    while(n<=sz)n<<=1;
    dat.resize(2*n-1,de);
    lazy.resize(2*n-1,le);
    for(int i=0;i<sz;++i){
      dat[i+n-1] = v[i];
    }
    for(int i=n-2;i>=0;--i){
      dat[i] = f(dat[i*2+1],dat[i*2+2]);
    }
  }

  void eval(int k,int l,int r){
    if(lazy[k]!=le){
      g(dat[k],lazy[k]);
      if(r-l>1){
        h(lazy[2*k+1],lazy[k]);
        h(lazy[2*k+2],lazy[k]);
      }
      lazy[k] = le;
    }
  }

  void update(int a,int b,T x,int k=0,int l=0,int r=-1){
    if(r<0)r=n;
    eval(k,l,r);
    if(b<=l||r<=a)return;
    if(a<=l&&r<=b){
      h(lazy[k],x);
      eval(k,l,r);
    }else{
      update(a,b,x,2*k+1,l,(r+l)/2);
      update(a,b,x,2*k+2,(r+l)/2,r);
      dat[k] = f(dat[2*k+1],dat[2*k+2]);
    }
  }

  T query(int a,int b,int k=0,int l=0,int r=-1){
    if(r<0)r=n;
    if(b<=l||r<=a)return de;
    eval(k,l,r);
    if(a<=l&&r<=b)return dat[k];
    T vl = query(a,b,2*k+1,l,(r+l)/2);
    T vr = query(a,b,2*k+2,(r+l)/2,r);
    return f(vl,vr);
  }

  T operator[](int k){
    return query(k,k+1);
  }

};

#define dt(a) decltype(a)

void RMQandRUQ(){
  int n,q;
  cin>>n>>q;
  auto f = [](auto a,auto b){return a<b?a:b;};
  auto g = [](auto& a,auto b){a=b;};
  auto h = [](auto& a,auto b){a=b;};
  int64_t INF = (1LL<<31)-1;
  lazy_segment_tree<int64_t,dt(f),dt(g),dt(h)> seg(n,f,g,h,INF,INF);
  while(q--){
    int com;
    cin>>com;
    if(com==1){
      int s,t;
      cin>>s>>t;
      cout<<(seg.query(s,t+1))<<endl;
    }else{
      int s,t,x;
      cin>>s>>t>>x;
      seg.update(s,t+1,x);
    }
  }
}

int main(){
  RMQandRUQ();
}