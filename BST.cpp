#include <iostream>
#include <stack>


using namespace std;

class Node{
    public:

    int value;
    Node * left;
    Node * right;

    Node(int val){
        value = val;
    }

};

class BinarySearchTree{
    int numberOfNodes =0;
    public:
    Node * root;
    BinarySearchTree(int value){
        root = new Node(value);
        numberOfNodes++;
    }

    void insert(int value){
        bool inserted = false;
        Node * curr = root;

        while(!inserted){
            if(value < curr->value){
                if(curr->left != nullptr){
                    curr = curr->left;
                }
                else{
                    curr->left = new Node(value);
                    inserted = true;
                }
            }
            else if(value > curr->value){
                if(curr->right != nullptr){
                    curr = curr->right;
                }
                else{
                    curr->right = new Node(value);
                    inserted = true;
                }
            }
        }
        numberOfNodes ++;
    }

    void InOrderTraversal(Node * current){

        if(current == nullptr){
            return;
        }
        InOrderTraversal(current->left);
        cout<< current->value<<" ";
        InOrderTraversal(current->right);

    }

    void PostOrderTraversal(Node * current){

        if(current == nullptr){
            return;
        }
        PostOrderTraversal(current->left);
        PostOrderTraversal(current->right);
        cout<<current->value<<" ";

    }

    void PreOrderTraversal(Node * current){
        if(current == nullptr){
            return;
        }
        cout<< current->value<<" ";
        PreOrderTraversal(current->left);
        PreOrderTraversal(current->right);
    }

    Node * findNode(int value, Node * root){
        Node * curr = root;
        if(curr->value == value){
            return curr;
        }
        else if (value < curr->value){
            if(curr->left != nullptr){
                return findNode(value,curr->left);
            }
            else{
                return nullptr;
            }
        }
        else{
            if(curr -> right != nullptr){
                return findNode(value,curr->right);
            }
            else{
                return nullptr;
            }
        }
    }

    Node * findParent(int value, Node * root){
        Node * curr = root;
        if(value < curr->value){
            if(value == curr->left->value){
                return curr;
            }
            else{
                return findParent(value,curr->left);
            }
        }
        else if(value > curr->value){
            if(value == curr->right->value){
                return curr;
            }
            else{
                return findParent(value,curr->right);
            }
        }
        return 0;

    }

    Node * findMax(Node * root){
        Node * curr = root;

        while(curr->right != nullptr){
            curr = curr->right;
        }
        return curr;
    }

    Node * findMin(Node * root){
        Node * curr = root;

        while(curr->left != nullptr){
            curr = curr->left;
        }
        return curr;
    }

    void deleteNode (int value){
        
        Node * toDelete = findNode(value,root);
        Node * parent = findParent(toDelete->value,root);
        if(toDelete == nullptr){
            cout<<"The value does not exist in the tree!"<<endl;
        }
        else{
            // Given that the node we want to delete is a leaf i.e does not have children
            if(toDelete->right == nullptr && toDelete->left == nullptr){
                if(parent->left->value == toDelete->value){
                    parent->left = nullptr;
                    delete toDelete;
                }
                else{
                    parent->right = nullptr;
                    delete toDelete;
                }
            }
            //Node has two children, set Node to the min of the subtree(Node -> right) and delete the min of subtree
            else if(toDelete->left != nullptr && toDelete->right != nullptr){
                Node * temp = findMin(toDelete->right);
                int tempVal = temp->value;
                deleteNode(tempVal);
                toDelete->value = tempVal;
               
            }
             // Node has one child
            else{
                if(toDelete->left != nullptr){
                    //Checking whether we are on the left or right of the parent
                    if(parent->left->value == toDelete->value){
                        parent->left = toDelete->left;
                        delete toDelete;
                    }
                    else{
                        parent->right = toDelete->left;
                        delete toDelete;
                    }
                }
                else{
                    if(parent->left->value == toDelete->value){
                        parent->left = toDelete->right;
                        delete toDelete;
                    }
                   else{
                        parent->right = toDelete->right;
                        delete toDelete;
                    }

                }
            }
        }
    }

};

int main(){

    BinarySearchTree  bst =  BinarySearchTree(5);

    bst.insert(3);
    bst.insert(8);
    bst.insert(7);
    bst.insert(10);
    bst.insert(2);
    bst.InOrderTraversal(bst.root);
    cout<<endl;
    bst.PreOrderTraversal(bst.root);
    cout<<endl;
    bst.PostOrderTraversal(bst.root);
    cout<<endl;
    // cout<<bst.findMin(bst.root)->value<<endl;
    bst.deleteNode(3);
    bst.InOrderTraversal(bst.root);
    cout<<endl;




    return 0;
}