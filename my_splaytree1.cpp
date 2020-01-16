#include<bits/stdc++.h>
using namespace std;

template<class T>
struct node{
  T val;
  T acml;
  size_t sz;
  node<T> *parent,*left,*right;
  node():sz(1),parent(nullptr),left(nullptr),right(nullptr){}
  node(T const& v):val(v),acml(v),sz(1),parent(nullptr),left(nullptr),right(nullptr){}
  T op(T const& lhs,T const& rhs){
    return lhs+rhs;
  }
  int state(){
    if(this->parent==nullptr)return 0;
    if(this->parent->left==this)return 1;
    if(this->parent->right==this)return 2;
    return 0;
  }
  void rotate(){
    if(this->parent==nullptr)return;
    node<T> *p,*pp,*c;
    p = this->parent;
    pp = p->parent;
    if(p->left==this){
      c = this->right;
      this->right = p;
      p->left = c;
    }
    if(p->right==this){
      c = this->left;
      this->left = p;
      p->right = c;
    }
    if(pp && pp->left==p)pp->left = this;
    if(pp && pp->right==p)pp->right= this;
    this->parent = pp;
    p->parent = this;
    if(c)c->parent = p;
    p->update();
    this->update();
  }
  void splay(){
    while(this->parent!=nullptr){
      if(this->parent->parent==nullptr){
        this->rotate();
      }
      else if(this->state()==this->parent->state()){
        this->parent->rotate();
        this->rotate();
      }
      else{
        this->rotate();
        this->rotate();
      }
    }
  }
  void update(){
    this->sz = 1;
    this->acml = this->val;
    if(this->left){
      this->sz += this->left->sz;
      this->acml = op(this->acml,this->left->acml);
    }
    if(this->right){
      this->sz += this->right->sz;
      this->acml = op(this->acml,this->right->acml);
    }
  }
};

template<class T>
struct splay_tree{
  size_t sz;
  node<T>* root;
  splay_tree():sz(0){}
  void dump_dfs(node<T>* cur){
    if(cur==nullptr)return;
    cout<<"l,c,r : ";
    if(cur->left&&cur->right)cout<<cur->left->val<<" "<<cur->val<<" "<<cur->right->val<<endl;
    else if(cur->left)cout<<cur->left->val<<" "<<cur->val<<" "<<"_"<<endl;
    else if(cur->right)cout<<"_"<<" "<<cur->val<<" "<<cur->right->val<<endl;
    else cout<<"_"<<" "<<cur->val<<" "<<"_"<<endl;
    dump_dfs(cur->left);
    dump_dfs(cur->right);
  }
  void dump_dfs2(node<T>* cur){
    if(!cur)return;
    cout<<cur->val<<" "<<cur->sz<<endl;
    dump_dfs2(cur->left);
    dump_dfs2(cur->right);
  }
  void dump(){
    dump_dfs(root);
    cout<<endl;
  }
  void dump_sz(){
    dump_dfs2(root);
    cout<<endl;
  }
  T fold_all(){
    return root->acml;
  }
  bool empty(){return sz==0;}
  node<T>* find_node(T const& v){
    node<T>* tmp = root;
    while(1){
      if(tmp->val==v)return tmp;
      if(tmp->val < v){
        if(tmp->right==nullptr)return tmp;
        tmp = tmp->right;
      }
      if(tmp->val > v){
        if(tmp->left==nullptr)return tmp;
        tmp = tmp->left;
      }
    }
  }
  void insert(T const& v){
    if(empty()){
      sz++;
      root = new node<T>(v);
      return;
    }
    node<T>* tmp = find_node(v);
    if(tmp->val == v)return;
    sz++;
    node<T>* add = new node<T>(v);
    if(tmp->val <= v){
      tmp->right = add;
    }
    if(tmp->val > v){
      tmp->left = add;
    }
    add->parent = tmp;
    add->splay();
    root = add;
  }
  bool erase(T const& v){
    assert(!empty());
    node<T>* tmp = find_node(v);
    tmp->splay();
    root = tmp;
    if(tmp->val != v)return false;
    sz--;
    if(root->right==nullptr&&root->left==nullptr){
      delete root;
    }
    else if(root->right==nullptr){
      root = root->left;
      delete root->parent;
      root->parent = nullptr;
    }
    else if(root->left==nullptr){
      root = root->right;
      delete root->parent;
      root->parent = nullptr;
    }
    else{
      node<T>* l = root->left;
      node<T>* c = find_node(tmp->val+1);
      c->splay();
      delete root;
      c->left = l;
      l->parent = c;
      root = c;
    }
    return true;
  }
  bool find(T const& v){
    if(empty())return false;
    node<T>* tmp = find_node(v);
    tmp->splay();
    root = tmp;
    return root->val == v;
  }
  node<T>* operator[](int k){
    assert(k < sz);
    node<T>* tmp = root;
    while(1){
      int lsz = tmp->left?tmp->left->sz:0;
      if(k<lsz){
        tmp = tmp->left;
      }
      if(k==lsz){
        tmp->splay();
        root = tmp;
        return tmp;
      }
      if(k>lsz){
        tmp = tmp->right;
        k = k-lsz-1;
      }
    }
  }
};

signed test1(){

  splay_tree<int> sp;
  int q;
  cin>>q;
  while(q--){
    int com;cin>>com;
    if(com==1){
      int x;cin>>x;
      sp.insert(x);
    }
    else if(com==2){
      int x;cin>>x;
      sp.erase(x);
    }
    else if(com==3){
      int x;cin>>x;
      cout<<(sp.find(x)?"found!":"not found")<<endl;
    }
    else if(com==4){
      int x;cin>>x;
      auto kth_node = sp[x];
      cout<<kth_node->val<<" "<<kth_node->acml<<endl;
    }
    else{
      sp.dump();
      sp.dump_sz();
    }
  }

}

void solve(){
  // https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/4/ALDS1_4_B
  int n;cin>>n;
  splay_tree<int> sp;
  while(n--){
    int x;cin>>x;
    sp.insert(x);
  }
  int q;cin>>q;
  int ans{0};
  while(q--){
    int x;cin>>x;
    ans += sp.find(x);
  }
  cout<<(ans)<<endl;
}

signed main(){
  solve();
}