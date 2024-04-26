#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
void solve(){
	int n;cin>>n;
	int ans=0;
	for(int i=1;i<=n;i++) ans+=(2*i-1)*i;
	cout<<ans<<' '<<2*n<<endl;
	for(int i=n;i>=1;i--){
		cout<<"1 "<<i<<' ';
		for(int j=1;j<=n;j++) cout<<j<<' ';cout<<endl;
		cout<<"2 "<<i<<' ';
		for(int j=1;j<=n;j++) cout<<j<<' ';cout<<endl;
	}
}
int main(){
	ios::sync_with_stdio(false);
	int _;cin>>_;
	while(_--) solve(); 
}
