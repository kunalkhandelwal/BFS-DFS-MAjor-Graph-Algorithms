//Aim: Implement Graph Traversal  and shortest path Algorithm while using Adjacency Matrix Repesentation.

#include<stdio.h>
#include<stdlib.h>

void dfs(int *,int,int *,int);//Depth First Search.
void bfs(int *,int,int *,int);//Breadth First Search.
void dsp(int *,int,int *,int);//Dijkstra's Shortest Path Algorithm.
void print(int *,int);//For Printing Adjacency Matrix.
void fwsp(int *,int);//Floyd Warshall's Shortest Path Algorithm.
void printSolution(int *,int);//For Floyd Warshall 
void main()
{
	int n,c,r,x,k=1;
   	printf("\nEnter the Numeber of Vertices:-");
   	scanf("%d",&n);
   	int *visited = (int *)malloc(n * sizeof(int)); 
   	int *a = (int *)malloc(n * n * sizeof(int));
        print(a,n);	
	while(r!=99)
	{
		printf("\nEnter the row or press 99 to Finish: ");
		scanf("%d",&r);
		if(r==99)
			break;
		printf("\nEnter the Column: ");
		scanf("%d",&c);
		a[r*n + c]=1;
		a[c*n + r]=1;
	}
	printf("\nEnter the Start Position: ");
	scanf("%d",&x);
	print(a,n);
	while(k!=0)
	{
	printf("\n1.Depth First Search\n2.Breadth First Search\n3.Dijkstra's Shortest Path Algorithm\n4.Warshall's Shortest Path Algorithm\n0.Exit\nEnter choice:-");
	scanf("%d",&k);
		switch(k)
		{
			case 1:
				dfs(a,x,visited,n);
				break;
			case 2:
				bfs(a,x,visited,n);
				break;
			case 3:
				dsp(a,x,visited,n);
				break;
			case 4:
    			        fwsp(a,n);
				break;
			case 0:
				break;
		}
	}
}
void dfs(int *a,int x,int visited[],int n)//Depth First Search.
{
	int vcount=0;
	visited[x]=1;
	printf(" %d ",x);
	while(vcount<n)
	{
		if(a[x*n + vcount]==1 && visited[vcount]==0)
			dfs(a,vcount,visited,n);
		vcount++;
	}
}
void bfs(int *a,int x,int *visited,int n)//Breadth First Search.
{
	int *q = (int *)malloc(n*sizeof(int));
	int front=-1,rear=-1,vcount = 0;
	visited[x] = 1;
	printf(" %d ",x);
	front++;
	rear++;
	q[rear] = x;
	while(front<=rear)
	{
		vcount = 0;
		x = q[front];
		front++;
		while(vcount<n)
		{
			if(a[x*n + vcount]==1 && visited[vcount] ==0)
			{
				visited[vcount]=1;
				printf(" %d ",vcount);
				rear++;
				q[rear] = vcount;
			}
			vcount++;
		}
	}
}
void dsp(int *a,int x,int *visited,int n)//Dijkstra's
{
	
	int i,r,c,nextnode;
	int *d = (int *)malloc(n*sizeof(int));//Distance
	int *q = (int *)malloc(n*sizeof(int));//Queue
	int *cost = (int *)malloc(n*sizeof(int));//Cost
	int *pre = (int *)malloc(n*sizeof(int));
	for (r = 0; r < n; r++)
      		for (c = 0; c < n; c++)
         		a[r*n + c] = r + c;
	d[x] = 0;//Distance of Source Node
	for (r = 0; r < n; r++)
	{
      		for (c = 0; c < n; c++)
		{
			if(a[r*n + c] == 0)
				cost[r*n + c] = 999;
			else
				cost[r*n + c] = a[r*n +c];
		}
	}
	for(i=0;i<n;i++)
	{
		d[i] = cost[x*n + i];
		pre[i] = x;
		visited[i] = 0;
	}
	d[x] = 0;
	visited[x] = 1;
	int count = 1;
	while(count<n-1)
	{
		int mindist=999;
		for(i=0;i<n;i++)
			if(d[i]<mindist && visited[i]==0)
			{
				mindist=d[i];
				 nextnode=i;
			}
			visited[nextnode]=1;
			for(i=0;i<n;i++)
			{
				if(visited[i] == 0)
					if(mindist+cost[nextnode*n + i]<d[i])
					{
						d[i]=mindist+cost[nextnode*n + i];
						pre[i]=nextnode;
					}
			}
		count++;
	}
	for(i=0;i<n;i++)
		if(i != x)
			printf("\nDistance of node %d from node %d = %d ",i,x,d[i]);
}
void print(int *a,int n)
{
	int r,c;
	for(r=0;r<n;r++)
	{
		{
			for(c=0;c<n;c++)
				printf(" %7d ",a[r*n+c]);
			printf("\n");
		}
		printf("\n");
	}
}
void fwsp(int *a,int n) 
{ 
    int i, j, k; 
    int *dist = (int *)malloc(n * n * sizeof(int));  
    printf("\nEnter  Weighted Matrix elements\n");
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++)
        {
            if(a[i*n + j] == 1)
            {
            	printf("\nEnter for %d row and %d column.\n",i,j);
            	scanf("%d",&dist[i*n + j]);
            }
        }
    }
    for (k = 0; k < n; k++) 
        for (i = 0; i < n; i++) 
            for (j = 0; j < n; j++) 
                if (dist[i*n + k] + dist[k*n + j] < dist[i*n + j]) 
                	dist[i*n + j] = dist[i*n + k] + dist[k*n + j]; 
    printSolution(dist,n); 
} 
void printSolution(int *dist,int n) 
{ 
    int i,j;
    printf ("The following matrix shows the shortest distances between every pair of vertices \n"); 
    for (i = 0; i < n; i++) 
    { 
        for (j = 0; j < n; j++) 
        { 
            if (dist[i*n + j] == -99) 
                printf("%7s", "INF"); 
            else
                printf (" %7d ", dist[i*n + j]); 
        } 
        printf("\n"); 
    } 
}
