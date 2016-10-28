
// http://stackoverflow.com/questions/36389371/why-the-words-do-not-contain-in-my-dictionary-c-trie
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Trie 
{
private:
	class Node {
	public:
		Node* next[26];
		bool isWord;  //216 bytes minimum!
	
		Node()
		{ 
			next[26] = {};
			isWord = false; 
		}
	};

	Node* root;

public:

	Trie() 
	{
	  root = new Node();
	}
	
	~Trie()
	{
		delete root;
	}
	
	void add(const string& line) 
	{
		Node* node  = root;

        for(int i = 0; i < line.size(); i++){
            char x = line[i];
            if(node->next[x-'a'] == nullptr)                    
                node->next[x-'a'] = new Node();
            node = node->next[x-'a'];
        }

        node->isWord = true;
	}

	bool isWord(const string& word) 
	{  
		Node* node = root;

        for(int i = 0; i < word.size(); i++){
            char x = word[i];
            if(node->next[x-'a'] == nullptr)
                return false;
            else
                node = node->next[x-'a'];
        }

        return node->isWord;
		
	}

	// return true if the dictionary contains any words that start with these letters
	bool startsWith(const string& prefix) 
	{  
		Node* node = root;

        for(int i = 0; i < prefix.size(); i++){
            char x = prefix[i];
            if(node->next[x-'a'] == nullptr)
                return false;
            else
                node = node->next[x-'a'];
        }
        return true; 
		
	}
	
	/*
	void traverse(string const& prefix, Node const& n) 
	{
    if (n.isWord)
        cout<<prefix;

    for (int i = 0; i < 26; ++i)
        if (n.next[i])
            traverse(prefix + ('a' + i), *n.next[i]);
	}
	*/
	
	friend bool hasChild(Node* parent)
	{
		for(int i = 0; i < 26; i++)
		{
			if(parent->next[i] != nullptr)
			{
				return true;
			}
		}
		return false;
	}
	
	friend void printNode(Node* root)
	{
			for(int i = 0; i < 26; i++)
			{
				Node* parent = root->next[i];
				if(parent!= nullptr)
				{	
					cout << "[" << char(i+'a') << "]-> ";
					

					for(int j = 0; j < 26; j++)
					{
						Node* child = parent->next[j];
						if(child != nullptr)
						{	
							cout << "[" << char(j+'a') << "]-> ";
							printNode(child);
						}
			
					}
				}
			}
	}
		
	
	friend ostream& operator<<(ostream& s, const Trie& trie) 
	{
	    s << "\n\t{ \n";
	    for(int i= 0; i < 26; i++)
	    {
        	if(trie.root->next[i] != nullptr)
        	{
        		cout << "\t\troot-> ";
        		cout << "[" << char(i+'a') << "]-> ";
        		printNode(trie.root->next[i]);
        		cout << " end\n";
        	}
        
	    }
		s << "\n\t}";
		return s;
	}
	
};

void openTestFile()
{
	Trie theDictTrie;
	string inWord;
	ifstream myfile ("dict.txt");
	string::size_type sz;
    string word;
    string line;
    int answer = 0;
    int wordCount = 0;
   
    if (myfile.is_open())
	{
    	while  (getline(myfile, line))
    	{
    		word = line.substr(0, line.find_first_of(" "));
    		theDictTrie.add(word);
    		wordCount++;
    	}
    	cout << "Word Count is = " << wordCount << " \n";
    	myfile.close();
	}
	else
    {
        cout << "Unable to open file";
    }
	

	do{
		cout << "-----------------------------------------------------------\n";
		cout << "What do you want to do to our Dictionary? \n";
		cout << "1: Search for a word \n";
		cout << "2: Determine if a word starts with letters \n";
		cout << "3: Add Word to Dictionary \n";
		cout << "4: Finished End Program \n";
		cout << "-----------------------------------------------------------\n";
		cin >> answer;
		if(answer == 1)
		{
			cout << "Type in a word you want to search for ... \n";
			cin >> inWord;
			if(theDictTrie.isWord(inWord))
			{
				cout << inWord << " is found in the Dictionary!!!\n";
			}
			else
			{
				cout << inWord << " is NOT found in the Dictionary!!!\n";
			}
		}
		else if(answer == 2)
		{
			cout << "Determine if a word starts with the letters ... \n";
			cin >> inWord;
			if(theDictTrie.startsWith(inWord))
			{
				cout << "Words found that do start with " << inWord << " in the Dictionary!!!\n";
			}
			else
			{
				cout << "Words NOT found that start with " << inWord << " in the Dictionary!!!\n";
			}
		}
		else if(answer == 3)
		{
			cout << "Type in a word you want to add to the Dictionary ... \n";
			cin >> inWord;
			theDictTrie.add(inWord);
			cout << inWord << " was added to the Dictionary!!!\n";
		}
		else
		{
			cout << "Num words in Dictionary is " << wordCount << "\n";
		//	cout << "Print of Trie is: \n" << theDictTrie << "\n";
		}
	}while(answer != 4);
}

void firstTest()
{
	Trie theDictTrie;
	string inWord;
	int answer = 0;
    int wordCount = 0;

	do{
		cout << "-----------------------------------------------------------\n";
		cout << "What do you want to do to our Dictionary? \n";
		cout << "1: Search for a word \n";
		cout << "2: Determine if a word starts with letters \n";
		cout << "3: Add Word to Dictionary \n";
		cout << "4: Finished End Program \n";
		cout << "-----------------------------------------------------------\n";
		cin >> answer;
		if(answer == 1)
		{
			cout << "Currently there are " << wordCount << " words in the Dictionary \n";
			cout << "Type in a word you want to search for ... \n";
			cin >> inWord;
			if(theDictTrie.isWord(inWord))
			{
				cout << inWord << " is found in the Dictionary!!!\n";
			}
			else
			{
				cout << inWord << " is NOT found in the Dictionary!!!\n";
			}
		}
		else if(answer == 2)
		{
			cout << "Currently there are " << wordCount << " words in the Dictionary \n";
			cout << "Determine if a word starts with the letters ... \n";
			cin >> inWord;
			if(theDictTrie.startsWith(inWord))
			{
				cout << "Words found that do start with " << inWord << " in the Dictionary!!!\n";
			}
			else
			{
				cout << "Words NOT found that start with " << inWord << " in the Dictionary!!!\n";
			}
		}
		else if(answer == 3)
		{
			cout << "Currently there are " << wordCount << " words in the Dictionary \n";
			cout << "Type in a word you want to add to the Dictionary ... \n";
			cin >> inWord;
			theDictTrie.add(inWord);
			wordCount++;
			cout << inWord << " was added to the Dictionary!!!\n";
			cout << "Currently there are " << wordCount << " words in the Dictionary \n";
		}
		else
		{
			cout << "Num words in Dictionary is " << wordCount << "\n";
			cout << "Print of Trie is: \n" << theDictTrie << "\n";
		}
	}while(answer != 4);

}
int main() 
{
	openTestFile();
//	firstTest();

  return 0;
}
