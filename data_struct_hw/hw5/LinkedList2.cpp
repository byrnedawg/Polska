#include <iostream>
#include <fstream>
#include <string>

using namespace std;
									 
class LinkedList2 {
private:
	class Node {
	public:
    int val;
		Node* next;
		Node(int v, Node* n) : val(v), next(n) {}
	};
	Node* head;
	Node* tail;
	int count;
public:
	LinkedList2() : head(nullptr), tail(nullptr) 
	{
		count = 0;
	}

	void addEnd(int v) 
	{
		if (head == nullptr) {
			head = new Node(v, nullptr);
			tail = head;
			cout << "\n The tail is pointing to " << tail -> val << "\n";
		}
		else
		{
			tail -> next = new Node(v, nullptr);
			tail = tail->next;
			cout << "\n The tail is pointing to " << tail -> val << "\n";
		}
		
		count++;
	}
	
	void addStart(int v) 
	{ 
		
		if(head == nullptr)
		{
			head = new Node(v, nullptr);
			tail = head;
			cout << "\n The tail is pointing to " << tail -> val << "\n";
		}
		else
		{
			Node *p = new Node(v, head);
			p -> next = head;
			head = p;
			cout << "\n The tail is pointing to " << tail -> val << "\n";
		}
		count++;
		
	}
	
	void insert(int i, int v) 
	{
		Node* p = head;
    	while (i > 0) 
    	{
			if (p == nullptr)
			{
				return;
			}
			p = p->next;
    		i--;
		}
    	p->next = new Node(v, p->next);
	}
	
	void removeEnd() 
	{
		if(head == nullptr)
		{
			cout << "Empty List \n";
			return;
		}
		if (head == tail)
		{
			head = nullptr;
			tail = nullptr;
			cout << "\n The tail is pointing to nothing\n";
			count--;
		}
		else if (head->next == tail) 
		{
			head->next = nullptr;
			tail = head;
			cout << "\n The tail is pointing to " << tail -> val << "\n";
			count--;
		
		}
		else
		{
			Node* p;
			for (p = head; p->next->next != nullptr; p = p->next)
			{
				;
			}
				p->next = nullptr;
				tail = p;
				count--;
				cout << "\n The tail is pointing to " << tail -> val << "\n";
		}
			
	}
	
	void removeStart() 
	{
		Node *p = head;
		if(head == nullptr)
		{
			cout << "Empty List \n";
			return;
		}
		
		if (head == tail)
		{
			head = nullptr;
			tail = nullptr;
			cout << "\n The tail is pointing to nothing\n";
			count--;
		}
		else if (head->next == tail) 
		{
			delete head;
			head = tail;
			cout << "\n The tail is pointing to " << tail -> val << "\n";
			count--;
		}
		else
		{
			head = p-> next;
			delete p;
			cout << "\n The tail is pointing to " << tail -> val << "\n";
			count --;
		}
	}

	friend ostream& operator<<(ostream& s, const LinkedList2& list) {
	    s << "{ ";
		for (Node* p = list.head; p != nullptr; p = p->next) {
			s << p->val << ' ';
		}
		s << "}";
		return s;
	}
 int size() const { //O(n)
		
		return count;
	}

	int get(int i) const { // O(n)
		Node* p = head;
		for ( ; i > 0; i--, p = p->next)
			if (p == nullptr)
				throw "LinkedList index out of bounds";
    return p->val;
	}
}	;


void firstTest()
{
	LinkedList2 a;
	for (int i = 0; i < 10; i++)
		a.addStart(i);
	cout << a << '\n';
	for (int i = 0; i < 10; i++)
		a.addEnd(i);
	cout << a << '\n';
}

void openTestFile()
{
	LinkedList2 testList;
	ifstream myfile ("HW4b.txt");
	//	ifstream myfile ("HW4c.txt");
	string::size_type sz;
    string command;
    string line;
    string numbers = "0123456789";
    string stringnum1, stringnum2, stringnum3, stringRemove;
    int startNum, stepNum, stopNum;
    string addFront = "ADD_FRONT";
    string addBack = "ADD_BACK";
    string output1 = "OUTPUT";
    string output2 = "OUTPUT\r";
    string removeFront = "REMOVE_FRONT";
    string removeBack = "REMOVE_BACK";
    
    if (myfile.is_open())
	{
    	while  (getline(myfile, line))
    	{
    		command = line.substr(0, line.find_first_of(' '));
    		if(command.compare("") != 0 && command.compare("\r")!= 0 )
    		{
	    		if((command.compare(addFront) == 0))
	    		{
	    			stringnum1 = line.substr(line.find_first_of(numbers.c_str()), line.find_first_of(':') - line.find_first_of(numbers.c_str()));
	    			stringnum2 = line.substr(line.find_first_of(':')+1,(line.find_last_of(':'))-line.find_first_of(':')-1);
	   				stringnum3 = line.substr(line.find_last_of(':')+1);
	   				startNum = stoi(stringnum1, &sz);
	   				stepNum = stoi(stringnum2, &sz);
	   				stopNum = stoi(stringnum3, &sz);
	    		//	cout << "The command for this line is ADD_FRONT\n";
		    	//	cout << "StartNum = " << startNum << "\n";
		    	//	cout << "StepNum = " << stepNum << "\n";
		   		//	cout << "StopNum = " << stopNum << "\n";
		   			for(int i = startNum; i <= stopNum; i= i+stepNum)
		   			{
		   				testList.addStart(i);
		   			}
	   			}
	   			else if((command.compare(addBack) == 0))
	   			{
	   				stringnum1 = line.substr(line.find_first_of(numbers.c_str()), line.find_first_of(':') - line.find_first_of(numbers.c_str()));
	    			stringnum2 = line.substr(line.find_first_of(':')+1,(line.find_last_of(':'))-line.find_first_of(':')-1);
	   				stringnum3 = line.substr(line.find_last_of(':')+1);
	   				startNum = stoi(stringnum1, &sz);
	   				stepNum = stoi(stringnum2, &sz);
	   				stopNum = stoi(stringnum3, &sz);
	   			//	cout << "The command for this line is ADD_BACK\n";
	   			//	cout << "StartNum = " << startNum << "\n";
		    	//	cout << "StepNum = " << stepNum << "\n";
		   		//	cout << "StopNum = " << stopNum << "\n";
		   			for(int i = startNum; i <= stopNum; i = i+stepNum)
		   			{
		   				testList.addEnd(i);
		   			}
	    		}
	    		else if((command.compare(output1) == 0) || (command.compare(output2) == 0))
	    		{
	    			//cout << "The command for this line is OUTPUT\n";
	    			cout << testList << "\n";
					cout << "Size of List = " << testList.size() << endl;
				//	cout << "Total Capacity = " << testList.getCapacity() << "\n";
	    		}
	    		else if((command.compare(removeFront) == 0))
	    		{
					stringRemove = line.substr(line.find_first_of(numbers.c_str()));
					startNum = stoi(stringRemove, &sz);
	    		//	cout << "The command for this line is REMOVE_FRONT\n";	
	    		//	cout << "RemoveNum= " << startNum << "\n";
	    			
	    			for(int i = 0; i < startNum; i++)
	    			{
	    				testList.removeStart();
	    			}
	    		}
	    		else if((command.compare(removeBack) == 0))
	    		{
	    			stringRemove = line.substr(line.find_first_of(numbers.c_str()));
					startNum = stoi(stringRemove, &sz);
	    		//	cout << "The command for this line is REMOVE_BACK\n";	
	    		//	cout << "RemoveNum= " << startNum << "\n";
	    			for(int i = 0; i < startNum; i++)
	    			{
	    				testList.removeEnd();
	    			}
	    		}
	    		else
	    		{
	    			cout << "The Text File may be corrupt no understood commands\n\n";
	    		}	
		    	
    		}
	    		
    	
    	}
    	myfile.close();
	}
	else
    {
        cout << "Unable to open file";
    }
}

void commandLineTest()
{
	LinkedList2 commandLineList;
	int answer = 0;
	int value = 0;
	cout << "Here is the current List: \n";
	cout << commandLineList << "\n";
//	cout << "Storage Used = " << commandLineList.getUsed() << "\n";				
//	cout << "Total Capacity = " << commandLineList.getCapacity() << "\n";
	do{
		cout << "-----------------------------------------------------------\n";
		cout << "What do you want to do to our List? \n";
		cout << "1: Add value to the End \n";
		cout << "2: Add value to the Front \n";
		cout << "3: Remove value from the End \n";
		cout << "4: Remove value from the Front \n";
		cout << "5: Display List and Stats \n";
		cout << "6: Finished End Program \n";
		cout << "-----------------------------------------------------------\n";
		cin >> answer;
		if(answer == 1)
		{
			cout << "What Value do you want to add to the End? \n";
			cin >> value;
			commandLineList.addEnd(value);
			cout << "Adding " << value << " to the end \n\n";
			cout << commandLineList << "\n";
			cout << "Size of List = " << commandLineList.size() << endl;				
		//	cout << "Total Capacity = " << commandLineList.getCapacity() << "\n";
			
		}
		else if(answer == 2)
		{
			cout << "What Value do you want to add to the Front? \n";
			cin >> value;
			commandLineList.addStart(value);
			cout << "Adding " << value << " to the Front \n\n";
			cout << commandLineList << "\n";
			cout << "Size of List = " << commandLineList.size() << endl;					
		//	cout << "Total Capacity = " << commandLineList.getCapacity() << "\n";
		}
		else if(answer == 3)
		{
			commandLineList.removeEnd();
			cout << "Removing from the End \n\n";
			cout << commandLineList << "\n";
			cout << "Size of List = " << commandLineList.size() << endl;					
		//	cout << "Total Capacity = " << commandLineList.getCapacity() << "\n";
		}
		else if(answer == 4)
		{
			commandLineList.removeStart();
			cout << "Removing from the Front \n\n";
			cout << commandLineList << "\n";
			cout << "Size of List = " << commandLineList.size() << endl;					
		//	cout << "Total Capacity = " << commandLineList.getCapacity() << "\n";
		}
		else
		{
			cout << "-----------------------------------------------------------\n";
			cout << commandLineList << "\n";
			cout << "Size of List = " << commandLineList.size() << endl;					
		//	cout << "Total Capacity = " << commandLineList.getCapacity() << "\n";
			cout << "-----------------------------------------------------------\n";
		}
	}while(answer != 6);
	
}


int main() 
{
//	openTestFile();
	commandLineTest();
//	firstTest();

  return 0;
}

	


