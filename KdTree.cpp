#include<iostream>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h> 

using namespace std;

//structure of a node in tree. x=x co-ordinate of the point,
//y=y co-ordinate of the point, le=left boundary of the point,
//ri=right boundary of the point, top=top boundary of the point,
//bottom=bottom boundary of the point, count=No. of nodes in its subtree.
struct Treenode
{
	int x, y,le,ri,top,bottom,count;
	Treenode* left;
	Treenode* right;
};

//Function used to sort points according to Y-co-ordinates
bool sortbysec(const pair<int,int> &a, 
              const pair<int,int> &b) 
{ 
    return (a.second < b.second); 
} 

//Function used to Build Kd tree. z contains input points, depth contains depth at which node is added, other four values are the boundary of the particular node.
struct Treenode* BuildKdTree(vector<pair<int, int> >& z,int depth,int l1,int r1,int b1,int t1)
{
	int mid=0;
	vector<pair <int,int>> pleft;
	vector<pair <int,int>> pright;
	struct Treenode* root;
	struct Treenode* node = (struct Treenode*)malloc(sizeof(struct Treenode));

	//If only one point in region the add as leaf.
	if(z.size()==1)
	{
		node->x = z[0].first;
		node->y= z[0].second;
		//printf("Depth %d = %d %d ",depth,node->x,node->y);
		//printf("depth %d = ",depth);
		//printf("%d %d || ",node->x,node->y);
		node->left = NULL;
		node->right = NULL; 
		return(node);	
	}
	//if even depth split at median x value
	else if(depth%2==0)
	{	
		sort(z.begin(),z.end());
		int size=z.size();
		mid = z.size()/2;
		int val=mid;
		if(z.size()%2==0)
		{
			val=val-1;		
		}
		//printf("depth %d = ",depth);
		node->x = z[val].first;
		node->y = -1;
		node->le = l1;
		node->ri = r1;
		node->bottom = b1;
		node->top = t1;
		//printf("%d %d == %d,%d,%d,%d ||  ",node->x,node->y,node->le,node->ri,node->bottom,node->top);
		for(int i=0;i<=val;i++)
		{
			pleft.push_back(make_pair(z[i].first,z[i].second));
		}
		int i=0;
		
		for(int i=val+1;i<z.size();i++)
		{
			pright.push_back(make_pair(z[i].first,z[i].second));
		}
		node->left = BuildKdTree(pleft,depth+1,node->le,node->x,node->bottom,node->top);
		node->right = BuildKdTree(pright,depth+1,node->x,node->ri,node->bottom,node->top);
				
	}
	//if odd depth split at median y value.
	else if(depth%2==1)
	{
		sort(z.begin(), z.end(), sortbysec);
		
		int size = z.size();
		mid = z.size()/2;
		int c = mid;
		if(z.size()%2==0)
		{
			c=c-1;	
		}
		node->x = -1;
		node->y = z[c].second;
		node->le = l1;
		node->ri = r1;
		node->bottom = b1;
		node->top = t1;
		//printf("depth %d = ",depth);
		//printf("%d %d || ",node->x,node->y);
		//printf("%d %d == %d,%d,%d,%d ||  ",node->x,node->y,node->le,node->ri,node->bottom,node->top);
		for(int i=0;i<=c;i++)
		{
			pleft.push_back(make_pair(z[i].first,z[i].second));
		}
		for(int i=c+1;i<z.size();i++)
		{
			pright.push_back(make_pair(z[i].first,z[i].second));
		}
		node->left = BuildKdTree(pleft,depth+1,node->le,node->ri,node->bottom,node->y);
		node->right = BuildKdTree(pright,depth+1,node->le,node->ri,node->y,node->top);
		
	}
	
	return node;
}

//Function used to calculate the number of nodes in subtree of each node and update count variable associated with each node.
void Updatecount(struct Treenode* node) 
{ 
    if (node == NULL) 
        return; 
  
    // first recur on left subtree 
    Updatecount(node->left); 
  
    // then recur on right subtree 
    Updatecount(node->right); 
  
    // now deal with the node 
     if ((node->left) == NULL && (node->right)==NULL) 
	{	       
		node->count = 1;
		return;
	}
     node->count = (node->left)->count + (node->right)->count;
} 

//Function made for personal debugging. Reports all the points in subtree of a given node.
void ReportSubtree(struct Treenode* node)
{
	if (node == NULL) 
        return; 
  
    // first recur on left subtree 
    ReportSubtree(node->left); 
  
    // then recur on right subtree 
    ReportSubtree(node->right); 
  
    // now deal with the node 
     if ((node->left) == NULL && (node->right)==NULL) 
        printf(" %d,%d || ",node->x,node->y); 
}

//Static variable to keep count of the number of points in given rectangular query range.
static int Total=0;

//Function used to search points in given rectangular query range and count total no.of points in given rectangular query range
void SearchQuery(Treenode* v,vector<pair<int,int>> &range)
{
	//if ν is a leaf then Report the point stored at ν if it lies in R.
	if(v->left==NULL && v->right==NULL)
	{
		if(v->x>=range[0].first && v->x<=range[1].first && v->y>=range[0].second && v->y<=range[1].second)
		{
			printf(" %d,%d ||",v->x,v->y);
			Total=Total+1;
		}
	}

	else 
	{
		//if region(lc(ν)) is fully contained in R then Report Subtree (lc(ν))
		if((v->left)->le>=range[0].first && (v->left)->ri<=range[1].first && (v->left)->bottom>=range[0].second && (v->left)->top<=range[1].second)
		{
			//printf("Fully Contained");
			ReportSubtree(v->left);
			Total = Total + (v->left)->count;
		}

		//if region(lc(ν)) intersects R then Search KD Tree (lc(ν), R)
		else if((v->x!=-1 && v->y==-1 && v->x>=range[0].first && v->x<=range[1].first) || (v->x==-1 && v->y!=-1 && v->y>=range[0].second && v->y<=range[1].second))
		{
			SearchQuery(v->left,range);
		}
		
		//if region(rc(ν)) is fully contained in Rvthen Report Subtree (rc(ν))		
		if((v->right)->le>=range[0].first && (v->right)->ri<=range[1].first && (v->right)->bottom>=range[0].second && (v->right)->top<=range[1].second)
		{
			//printf("Fully Contained");
			ReportSubtree(v->right);
			Total = Total + (v->right)->count;
		}

		//if region(rc(ν)) intersects R then Search KD Tree  (rc(ν), R)
		else if((v->x!=-1 && v->y==-1 && v->x>=range[0].first && v->x<=range[1].first) || (v->x==-1 && v->y!=-1 && v->y>=range[0].second && v->y<=range[1].second))
		{
			SearchQuery(v->right,range);
		}

	}
}



//Function Used for personal debugging. Not used in code.
void printPostorder(struct Treenode* node) 
{ 
    if (node == NULL) 
        return; 
  
    // first recur on left subtree 
    printPostorder(node->left); 
  
    // then recur on right subtree 
    printPostorder(node->right); 
  
    // now deal with the node 
    if ((node->left) == NULL && (node->right)==NULL) 
        printf("(%d,%d) count = %d || ",node->x,node->y,node->count); 
} 

int main()
{
	//Creating a vector of input points
	vector<pair <int,int>> p;
	int a[]={5,15,30,10,35,80,40,45,60,70,85,55,65};
	int b[]={40,60,30,120,100,20,35,45,33,43,34,110,70};
	for (int i=0; i<13; i++)
	{
		p.push_back( make_pair(a[i],b[i]) );
	}
	printf("\nGiven Points:\n");
	for(int i=0;i<p.size();i++)
	{
		printf(" %d,%d ||",p[i].first,p[i].second);	
	}
	//printf("%ld",p.size());


	//Building KD Tree
	int infinite = std::numeric_limits<int>::max();
	struct Treenode* head = BuildKdTree(p,0,-infinite,infinite,-infinite,infinite);
	//printPostorder(head); 

	//Calculating No. of nodes in each subtree and updating the count
	Updatecount(head);
	//printPostorder(head); 

	//Defining the rectangular query range
	vector<pair <int,int>> r;
	int ab[]={15,85};
	int cd[]={34,60};
	for (int i=0; i<4; i++)
	{
		r.push_back( make_pair(ab[i],cd[i]) );
	}
	printf("\n\nRectangular Query Range = (%d,%d)*(%d,%d)",r[0].first,r[0].second,r[1].first,r[1].second);

	//Searching points in given rectangular query range and count total no.of points in given rectangular query range
	printf("\n\nFollowing points lie in the given range\n");
	SearchQuery(head,r);
	printf("\n\nTotal number of points that lie in the given range (%d,%d) * (%d,%d) = %d\n",r[0].first,r[0].second,r[1].first,r[1].second,Total);
	
}
