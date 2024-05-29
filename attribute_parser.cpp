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
        string discard{};
        string attrValue{};
        
        string line{};
        getline(cin,line);
        int nrAttr=count(line.begin(),line.end(),'=');
        stringstream sstream(line);
        for(int i =0; i < nrAttr; i++){
            getline(sstream,attrName,'=');
            getline(sstream,discard,'"');
            getline(sstream,attrValue,'"');
            int first = attrName.find_first_not_of(' ');
            int last = attrName.find_last_not_of(' ');
            attrName = attrName.substr(first,(last-first+1));
            obj.attr[attrName] = attrValue;
        }
        
        
    }
    
    return cin;
}

int main() {
    
    stringstream test("<tag3 another=\"another\" final=\"final\">");
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
