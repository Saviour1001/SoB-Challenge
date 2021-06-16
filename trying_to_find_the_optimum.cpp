#include "bits/stdc++.h"
using namespace std;
#define int               long long
#define ll                long long
#define pb                push_back
#define ppb               pop_back
#define pf                push_front
#define ppf               pop_front
#define all(x)            (x).begin(),(x).end()
#define uniq(v)           (v).erase(unique(all(v)),(v).end())
#define sz(x)             (int)((x).size())
#define fr                first
#define sc                second
#define pii               pair<int,int>
#define rep(i,a,b)        for(int i=a;i<b;i++)
#define mem1(a)           memset(a,-1,sizeof(a))
#define mem0(a)           memset(a,0,sizeof(a))
#define ppc               __builtin_popcount
#define ppcll             __builtin_popcountll
#define ln "\n"
#define deb(x) cout << #x << " " << x<<ln;


const long long INF = 1e18;
const int32_t M = 1e9 + 7;
const int32_t MM = 998244353;
const int N = 0;

class MempoolTransactions
{
public:
	string tx_id;
	int fee;
	int weight;
	vector<string> parents;
};


pair<string, MempoolTransactions*> createNewRow(vector<string> &single_row) {
	auto obj = new MempoolTransactions();
	obj->tx_id = single_row[0];
	obj->fee = stoi(single_row[1]);
	obj->weight = stoi(single_row[2]);
	vector<string> p;
	for (int i = 3; i < single_row.size(); i++) {
		p.pb(single_row[i]);
	}
	obj->parents = p;
	return {single_row[0], obj};
}

void readFile(string fileName, unordered_map<string, MempoolTransactions*>& map) { // reading the file and storing each record in a hashmap
	ifstream fin(fileName);														   // which is storing transaction ids and their respective
	vector<string> single_row;                                                     // details
	string single_line, word, tmp;
	getline(fin, single_line);  // Removing the relational schema
	while (getline(fin, single_line))
	{
		single_row.clear();
		stringstream s(single_line);
		while (getline(s, word, ','))
		{
			single_row.pb(word);
		}
		pair<string, MempoolTransactions*> p = createNewRow(single_row);
		map[p.fr] = p.sc;
	}
	fin.close();
	deb(map.size());
}

void writeFile(vector<string>& included_tx_vector, string fn) {
	ofstream fo(fn);
	for (auto s : included_tx_vector)
		fo << s << endl;
	fo.close();
}


bool checker(MempoolTransactions* tx, set<string>& included_tx_set) { // checking if a transaction has parent transactions and
	for (auto parent : tx->parents)                                  // if it has, are the parent transactions already included in the block
	{
		if (included_tx_set.find(parent) == included_tx_set.end())
			return false;
	}
	return true;
}

signed main() {

	unordered_map<string, MempoolTransactions*> map; // Using map to store all the records
	string fileName = "mempool.csv";
	readFile(fileName, map);

	set<pair<float, MempoolTransactions*>, greater<pair<float, MempoolTransactions*>>> tx_set; //sorting for the highest fees
	set<string> included_transaction_set; // set which contains the final block
	vector<string> included_transaction_vector;

	for (auto p : map) {
		tx_set.insert({(float)p.second->fee / (float)p.second->weight, p.second});
	}

	int currentWeight = 0;
	int Fee = 0;
	int blockWeight = 4000000;

	while (currentWeight <= blockWeight) {

		bool flag = false; // Flag to break if caught in an infinite loop

		for (auto itr = tx_set.begin(); itr != tx_set.end(); itr++) {

			MempoolTransactions* curr_tx = (*itr).second;
			int current_id_Fee = curr_tx->fee;
			int current_id_Weight = curr_tx->weight;

			if (currentWeight + current_id_Weight <= blockWeight && checker(curr_tx, included_transaction_set))
			{
				currentWeight += current_id_Weight;
				included_transaction_set.insert(curr_tx->tx_id);
				included_transaction_vector.pb(curr_tx->tx_id);

				Fee += current_id_Fee;
				tx_set.erase(itr);	  // Erase the transactions from the set which are already included
				flag = true;          // Continue searching for new transactions
				break;
			}
		}

		if (!flag) // if no valid transactions are found break out of the loop
			break;
	}

	deb(included_transaction_vector.size())
	deb(Fee)
	deb(currentWeight)

	writeFile(included_transaction_vector, "block.txt");
	return 0;
}
