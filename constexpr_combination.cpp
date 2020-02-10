#include<bits/stdc++.h>
using namespace std;

template<size_t sz,int64_t modulo = int64_t(1e9+7)>
struct combination{
  int64_t fac[sz],finv[sz],inv[sz];
  constexpr combination():fac(),finv(),inv(){
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for(int i=2;i<sz;++i){
      fac[i] = fac[i-1]*i%modulo;
      inv[i] = modulo-inv[modulo%i]*(modulo/i)%modulo;
      finv[i] = finv[i-1]*inv[i]%modulo;
    }
  }
  constexpr int64_t operator () (int64_t n,int64_t k)const{
    if(n<k)return 0;
    if(n<0||k<0)return 0;
    return fac[n]*(finv[k]*finv[n-k]%modulo)%modulo;
  }
};

signed main(){

  constexpr combination<262144> com;
  cout<< com(2,1) <<endl;
  cout<< com(4,2) <<endl;

}