#include "Queue.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
using namespace cop4530;


int str2int(string s)
{
    int value;
    istringstream buffer(s);
    buffer>> value;
    return value;
}

vector<string>& loaddata(vector<string>& data)
{
    ifstream input_file("proj3.input",ios::in);
    string input;
    while(getline(input_file,input)){
        if (input.empty())
            break;
        data.push_back(input);
    }
   cout<<data[0]<<" cities:"<<endl;
   for(int i=1;i<9;++i)
       cout<<"    "<<data[i]<<endl;
   cout <<"\n";
   input_file.close();
}

vector<string> citi_list(vector<string>& data)
{
   vector<string> citi_list;
   for (int i=1;i<9;++i)
       citi_list.push_back(data[i]);
   return citi_list;
}
vector<int>& parse(string s, vector<int>& sub)
{
    istringstream iss(s);
    string word;
    int num;

    while(iss>>word){
    num=str2int(word);
    sub.push_back(num);
    }
    return sub;
}

vector<string>& neibor_finder(const vector<string>& data,
                              vector<int> sub,vector<string>& neibor)
{
    for(int i=0;i<sub.size();++i)
    {
       if(sub[i]>0)
         {cout<<"    "<<data[i+1]<<", ";
          cout<<"$"<<sub[i]<<endl;
          neibor.push_back(data[i+1]);}
    }
}

int search (const vector<string>& lib,string x )
{
    for(int i=0;i<lib.size();++i){
        if (lib[i]==x)
            return 1;
    }
    return 0;
}
map<string,vector<string>> map_build(const vector<string>& data)
{
    cout <<"direct flights between cities"<<endl;
    cout <<"--------------------------"<<endl;
    map<string,vector<string>> mymap;
    int num=str2int(data[0]);
    vector<int> sub;
    vector<string> neibor;

    for(int k=num+1;k<num+9;++k)
    {
     cout<<data[k-num]<<":"<<endl;
     parse(data[k],sub);
     neibor_finder(data,sub,neibor);
     mymap.insert(pair<string,vector<string>>(data[k-num],neibor));
     sub.clear();
     neibor.clear();
    }
    cout <<"------------------"<<endl;
    return mymap;
}

int search_path(vector<vector<string>>& path,string t)
{
     int j=0;
     for(;j<path.size();++j)
      {
        if(search(path[j],t)==1)
             { return j;}
      }
}

void replicate(const vector<string>& temp, int j,
               vector<vector<string>>& path)
{
  for(int k=0;k<temp.size()-1;++k)
        {path.push_back(path[j]);}
}

void add_element(vector<vector<string>>& path,
                 vector<string>& temp, int j)
{
     path[j].push_back(temp[0]);
     for(int k=1;k<temp.size();++k)
       {
         path[path.size()-k].push_back(temp[k]);
       }
}
void initialize(vector<vector<string>>& path,
                     vector<string>& visited,
                      Queue<string>& qq,string start)
{
    visited.push_back(start);
    qq.push(start);
    vector<string> entry;
    entry.push_back(start);
    path.push_back(entry);
}

vector<string> filter(vector<string>& temp,vector<string>& visited)
{
    vector<string> filter_list;
    for(int i=0;i!=temp.size();++i)
      {
        if (search(visited,temp[i])==0)
           filter_list.push_back(temp[i]);
      }
    return filter_list;
}

vector<vector<string>>& path_build (vector<vector<string>>&path,
                                    int mark, string t,
                                    vector<string>& filtered)
{
     if(filtered.size()!=0){
     int j=search_path(path,t);
     replicate(filtered,j,path);
     add_element(path,filtered,j);}
}

vector<string>& filter_lib(string t,map<string,vector<string>>& mymap,
                           vector<string>& filtered,
                          vector<string>& visited)
{
   vector<string> temp= mymap.find(t)->second;
   filtered=filter(temp,visited);
}
void read(string&start,string& destination)
{
   string temp1,temp2;
   cout<<"Source City:";
   getline(cin, temp1);
   cout<<"Destination City:";
   getline(cin, temp2);

   start=temp1;
   destination=temp2;
}

int entrysearch(vector<string>& data,
                string start,string destination)
{
   vector<string> lib=citi_list(data);
   int x=search(lib,start);
   int y=search(lib,destination);
   if(x==0){
      cout<<" path not found, source city,";
      cout<< start<<", not on the map"<<endl;
      return 0;}
   else if (y==0){
      cout<<" path not found, source city,";
      cout<< destination<<", not on the map"<<endl;
      return 0;}
   else
      return 1;
}
void hint()
{
   char answ;
   cout <<"Search another route? [Y/N]";
   cin >> answ;
   if (answ =='n'||answ=='N')
       exit(0);
}

vector<string> cpu(Queue<string> &qq,
                    map<string,vector<string>>& mymap,
                    vector<string>& visited,
                    vector<vector<string>>&path,
                    string destination)
{
    int mark=0;
    int final=1;
    vector<string> filtered;
    while(!qq.empty())
    {
        if (final==0)
             break;
        string t=qq.front();
        ++mark;
        filter_lib(t,mymap,filtered,visited);
        for(int i=0;i!=filtered.size();++i)
          {
            visited.push_back(filtered[i]);
            qq.push(filtered[i]);
            if (filtered[i]==destination)
               final=0;
          }

         path_build(path,mark,t,filtered);
         qq.pop();
   }
    int des_row=search_path(path,destination);
    vector<string> target=path[des_row];
    return target;
}

void matrix_build(vector<string>& data,
                  vector<vector<int>>& matrix)
{
    int num=str2int(data[0]);
    vector<int> sub;
    for(int k=num+1;k<num+9;++k)
    {
     parse(data[k],sub);
     matrix.push_back(sub);
     sub.clear();
    }
}

int index_finder(vector<string> list,string x)
{
  int i=0;
  for(;i<list.size()+1;++i)
    {
     if (list[i]==x)
         return i;
    }
}
int price_finder(vector<string>& data,vector<string>&target
                 ,vector<vector<int>>& matrix)
{

    vector<string> list=citi_list(data);
    vector<int> index_lib;
    for(int i=0;i!=target.size();++i)
    {
     index_lib.push_back(index_finder(list,target[i]));
    }

   int price=0;
   for(int i=0;i<index_lib.size()-1;++i)
   {
     int row=index_lib[i];
     int column=index_lib[i+1];
     int money=matrix[row][column];
     price=price+money;
   }
   return price;
}

void targetprint(const vector<string>& target)
{
   cout <<"   "<< target[0];
   for (int i=1;i<target.size();++i)
       cout << " -> " <<target[i];
   cout <<" ";
}
int main()
{
    vector<string> data;
    loaddata(data);

    vector<vector<int>> matrix;
    matrix_build(data,matrix);

    map<string,vector<string>> mymap;
    mymap=map_build(data);

    int check=0;
    string start;
    string destination;

    while(check==0){
    read(start,destination);
    int check=entrysearch(data,start,destination);
    if (check==0)
        hint();
    else
        break;
     }

    Queue<string> qq;
    vector<string> visited;
    vector<vector<string>> path;
    initialize(path,visited,qq,start);

    vector<string> target=cpu(qq,mymap,visited,path,destination);
    targetprint(target);
    int total=price_finder(data,target,matrix);
    cout <<", $"<<total<<endl;



return 0;
}
