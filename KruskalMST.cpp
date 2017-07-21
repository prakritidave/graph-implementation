// KruskalMST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct setUnion{
vector<int>parent;
vector<int>size;
int n; //number of elements in set;
};


class kruskal{

	setUnion *s;
	vector< pair<int, pair<int, int> > >edges;
	int nedges;
	int nvertices;

public:

	kruskal(int v, int e){
		nedges=e;
		nvertices=v;
		s=new setUnion();	
		setUnionInit();
	}

	void setUnionInit(){
     
		for(int i=0; i<=nvertices; i++){	
			s->parent.push_back(i);
			s->size.push_back(1);		
		}
	   
		s->n=nvertices;
	}


	void addEdges(){
	
		cout<<"\n enter all edges ";
		int x,y,wt;

		for(int i=0; i<nedges; i++){
		
			cout<<"\n enter source and destination ";
			cin>>x;
			cin>>y;
			cout<<"\n enter edge cost ";
			cin>>wt;
			edges.push_back(make_pair(wt, make_pair(x,y)));		
		}	  	
	}

	void sortEdges(){	
		sort(edges.begin(),edges.end());	
	}

	void printEdges(){
	
		cout<<"\n print graph \n";
		vector< pair<int, pair<int,int> > >::iterator outer;

		for(outer = edges.begin(); outer!=edges.end(); outer++){
		  
			int wt= outer->first;
			int x=outer->second.first;
			int y=outer->second.second;
			cout<<"from "<<x<<" to "<<y<<" weight "<<wt;
			cout<<endl;
		
		}

	}

	int find(int x){
	
		if(s->parent[x] == x)return x;
		s->parent[x]=find(s->parent[x]);
		return s->parent[x];	
	}

	bool sameComponent(int u, int v){
	
	    return (find(v) == find(u));				
	}

	void union_sets(int u, int v){
	
		int r1,r2;

		r1=find(u);
		r2=find(v);
	
		if(r1 == r2)return;

		if(s->size[r1] >= s->size[r2]){	  
			s->parent[r2]=r1;
			s->size[r1] += s->size[r2];				
		}
		else{
		
			s->parent[r1]=r2;
			s->size[r2] += s->size[r1];
		}
	
	}


	void kruskalMST(){
	
	int mstwt=0;
	vector< pair<int, pair<int, int>> >::iterator outer;
	int wt,x,y;

	sortEdges();

	cout<<"\n minimal spanning tree \n";

	for(outer=edges.begin(); outer!=edges.end(); outer++){
		
		wt=outer->first;
		x=outer->second.first;
		y=outer->second.second;

		if(!sameComponent(x, y)){	
			cout<<x<<" - "<<y<<endl;
			union_sets(x,y);
			mstwt+=wt;
		}				

	}

	cout<<"\n minimal spanning tree weight "<<mstwt<<" ";
	  
	
	}

};

int _tmain(int argc, _TCHAR* argv[])
{
	int v,e;
	cout<<"\n enter the number of vertices ";
	cin>>v;

	cout<<"\n enter the number of edges ";
	cin>>e;
	
	kruskal *k = new kruskal(v,e);

	k->addEdges();
	k->printEdges();
	k->kruskalMST();

	return 0;
}

