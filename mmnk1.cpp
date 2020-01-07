#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll,ll>;
constexpr ll MOD = (1e9+7);
template<class T>vector<T> vec(size_t a){return vector<T>(a);}
template<class T, class... Ts>auto vec(size_t a, Ts... ts){return vector<decltype(vec<T>(ts...))>(a, vec<T>(ts...));}

template<ll MOD=ll(1e9+7)>
ll mod_pow(ll n,ll p){
  ll ans=1LL;
  while(p){
    if(p&1)ans*=n;
    n*=n;
    p>>=1;
    ans%=MOD;
    n%=MOD;
  }
  return ans;
}


int main(){
  int n,b,k;
  cin>>n>>b>>k;
  ll ans = mod_pow(b,k);
  ans -= mod_pow(b-1,k);
  cout<<(ans)<<endl;
}

int _main(){

  // n桁,b進数,kが現れる
  int n,b,k;
  cin>>n>>b>>k;

  auto dp = vec<ll>(n+1,b+1);
  //dp[i][j] := i桁目まで見てkがj個ある組合せの数
  dp[1][0]=b-1;
  dp[1][1]=1;
  for(int i=2;i<=n;++i){
    dp[i][0] = dp[i-1][0]*(b-1)%MOD;
    for(int j=1;j<b;++j){
      dp[i][j] += dp[i-1][j-1]%MOD;
      dp[i][j] += dp[i-1][j]*(b-1)%MOD;
    }
  }
  ll ans =0;
  for(int i=1;i<=k;++i)(ans+=dp[n][i])%=MOD;
  cout<<(ans)<<endl;

}