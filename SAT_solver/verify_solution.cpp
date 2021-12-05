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
#include<algorithm>
#define ll long long
using namespace std;

bool verify(vector<vector<string>> clauses, vector<string> sol){
    for(int a=0;a<sol.size()+1;a++){
    for(int i=0;i<sol.size();i++){
        for(int j=0;j<clauses.size();j++){
            int c = count(clauses[j].begin(),clauses[j].end(),sol[i]);
            if(c!=0){
                auto it = find(clauses.begin(),clauses.end(),clauses[j]);
                clauses.erase(it);
            }
            int d;
            string x;
            if(sol[i][0]=='!'){
                x = sol[i].substr(1,sol[i].length());
                d = count(clauses[j].begin(),clauses[j].end(),x);
            }
            else{
                x = '!' + sol[i];
                d = count(clauses[j].begin(),clauses[j].end(),x);
            }
            if(d!=0){
                auto itr = find(clauses[j].begin(),clauses[j].end(),sol[i]);
                clauses[j].erase(itr);
            }
        }
    }
    }
    for(int k=0;k<clauses.size();k++){
        if(clauses[k].size()!=0){
            return false;
        }
    }
    return true;
}

vector<string> evaluate(vector<vector<string>> v){
    vector<string> values;
    for(int i=0;i<v.size();i++){
        if(v[i][1]==" true"){
            values.push_back(v[i][0]);
        }
        else{
            values.push_back('!' + v[i][0]);
        }
    }
    return values;
}

int main(){
    string input = "";                      //give the CNF formula in product of sums form to the string input
    
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

    vector<vector<string>> vec;                 // give the output given by output_format.py to the vector vec
    
    cout<<"satisfies? - "<<verify(values,evaluate(vec))<<endl;
    return 0;
}