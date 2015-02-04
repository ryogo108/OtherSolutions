#include<iostream>
#include<set>
#include<complex>
#include<vector>

// 許容する誤差
#define EPS (1e-10)
// 2つのスカラーが等しいかどうか
#define EQ(a,b) (abs((a)-(b)) < EPS)
// 2つのベクトルが等しいかどうか
#define EQV(a,b) ( EQ((a).real(), (b).real()) && EQ((a).imag(), (b).imag()) )

using namespace std;
namespace std{
    template<class T> bool operator<(const complex<T> &a, const complex<T> &b){
        return a.real() == b.real() ? a.imag() < b.imag() : a.real() < b.real();
    }
};
typedef complex<double>P;

struct line{
	line(){};
	line(P a1,P a2){
		p1=a1;
		p2=a2;
	}
	P p1,p2;
};
double dot(P a, P b) {
  return (a.real() * b.real() + a.imag() * b.imag());
}
double cross(P a, P b) {
  return (a.real() * b.imag() - a.imag() * b.real());
}
int is_intersected_l(P a1, P a2, P b1, P b2) {
  return !EQ( cross(a1-a2, b1-b2), 0.0 );
}
P intersection_l(P a1, P a2, P b1, P b2) {
  P a = a2 - a1; P b = b2 - b1;
  return a1 + a * cross(b, b1-a1) / cross(b, a);
}
int is_point_on_line(P a, P b, P c) {
  return EQ( cross(b-a, c-a), 0.0 );
}
int is_eq_line(line l1,line l2){
	return is_point_on_line(l1.p1,l1.p2,l2.p1) && is_point_on_line(l1.p1,l1.p2,l2.p2);
}
vector<line> table;

int che(line l){
	set<P>rem;
	vector<line>::iterator itr=table.begin();
	for(;itr!=table.end();itr++){
		line tmp=*itr;
		if(is_intersected_l(l.p1,l.p2,tmp.p1,tmp.p2)){
			rem.insert(intersection_l(l.p1,l.p2,tmp.p1,tmp.p2));
		}
		else if(is_eq_line(l,tmp))return 0;
	}
	table.push_back(l);
	return rem.size()+1;
}
int main(){
	int n;
	cin>>n;
	int ans=1;
	for(int i=0;i<n;i++){
		P p1,p2;
		cin>>p1.real()>>p1.imag();
		cin>>p2.real()>>p2.imag();
		ans+=che(line(p1,p2));
	}
	cout<<ans<<endl;
}
