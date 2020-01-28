#include<bits/stdc++.h>
using namespace std;

template<class T>
struct matrix{
  size_t row,col;
  vector<vector<T>> data;
  matrix(){}
  matrix(size_t n):row(n),col(n){
    data = vector<vector<T>>(row,vector<T>(col));
  }
  matrix(size_t r,size_t c):row(r),col(c){
    data = vector<vector<T>>(row,vector<T>(col));
  }
  matrix(vector<vector<T>>const& mat):
    data(mat),row(mat.size()),col(mat[0].size()){}
  
  matrix operator + (matrix const& rhs){
    assert(this->row == rhs.row);
    assert(this->col == rhs.col);
    vector<vector<T>> result (this->row,vector<T>(this->col));
    for(size_t i=0;i<this->row;++i)
      for(size_t j=0;j<this->col;++j)
        result[i][j] += rhs.data[i][j];
    return result;
  }

  matrix operator * (matrix const& rhs){
    assert(this->row == rhs.col);
    assert(this->col == rhs.row);
    vector<vector<T>> result (this->row,vector<T>(rhs.col));
    for(size_t i=0;i<this->row;++i)
      for(size_t j=0;j<rhs.col;++j)
        for(size_t k=0;k<this->col;++k)
          result[i][j] += this->data[i][k]*rhs.data[k][j];
    return result;
  }

  matrix &operator += (matrix const& rhs){
    assert(this->row == rhs.row);
    assert(this->col == rhs.col);
    for(size_t i=0;i<this->row;++i)
      for(size_t j=0;j<this->col;++j)
        this->data[i][j] += rhs.data[i][j];
    return *this;
  }

  matrix &operator *= (matrix const& rhs){
    assert(this->row == rhs.col);
    assert(this->col == rhs.row);
    vector<vector<T>> result (this->row,vector<T>(rhs.col));
    for(size_t i=0;i<this->row;++i)
      for(size_t j=0;j<rhs.col;++j)
        for(size_t k=0;k<this->col;++k)
          result[i][j] += this->data[i][k]*rhs.data[k][j];
    this->col = rhs.col;
    this->data = result;
    return *this;
  }

  vector<T>& operator [](size_t k){
    assert(k<row);
    return this->data[k];
  }
  friend ostream& operator << (ostream& os,matrix const& mat){
    for(size_t i=0;i<mat.row;++i){
      for(size_t j=0;j<mat.col;++j){
        os << mat.data[i][j] << (j+1<mat.col?", ":(i+1<mat.row?"\n":""));
      }
    }
    return os;
  }
  friend istream &operator >> (istream& is,matrix& mat){
    for(size_t i=0;i<mat.row;++i)
      for(size_t j=0;j<mat.col;++j)
        is >> mat.data[i][j];
    return is;
  }
};

signed main(){

  int n,m;
  cin>>n>>m;
  matrix<int> a(n,m),b(m,n);
  cin>>a>>b;
  cout<<(a*b)<<endl;

}