#include<bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i=0;i<n;++i)

constexpr int inf = numeric_limits<int>::max();

template<class T>
struct matrix{
  size_t n;
  vector<vector<T>> data;
  T add_ide,pro_ide;
  matrix(){}
  matrix(size_t sz):n(sz){
    data = vector<vector<T>>(n,vector<T>(n));
  }
  matrix(size_t sz,T v):n(sz){
    data = vector<vector<T>>(n,vector<T>(n,v));
  }
  matrix(vector<vector<T>> const& mat):data(mat),n(mat.size()){}

  matrix operator+(matrix const& rhs){
    assert(this->n == rhs.n);
    matrix mat(rhs.size(),add_ide);
    rep(i,n)rep(j,n)mat.data[i][j]=this->data[i][j]+rhs.data[i][j];
    return mat;
  }
  matrix &operator+=(matrix const& rhs){
    assert(this->n == rhs.n);
    rep(i,n)rep(j,n)this->data[i][j] += rhs.data[i][j];
    return *this;
  }
  matrix operator*(matrix const& rhs){
    assert(this->n == rhs.n);
    matrix mat(this->n,add_ide);
    mat.add_ide = this->add_ide;
    mat.pro_ide = this->pro_ide;
    rep(i,n)rep(j,n)rep(k,n)mat.data.at(i).at(j) += (this->data.at(i).at(k)*rhs.data.at(k).at(j)*pro_ide)+add_ide;
    return mat;
  }
  matrix &operator*=(matrix const& rhs){
    *this = *this*rhs;
    return *this;
  }
  friend ostream &operator<<(ostream& os,matrix const& mat){
    rep(i,mat.n){
      rep(j,mat.n){
        os<<mat.data.at(i).at(j)<<(j+1<mat.n?" ":i+1<mat.n?"\n":"");
      }
    }
    return os;
  }
  friend istream &operator>>(istream& is,matrix& mat){
    rep(i,mat.n)rep(j,mat.n)is>>mat.data[i][j];
    return is;
  }
  vector<T> &operator[](size_t i){
    return this->data.at(i);
  }
};

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
    if(this->value == inf)return *this;
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

using myint = minplus_semiring<int>;

signed _main(){
  int n;
  cin>>n;
  matrix<int64_t> mat(n);
  mat.add_ide = 0;
  mat.pro_ide = 1;
  cin>>mat;
  cout<<endl;
  cout<<mat<<endl;
  cout<<endl;
  mat = mat*mat;
  cout<<mat<<endl;
  cout<<endl;
  mat = mat*mat;
  cout<<mat<<endl;
}

signed main(){

  int n,m;
  cin>>n>>m;
  matrix<myint> mat(n,inf);
  mat.add_ide = inf;
  mat.pro_ide = 0;
  rep(i,m){
    int a,b,c;
    cin>>a>>b>>c;
    a--;b--;
    mat[a][b] = c;
  }
  cout<<(mat)<<endl<<endl;
  cout<<(mat*mat)<<endl<<endl;
  cout<<(mat*mat*mat)<<endl;


}