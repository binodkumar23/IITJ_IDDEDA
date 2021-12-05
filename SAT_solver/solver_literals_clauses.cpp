#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<sstream>
#include<random>
#include<string>
#include<iterator>
#include<algorithm>
#include<time.h>
#include<chrono>
#define ll long long
using namespace std;


vector<vector<int>> simplify(vector<vector<int>> v, int literal){
    vector<vector<int>> alpha;
    for(int k=0;k<v.size();k++){
        vector<int> ha;
        for(int l=0;l<v[k].size();l++){
            if(v[k][l]!=(-(literal))){
                ha.push_back(v[k][l]);
            }
        }
        alpha.push_back(ha);
    }
    ll i=0;
    while(i<alpha.size()){
        for(int j=0;j<alpha[i].size();j++){
            if(alpha[i][j]==literal){
                alpha.erase(alpha.begin()+i);
                break;
            }
        }
        i++;
    }
    return alpha;
}

vector<vector<int>> encode(vector<vector<string>> v){
    vector<vector<int>> encoded;
    for(int i = 0; i<v.size();i++){
        vector<int> variables;
        for(int j = 0;j<v[i].size();j++){
            if(v[i][j][0]!='!'){
                variables.push_back(stoi(v[i][j]));
            }
            else{
                variables.push_back(-(stoi(v[i][j].substr(1,v[i][j].length()))));
            }
        }
        encoded.push_back(variables);
    }
    return encoded;
}

ll new_literal(vector<vector<int>> v){
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[i].size();j++){
            if(v[i][j]>0){
                return v[i][j];
            }
            else{
                return -(v[i][j]);
            }
        }
    }
}

bool dpll(vector<vector<int>> v){
    if(v.size()==0){
        return true;
    }
    for(int i=0;i<v.size();i++){
        if(v[i].size()==0){
            cout<<endl;
            cout<<"Unsatisfiable"<<endl;
            return false;
        }
    }
    for(int k = 0; k<v.size();k++){
        if(v[k].size()==1){
            if(v[k][0]>0){
                cout<<abs(v[k][0])<<": true"<<',';
            }
            else{
                cout<<abs(v[k][0])<<": false"<<',';
            }
            return dpll(simplify(v,v[k][0]));
        }
    }
    ll literal = new_literal(v);
    if(dpll(simplify(v,literal))){
        cout<<literal<<": true"<<',';
        return true;
    }
    else{
        cout<<literal<<": false"<<',';
        return dpll(simplify(v,-(literal)));
    }
}

string make_clause(ll n_v,ll n_c){
    vector<string> v;
    for(int i=0;i<n_v;i++){
        string p = to_string(i);
        v.push_back(p);
    }
    random_shuffle(v.begin(),v.end());
    string s="";
    for(int j=0;j<n_c;j++){
        s+= "(";
        int min = n_v/2;
        int max = n_v;
        srand(j);
        int randint = rand()%(max-min+1) + min;
        for(int k=0;k<randint;k++){
            int randbool = rand()%2;
            if(randbool==0){
                s+='!';
            }
            s+=v[k];
            if(k != randint-1){
                s+='+';
            }
        }
        s+=')';
    }
    return s;
}

int main(){   
    ll n_v,n_c; cin>>n_v>>n_c;
    string input = make_clause(n_v,n_c);
    auto start=chrono::steady_clock::now();
    input = input.substr(1,input.length());
    stringstream ss(input);
    string clause_string;
    vector<string> clauses;
    while(getline(ss, clause_string, ')')){
        clauses.push_back(clause_string);
    }
    for(int i = 1; i<clauses.size();i++){
        clauses[i] = clauses[i].substr(1,clauses[i].length());
    }
    vector<vector<string>> values;
    for(int j = 0; j<clauses.size();j++){
        vector<string> CharValues;
        int a=1;
        string s="";
        for(int k=0;k<clauses[j].length();k++){
            if(clauses[j][k]=='+'){
                s = "";
                a = 1;
                continue;
            }
            if(clauses[j][k]=='!'){
                a = 0;
                s="!";
                continue;
            }
            else{
                s+=clauses[j][k];
                CharValues.push_back(s);
            }
        }
        values.push_back(CharValues);
    }
    dpll(encode(values));
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout<<endl;
    cout<<chrono::duration<double, milli>(diff).count()<<" ms";
    return 0;
}