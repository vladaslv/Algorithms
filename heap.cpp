#include <iostream>
#include <vector>
#include <map>

using namespace std;

int n, m;

struct product {
	int number;
	int price;
};

struct client {
	int money;
	int order;
	int order_first;
	vector<int> goods;
};

client deleted_element;
vector<product> warehouse;
vector<client> heap_clients;

map<int, vector<int>> result_to_print;

void push_element(client & c) {
	heap_clients.push_back(c);
	int current = heap_clients.size() - 1;
	int parent = (current - 1) / 2;

	while (current > 0 && parent >= 0) {
		if (heap_clients[current].money > heap_clients[parent].money || (heap_clients[current].money == heap_clients[parent].money && heap_clients[current].order < heap_clients[parent].order)) {
			swap(heap_clients[current], heap_clients[parent]);
			current = parent;
			parent = (current - 1) / 2;
		}
		else break;
	}
}


void pop_element() {
	deleted_element = heap_clients[0];

	if (heap_clients.size() == 1)
		heap_clients.pop_back();
	else {
		int current = 0, largest;
		int l, r;

		swap(heap_clients[0], heap_clients[heap_clients.size() - 1]);
		heap_clients.pop_back();

		while (current < heap_clients.size()) {
			largest = current;
			l = 2 * current + 1;
			
			if (l < heap_clients.size()) {
				if (heap_clients[l].money > heap_clients[largest].money || (heap_clients[l].money == heap_clients[largest].money && heap_clients[l].order < heap_clients[largest].order)) {
					largest = l;
				}

				r = l + 1;
				if (r < heap_clients.size() && (heap_clients[r].money > heap_clients[largest].money || (heap_clients[r].money == heap_clients[largest].money && heap_clients[r].order < heap_clients[largest].order))) {
					largest = r;
				}

				if (largest != current) {
					swap(heap_clients[current], heap_clients[largest]);
					current = largest;
				}
				else break;
			}
			else
				break;
		}

	}

}

void swap(client * x, client * y)
{
	client temp = *x;
	*x = *y;
	*y = temp;
}

int main()
{
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		product p;
		cin >> p.number >> p.price;
		warehouse.push_back(p);
	}

	int good;

	int order_counter, n_goods;
	for (order_counter = 0; order_counter < m; order_counter++) {
		client c;
		cin >> c.money >> n_goods;

		c.order_first = order_counter;
		c.order = order_counter;
	
		for (int j = 0; j < n_goods; j++) {
			cin >> good;
			c.goods.push_back(good);
		}

		push_element(c);
	}

	int current_good;

	while (heap_clients.size() > 0) {
		current_good = heap_clients[0].goods.front();
		if (warehouse[current_good].number > 0 && heap_clients[0].money >= warehouse[current_good].price) {
			result_to_print[heap_clients[0].order_first].push_back(current_good);
			warehouse[current_good].number--;
			heap_clients[0].money -= warehouse[current_good].price;
			heap_clients[0].goods.erase(heap_clients[0].goods.begin());

			pop_element();
			if (!deleted_element.goods.empty() && deleted_element.money > 0) {
				deleted_element.order = order_counter;
				order_counter++;
				push_element(deleted_element);
			}
		}

		else if (warehouse[current_good].number == 0 || heap_clients[0].money < warehouse[current_good].price) {
			heap_clients[0].goods.erase(heap_clients[0].goods.begin());

			if (heap_clients[0].goods.empty())
				pop_element();
		}
	}


	for (int i = 0; i < m; i++) {
		if (result_to_print[i].empty())
			cout << "-" << endl;
		else {
			for (auto it = result_to_print[i].begin(); it != result_to_print[i].end(); it++)
				cout << *it << " ";
			cout << endl;
		}
	}

	return 0;
}
