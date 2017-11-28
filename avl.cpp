#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;

struct avl_node
{
    int data;
    struct avl_node *left;
    struct avl_node *right;
}*root;

class binaryTree 
{
	public:
		binaryTree(){root=NULL;}
		virtual avl_node* insert(avl_node *, int ) = 0;
		virtual void display(avl_node *, int) = 0;
		void inorder(avl_node *);
		void preorder(avl_node *);
		void postorder(avl_node *);
		
}

class avlTree: public binaryTree
{
    public:
        int height(avl_node *);
        int diff(avl_node *);
        avl_node *rr_rotation(avl_node *);
        avl_node *ll_rotation(avl_node *);
        avl_node *lr_rotation(avl_node *);
        avl_node *rl_rotation(avl_node *);
        avl_node* balance(avl_node *);
        avl_node* insert(avl_node *, int );
        void display(avl_node *, int);
        void PrintFile();
        void check_draw(avl_node *temp, avl_node *parent);
        avlTree()
        {
            root = NULL;
        }
};
 
int main()
{
    int choice, item;
    avlTree avl;
    while (1)
    {
        cout<<"\n---------------------"<<endl;
        cout<<"AVL Tree"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Insert Element into the tree"<<endl;
        cout<<"2.Display AVL Tree in terminal"<<endl;
        cout<<"3.Display AVL Tree picture"<<endl;
        cout<<"4.InOrder traversal"<<endl;
        cout<<"5.PreOrder traversal"<<endl;
        cout<<"6.PostOrder traversal"<<endl;
        cout<<"7.Exit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter value to be inserted: ";
            cin>>item;
            root = avl.insert(root, item);
            break;
        case 2:
            if (root == NULL)
            {
                cout<<"Tree is Empty"<<endl;
                continue;
            }
            cout<<"Balanced AVL Tree:"<<endl;
            avl.display(root, 1);
            break;
        case 3:
        	if (root == NULL)
            {
                cout<<"Tree is Empty"<<endl;
                continue;
            }
        	avl.PrintFile();
            break;
        case 4:
            cout<<"Inorder Traversal:"<<endl;
            avl.inorder(root);
            cout<<endl;
            break;
        case 5:
            cout<<"Preorder Traversal:"<<endl;
            avl.preorder(root);
            cout<<endl;
            break;
        case 6:
            cout<<"Postorder Traversal:"<<endl;
            avl.postorder(root);
            cout<<endl;
            break;
        case 7:
            exit(1);    
            break;
        default:
            cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
}
 
int avlTree::height(avl_node *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
 
int avlTree::diff(avl_node *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}
 
avl_node *avlTree::rr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

avl_node *avlTree::ll_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}
 
avl_node *avlTree::lr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}
 
avl_node *avlTree::rl_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}
 
avl_node *avlTree::balance(avl_node *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}
 
avl_node *avlTree::insert(avl_node *root, int value)
{
    if (root == NULL)
    {
        root = new avl_node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (value < root->data)
    {
        root->left = insert(root->left, value);
        root = balance (root);
    }
    else if (value >= root->data)
    {
        root->right = insert(root->right, value);
        root = balance (root);
    }
    return root;
}
 
void avlTree::display(avl_node *ptr, int level)
{
    int i;
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
        cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->data;
        display(ptr->left, level + 1);
    }
}

void avlTree::PrintFile()
{
			ofstream fout("tree.dot");
        	if(!fout.is_open()) { 
					cout << "File not opened"<< endl;
        	}
        	fout << "digraph HelloWorld {"<<endl;
        	cout<<root->right<<" "<<root<<endl;
        	fout.close();
        	check_draw(root->left, root);
        	check_draw(root->right, root);
        	ofstream foutr("tree.dot", ios_base::app);
        	foutr<<"}"<<endl;
        	foutr.close();
        	system("dot -Tpng -o fsm.png tree.dot");
			system("start fsm.png");
}
	
void avlTree::check_draw(avl_node *node_c, avl_node *node_p)
{
			ofstream fout("tree.dot", ios_base::app);
			if(!fout.is_open()) { 
					cout << "File not opened"<< endl;
        	}
			if(node_c != NULL && node_p !=NULL){
				fout <<"\t"<<node_p->data<<"->"<<node_c->data<<";"<<endl;
				fout.close();
			}
			else {
				fout.close();
		    	return;
		    }
		    if (node_c->right == NULL && node_c->left == NULL) {
		    	 return;
			}
			else if(node_c->right == NULL && node_c->left != NULL){
				check_draw(node_c->left, node_c);
			}
			else if(node_c->right != NULL && node_c->left == NULL){
				check_draw(node_c->right, node_c);
			}
			else {
				check_draw(node_c->left, node_c);
				check_draw(node_c->right, node_c);
					
			}
		    fout.close();
}

void avlTree::inorder(avl_node *tree)
{
    if (tree == NULL)
        return;
    inorder (tree->left);
    cout<<tree->data<<"  ";
    inorder (tree->right);
}

void avlTree::preorder(avl_node *tree)
{
    if (tree == NULL)
        return;
    cout<<tree->data<<"  ";
    preorder (tree->left);
    preorder (tree->right);
 
}
 
void avlTree::postorder(avl_node *tree)
{
    if (tree == NULL)
        return;
    postorder ( tree ->left );
    postorder ( tree ->right );
    cout<<tree->data<<"  ";
}
