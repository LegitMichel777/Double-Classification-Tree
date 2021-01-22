#include "lm7lib.hpp"
using namespace std;
typedef long long ll;
void nein(char &in) {
    system("stty raw");
    in = getchar();
    system("stty cooked");
}
void nein(string &in) {
    system("stty raw");
    cin>>in;
    system("stty cooked");
}
void nein(ll &in) {
    system("stty raw");
    cin>>in;
    system("stty cooked");
}
bool isprime(ll x) {
    for (ll i=2;i*i<=x;i++) {
        if (x%i==0) {
            return false;
        }
    }
    return true;
}
void clearfile(string path) {
    ofstream out(path);
    out.close();
}
void mswait(ll ms) {
    auto c=chrono::high_resolution_clock::now();
    while (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - c).count()<=ms);
}
string add(string in,string in2) {
    //Make adding process more efficient by removing additional vectors
    //Split addition into parts to be more efficient
    vector <ll> a;
    vector <ll> b;
    bool dec = false;
    if (in.find(".") != string::npos||in2.find(".") != string::npos) {
        dec = true;
    }
    ll ax = in.length() - 1,bx = in2.length() - 1;
    if (dec){
        if (in.find(".") != string::npos) {
            ax = in.find(".") - 1;
        }
        if (in2.find(".") != string::npos) {
            bx = in2.find(".") - 1;
        }
    }
    for (ll times = ax;times>=0;times--) {
        a.push_back(in[times] - '0');
    }
    for (ll times = bx;times>=0;times--) {
        b.push_back(in2[times] - '0');
    }
    ll carry = 0;
    vector <ll> adec;
    vector <ll> bdec;
    vector<ll> addec;
    if (dec) {
        for (ll times = ax + 2;times<in.length();times++) {
            adec.push_back(in[times] - '0');
        }
        for (ll times = bx + 2;times<in2.length();times++) {
            bdec.push_back(in2[times] - '0');
        }
        for (ll times = max(adec.size(),bdec.size()) - 1;times>=0;times--) {
            if (times < adec.size()&&times<bdec.size()) {
                if (adec[times] + bdec[times] + carry <10) {
                    addec.push_back(adec[times] + bdec[times] + carry);
                    carry = 0;
                } else {
                    addec.push_back(adec[times] + bdec[times] + carry - 10);
                    carry = 1;
                }
            } else if (times>=adec.size()) {
                addec.push_back(bdec[times]);
            } else {
                addec.push_back(adec[times]);
            }
        }
    };
    vector<ll>addx;
    ll times = 0;
    for (;times < max(a.size(),b.size());times++) {
        if (times<=a.size() - 1 && times<=b.size() - 1) {
            if (a[times] + b[times] + carry < 10) {
                addx.push_back(a[times] + b[times] + carry);
                carry = 0;
            } else {
                addx.push_back(a[times] + b[times] - 10 + carry);
                carry = 1;
            }
        } else if (times >a.size() - 1) {
            if (b[times] + carry <10) {
                addx.push_back(b[times] + carry);
                carry = 0;
            } else {
                addx.push_back(b[times] + carry - 10);
                carry = 1;
            }
        } else {
            if (a[times] + carry < 10) {
                addx.push_back(a[times] + carry);
                carry = 0;
            } else {
                addx.push_back(a[times] +carry - 10);
                carry = 1;
            }
        }
    }
    string result;
    if (carry == 1) {
        result += '1';
    }
    for (ll times = addx.size() - 1;times>=0;times--) {
        result += to_string(addx[times]);
    }
    if (dec) {
        result += '.';
        for (ll times = addec.size() - 1;times>=0;times--) {
            result += to_string(addec[times]);
        }
    }
    return result;
}
string multiply(string in,string in2) {
    //Add decimal support
    vector <ll> a;
    vector <ll> b;
    bool negative = false;
    bool dec=false;
    ll ax = in.length() - 1,bx = in2.length() - 1;
    ll negativep = 0;
    for (ll times = ax;times>=0;times--) {
        if (in[times] == '-') {
            negative = true;
            ax--;
        } else if (in[times] == '.'){
            negativep += times;
            ax--;
            dec = true;
        } else {
            a.push_back(in[times] - '0');
        }
    }
    for (ll times = bx;times>=0;times--) {
        if (in2[times] == '-') {
            negative = 1-negative;
            bx--;
        } else if (in2[times] == '.') {
            negativep += times;
            bx--;
            dec=true;
        } else {
            b.push_back(in2[times] - '0');
        }
    }
    string tmp3 = "0";
    if (in.length() == 1) {
        for (ll times = 0;times < in2.length();times++) {
            ll tmp = a[0] * b[times];
            string tmp2 = to_string(tmp);
            for (ll times2 = 0;times2 < times;times2++) {
                tmp2 += '0';
            }
            tmp3 = add(tmp3,tmp2);
        }
    } else {
        for (ll times = 0;times<in.length();times++) {
            string tmp = multiply(to_string(a[times]),in2);
            for (ll times2 = 0;times2<times;times2++) {
                tmp += '0';
            }
            tmp3 = add(tmp3,tmp);
        }
    }
    if (negative) {
        tmp3 = '-'+tmp3;
    }
    if (!dec) {
        return tmp3;
    }
    bool filterdone;
    for (ll i=0;i<tmp3.size();i++) {
        if (tmp3[i]!='0'||tmp3[i]!='.'||tmp3[i]!='-') {
            stringstream ss;
            
        }
    }
    return tmp3;
}
string factorial(ll x) {
    bool negative = false;
    if (x<0) {
        negative = true;
    }
    x = abs(x);
    string answer = "1";
    for (ll times = 1;times<x + 1;times++) {
        answer = multiply(answer,to_string(times));
    }
    if (negative) {
        return '-'+ answer;
    } else {
        return answer;
    }
}
string power(ll x,unsigned long long y) {
    bool negative = false;
    if (x<0 &&y%2 == 1) {
        negative = true;
    }
    x = abs(x);
    string answer = "1";
    string muply = to_string(x);
    for (ll times = 0;times<y;times++) {
        answer = multiply(muply,answer);
    }
    if (negative) {
        return '-' + answer;
    }
    return answer;
}
unsigned long long uhash(string x,ll base) {
    if (base<96) {
        return 0;
    }
    unsigned long long rt;
    rt = x[0];
    for (ll i=1;i<x.length();i++) {
        rt*=base;
        rt+=x[i];
    }
    return rt;
}
string uinfhash(string x,ll base) {
    if (base<96) {
        return 0;
    }
    string rt;
    rt = to_string(int(x[0]));
    for (ll i=1;i<x.length();i++) {
        rt = multiply(rt,to_string(base));
        rt = add(rt,to_string(int(x[i])));
    }
    return rt;
}
