#include<bits/stdc++.h>
using namespace std;

template<int64_t MOD>
struct mod_int{
  int64_t val;
  constexpr mod_int():val(0){}
  constexpr mod_int(int64_t x)noexcept:val(x>=0?x%MOD:(MOD-(-x)%MOD)%MOD){}
  constexpr int64_t value()const noexcept{return val;}
  constexpr int64_t get_MOD()const noexcept{return MOD;}
  constexpr mod_int operator+(mod_int const& rhs){
    return mod_int(*this)+=rhs;
  }
  constexpr mod_int operator-(mod_int const& rhs){
    return mod_int(*this)-=rhs;
  }
  constexpr mod_int operator*(mod_int const& rhs){
    return mod_int(*this)*=rhs;
  }
  constexpr mod_int operator/(mod_int const& rhs){
    return mod_int(*this)/=rhs;
  }
  constexpr mod_int &operator+=(mod_int const& rhs)noexcept{
    val += rhs.val;
    if(val>=MOD)val-=MOD;
    return *this;
  }
  constexpr mod_int &operator-=(mod_int const& rhs)noexcept{
    if(val<rhs.val)val+=MOD;
    val-=rhs.val;
    return *this;
  }
  constexpr mod_int &operator*=(mod_int const& rhs)noexcept{
    (val*=rhs.val)%=MOD;
    return *this;
  }
  constexpr mod_int &operator/=(mod_int rhs)noexcept{
    *this*=rhs.inverse();
    return *this;
  }
  constexpr bool operator==(mod_int const& rhs)const{
    return val==rhs.val;
  }
  constexpr bool operator!=(mod_int const& rhs)const{
    return !(val==rhs.val);
  }
  constexpr bool operator<(mod_int const& rhs)const{
    return val<rhs.val;
  }
  constexpr bool operator>(mod_int const& rhs)const{
    return val>rhs.val;
  }
  constexpr bool operator<=(mod_int const& rhs)const{
    return !(val>rhs.val);
  }
  constexpr bool operator>=(mod_int const& rhs)const{
    return !(val<rhs.val);
  }
  constexpr friend std::ostream &operator<<(std::ostream& os, mod_int const& mi){
    return os<<mi.val;
  }
  constexpr friend std::istream &operator>>(std::istream& is, mod_int & mi){
    int64_t t;is>>t;
    mi = mod_int<MOD>(t);
    return is;
  }
  constexpr mod_int inverse(){
    int64_t a=val,b=MOD,u=1,v=0,t=0;
    while(b>0){
      t=a/b;
      std::swap(a-=t*b,b);
      std::swap(u-=t*v,v);
    }
    return mod_int(u);
  }
  constexpr mod_int mpow(int64_t n)const{
    mod_int res(1),e(*this);
    while(n){
      if(n&1)res*=e;
      e*=e;
      n>>=1;
    }
    return res;
  }
};
using mint = mod_int<1000000007>;
mint mpow(int64_t x,int64_t n){
  mint res(1),e(x);
  while(n){
    if(n&1)res*=e;
    e*=e;
    n>>=1;
  }
  return res;
}

struct combination{
  using i64 = int64_t;
  static constexpr i64 COM_MAX = 2e6;
  static constexpr i64 MOD = 1e9+7;
  vector<i64> fac,inv,finv;
  combination(){
    fac.resize(COM_MAX);
    inv.resize(COM_MAX);
    finv.resize(COM_MAX);
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    for(int i=2;i<COM_MAX;++i){
      fac[i]=fac[i-1]*i%MOD;
      inv[i]=MOD-inv[MOD%i]*(MOD/i)%MOD;
      finv[i]=finv[i-1]*inv[i]%MOD;
    }
  }
  template<class T>
  mint nCk(T n,T k){
    if(n<k)return 0;
    if(n<0||k<0)return 0;
    if(n>=COM_MAX){
      mint res1 = mint(1);
      mint res2 = mint(fac[k]);
      for(int i=1;i<=k;++i){
        res1 *= n-(i-1);
      }
      return res1/res2;
    }
    return mint(fac[n]*(finv[k]*finv[n-k]%MOD));
  }
  template<class T>
  mint nHk(T n,T k){
    return nCk(n+k-1,n-1);
  }
  template<class T>
  mint operator()(T n,T k){
    return nCk(n,k);
  }
};

signed main(){

  int n,k;
  cin>>n>>k;

  assert(!(n==3));

  combination com;

  mint ans{0};
  int mx = min(n-1,k);
  for(int i=0;i<=mx;++i){
    ans += com(n,i)*com.nHk(n-i,i);
  }
  cout<<(ans)<<endl;

}