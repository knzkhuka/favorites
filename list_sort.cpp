#include<iostream>

using std::cout;
using std::endl;

int in(){
  int x;
  scanf("%d",&x);
  return x;
}

template<class T>
class mylist{
private:
  template<class U>
  struct node{
    U value;
    node<U>* prv;
    node<U>* nxt;
  };
  node<T>* head;
  node<T>* tail;
  size_t sz;

  node<T>* merge(node<T>* s,node<T>* t){
    auto h = (node<T>*)malloc(sizeof(node<T>));
    auto tmp = h;
    while(s!=nullptr&&t!=nullptr){
      if(s->value <= t->value){
        tmp->nxt = s;
        s->prv = tmp;
        s = s->nxt;
      }else{
        tmp->nxt = t;
        t->prv = tmp;
        t = t->nxt;
      }
      tmp = tmp->nxt;
    }
    if(s==nullptr){
      tmp->nxt = t;
      t->prv = tmp;
    }else{
      tmp->nxt = s;
      s->prv =tmp;
    }
    return h->nxt;
  }
  node<T>* merge_sort(node<T>* s){
    if(s==nullptr||s->nxt==nullptr){
      return s;
    }
    auto a = s;
    auto b = s->nxt;
    auto p = s->prv;
    if(b!=nullptr){
      b = b->nxt;
    }
    while(b!=nullptr){
      a = a->nxt;
      b = b->nxt;
      if(b!=nullptr){
        b = b->nxt;
      }
    }
    auto t = a->nxt;
    a->nxt = nullptr;
    t->prv = nullptr;
    s = merge_sort(s);
    t = merge_sort(t);
    return merge(s,t);
  }

public:
  mylist(){
    head = (node<T>*)malloc(sizeof(node<T>));
    tail = (node<T>*)malloc(sizeof(node<T>));
    head->prv = nullptr;
    head->nxt = nullptr;
    sz = 0;
  }
  bool empty(){
    return sz==0;
  }
  size_t size(){
    return sz;
  }
  void push_back(T v){
    if(empty()){
      tail->value = v;
      tail->prv = head;
      tail->nxt = nullptr;
      head->nxt = tail;
      sz++;
      return;
    }
    auto tmp = (node<T>*)malloc(sizeof(node<T>));
    tmp->value = v;
    tail->nxt = tmp;
    tmp->prv = tail;
    tail = tmp;
    sz++;
  }
  void push_front(T v){
    if(empty()){
      tail->value = v;
      tail->prv = head;
      tail->nxt = nullptr;
      head->nxt = tail;
      sz++;
      return;
    }
    auto tmp = (node<T>*)malloc(sizeof(node<T>));
    tmp->value = v;
    head->nxt->prv = tmp;
    tmp->nxt = head->nxt;
    head->nxt = tmp;
    tmp->prv = head;
    sz++;
  }
  void pop_back(){
    if(empty()){
      return;
    }
    sz--;
    tail = tail->prv;
    free(tail->nxt);
    tail->nxt = nullptr;
  }
  void pop_front(){
    if(empty()){
      return;
    }
    sz--;
    auto tmp = head->nxt;
    head->nxt = tmp->nxt;
    if(tmp->nxt==nullptr){
      free(tmp);
      return;
    }
    tmp->nxt->prv = head;
    free(tmp);
  }
  void dump(){
    auto tmp = head->nxt;
    while(tmp!=nullptr){
      cout<<tmp->value<<" ";
      tmp = tmp->nxt;
    }
    cout<<endl;
  }
  void rev_dump(){
    auto tmp = tail;
    while(1){
      cout<<tmp->value<<" ";
      if(tmp==head->nxt)break;
      tmp = tmp->prv;
    }
    cout<<endl;
  }
  void sort(){
    head->nxt = merge_sort(head->nxt);
    auto tmp = head->nxt;
    while(tmp->nxt!=nullptr){
      tmp->nxt->prv = tmp;
      tmp = tmp->nxt;
    }
    tail = tmp;
  }
};

int main(){



}