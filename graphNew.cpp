// graphNew.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct edgenode{
	int val;
	int weight;
	edgenode *next;

	edgenode():val(0), weight(0), next(NULL) {}
	edgenode(int x):val(x), weight(0), next(NULL) {}
	edgenode(int x, int wt):val(x), weight(wt), next(NULL) {}
};

class graph{	

	int nvertices;
	int nedges;	
	bool directed;
	vector<edgenode*>edges;	 
	vector<int>degree;
	vector<bool>discovered;
	vector<bool>processed;
	vector<int>parent;
	vector<int>entry;
	vector<int>exit;
	vector<bool>intree;
	vector<int>distance;
	vector< vector<int> >storepaths;	
	stack<int>topologicalOrder;

public:

	graph(int v, int e,bool dir){

		 nvertices=v+1;
	     nedges=e+1;	     

		 for(int i=0; i<nvertices; i++){

			 degree.push_back(0);
			 edges.push_back(NULL);
			 discovered.push_back(false);
			 processed.push_back(false);
			 parent.push_back(-1);
			 entry.push_back(-1);
			 exit.push_back(-1);
			 intree.push_back(false);
			 distance.push_back(INT_MAX);
		 }							
     }

	void reset(){
	
		for(int i=0; i<nvertices; i++){			 			 
			 discovered[i]=false;
			 processed[i]=false;
			 parent[i]=-1;
			 intree[i]=false;
			 distance[i]=INT_MAX;

		 }	
	
	}


	void addWeightedEdge(int x, int y, int w){

		edgenode *p=new edgenode(y,w);				
		
		if(edges[x] == NULL)				
			edges[x]=p;								
		else{		   
		   p->next=edges[x];						
		   edges[x]=p;
		   degree[x]++;
		}
			
		if(!directed){
			p=new edgenode(x,w);

			if(edges[y] == NULL)					
			  edges[y]=p;					  		
		   else{		   
		    p->next=edges[y];						
		    edges[y]=p;
		    degree[y]++;
		}	
	}

}

	void addEdge(int x, int y){

		edgenode *p=new edgenode(y);				
		
		if(edges[x] == NULL)				
			edges[x]=p;	

		else{		   
		   p->next=edges[x];						
		   edges[x]=p;
		   degree[x]++;
		}
			
		if(!directed){
			p=new edgenode(x);

			if(edges[y] == NULL)					
			  edges[y]=p;

		   else{		   
		    p->next=edges[y];						
		    edges[y]=p;
		    degree[y]++;
		}	
	}

}

	void initializeGraph(){	   				
		int v1,v2;

		for(int i=1; i<nedges; i++){	
			cout<<"\n enter from and to vertex for edge ";
			cin>>v1;			
			cin>>v2; 			
		    addEdge(v1,v2);
			cout<<" ";
		}

		printGraph();
	
}


	void initializeWeightedGraph(){	   				
		int v1,v2,wt;

		for(int i=1; i<nedges; i++){	
			cout<<"\n enter from and to vertex for edge ";
			cin>>v1;			
			cin>>v2; 	
			cout<<"\n enter weight ";
			cin>>wt;
			addWeightedEdge(v1,v2,wt);
			cout<<" ";
		}

		printGraph();
	
}

	void printGraph(){
	
		for(int i=0; i<nvertices; i++){

			if(edges[i]){
				cout<<"\n edges from vertex "<<i<<"-";
			edgenode *p=edges[i];

			while(p!=NULL){			 
				cout<<" value "<<p->val;

				  if(p->weight)
				      cout<<" weight "<<p->weight;									
			    p=p->next;
			}

		    cout<<"\n";
		}
		    
	}
	
}

	void bfs(int start){
		
		queue<int>qbfs;
		int v1,v2;

		discovered[start]=true;
		parent[start]=-1;

		qbfs.push(start);
		edgenode *current;

		while(!qbfs.empty()){
		
			v1=qbfs.front();
			cout<<" "<<v1;

			qbfs.pop();
			processed[v1]=true;
			current=edges[v1];

			while(current!=NULL){
				v2=current->val;

				if(!processed[v2] || directed){				
					//cout<<"\n process edge from "<<v1<<" to "<<v2;
				}

				if(!discovered[v2]){
					qbfs.push(v2);
					discovered[v2]=true;
					parent[v2]=v1;

				}

				current=current->next;

			}		
		
		}
	
	}


	void bfsAll(){
	
		for(int i=1; i<nvertices; i++){
			if(!discovered[i])
			   bfs(i);			
		}	  
	}



	void dfs(int start){

	   static int time =0;
	   cout<<" "<<start;

	   discovered[start]=true;
	   time+=1;

	   entry[start]=time;

	   edgenode *current=edges[start];

	   processed[start]=true;

	   while(current!=NULL){
		   int vertex=current->val;

		   if(!processed[vertex] || directed)			
					//cout<<"\n process edge from "<<start<<" to "<<vertex;
			
		   if(!discovered[vertex]){
			   parent[vertex]=start;
		       dfs(vertex);
		   }
		   
		   current=current->next;
	   }

	   topologicalOrder.push(start);
	   time+=1;
	   exit[start]=time;
	   

 }

	void dfsAll(){

	for(int i=1; i<nvertices; i++){
			if(!discovered[i])
			   dfs(i);			
		}
	}

	void printAllPathsfromAtoB(int a, int b){
	  vector<int>paths;

	  findAllPathsfromAtoB(a, b, paths);
	
	  for(int i=0; i<storepaths.size(); i++){	  
		  cout<<endl;

		  for(int j=0; j<storepaths[i].size(); j++)		  
			  cout<<storepaths[i][j]<<" ";	

	  }
	
  }
	
	void findAllPathsfromAtoB(int a, int b, vector<int>&paths){
	
           discovered[a]=true;
		   paths.push_back(a);

		   edgenode *p=edges[a];

		   while(p!=NULL){
			   
			   if(p->val == b){			   
				   paths.push_back(b);
				   storepaths.push_back(paths);
				   paths.pop_back();
			   }
			   else {
				   if(!discovered[p->val])			   
				      findAllPathsfromAtoB(p->val, b, paths);
			   }
			   
			   p=p->next;

		   }

		   discovered[a]=false;
		   paths.pop_back();      	
	}
	

	void prims(int start){
	
		distance[start]=0;
		int v=start;
		parent[start]=-1;

		while(intree[v] == false){
			intree[v]=true;
			edgenode *p=edges[v];

			while(p!=NULL){
			
				if(p->weight < distance[p->val] && !intree[p->val]){				
					distance[p->val]=p->weight;			
					parent[p->val]=v;
				}
				p=p->next;			
			}
		
		int dis=INT_MAX;

		for(int i=1; i<nvertices; i++){

			if(!intree[i] && distance[i]<dis){
				dis=distance[i];
				v=i;
			}			
		}

	}

		cout<<"\n";

		for(int i=nvertices-1; i>1; i--){

			if(intree[i]){
			  cout<<parent[i]<<" to "<<i<<" distance "<<distance[i];
		      cout<<"\n";
			}
		   
		}
		
	}

	void dijkstras(int start){
	
		distance[start]=0;
		int v=start;

		while(intree[v] == false){
		
			intree[v]=true;
			edgenode *p=edges[v];	

			while(p!=NULL){
			
				if(distance[p->val] > distance[v]+p->weight){				
					distance[p->val]=distance[v]+p->weight;
					parent[p->val]=v;				
				}
				p=p->next;
			
			}
		
			int dist=INT_MAX;
			for(int i=1; i<nvertices; i++){
			
				if(!intree[i] && (distance[i]<dist)){				
					dist=distance[i];
				    v=i;
				}
			}


		}

		cout<<"\n dijkstra's single source shortest path from vertex 1\n";

		for(int i=nvertices-1; i>1; i--){
		 
			cout<<" to "<<i<<" from "<<parent[i];
		    cout<<endl;
		}
	
	}

	void topologicalSort(){
	  
		cout<<"\n perform DFS\n";
		dfsAll();
		cout<<"\n Topological Order \n";

		while(topologicalOrder.size()!=1){

			cout<<topologicalOrder.top()<<" -> ";
		    topologicalOrder.pop();		
		}
		
		cout<<topologicalOrder.top();
		topologicalOrder.pop();	
			
	}
	
};


int _tmain(int argc, _TCHAR* argv[])
{
	int v,e,a,b,option;
	bool isdirected;	

	cout<<"\n enter 1: BFS, 2: DFS, 3: Prims, 4: Dijkstra, 5: Topological Sort, 6: find all Paths from a to b \n";
	cin>>option;

	cout<<"\n enter number of vertices for the graph ";
	cin>>v;

	cout<<"\n enter number of edges for the graph ";
	cin>>e;	

	cout<<"\n enter 1 for directed, 0 for undirected graph ";
	cin>>isdirected;
	
	graph *g=new graph(v, e, isdirected);	

	switch (option)
	{
	case 1: {
		g->initializeGraph();		
		g->bfsAll();
			break;}

	case 2: {
		g->initializeGraph();		
		g->dfsAll();
			break;}

	case 3:{
		   g->initializeWeightedGraph();		   
		   g->prims(1);
		   break;}

	case 4:{
		   g->initializeWeightedGraph();		   
		   g->dijkstras(1);
		   break;
		   }

	case 5:{
		      g->initializeGraph();
		      g->topologicalSort();
		      break;
		   }
	case 6:{
		     g->initializeGraph();		       
			 cout<<"\n enter a and b ";
			 cin>>a>>b;
			 g->printAllPathsfromAtoB(a,b);
			 break;
		   }
	default:
		break;
  }			   		
		
	return 0;
}

