#include<bits/stdc++.h>
using namespace std;

constexpr int inf = numeric_limits<int>::max();

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
  matrix identity_element(size_t n,T add_ide,T pro_ide){
    vector<vector<T>> identity_element (n,vector<T>(n,add_ide));
    for(size_t i=0;i<n;++i){
      identity_element[i][i] = pro_ide;
    }
    matrix ide(n);
    ide.data = identity_element;
    return ide;
  }
};

template<class T>
matrix<T> mat_pow(matrix<T> mat,int n,T add_ide,T pro_ide){
  assert(mat.row == mat.col);
  matrix<T> result = mat.identity_element(mat.row,add_ide,pro_ide);
  while(n){
    if(n&1)result*=mat;
    mat = mat*mat;
    n>>=1;
  }
  return result;
}

template<class T>
struct minplus_semiring{
  static constexpr T inf = numeric_limits<T>::max();
  T value;
  minplus_semiring(){}
  minplus_semiring(T v):value(v){}
  minplus_semiring operator + (minplus_semiring const& rhs){
    return this->value < rhs.value ? *this : rhs;
  }
  minplus_semiring operator * (minplus_semiring const& rhs){
    if(this->value == this->inf)return minplus_semiring(inf);
    if(rhs.value == this->inf)return minplus_semiring(inf);
    return minplus_semiring(this->value + rhs.value);
  }
  minplus_semiring& operator += (minplus_semiring const& rhs){
    if(this->value > rhs.value)this->value = rhs.value;
    return *this;
  }
  minplus_semiring& operator *= (minplus_semiring const& rhs){
    if(rhs.value == inf)this->value = inf;
    else this->value += rhs.value;
    return *this;
  }
  friend ostream& operator << (ostream& os,minplus_semiring const& elm){
    return os << (elm.value==elm.inf?"_":to_string(elm.value));
  }
  friend istream& operator >> (istream& is,minplus_semiring& elm){
    return is >> elm.value;
  }
};
using toropical = minplus_semiring<int>;

signed main(){

  int n,m;
  cin>>n>>m;

  matrix<toropical> dist(n);
  for(int i=0;i<n;++i)for(int j=0;j<n;++j)dist[i][j]=inf;

  for(int i=0;i<m;++i){
    int a,b,c;
    cin>>a>>b>>c;
    a--;b--;
    dist[a][b] = c;
  }

  cout<<dist<<endl<<endl;
  cout<< mat_pow(dist,2,toropical(inf),toropical(0)) <<endl<<endl;
  cout<< (dist*dist) <<endl;

}