#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <limits.h>
using namespace std;

typedef struct tag_t{
    string name;
    map<string,string> attr;
}tag;

ostream& operator<<(ostream& cout, tag& obj){
    cout << "tag-name: " << obj.name << '\n';
    for(const auto& ele : obj.attr){
        cout << "attribute: " << ele.first<< "=" << ele.second<<'\n';
    }
    return cout;
}

istream& operator>>(istream& cin, tag& obj){
    cin>>obj.name;
    if(obj.name.find('>') != obj.name.npos){
        //removing the first and the last character from obj.name
        obj.name = obj.name.substr(1,obj.name.size()-2);
        return cin; // exit early
    }else{
        //just removing the first <
        obj.name = obj.name.substr(1);
        
        string attrName{};
        string attrValue{};
        char delim{};
        while(true){
            cin>>attrName;
            cin>>delim;
            cin>>attrValue;
                if(attrValue.find('>') != attrValue.npos){
                    //remove the > from the value
                    attrValue=attrValue.substr(1,attrValue.size()-3);
                    obj.attr[attrName] = attrValue;
                    break;
                }
            attrValue=attrValue.substr(1,attrValue.size()-2);
            obj.attr[attrName] = attrValue;
        }
    }
    
    return cin;
}

int main() {
    
    stringstream test("<tag3 another = 'another' final = 'final'>");
    tag ttest;
    test >> ttest;
    //cout << ttest;
    
    string s{};
    stringstream ss{};
    int N{};
    int Q{};
    getline(cin,s);
    ss << s;
    ss >> N;
    ss >> Q;
    
    vector<tag> tags{};
    
    for(int i=0; i <N;i++){
        tag t;
        cin>>t;
        tags.push_back(t);
        
    }
    cin.ignore(numeric_limits<int>::max(),'\n');
    for(int i=0; i <Q;i++){
        string query{};
        getline(cin,query);
        int starting_index=query.rfind('.');
        stringstream queryStream(query.substr(starting_index+1));
        string tagName{};
        string attrName{};
        getline(queryStream,tagName,'~');
        getline(queryStream,attrName,'~');
        bool found{false};
        for(auto& ele : tags){
            if(ele.name==tagName){
                for(auto& attr : ele.attr){
                    if(attr.first == attrName){
                        cout << ele.attr[attrName] << '\n';
                        found = true;        
                    }
                }
                
            }
        }
        if(!found){
            cout << "Not Found!\n";
        }
        
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
