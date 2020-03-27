#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::endl;

template<class T>
struct heap{
  std::vector<T> data;
  size_t sz;
  constexpr inline bool cmp(T const& lhs,T const& rhs)const noexcept{
    // max := <
    // min := >
    return lhs < rhs;
  }
  heap():data(1){}
  heap(std::vector<T> const& v){
    int n = v.size();
    data.resize(n+1);
    sz = n;
    for(int i=0;i<n;++i){
      data[i+1] = v[i];
    }
    for(int i=sz/2;i>0;--i){
      heapify(i);
    }
  }
  bool empty()const{
    return sz==0;
  }
  size_t size()const{
    return sz;
  }
  void heapify(int k){
    int l = k<<1;
    int r = k<<1|1;
    int key = k;
    if(l<=sz && cmp(data[k],data[l]))key=l;
    if(r<=sz && cmp(data[key],data[r]))key=r;
    if(key!=k){
      std::swap(data[k],data[key]);
      heapify(key);
    }
  }
  void pop(){
    data[1] = data.back();
    data.pop_back();
    heapify(1);
    sz--;
  }
  void push(T x){
    data.emplace_back(x);
    int pos = ++sz;
    int par = pos>>1;
    while(pos>1 && cmp(data[par],data[pos])){
      std::swap(data[pos],data[par]);
      pos = par;
      par = pos>>1;
    }
  }
  T top()const{
    return data[1];
  }
  void dump(){
    int a=1,b=0;
    for(int i=1;i<=sz;++i){
      cout<<data[i];
      b++;
      if(a==b){
        a<<=1,b=0;
        cout<<",";
      }else{
        cout<<" ";
      }
    }
    cout<<endl;
  }
};

// https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/2/ITP2_2_C

signed main(){

  int n,q;
  cin>>n>>q;
  std::vector<heap<int>> ques(n);
  while(q--){
    int c;cin>>c;
    if(c==0){
      int t,x;cin>>t>>x;
      ques[t].push(x);
    }
    else if(c==1){
      int t;cin>>t;
      if(ques[t].size())cout<<ques[t].top()<<endl;
    }
    else {
      int t;cin>>t;
      if(ques[t].size())ques[t].pop();
    }
  }

}