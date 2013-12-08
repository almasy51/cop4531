#include <vector>
#include <map>	
#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <fstream>
using namespace std;

struct vert{
	char curr;
	vector<char> adj;
	vector<int> wt;
	char prev;
	vector<int> dist;	
	int visited;
	int wei;
};



int main(){
	vert ver;
	map<char, vert> n;
	map<char, vert> m;
	char j,k,c;
	int i;
	string in;
	string input;
	char filename[80];
	ifstream ifs;
	ifstream infile;
	ofstream ofs;
	vector< pair<char, int> > vqueue;
	char source;
	vert v;
	int totalw, weight = 0;
	char end;
	vector<char> sol;
	
	ofs.open("out.txt");
	
	cout<< "Select file to open: ";
	cin>>filename;
	infile.open(filename, ifstream::in);
	
	getline(infile, in);
	
	while(!isalnum(infile.peek())){
		getline(infile,in);
	}
	
	if(in == "D"){
		while(getline(infile, in)){
			;
			stringstream ss(in);
			getline(ss,input,' ');
			stringstream fs(input);
			fs >> j;
			getline(ss,input, ' ');
			stringstream sfs(input);
			sfs >> k;
			getline(ss,input, ' ');
			stringstream sss(input);
			sss >> i;
			v.curr = j;
			v.visited = 0;
			v.wei = 1000000;
			n.insert ( pair<char,vert >(j,v) );
			n.at(j).adj.push_back(k);
			n.at(j).wt.push_back(i);
			n.insert ( pair<char,vert >(k,v) );
		}
	}
	else{
		while(getline(infile, in)){
			;
			stringstream ss(in);
			getline(ss,input,' ');
			stringstream fs(input);
			fs >> j;
			getline(ss,input, ' ');
			stringstream sfs(input);
			sfs >> k;
			getline(ss,input, ' ');
			stringstream sss(input);
			sss >> i;
			v.curr = j;
			v.visited = 0;
			v.wei = 1000000;
			n.insert ( pair<char,vert >(j,v) );
			n.at(j).adj.push_back(k);
			n.at(j).wt.push_back(i);
			v.curr = k;
			n.insert ( pair<char,vert >(k,v) );
			n.at(k).adj.push_back(j);
			n.at(k).wt.push_back(i);
		}
	}
	
	cout << "Select source node: "<< endl;
	cin >> source;
	cout << "Select end node: " << endl;
	cin >> end;
	
	vqueue.push_back(make_pair(source, 0));
	n.at(source).visited = 1;
	n.at(source).wei = 0;
	i=0;	
	
	while(!vqueue.empty()){
		
		k = vqueue.begin()->first;
		vector<char>::iterator it = n.at(vqueue.begin()->first).adj.begin();
		vector<char>::iterator its = n.at(vqueue.begin()->first).adj.end();
		vqueue.erase(vqueue.begin());
		n.at(k).visited = 1;	

		for(it; it != its; ++it){
			j = *it;			
			weight = n.at(k).wt.at(i) + n.at(k).wei;
			if(weight < n.at(j).wei){
				n.at(j).wei = weight;
				n.at(j).dist.push_back(weight);
				n.at(j).prev = k;		
				vqueue.push_back(make_pair(j,weight));			
			}
			i++;
		}
		i=0;
	
	}
	ofs << "Dijkstra's: " << endl;
	ofs << "Source: " << source << endl;
	for(map<char,vert>::iterator it = n.begin(); it != n.end(); it++){
		ofs << "Node " << it->first << ": " << n.at(it->first).wei << endl;
	}
	ofs<<endl;
	
	vqueue.clear();
	
	i=0;
	vqueue.push_back(make_pair(source, 0));
	m.insert(pair<char,vert>(source,v));
	while(!vqueue.empty()){
		k = vqueue.begin()->first;
		vqueue.erase(vqueue.begin());
		if(k == end){
			break;
		}
		for(vector<char>::iterator it = n.at(k).adj.begin(); it != n.at(k).adj.end(); it++){
			j = *it;
			pair<map<char,vert>::iterator,bool> ret;
			ret = m.insert(pair<char,vert>(j,v));
			if(ret.second == true){
				vqueue.push_back(make_pair(j, m.at(j).wei));
				m.at(k).adj.push_back(j);
				m.at(k).wt.push_back(n.at(k).wt.at(i));
				//n.at(k).wt.push_back(i);
			}
			i++;	
		}
		i=0;
	}

	vqueue.clear();

	vqueue.push_back(make_pair(source, 0));
	m.at(source).visited = 1;
	m.at(source).wei = 0;
	i=0;	
	
	while(!vqueue.empty()){
		
		k = vqueue.begin()->first;
		vector<char>::iterator it = m.at(vqueue.begin()->first).adj.begin();
		vector<char>::iterator its = m.at(vqueue.begin()->first).adj.end();
		vqueue.erase(vqueue.begin());
		m.at(k).visited = 1;	

		for(it; it != its; ++it){
			j = *it;			
			weight = m.at(k).wt.at(i) + m.at(k).wei;
			
			if(weight < m.at(j).wei){
				m.at(j).wei = weight;
				m.at(j).dist.push_back(weight);
				m.at(j).prev = k;		
				vqueue.push_back(make_pair(j,weight));			
			}
			i++;
		}
		i=0;
	
	}

	ofs << "Shortest Reliable Path: " << endl;
	ofs << "Source: " << source << endl;
	for(map<char,vert>::iterator it = m.begin(); it != m.end(); it++){
		ofs << "Node " << it->first << ": " << m.at(it->first).wei << endl;
	}
	ofs<<endl;

	ofs.close();
	ifs.close();
	
	return(0);
};