#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;


struct Node {
	vector<int> neighbours;
};

inline void printTAK(int * green, int * red, int & s, int & f, char color) {
	if (f != s || color != 'g') {
		if (color == 'g') {
			printTAK(green, red, s, green[f], 'r');
		}
		else {
			printTAK(green, red, s, red[f], 'g');
		}
	}

	cout << f << " ";
}

bool isCycle(Node * arr, int node, char * visited) {
	visited[node] = 'G';

	for (auto it = arr[node].neighbours.begin(); it != arr[node].neighbours.end(); it++) {
		if (visited[(*it)] == 'G')
			return true;

		if (visited[(*it)] == 'W' && isCycle(arr, (*it), visited))
			return true;
	}

	visited[node] = 'B';
	return false;
}

bool checkRemis(Node * arr, int & n, int & start) {
	char * visited = new char[n];
	for (int i = 0; i < n; i++) {
		visited[i] = 'W';
	}

	if (isCycle(arr, start, visited)) {
		delete[]visited;
		return true;
	}

	else {
		delete[]visited;
		return false;
	}


}

inline void Foo(Node * arr, int & start, int & n) {
	int * green = new int[n];
	int * red = new int[n];
	for (int i = 0; i < n; i++) {
		green[i] = -1;
		red[i] = -1;
	}

	queue<int> q;
	q.push(-1); // -1 - green
	q.push(start);
	green[start] = n;

	int finish;
	bool remis = checkRemis(arr, n, start);
	bool tak = false;
	int nd;

	while (!q.empty()) {
		nd = q.front();
		q.pop();


		if (nd == -1) {  //g

			nd = q.front();
			q.pop();

			if (arr[nd].neighbours.empty()) {
				tak = true;
				finish = nd;
			}

			if (arr[nd].neighbours.empty()) {
				cout << "TAK" << endl;
				printTAK(green, red, start, nd, 'g');
				delete[]green;
				delete[]red;
				return;
			}

			for (auto it = arr[nd].neighbours.begin(); it != arr[nd].neighbours.end(); it++) {
				if (red[(*it)] == -1) {
					q.push(-2); //r
					q.push(*it);
					red[(*it)] = nd;
				}
			}
		}
		else {
			nd = q.front();
			q.pop();

			if (arr[nd].neighbours.empty()) {
				tak = true;
				finish = nd;
			}

			for (auto it = arr[nd].neighbours.begin(); it != arr[nd].neighbours.end(); it++) {
				if (green[(*it)] == -1) {
					q.push(-1); //g
					q.push(*it);
					green[(*it)] = nd;
				}
			}
		}
	}

	if (tak == true) {
		if (green[finish] != -1) {
			cout << "TAK" << endl;
			printTAK(green, red, start, finish, 'g');
		}
		else {
			if (!remis)cout << "NIE" << endl;
			else cout << "REMIS" << endl;
		}
	}
	else cout << "REMIS" << endl;


	delete[]red;
	delete[]green;

}



int main()
{
	ios_base::sync_with_stdio(false);

	int n_games;
	cin >> n_games;

	int n, m, start;
	int v1, v2;


	for (int g = 0; g < n_games; g++) {
		cin >> n >> m >> start;
		Node * arr = new Node[n];

		for (int i = 0; i < m; i++) {
			cin >> v1 >> v2;
			arr[v1].neighbours.push_back(v2);
		}
		for (int i = 0; i < n; i++) {
			sort(arr[i].neighbours.begin(), arr[i].neighbours.end());
		}

		if (arr[start].neighbours.empty()) cout << "TAK" << endl << start << endl;
		else Foo(arr, start, n);

		delete[]arr;
	}


	return 0;
}
