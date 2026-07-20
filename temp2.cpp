// #include<bits/stdc++.h>
// using namespace std;

// int main(){

//     int t;
//     cin>>t;
//     while(t--){

//         int n,k;
//         cin>>n>>k;

//         vector<int>vec(n);
//         for(int i=0; i<n; i++){
//             cin>>vec[i];
//         }

//         //check if array is sorted.
//         bool flag = true;
//         for(int i=0; i<n-1; i++){

//             if(vec[i] > vec[i+1]){
//                 flag=false;
//                 break;
//             }
//         }

//         if(flag || (!flag && k>1))
//             cout<<"YES"<<endl;
//         else
//             cout<<"NO"<<endl;
//     }
// }

#include <bits/stdc++.h>
using namespace std;

int main() {

	long long n,items;
	cin>>n>>items;
	   
	vector<long long>temp;
	
	for(long long i=0; i<n; i++){
	    long long a;
	    cin>>a;
	    temp.push_back(a);
	}
    
    long long currItems=0;
    
    
    long long maxTime = 0;
    for(long long i=0; i<n; i++){
        maxTime = max(maxTime,temp[i]);
    }
    
    for(long long i=0; i<n; i++){
        currItems += (maxTime / temp[i]);
    }
    // long long mod = pow(10,9)+7;
    long long ans = ((items * maxTime));
    long long req = ((ans)/(1.0*currItems));
    
    cout<<ans<<endl;
    cout<<req<<endl;
    
}















