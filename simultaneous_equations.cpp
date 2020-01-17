#include<bits/stdc++.h>
using namespace std;

int select(vector<vector<double>> const& mat,size_t j){
  size_t n = mat.size();
  for(size_t i=j;i<n;++i){
    if(mat[i][j]!=0)return i;
  }
  return -1;
}

void calc(vector<vector<double>>& mat,vector<double>& b,int base){
  size_t n = mat.size();
  double c = mat[base][base];
  for(size_t i=base;i<n;++i){
    mat[base][i] /= c;
  }
  b[base] /= c;
  for(size_t i=0;i<n;++i){
    if(i==base)continue;
    double num = mat[i][base];
    for(size_t j=0;j<n;++j){
      mat[i][j] -= mat[base][j]*num;
    }
    b[i] -= b[base]*num;
  }
}

vector<double> solve(vector<vector<double>> mat,vector<double> b){
  size_t n = mat.size();
  for(size_t i=0;i<n;++i){
    int base = select(mat,i);
    if(base==-1)continue;
    swap(mat[i],mat[base]);
    swap(b[i],b[base]);
    calc(mat,b,i);
  }
  return b;
}

signed main(){

  int n = 4;
  vector<vector<double>> mat = {
    {2,4,2,2},
    {4,10,3,3},
    {2,6,1,1},
    {3,7,1,4}
  };
  vector<double> b = {8,17,9,11};

  auto res = solve(mat,b);
  for(auto r:res)cout<<r<<" ";cout<<endl;
  

}