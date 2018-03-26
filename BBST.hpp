#include <algorithm>

#pragma once


template<typename T> class AVL{
private:
    
    struct node{
		int height;
        T val;
        node *left, *right;
        node(T v){
			left=right=NULL;
			val=v;
			height=1;
			}
		static int getheight(node* r){
            if(r==NULL) return 0;
            return r->height;
		}
		int getbalancefactor(){
            return getheight(left)-getheight(right);
            return getheight(left)-getheight(right);
	}
    };
    int sizel;
    node* root;
    node* &minnode(node* &r){
		if(r->left==NULL) return r;
		return minnode(r->left);
	}
    node* leftrotate(node* r){
        node* rch=r->right;
        r->right=rch->left;
        rch->left=r;
        r=rch;
        r->left->height=std::max(node::getheight(r->left->left), node::getheight(r->left->right))+1;
        r->height=std::max(node::getheight(r->left), node::getheight(r->right))+1;
        return r;
    }
    
    node* rightrotate(node* r){
        node* rch=r->left;
        r->left=rch->right;
        rch->right=r;
        r=rch;
        r->right->height=std::max(node::getheight(r->right->left), node::getheight(r->right->right))+1;
        r->height=std::max(node::getheight(r->left), node::getheight(r->right))+1;
        return r;
    }
    
    void deleteall(node* r){
        if(r==NULL)return;
        deleteall(r->left);deleteall(r->right);
        delete r;
    }
    
    void insert(node* &r, T val){
		if(r==NULL){
				r=new node(val);
				sizel++;
				return;
		}
		if(val<r->val) insert(r->left, val);
		else if(val>r->val) insert(r->right, val);
		
		r->height=std::max(node::getheight(r->left), node::getheight(r->right))+1;	
		
		int balance=r->getbalancefactor();
		
		if(balance>1 && r->left->val>val) //LL
				r=rightrotate(r);
		else if(balance>1 && r->left->val<val){ //LR
				r->left=leftrotate(r->left);
				r=rightrotate(r);
		}
		else if(balance<-1 && r->right->val<val) //RR
				r=leftrotate(r);
		else if(balance<-1 && r->right->val>val){//RL
				r->right=rightrotate(r->right);
				r=leftrotate(r);
		}	
		return;
    }
    
    void erase(node* &r, T val){
		if(r==NULL) return;
		if(val<r->val) erase(r->left, val);
		else if(val>r->val) erase(r->right, val);
		else{
			sizel--;
			if(r->left==NULL && r->right==NULL){
				delete r;
				r=NULL;
			}
			else if(r->left==NULL){
				node* del=r;
				r=r->right;
				delete del;
			}
			else if(r->right==NULL){
				node* del=r;
				r=r->left;
				delete del;
			}
			else{
				node* &todelete=minnode(r->right);
				r->val=todelete->val;
				node* del=todelete;
				todelete=todelete->right;
				delete del; 
			}
		
		}
		if(r==NULL) return;
		r->height=std::max(node::getheight(r->left), node::getheight(r->right))+1;
		int balance=r->getbalancefactor();
		if(balance>1 && r->left->getbalancefactor()>=0) //LL
			r=rightrotate(r);
		else if(balance>1 && r->left->getbalancefactor()<0){//LR
			r->left=leftrotate(r->left);
			r=rightrotate(r);
		}
		else if(balance<-1 && r->right->getbalancefactor()<0) //RR
			r=leftrotate(r);
		else if(balance<-1 && r->right->getbalancefactor()>=0){ //RL
			r->right=rightrotate(r->right);
			r=leftrotate(r);
		}
		return;
	}
	
	
	bool find(node* r, T val){
		if(val==r->val) return true;
		else if(val<r->val) return find(r->left, val);
		else if(val>r->val) return find(r->right, val);
		return false;
	}
public:
    AVL(){
        root=NULL;
        sizel=0;
    }
    ~AVL(){
        deleteall(root);
    }
    void insert(T val){
		insert(root, val);
    }
    void inordine(){
        inordine(root);
    }
    bool find(T val){
		return find(root, val);
	}
	void erase(T val){
		erase(root, val);
		return;
	}
	int size(){
		return sizel;
	}
};
