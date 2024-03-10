#include<bits/stdc++.h>
using namespace std;

int main() {
	stack<int> s;
	int n,x,sp,y,ans=0,over=0;
	cin>>n;
	while(n--) {
		cin>>x;
		if(x==1) cin>>sp;
		else if(x==2) ans+=over,over=0;
		else if(x==3) cin>>y,s.push(y);
		else if(x==4) over=0;
		else if(x==5)
			while(!s.empty()) s.pop();
		else over++;
		while(!s.empty()&&s.top()<sp) s.pop(),ans++;
	}
	cout<<ans;
	return 0;
}
