#include <iostream>

using namespace std;

template <typename t,int value>
class BTree{
    struct BTreeNode
        {
            t *keys;
            int maxKeysNom;
            BTreeNode **Child;
            int CurrentKeysNumber;
            bool leaf;
            BTreeNode(int m)
            {
                maxKeysNom=m;
                keys=new t[maxKeysNom];
                Child=new BTreeNode*[value];
                CurrentKeysNumber=0;
                leaf=true;
                for(int i=0 ;i <maxKeysNom;i++ )
                    Child[i]=nullptr;
            }
            BTreeNode *Find(int val, BTreeNode *node1, int k, BTreeNode *node2)
            {
                if(leaf==true)
                {
                    int i =k;
                    while(!keys[i-1] )
                        i--;
                    while(keys[i-1]>val && i!=0)
                    {
                        keys[i]=keys[i-1];
                        i--;
                    }
                    keys[i]=val;
                    CurrentKeysNumber++;
                }
                else
                {
                    int i=0;
                    while(i<CurrentKeysNumber && val>keys[i])
                        i++;
                    Child[i]->Find(val,this,k,node2);
                }
                if(CurrentKeysNumber == k)
                {
                    if(this==node2)
                    {
                        BTreeNode *newnode=new BTreeNode(k);
                        newnode->leaf=false;
                        newnode->Child[0]=this;
                        newnode->Split(this,k);
                        return newnode;
                    }
                    else
                        node1->Split(this,k);
                }
                return node2;
            }
            void Split(BTreeNode *node,int k)
            {
                BTreeNode *newnode=new BTreeNode(k);
                int ir=0, m=(k-1)/2,gg=0;
                int n=node->CurrentKeysNumber;
                int c=node->keys[m];
                int v=(k/2)+1;
                int w=v;
                for(int i=m+1 ; i<n ; i++)
                {
                    newnode->keys[ir]=node->keys[i];
                    ir++;
                    node->CurrentKeysNumber--;
                    newnode->CurrentKeysNumber++;
                }
                if(node->leaf == false)
                {
                    for(int a=w ; a<=k ;a++)
                    {
                        newnode->Child[gg]=node->Child[a];
                        gg++;
                    }
                    newnode->leaf=node->leaf;
                }
                int h=k-1;
                while(Child[h] != node)
                {
                    Child[h+1]=Child[h];
                    h--;
                }
                Child[h+1]=newnode;
                int j=k-1;
                while(!keys[j-1] && j!=0)
                    j--;
                while(keys[j-1]> c && j!=0)
                {
                    keys[j]=keys[j-1];
                    j--;
                }
                keys[j]=c;
                CurrentKeysNumber++;
                node->CurrentKeysNumber--;
            }
            void printNodes(int i)
            {
                for(int index=0; index<CurrentKeysNumber;index++)
                    cout<<keys[index]<<" ";
                if(leaf==false)
                {
                    i++;
                    for(int j=0;j<=CurrentKeysNumber;j++)
                    {
                        cout<<endl;
                        cout<<" "<<"";
                        Child[j]->printNodes(i);


                    }
                }
            }
        };

public:
    BTreeNode *root;
    int order;
    bool InsertAgain=false;
    BTree()
    {
        root=nullptr;
        this->order=value;
    }
    void Insert(t val)
    {
        if(root == nullptr)
        {
            BTreeNode *newnode=new BTreeNode(order);
            root=newnode;
            root->leaf=true;
            root->keys[0]=val;
            root->CurrentKeysNumber=1;
        }
        else
            root=root->Find(val,root,order,root);
    }
    void Print()
    {
        root->printNodes(0);
    }

};
int main()
{
    BTree<char,5> t;
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');
    t.Print();
    return 0;
}
