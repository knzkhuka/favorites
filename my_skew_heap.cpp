#include<bits/stdc++.h>

// min,add heap
template<class T>
struct skew_heap{
  struct node{
    T val;
    T lazy;
    node* left;
    node* right;
    node():left(nullptr),right(nullptr){}
    node(T& v):val(v),lazy(0),left(nullptr),right(nullptr){}
  };
  node* root;
  size_t sz;
  skew_heap():root(nullptr),sz(0){}
  skew_heap(T& v){
    root = new node(v);
    sz = 1;
  }
private:
  void lazy(node* n){
    n->val += n->lazy;
    if(n->left)n->left->lazy += n->lazy;
    if(n->right)n->right->lazy += n->lazy;
    n->lazy = 0;
  }
  node* meld(node* a,node* b){
    if(!a)return b;
    if(!b)return a;
    if( a->val+a->lazy > b->val+b->lazy )std::swap(a,b);
    lazy(a);
    a->right = meld(a->right,b);
    std::swap(a->left,a->right);
    return a;
  }
public:
  T top(){
    assert(!empty());
    lazy(this->root);
    return root->val;
  }
  void pop(){
    assert(!empty());
    free(root);
    root = meld(root->right,root->left);
    sz--;
  }
  void push(T v){
    skew_heap<T> tmp(v);
    this->meld(tmp);
  }
  void add(T v){
    this->root->lazy += v;
  }
  void meld(skew_heap& h){
    this->root = meld(this->root,h.root);
    this->sz += h.sz;
    h.sz = 0;
    h.root = nullptr;
  }
  bool empty()const{
    return sz==0;
  }
  size_t size()const{
    return this->sz;
  }
};

using heap = skew_heap<int>;

signed main(){

  int n;
  std::cin>>n;
  heap h;
  for(int _=0;_<n;++_){
    int a;
    std::cin>>a;
    h.push(a);
  }

  int m;
  std::cin>>m;
  heap hh;
  for(int _=0;_<m;++_){
    int a;
    std::cin>>a;
    hh.push(a);
  }

  h.meld(hh);

  while(!h.empty()){
    std::cout<< h.top() <<" ";
    h.pop();
  }
  std::cout<<std::endl;

}