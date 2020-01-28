#include<bits/stdc++.h>
using namespace std;

template<class T>
struct minplus_semiring{
  static constexpr T INF = numeric_limits<T>::max();
  T value;
  minplus_semiring(){}
  minplus_semiring(T v):value(v){}
  minplus_semiring operator + (minplus_semiring const& rhs){
    return this->value < rhs.value ? *this : rhs;
  }
  minplus_semiring operator * (minplus_semiring const& rhs){
    return minplus_semiring(this->value + rhs.value);
  }
  minplus_semiring& operator += (minplus_semiring const& rhs){
    if(this->value > rhs.value)this->value = rhs.value;
    return this;
  }
  minplus_semiring& operator *= (minplus_semiring const& rhs){
    return this->value += rhs.value;
  }
  friend ostream& operator << (ostream& os,minplus_semiring const& elm){
    return os << elm.value;
  }
  friend istream& operator >> (istream& is,minplus_semiring& elm){
    return is >> elm.value;
  }
};


signed main(){

  minplus_semiring<int> a,b;
  cin>>a>>b;
  cout<<"a+b "<<a+b<<endl;
  cout<<"a*b "<<a*b<<endl;

}