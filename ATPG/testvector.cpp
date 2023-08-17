#include<bits/stdc++.h>
using namespace std;
void backtrack(map<int,vector<int>>l,map<int,string>gate,int val,int node,stack<pair<int,int>>&st)
{
    if(l.find(node)==l.end())
    {
        st.push(make_pair(node,val));
        return;
    }
    else
    {
        if(gate[node]=="OR" && val==0)              //implecation
        {
            st.push(make_pair(l[node][0],0));
            backtrack(l,gate,0,l[node][0],st);
            st.push(make_pair(l[node][1],0));
            backtrack(l,gate,0,l[node][1],st);
        }
        if(gate[node]=="AND" && val==1)            // implication
        {
            st.push(make_pair(l[node][0],1));
            backtrack(l,gate,1,l[node][0],st);
            st.push(make_pair(l[node][1],1));
            backtrack(l,gate,1,l[node][1],st);
        }
        if(gate[node]=="OR" && val==1)            //decision
        {
            st.push(make_pair(l[node][0],1));
            backtrack(l,gate,1,l[node][0],st);
        }
        if(gate[node]=="AND" && val==0)          //decision
        {
            st.push(make_pair(l[node][0],0));
            backtrack(l,gate,0,l[node][0],st);
        }
        if(gate[node]=="NOT" && val==0)
        {
            st.push(make_pair(l[node][0],1));
            backtrack(l,gate,1,l[node][0],st);
        }
        if(gate[node]=="NOT" && val==1)
        {
            st.push(make_pair(l[node][0],0));
            backtrack(l,gate,0,l[node][0],st);
        }
    }
}

void forward_prop(map<int,vector<int>>l,map<int,vector<int>>parent,int node,int observe_node,int &parity,map<int,char>&state,map<int,string>gate,map<int,int>ranks)
{   if(node==observe_node)return;
    int pa,cmp=1e9;
    for(int i:parent[node])
    {
        if(ranks[i]<cmp)
        {
            pa=i;
            cmp=ranks[i];
        }
    }
    if(gate[pa]=="AND")
    {
        for(int i:l[pa])
        {
            if(i!=node)
            {
                stack<pair<int,int>>st;
                backtrack(l,gate,1,i,st);
                while(!st.empty())
                {
                    pair<int,int>pr=st.top();
                    if(state.find(pr.first)!=state.end())
                    {
                        if(pr.second==1)state[pr.first]='1';
                        if(pr.second==0)state[pr.first]='0';
                    }
                    st.pop();
                }
            }
        }
    }
    if(gate[pa]=="OR")
    {
        for(int i:l[pa])
        {
            if(i!=node)
            {
                stack<pair<int,int>>st;
                backtrack(l,gate,0,i,st);
                while(!st.empty())
                {
                    pair<int,int>pr=st.top();
                    if(state.find(pr.first)!=state.end())
                    {
                        if(pr.second==1)state[pr.first]='1';
                        if(pr.second==0)state[pr.first]='0';
                    }
                    st.pop();
                }
            }
        }
    }
    if(gate[pa]=="NOT")parity=parity^1;
    if(pa==observe_node)return;
    else forward_prop(l,parent,pa,observe_node,parity,state,gate,ranks);
}
void bfs_rank(map<int,int>&ranks,map<int,vector<int>>l,int output_node)
{
    queue<int>q;
    q.push(output_node);
    ranks[output_node]=0;
    while(!q.empty())
    {
        int head=q.front();
        q.pop();
        for(vector<int>::iterator it=l[head].begin(); it!=l[head].end(); it++)
        {
            ranks[*it]=ranks[head]+1;
            q.push(*it);
        }
    }
    return;
}
int main()
{
    map<int,vector<int>>l;
    map<int,string>gate;
    map<int,vector<int>>parent;
    map<int,int>ranks;
    int cnt=0;
    unordered_set<int>se;
    cout<<"Please assign node from integer 0 and give input in consecutive integers"<<endl;
    cout<<"Input any negative number to complete your Netlist"<<endl;
    while(true)
    {
        int i;
        string s;
        cin>>i>>s;
        if(i>=0)
        {
            if(se.find(i)==se.end())
            {
                se.insert(i);
                cnt++;
            }
            if(s=="AND")
            {
                int c1,c2;
                cin>>c1>>c2;
                if(se.find(c1)==se.end())
                {
                    cnt++;
                    se.insert(c1);
                }
                if(se.find(c2)==se.end())
                {
                    cnt++;
                    se.insert(c2);
                }
                l[i].push_back(c1);
                l[i].push_back(c2);
                parent[c1].push_back(i);
                parent[c2].push_back(i);
                gate[i]=s;
            }
            if(s=="OR")
            {
                int c1,c2;
                cin>>c1>>c2;
                if(se.find(c1)==se.end())
                {
                    cnt++;
                    se.insert(c1);
                }
                if(se.find(c2)==se.end())
                {
                    cnt++;
                    se.insert(c2);
                }
                l[i].push_back(c1);
                l[i].push_back(c2);
                gate[i]=s;
                parent[c1].push_back(i);
                parent[c2].push_back(i);
            }

            if(s=="NOT")
            {
                int c1;
                cin>>c1;
                gate[i]=s;
                if(se.find(c1)==se.end())
                {
                    cnt++;
                    se.insert(c1);
                }
                l[i].push_back(c1);
                parent[c1].push_back(i);
            }
        }

        else break;
    }
    int input=0;
    map<int,char>state;
    for(unordered_set<int>::iterator it=se.begin(); it!=se.end(); it++)
    {
        if(l.find(*it)==l.end())
        {
            state[*it]='x';
            input++;
        }
    }
    cout<<"Number of Nodes "<<cnt<<endl;
    cout<<"Number of input "<<input<<endl;
    cout<<"Enter observable Node"<<endl;
    int observe_node;
    cin>>observe_node;
    bfs_rank(ranks,l,observe_node);
    int parity=0,node,fault;
    cout<<"enter faulty node "<<endl;
    cin>>node;
    cout<<"Value of stuck at fault 0/1"<<endl;
    cin>>fault;
    forward_prop(l,parent,node,observe_node,parity,state,gate,ranks);
    stack<pair<int,int>>st;
    backtrack(l,gate,fault^1,node,st);
    while(!st.empty())
    {
        pair<int,int>pr=st.top();
        if(state.find(pr.first)!=state.end())
        {
            if(pr.second==1)state[pr.first]='1';
            if(pr.second==0)state[pr.first]='0';
        }
        st.pop();
    }
    for(auto j=state.begin(); j!=state.end(); j++)
    {
        cout<<j->first<<" "<<j->second<<endl;
    }
}
