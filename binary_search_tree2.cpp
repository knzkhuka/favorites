#include<iostream>
#include<limits>

#define rep(i,n) for(int i=0;i<int(n);++i)

using std::cout;
using std::endl;

int in(){
  int x;scanf("%d",&x);return x;
}

template<class T>
struct bst{

  template<class U>
  struct node{
    U val;
    node<U>* par;
    node<U>* lef;
    node<U>* rig;
    node():par(nullptr),lef(nullptr),rig(nullptr){}
    node(U v):val(v),par(nullptr),lef(nullptr),rig(nullptr){}
  };

  node<T>* root;
  size_t sz;

  bst(){
    root = new node<T>(std::numeric_limits<T>::max());
    sz = 0;
  }
  bool empty(){
    return sz==0;
  }
  size_t size(){
    return sz;
  }

  bool insert(T v){
    auto tmp = new node<T>(v);
    auto cur = root;
    while(1){
      if(tmp->val == cur->val){
        return false;
      }
      else if(tmp->val < cur->val){
        if(cur->lef == nullptr){
          cur->lef = tmp;
          tmp->par = cur;
          return true;
        }
        cur = cur->lef;
      }
      else {
        if(cur->rig == nullptr){
          cur->rig = tmp;
          tmp->par = cur;
          return true;
        }
        cur = cur->rig;
      }
    }
  }
  bool find(T v){
    auto tmp = root;
    while(tmp!=nullptr){
      if(v == tmp->val){
        return true;
      }
      if(v < tmp->val){
        tmp = tmp->lef;
      }else{
        tmp = tmp->rig;
      }
    }
    return false;
  }
  bool erase(T v){
    auto tmp = root;
    auto max_node = [](node<T>* cur){
      while(cur->rig!=nullptr){
        cur = cur->rig;
      }
      return cur;
    };
    while(1){
      if(tmp==nullptr){
        return false;
      }
      else if(v == tmp->val){
        if(tmp->lef==nullptr&&tmp->rig==nullptr){
          if(tmp->par->val < tmp->val){
            tmp->par->rig = nullptr;
            delete tmp;
            return true;
          }else{
            tmp->par->lef = nullptr;
            delete tmp;
            return true;
          }
        }
        else if(tmp->lef==nullptr){
          if(tmp->par->val < tmp->val){
            tmp->par->rig = tmp->rig;
            tmp->rig->par = tmp->par;
            delete tmp;
            return true;
          }else{
            tmp->par->lef = tmp->rig;
            tmp->rig->par = tmp->par;
            delete tmp;
            return true;
          }
        }
        else if(tmp->rig==nullptr){
          if(tmp->par->val < tmp->val){
            tmp->par->rig = tmp->lef;
            tmp->lef->par = tmp->par;
            delete tmp;
            return true;
          }else{
            tmp->par->lef = tmp->lef;
            tmp->lef->par = tmp->par;
            delete tmp;
            return true;
          }
        }
        auto n = max_node(tmp->lef);
        n->par->rig = nullptr;
        n->par = tmp->par;
        n->rig = tmp->rig;
        n->lef = tmp->lef;
        tmp->rig->par = n;
        tmp->lef->par = n;
        tmp->par->lef = n;
        delete tmp;
        return true;
      }
      else if(v < tmp->val){
        tmp = tmp->lef;
      }
      else if(v > tmp->val){
        tmp = tmp->rig;
      }
    }
  }

  template<class F>
  void dfs(F& f,node<T>* cur){
    if(cur==nullptr)return ;
    dfs(f,cur->lef);
    f(cur);
    dfs(f,cur->rig);
  }
  void dump(){
    auto out = [](node<T>* cur){cout<<cur->val<<" ";};
    dfs<decltype(out)>(out,root->lef);
    cout<<endl;
  }

};

int main(){

  bst<int> a;

  int n = in();
  rep(i,n){
    a.insert(in());
  }
  a.dump();

  int m = in();
  rep(i,m){
    a.erase(in());
    a.dump();
  }
  

}