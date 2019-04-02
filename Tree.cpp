#include <iostream>
#include "Tree.hpp"
#include <exception>
using namespace std;
using namespace ariel;


	Tree::Tree()
{
    tSize = 0;
    tRoot = NULL;
}

Tree::~Tree()
{
    
}

    int Tree::insert(int i){
        // tree is empty
        if(tRoot == NULL){
            treeNode* Node = new treeNode();
            Node->data = i;
            Node->leftSon = NULL;
            Node->rightSon = NULL;
            Node->tParent = NULL;
            tRoot = Node;
            tSize++;
        }
        else{   // checks if key already exists in the tree, if not, add the new key to the left/right side.
            treeNode* Node = search(tRoot, i);  
            if(i == Node->data)
                throw "Key is already in the tree";

            else if(i < Node->data){
                treeNode* newNode = new treeNode();
                newNode->data = i;
                newNode->leftSon = NULL;
                newNode->rightSon = NULL;

                newNode->tParent = Node;
                Node->leftSon = newNode;
                tSize++;
            }
            else{
                treeNode* newNode = new treeNode();
                newNode->data = i;
                newNode->leftSon = NULL;
                newNode->rightSon = NULL;

                newNode->tParent = Node;
                Node->rightSon = newNode;
                tSize++;
            }

        }
        return 0;
    }

     int Tree::remove(int i){
        treeNode* Node = search(tRoot, i);

            if(Node->rightSon != NULL){
                treeNode* newNode = search(Node->rightSon, i);
                int temp = newNode->data;
                newNode->data = i;
                Node->data = temp;

                if(newNode->rightSon == NULL && newNode->leftSon == NULL){
                    newNode->tParent->leftSon = NULL;
                    delete(newNode);
                    tSize--;
                }

                else if(newNode->leftSon == NULL){
                    newNode->tParent->leftSon = newNode->rightSon;
                    newNode->rightSon->tParent = newNode->tParent;
                    newNode->tParent = NULL;
                    delete(newNode);
                    tSize--;
                }
            }

            else{
                treeNode* newNode = search(Node->leftSon, i);
                int temp = newNode->data;
                newNode->data = i;
                Node->data = temp;

                if(newNode->rightSon == NULL && newNode->leftSon == NULL){
                    newNode->tParent->rightSon = NULL;
                    delete(newNode);
                    tSize--;
                }
                  else if(newNode->rightSon == NULL){
                    newNode->tParent->rightSon = newNode->leftSon;
                    newNode->leftSon->tParent = newNode->tParent;
                    newNode->tParent = NULL;
                    delete(newNode);
                    tSize--;
                }
            }
            return i;
        }
        

     int Tree::size(){
        return tSize;
    }

     bool Tree::contains(int i){
        if(tRoot == NULL) return false;

        treeNode* Node = search(tRoot, i);
        if(Node->data == i) return true;
        return false;
    }

     int Tree::root(){
        return tRoot->data;
    }

     int Tree::parent(int i){
        treeNode* Node = search(tRoot,i);
        if(Node->tParent == NULL) {       
            throw "this node is the root, it doesnt have a parent";                    
        }
        else return Node->tParent->data;       // else return the data of his parent
    }

     int Tree::left(int i){
        treeNode* Node = search(tRoot, i);
        if(Node->data == i){
            if(Node->leftSon != NULL) return Node->leftSon->data;
            else 
                throw "left son doesnt exist"; 
        }   
        return i;
    }

     int Tree::right(int i){
             treeNode* Node = search(tRoot, i);
        if(Node->data == i){
            if(Node->rightSon != NULL) return Node->rightSon->data;
            else 
                throw "right son doesnt exist"; 
        }
        return i;
    }

     void Tree::print(){
       print(this->tRoot);
    }

    void Tree::print(treeNode* Node){
        if(Node == NULL) return;

        print(Node->leftSon);
        cout<< Node->data<< ", " <<endl;

        print(Node->rightSon);
    }
    

    treeNode* Tree::search(treeNode* root, int key){
    
    // Key already exist on tree
    if (root->data == key) 
        return root;

    // Key is greater than root's key 
    if (root->data < key){
        if(root->rightSon == NULL) return root;
        else 
            return search(root->rightSon, key); 
    }
  
    // Key is smaller than root's key 
    if(root->leftSon == NULL){
        return root;
    }
    else
     return search(root->leftSon, key);
    }
