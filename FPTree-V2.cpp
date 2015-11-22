#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <list>
using namespace std;
const int MAX_LENTH = 1000;
const int MAX_ITEMS = 5 + 1e7;
const char* SPLITCHAR = " ";
/*utility function*/
/**
*split str according to TEMP
*string TEMP
*/
list<string> splitStr(string str,string TEMP)
{
    string::size_type pos;
    list<string> result;
    //去掉'\n'字符
    int size = str.size() - 1;

    for(int i = 0;i < size;i ++)
    {
        pos = str.find(TEMP,i);
        if(pos < size)
        {
            string s = str.substr(i,pos-i);
            result.push_back(s);
            i = pos + TEMP.size() - 1;
        }
        else {
        	string s = str.substr(i,size - i);
        	result.push_back(s);
        	break;
        }
    }
    return result;
}
list< pair<int,list<string> > > getTransRecordsFormFile(const char* fileName)
{
	list< pair<int,list<string> > > res;
	FILE* f = fopen(fileName,"r");
	if(f == NULL) {
		cout << "load input file failed!" << endl;
		exit(0);
	}
	else {
		char *buffer;
		while(fgets(buffer,MAX_LENTH,f) != NULL) {
			list<string> v = splitStr(buffer, SPLITCHAR);
			res.push_back(make_pair(1,v));
		}
	}
	fclose(f);
	return res;
}
void printRecords(list< pair<int,list<string> > > R)
{
	list< pair<int,list<string> > >::iterator itI;
	list<string>:: iterator itJ;
	for(itI = R.begin();itI != R.end();itI ++) {
		cout << "(" << (*itI).first << ") ";
		for(itJ = ((*itI).second).begin();itJ != ((*itI).second).end();itJ ++) {
			cout << (*itJ) <<" ";
		}
		cout<<endl;
	}
}

/*TreeNode class*/
class TreeNode
{
public:
	TreeNode()
	{
		parent = NULL;
		nextHomonym = NULL;
		children = NULL;
		count = 0;
	}
	TreeNode(string name)
	{
		parent = NULL;
		nextHomonym = NULL;
		children = NULL;
		count = 0;
		this->name = name;
	}
	void setName(string name)
	{
		this->name = name;
	}
	void setCount(int count)
	{
		this->count = count;
	}
	void setParent(TreeNode* parent)
	{
		this->parent = parent;
	}
	void setChildren(list<TreeNode*> *children)
	{
		this->children = children;
	}
	void addChild(TreeNode* child)
	{
		if(children == NULL) {
			children = new list<TreeNode*>;
		}
		(*children).push_back(child);
	}
	void setNextHomonym(TreeNode* nextHomonym)
	{
		this->nextHomonym = nextHomonym;
	}
	void addCountBy(int n)
	{
		this->count += n;
	}

	int getCount()
	{
		return this->count;
	}
	string getName()
	{
		return this->name;
	}
	TreeNode* getParent()
	{
		return this->parent;
	}
	TreeNode* getNextHomonym()
	{
		return this->nextHomonym;
	}
	list<TreeNode*>* getChildren()
	{
		return this->children;
	}
	TreeNode* findChild(string name)
	{
		if(children == NULL) return NULL;
		TreeNode* res = NULL;
		list<TreeNode*>::iterator it;
		for(it = (*children).begin();it != (*children).end();it ++) {
			if( (*it)->name == name) {
				res = (*it);
				break;
			}
		}
		return res;
	}
private:
	string name;
	int count;
	TreeNode* parent;
	TreeNode* nextHomonym;
	list<TreeNode*> *children;
};

/*sort function*/
bool cmp(TreeNode* a, TreeNode* b)
{
	return a->getCount() > b->getCount();
}
bool cmpRecord(pair<string,int> a, pair<string,int> b)
{
    return a.second < b.second;
}
bool cmpMode(pair<int, list<string> > a, pair<int, list<string> > b)
{
	if(a.second.size() == b.second.size()) {
		return a.first > b.first;
	}
	return a.second.size() < b.second.size();
}
bool cmpKMode(pair<int, list<string> > a, pair<int, list<string> > b)
{
	if(a.first == b.first) {
		return a.second.size() > b.second.size();
	}
	return a.first > b.first;
}
/*FPTree class*/

class FPTree
{
public:
	int Vcnt;
	pair<int, list<string> > resMode[MAX_ITEMS];
	FPTree()
	{
		//default min support
		minSupport = 3;
		Vcnt = 0;
		modeSize = 0;
		DEBUG = 0;
	}
	void setMinSupport(int newMinSupport)
	{
		minSupport = newMinSupport;
	}
	void setDebug(bool DEBUG)
	{
		this->DEBUG = DEBUG;
	}
	int getMinSupport()
	{
		return minSupport;
	}
	void clearMap()
	{
		mapStrInt.clear();
	}
	void setMap(string str,int cnt)
	{
		mapStrInt[str] = cnt;
	}
	void addMapBy(string str, int inc)
	{
		mapStrInt[str] += inc;
	}

	void FPGrowth(list< pair<int,list<string> > > records, list<string> pattern)
	{
		if(records.empty()) return ;
		Vcnt ++;
		
		list<TreeNode*> HeaderTable = buildHeaderTable(records);
		TreeNode* root = buildFPTree(records, HeaderTable);

		if(DEBUG) {
			cout << "--------------------------" << endl;
			cout<< "Now the depth is: " << Vcnt << endl;

			cout<< "Now the records is: " << endl;
			printRecords(records);

			cout<< "Now the pattern is: " << endl;
			printPattern(pattern);

	        cout<< "Now the F1 is: " << endl;
	        printHeaderTable(HeaderTable);

	        cout<< "Now the FPTree is: " << endl;
		    printTree(root);
		}

		if(root->getChildren() == NULL) {
			return ;
		}

		if(DEBUG) cout << "Now the result is : " << endl;

		list<TreeNode*>::iterator _it;
		for(_it = HeaderTable.begin();_it != HeaderTable.end();_it ++) {
			TreeNode* node = (*_it);
			list<string> items = pattern;
			items.push_front(node->getName());
			if(DEBUG) {
				cout << node->getCount() << " : ";
				for(list<string>::iterator I = items.begin();I != items.end();I ++) {
					cout << (*I) << " ";
				}
				cout << endl;
			}
			resMode[modeSize ++] = make_pair(node->getCount(), items);
		}

		list<TreeNode*>::iterator it;
		for(it = HeaderTable.begin();it != HeaderTable.end();it ++) {
			TreeNode* header = (*it);
			list<string> newPattern = pattern;
		    list< pair<int,list<string> > > newRecords;
			//构造新的模式串
			newPattern.push_front(header->getName());
			TreeNode* nextNode = header->getNextHomonym();
			while(nextNode != NULL) {
				list<string> record;

				int cnt = nextNode->getCount();
				TreeNode* preNode = nextNode;
				while( ((preNode = preNode->getParent())->getName()) != "") {
					record.push_back(preNode->getName());
				}
				if(!record.empty()) {
					newRecords.push_back(make_pair(cnt,record));
				}
				record.clear();
				nextNode = nextNode->getNextHomonym();
			}
			delete header;
			FPGrowth(newRecords, newPattern);
		}
		HeaderTable.clear();
	}

	//构造频繁1项集
	list<TreeNode*> buildHeaderTable(list< pair<int,list<string> > > records)
	{
		list<TreeNode*> F1;
		map<string,TreeNode*> mpTree;
		mpTree.clear();
		F1.clear();
		clearMap();

		list< pair<int,list<string> > >::iterator itI;
	    list<string>:: iterator itJ;
	    for(itI = records.begin();itI != records.end();itI ++) {
	    	int cnt = (*itI).first ;
		    for(itJ = ((*itI).second).begin();itJ != ((*itI).second).end();itJ ++) {
				string item = (*itJ);
				if(mpTree.find(item) == mpTree.end()) {
					TreeNode* node = new TreeNode(item);
					node->setCount(cnt);
					mpTree[item] = node;
					setMap(item,cnt);
				}
				else {
					( mpTree[item] )->addCountBy(cnt);
					addMapBy(item,cnt);
				}
			}
		}

		for(map<string,TreeNode*>:: iterator it = mpTree.begin();it != mpTree.end();it ++) {
			if(( it->second )->getCount() >= minSupport) {
				F1.push_back( (it->second) );
			}
		}
		F1 = sortF1(F1);
		return F1;
	}

	//构造对应的FP-Tree
	TreeNode* buildFPTree(list< pair<int,list<string> > > records, list<TreeNode*> F1)
	{
		TreeNode* root = new TreeNode();

		list< pair<int,list<string> > >::iterator itI;
		for(itI = records.begin();itI != records.end();itI ++) {
			int cnt = (*itI).first;
			list<string> sortedRecord = sortByMap((*itI).second);

			TreeNode* parent = root;
			TreeNode* node;
			bool ok = true;//标记是否有新的分支
			while(!sortedRecord.empty()) {

				string item = sortedRecord.back();
				if(ok && (node = (parent->findChild(item))) != NULL) {
					node->addCountBy(cnt);
					parent = node;
				}
				else {
					ok = false;
					TreeNode* newNode = new TreeNode(item);
					newNode->setCount(cnt);
					newNode->setParent(parent);
					parent->addChild(newNode);
					parent = newNode;
					//链接同名节点
					list<TreeNode*>::iterator it;
					for(it = F1.begin();it != F1.end();it ++) {
						TreeNode* f = (*it);
						if(f->getName() == item) {
							while( f->getNextHomonym() != NULL ) {
								f = f->getNextHomonym();
							}
							f->setNextHomonym(newNode);
							break;
						}
					}
				}
				sortedRecord.pop_back();
			}
			sortedRecord.clear();
		}
		return root;
	}

	list<string> sortByMap(list<string> record)
	{
		vector< pair<string,int> > tmp;
		list<string> sortedRecord;
		list<string>::iterator it;
		for(it = record.begin();it != record.end();it ++) {
			string now = (*it);
			if(mapStrInt[now] >= minSupport) {
				tmp.push_back(make_pair(now, mapStrInt[now]));
			}
		}
		sort(tmp.begin(), tmp.end(), cmpRecord);
		for(int i = 0;i < tmp.size();i ++) {
			sortedRecord.push_back(tmp[i].first);
		}
		tmp.clear();
		return sortedRecord;
	}
	
	list<TreeNode*> sortF1(list<TreeNode*> F1)
	{
		vector<TreeNode*> tmp;
		list<string> sortedRecord;
		tmp.clear();
		list<TreeNode*>::iterator it;
		for(it = F1.begin();it != F1.end();it ++) {
			tmp.push_back((*it));
		}
		F1.clear();
		sort(tmp.begin(), tmp.end(), cmp);
		for(int i = 0;i < tmp.size();i ++) {
			F1.push_back(tmp[i]);
		}
		tmp.clear();
		return F1;
	}
	/*function for looking process*/
	void printHeaderTable(list<TreeNode*> HeaderTable)
	{
		list<TreeNode*>::iterator it;
		for(it = HeaderTable.begin();it != HeaderTable.end();it ++) {
			cout << (*it)->getName() << " : ";
			cout << (*it)->getCount() << endl; 
		}
	}
	void printPattern(list<string> pattern)
	{
		list<string>::iterator it;
		for(it = pattern.begin();it != pattern.end();it ++) {
			cout << (*it) << " ";
		}
		cout << endl;
	}
	void printTree(TreeNode* rt)
	{
		if( rt->getChildren()  == NULL) return ;
		list<TreeNode*>::iterator it;
		list<TreeNode*> *child = rt->getChildren();
		for(it = (*child).begin();it != (*child).end();it ++) {
			cout << (rt->getName()) << "(" << (rt->getCount()) << ") -> " << (*it)->getName() <<"(" << (*it)->getCount() << ")" << endl;
			printTree(*it);
		}
	}

	void printAllSortedMode()
	{
		sort(resMode, resMode + modeSize, cmpMode);
		for(int i = 0;i < modeSize;i ++) {
			int sz = resMode[i].second.size();
			if(i == 0 || sz != resMode[i-1].second.size()) {
				cout << "The " << sz << " frequent items set :" <<endl;
			}
			list<string>::iterator it;
			cout << "{";
			for(it = (resMode[i].second).begin();it != (resMode[i].second).end();it ++) {
				cout << (*it) << " ";
			}
			cout << "} [" << (resMode[i].first) << "]" << "\n";
		}
		cout << "--------------------------" << "\n";
	}
	void printTopKMode(int k)
	{
		sort(resMode, resMode + modeSize, cmpKMode);
		k = min(k, modeSize);
		cout << "The top " << k << " frequent items set is:" << endl;
		for(int i = 0;i < k;i ++) {
			list<string>::iterator it;
			cout << "{";
			for(it = (resMode[i].second).begin();it != (resMode[i].second).end();it ++) {
				cout << (*it) << " ";
			}
			cout << "} [" << (resMode[i].first) << "]" << "\n";
		}
	}
private:
	int minSupport;
	int modeSize ;
	//select DEBUG mode
	bool DEBUG;
	//用来记录字符串出现的次数
    map<string,int> mapStrInt;
};

int main()
{
	list< pair<int,list<string> > > R = getTransRecordsFormFile("test\\in.txt");
	list<string> v;

	int n, mode, DEBUG;
	cout << "Input the min support:" << endl;
	cin >> n;
	cout << "Input the mode of processing:" << endl;
	cout << "0: Results will be print in screen" << endl;
	cout << "1: Results will be print in file" << endl;
	cin >> mode;
	cout << "Need DEBUG(will print all information)?" << endl;
	cin >> DEBUG;
	if(mode == 1) freopen("test\\out.txt","w",stdout);

	FPTree* fptree = new FPTree();

	fptree->setDebug(DEBUG != 0);
	fptree->setMinSupport(n);
    cout<<"The minSupport is: "<< fptree->getMinSupport() <<endl;

    clock_t start=clock();	
	fptree->FPGrowth(R, v);
	clock_t finish=clock();

	cout << "The depth is : " << fptree->Vcnt <<endl;
	cout << "(FP-Tree Growth)Time: " << (double)(finish - start) / CLOCKS_PER_SEC << "s." << endl;

	cout << "--------------------------" << endl;
	//print result after sorting all data
	fptree->printAllSortedMode();
	fptree->printTopKMode(10);

	exit(0);
}
