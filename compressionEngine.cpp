#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct node
{
	char value;
	node* left;
	node* right;
	double probability;
};
struct compareNodes
{
	bool operator()(node* &n1, node* n2)
	{
		return n1->probability > n2->probability;
	}
};

void createNodes(string text, priority_queue<node*, vector<node* >, compareNodes> &pq);
int getOccurancesAndRemoveAll(string &text, char c);
void buildTree(priority_queue<node*, vector<node* >, compareNodes> &pq);
char decode(node* root, vector<bool> bin);
void buildConversionMap(node* root, map<char, vector<bool> > &converstionMap, vector<bool> &temp);

int main()
{
	string text = "text";
	priority_queue<node*, vector<node* >, compareNodes> pq;
	createNodes(text, pq);
	buildTree(pq);
	node* root = pq.top();
	map<char, vector<bool> > converstionMap;
	vector<bool> temp;
	buildConversionMap(root, converstionMap, temp);
	vector<bool> bin;
	char printTem = 't';
	bin = converstionMap[printTem];
	cout << printTem << " : ";
	int i;
	for(i = 0; i < bin.size(); i++)
		cout << bin[i];
	cout << endl;
	return 0;
}
void createNodes(string text, priority_queue<node*, vector<node* >, compareNodes> &pq)
{
	double length = text.length();
	while(text.length() > 0)
	{
		char c = text[0];
		int frequency = getOccurancesAndRemoveAll(text, c);
		node* n = new node;
		n->value = c;
		n->probability = frequency/length;
		pq.push(n);
	}
}
int getOccurancesAndRemoveAll(string &text, char c)
{
	int count = 0;
	int i;
	for(i = 0; i < text.length(); i++)
	{
		if(text[i] == c)
		{
			text = text.substr(0, i) + text.substr(i + 1);
			i--;
			count++;
		}
	}
	return count;
}
void buildTree(priority_queue<node*, vector<node* >, compareNodes> &pq)
{
	while(pq.size() > 1)
	{
		node* right = pq.top();
		pq.pop();
		node* left = pq.top();
		pq.pop();
		node* connector = new node;
		connector->left = left;
		connector->right = right;
		connector->probability = right->probability + left->probability;
		pq.push(connector);
	}
}
char decode(node* root, vector<bool> bin)
{
	int i;
	for(i = 0; i < bin.size(); i++)
	{
		if(bin[i])
		{
			root = root->right;
		}
		else
		{
			root = root->left;
		}
	}
	return root->value;
}
void buildConversionMap(node* root, map<char, vector<bool> > &converstionMap, vector<bool> &temp)
{
	if(root->left != NULL)
	{
		temp.push_back(false);
		buildConversionMap(root->left, converstionMap, temp);
	}
	if(root->right != NULL)
	{
		temp.push_back(true);
		buildConversionMap(root->right, converstionMap, temp);
	}
	converstionMap.insert({root->value, temp});
	temp.erase(temp.begin(), temp.end());
}
