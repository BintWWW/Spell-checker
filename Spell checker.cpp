// Bintao Wang
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int found=0;
class node
{
public:
    char info;
    string Word;
    class node* ptrs[256];
    node()
    {
        for(int i=0; i<256; i++)
        {
            ptrs[i]=NULL;
        }
        info=NULL;
        Word="";
    }
};
void insertword(string word,int pos,class node * root)
{
    if(word.length()==pos)
    {
        root->Word=word;
        return;
    }
    if( root-> ptrs[word[pos]]==NULL )
    {
        node *newnode;
        newnode= new node;
        newnode->info=word[pos];
        root->ptrs[word[pos]]=newnode;
        insertword(word,pos+1,root->ptrs[word[pos]]);
    }
    else
        insertword(word,pos+1,root->ptrs[word[pos]]);
}

void find(string key,int pos, class node * root)
{
    if((key != root->Word) && (root->ptrs[key[pos]] != NULL))
        find(key,pos+1,root->ptrs[key[pos]]);
    else if(key==root->Word)
    {
        cout<<"The spelling of the word '"<<root->Word<<"' is correct"<<endl;
        found=1;
    }
}

void printall(class node * root)
{
    for(int i=0; i<256; i++)
        if(root->ptrs[i]!=NULL)
        {
            printall(root->ptrs[i]);
        }
    if(root->Word != "")
        cout<<" -> "<<root->Word<<endl;
}

void suggest(string key,int pos, class node * root)
{
    if((key != root->Word) && (root->ptrs[key[pos]] != NULL))
    {
        suggest(key,pos+1,root->ptrs[key[pos]]);
    }
    else
    {
        printall(root);
    }
}

int main()
{
    ifstream in("dic.txt");
    string word,current="",key;
    node *root;
    root = new node;
    while(in)
    {
        in>>word;
        insertword(word,0,root);
    }
    in.close();
    cout<<endl<<"Trie Construction Successful"<<endl;
    cout << "dic.txt opened"<< endl;
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    cout << "|                                           |" << endl;
    cout << "+        * Spell checker (A~Z) *            +" << endl;
    cout << "|                                           |" << endl;
    cout << "+  Type 'QUIT' to close this spell checker. +" << endl;
    cout << "|                                           |" << endl;
    cout << "+    Type 'HELP' if you need any help.      +" << endl;
    cout << "|                                           |" << endl;
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    cout << endl;
    cout << "=====================================================" << endl;
    cout<<"Enter the word to be searched for : ";
    cin>>key;
    while(key != "QUIT")
    {
        cout << "-----------------------------------------------------" << endl;
        if(key == "HELP")
        {
            cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
            cout << "|                                           |" << endl;
            cout << "+  Note: When you are typing a word,        +" << endl;
            cout << "|    make sure that all of the characters   |" << endl;
            cout << "+    are not capitalized, except 'I'        +" << endl;
            cout << "|    or the spell checker will say you      |" << endl;
            cout << "+    are spelling wrong.                    +" << endl;
            cout << "|                                           |" << endl;
            cout << "+    And make sure you don't type           +" << endl;
            cout << "|    punctuations, the system can't read    |" << endl;
            cout << "+    punctuations.                          +" << endl;
            cout << "|                                           |" << endl;
            cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
            cout << "=====================================================" << endl;
            cout<<"Enter the word to be searched for : ";
            cin>>key;
        }
        else
        {
            find(key,0,root);
            if(!found)
            {
                cout<<endl<<"The spelling is incorrect, Possible suggestions are :"<<endl;
                suggest(key,0,root);
            }
            cout << "=====================================================" << endl;
            cout<<"Enter the word to be searched for : ";
            cin>>key;
        }

    }
    cout << "Goodbye. Thank you for using!!";
    return 0;
}
/*
using namespace std;


int main()
{
    cout << "***************************************" << endl;
    cout << "*Help: This spell check has   *" << endl;
    cout << "" << endl;





    return 0;
}*/
