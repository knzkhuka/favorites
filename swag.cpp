#include<bits/stdc++.h>
using namespace std;

template<class T,class F>
struct SWAG{

  struct node{
    T val;
    T acm;
    node(){}
    node(T v,T a):val(v),acm(a){}
  };
  
  stack<node> front_stack,back_stack;
  F f;
  
  SWAG(F f):f(f){}
  
  size_t size()const{
    return front_stack.size() + back_stack.size();
  }
  bool empty()const{
    return front_stack.empty() && back_stack.empty();
  }

  T fold(){
    assert(!empty());
    if(front_stack.empty()){
      return back_stack.top().acm;
    }
    else if(back_stack.empty()){
      return front_stack.top().acm;
    }
    else{
      return f(front_stack.top().acm,back_stack.top().acm);
    }
  }

  void push(T const& v){
    if(back_stack.empty()){
      back_stack.emplace(v,v);
    }
    else{
      T cal{f(back_stack.top().acm,v)};
      back_stack.emplace(v,cal);
    }
  }

  void pop(){
    assert(!empty());
    if(front_stack.empty()){
      front_stack.emplace(back_stack.top().val,back_stack.top().val);
      back_stack.pop();
      while(!back_stack.empty()){
        T cal{f(front_stack.top().acm,back_stack.top().val)};
        front_stack.emplace(back_stack.top().val,cal);
        back_stack.pop();
      }
    }
    front_stack.pop();
  }

};

signed main(){

  int n,k;
  cin>>n>>k;
  vector<int> a(n);
  for(auto&ai:a)cin>>ai;

  auto f= [](auto a,auto b){return a<=b?a:b;};
  SWAG<int,decltype(f)> s(f);

  for(int i=0;i<k;++i)s.push(a[i]);
  for(int i=k;i<n;++i){
    cout<<s.fold()<<" ";
    s.push(a[i]);
    s.pop();
  }
  cout<<s.fold()<<endl;

}