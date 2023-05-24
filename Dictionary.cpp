#include<iostream>
#include<string>
#include<iomanip>


using namespace std;

class treeNode
{
private:
	    treeNode *left,*right;
	    string word,meaning,description;
public:
	    treeNode(string w,string m, string d);
		void setData(string w,string m, string d);
		string getWord();
		string getMeaning();
		string getDescription();
		void DisplayWordMeaning();
		void setLeft(treeNode *);
		treeNode* getLeft();
		void setRight(treeNode *);
		treeNode *getRight();
};

 
unsigned int DJBHash(string str);
treeNode* FindMin(treeNode * T);
bool Find(treeNode* root, string wrd );
void Edit(treeNode* root, string wrd , string newWrd,  string mng, string des);
void insert(treeNode* root, string wrd , string mng, string des);
void printDictionary(treeNode* root);
treeNode* Delete(treeNode* root, string wrd);
void DeleteDictionary(treeNode*);

treeNode::treeNode(string w,string m, string d)
{
	word = w;
	meaning = m;
	description = d;
	left = NULL;
	right = NULL;
}

void treeNode::setData(string w,string m, string d)
{
	word = w;
	meaning = m;
	description = d;
}
void treeNode::DisplayWordMeaning()
{
	cout << "Word        : "  << word << "\n" << "Meaning     : "  << meaning << "\n" << "Description : "  << description << endl ;
	cout << "_____________________________________" << endl;
}
string treeNode::getWord()
{
	return word;
}
string treeNode::getMeaning()
{
	return meaning;
}
string treeNode::getDescription()
{
	return description;
}
void treeNode::setLeft(treeNode *l)
{
	left = l;
}
void treeNode::setRight(treeNode *r)
{
	right = r;
}
treeNode* treeNode::getRight()
{
	return right;
}
treeNode* treeNode::getLeft()
{
	return left;
}

unsigned int DJBHash(string str)
{
   unsigned int hash = 5381;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = ((hash << 5) + hash) + str[i];
   }
   return hash;
}


treeNode* FindMin(treeNode * T)
{
	if(T == NULL)
		return NULL;
	else if(T->getLeft() == NULL)
		return T;
	else 
		return FindMin(T->getLeft());
}

bool Find(treeNode* root, string wrd )
{
	if(root != NULL)
	{
		
		if(Find(root->getLeft(), wrd ) == true)	 
			return true;
		if(Find(root->getRight(), wrd ) == true) 
			return true;
		if(wrd == root->getWord())
		{
			root->DisplayWordMeaning();	
			return true;
		}
		else
			return false;
		
	}
}

void Edit(treeNode* root, string wrd , string newWrd,  string mng, string des)
{
	if(root != NULL)
	{
		Edit(root->getLeft(),wrd,newWrd,mng,des);
		Edit(root->getRight(),wrd,newWrd,mng,des);
		if(wrd == root->getWord())
		{
     		// edit here
			root->setData(newWrd,mng,des);
		}
	}
}

void insert(treeNode* root, string wrd , string mng, string des)
{
	unsigned int d = 0 ;
	treeNode* Newnode = new treeNode(wrd, mng, des);
	treeNode *p,*q;
	p = q = root;
	d = DJBHash(wrd);
	while(d != DJBHash(p->getWord()) && q != NULL)
	{
		p = q;
		if(d < DJBHash(p->getWord()))
		{
			q = p->getLeft();
		}
		else
		{
			q = p->getRight();
		}
	
	}
		if(d == DJBHash(p->getWord()))
		{
			cout << endl << "dublicate value :" << p->getWord() << endl;
			 
		}
		else if(d < DJBHash(p->getWord()))
		{
			p->setLeft(Newnode);
		}
		else if(d > DJBHash(p->getWord()))
		{
			p->setRight(Newnode);
		}
}

void printDictionary(treeNode* root)
{
	if(root != NULL)
	{
		root->DisplayWordMeaning();
		printDictionary(root->getLeft());
		printDictionary(root->getRight());
	}
	
}

void DeleteDictionary(treeNode* root)
{
	if(root != NULL)
	{
		DeleteDictionary(root->getLeft());
		DeleteDictionary(root->getRight());
		delete root;
	}
}
treeNode* Delete(treeNode* root, string wrd)
{
	treeNode* tmpCell;
    if(root == NULL)
	{
		cout << "Element not found" << endl;
		return NULL;
	}
	else if(DJBHash(wrd) < DJBHash(root->getWord()))  
		root->setLeft(Delete(root->getLeft(),wrd));     
	else if(DJBHash(wrd) > DJBHash(root->getWord()))       
		root->setRight(Delete(root->getRight(),wrd));

	else if(root->getLeft() && root->getRight())          
	{
		tmpCell = FindMin(root->getRight());
		root->setData(tmpCell->getWord(),tmpCell->getMeaning(),tmpCell->getDescription());
		root->setRight(Delete(root->getRight(),wrd));
	}
	else												    
	{
		tmpCell = root;
		if(root->getLeft() == NULL)
			root = root->getRight();
		else if(root->getRight() == NULL)
			root = root->getLeft();
		delete tmpCell;
	}

	return root;
}





int main()
{
	string key , key2, key3, key4;
	string arrayW[] = {"apple","astute","bamboo","brisk","cascade","dormant","eclipse","0"};
	string arrayM[] = {" a round fruit with red or green skin and a white interior",
	"ability to accurately assess situations or people and turn this to one's advantage",
	"a tall, fast-growing grass plant",
	"quick, energetic, and active",
	"a waterfall, especially one of considerable size",
	" in a state of rest or inactivity, especially during a period of low activity"
	,"an obscuring of the light from one celestial body by the passage of another between it and the observer or between it and its source of illumination",
	"0"};
	string arrayD[] = {"adjective","noun","adjective","noun","noun","abberivation","noun","0"};
	treeNode *tmp;
	treeNode *root = new treeNode(arrayW[0],arrayM[0],arrayD[0]);
	for(int i=1 ; arrayW[i]!= "0" ; i++)
	{
		insert(root,arrayW[i],arrayM[i],arrayD[i]);
	}
	do
	{
		cout << endl;
		cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++ DICTIONARY ++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
		cout<<"Made by:\n21K-3563\n21K-3626\n21K-3577\n";
		cout<<"Menu"<<endl;
		cout << "Press i to insert " << endl; 
	    cout << "      e to edit " << endl; 
		cout << "      d to delete" << endl;
		cout << "      s to show dictionary " << endl; 
		cout << "      f to find word" << endl;
		cout << "      exit to edn program" << endl;
		//cin >> key;
		getline(cin,key);
		if(key == "e")
		{
			string m,d;
			cout << "Enter word to replace :    ";
			getline( cin,key);
			cout << "Enter word to replace with :    ";
			getline( cin,key2);
			cout << "Enter meaning :    ";
			getline( cin,m);
			cout << "Enter description :    ";
			getline( cin,d);
			Edit(root, key , key2,m, d);
		}
		else if(key == "i")
		{
			cout << "Enter new word :    ";
			getline( cin,key2);
			cout << "Enter new Meaning :    ";
			getline( cin,key3);
			cout << "enter new Description :    ";
			getline( cin,key4);
			insert(root,key2,key3,key4);
		}
		else if(key == "d")
		{
			cout << "Enter word To delete :    ";
			getline(cin,key2);
			if((root = Delete(root,key2)) != NULL)
				cout << "Successfully deleted : " << key2 << endl; 
		}
		else if(key == "s")
		{
			
			printDictionary(root);
		}
		else if(key == "f")
		{
			getline(cin, key2);
			if(!Find(root, key2 ))
				cout << key2 << " not found" << endl ;
		}

	}while(key != "exit");
	DeleteDictionary(root);
	return 0;
}