#include <iostream>
#include <string>

using namespace std;

template <class Q>
struct NodeQ {
	Q data;
	int size;
	NodeQ * next;
	NodeQ() : data(NULL), next(NULL) {}
	NodeQ(const Q & data) : data(data), next(NULL) {}
};

template <class Q>
class Queue {
	NodeQ<Q> * head;
	NodeQ<Q> * tail;
	int size;
public:
	Queue() : head(NULL), tail(NULL), size(0) {}
	~Queue();
	void push_back(const Q & data);
	void pop_front(Q & val);
	bool isEmpty() { return (size == 0); }
	Q front() { return head->data; }
	int getSize() { return size; }
};

template <class Q>
Queue<Q>::~Queue<Q>() {
	NodeQ<Q> * tmp;

	while (head != NULL) {
		tmp = head;
		head = head->next;
		delete tmp;
	}
	size = 0;
	tail = NULL;
}


template <class Q>
void Queue<Q>::push_back(const Q & data) {
	if (size == 0) {
		head = new NodeQ<Q>(data);
		tail = head;
	}
	else {
		NodeQ<Q> * tmp = new NodeQ<Q>(data);
		tail->next = tmp;
		tail = tail->next;
	}
	size++;
}

template <class Q>
void Queue<Q>::pop_front(Q & val) {
	if (!isEmpty()) {
		val = head->data;

		NodeQ<Q> * tmp = head;
		head = head->next;

		delete tmp;

		size--;
	}
}



template <class T>
struct Node {
	T data;
	Node * next;
	Node() : data(NULL), next(nullptr) {}
	Node(const T & data) : data(data), next(NULL) {}
};


template <class T>
class Stack {
	Node<T> * top;
	int size;

public:
	Stack<T>() : top(NULL), size(0) {}
	~Stack();
	bool isEmpty() { return (top == NULL); }
	void push(const T & data);
	void pop(T & val);
	T getTop() { return top->data; }
	int getSize() { return size; }
};

template <class T>
Stack<T>::~Stack() {
	Node<T> * tmp = top;
	while (top != NULL) {
		tmp = top;
		top = top->next;
		delete tmp;
	}
	size = 0;
}

template <class T>
void Stack<T>::push(const T & data) {
	Node<T> * tmp = new Node<T>(data);
	tmp->next = top;
	top = tmp;
	size++;
}

template <class T>
void Stack<T>::pop(T & val) {
	if (!isEmpty()) {
		val = top->data;

		Node<T> * tmp = top;
		top = top->next;
		delete tmp;
		size--;
	}
}


struct Digit {
	bool num_b, op_b;
	char op_v;
	int num_v;

	Digit() : num_b(false), op_b(false), op_v(NULL), num_v(NULL) {}

	Digit(const char & op_v) {
		this->op_v = op_v;
		this->op_b = true;
		this->num_b = false;
	}

	Digit(const int & num_v) {
		this->num_v = num_v;
		this->num_b = true;
		this->op_b = false;
	}

};

bool isNumber(char c) { return (c >= '0' && c <= '9'); }
bool isNumber(Digit d) { return d.num_b; }

bool isOperator(char c) { return (c == '+' || c == '-' || c == '*' || c == '/'); }
bool isOperator(Digit d) { return d.op_b; }

bool isBracket(char c) { return (c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}'); }

int getPrecedence(char c) {
	switch (c) {
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	default: return -1;
	}
}

bool operate(Stack<double> & s, char opr) {
	double value1, value2;
	s.pop(value2);
	s.pop(value1);
	if (opr == '+') s.push(value1 + value2);
	else if (opr == '-') s.push(value1 - value2);
	else if (opr == '*') s.push(value1 * value2);
	else {
		if (value2 == 0) return false;
		s.push(value1 / value2);
	}
	return true;
}

void handleNumber(int & i, string & input, Queue<Digit> & q, bool & minus) {
	int value = 0;
	i--;

	
	while (isNumber(input[i + 1])) {
		i++;
		value *= 10;
		value += (int)(input[i] - 48);
	}

	if (minus) {
		value *= -1;
		minus = false;
		if (i > 1)
			i++;
	}

	Digit tmp(value);
	q.push_back(tmp);
}

bool correctNumBrackets(string & input) {
	int round = 0, square = 0, buckle = 0;
	for (int i = 0; i < input.length(); i++) {
		switch (input[i]){
		case '(': round++; break;
		case ')': round--; break;
		case '[': square++; break;
		case ']': square--; break;
		case '{': buckle++; break;
		case '}': buckle--; break;
		}
	}
	return (round == 0 && square == 0 && buckle == 0);
}

bool convert(string & input, Queue<Digit> & q) {
	Stack<char> s;
	char c;
	bool minus = false;

	for (int i = 0; i < (int)input.length(); i++) {
		if (isNumber(input[i])) {
			handleNumber(i, input, q, minus);
		}
		else if (input[i] == '(' || input[i] == '[' || input[i] == '{') {
			if (i + 2 < (int)input.length() && !minus && input[i + 1] == '-' && isNumber(input[i + 2])) {
				minus = true;
				i++;
			}
			else s.push(input[i]);
		}

		else if (input[i] == ')') {
			if (i > 1 && input[i - 1] == '(') {
				return false;
			}
			
			while (s.getTop() != '(') {
				if (s.getTop() == '{' || s.getTop() == '[')
					return false;
				else {
					Digit tmp(s.getTop());
					q.push_back(tmp);
					s.pop(c);
				}
			}
			s.pop(c);
		}

		else if (input[i] == ']') {
			if (i > 1 && input[i - 1] == '[') {
				return false;
			}

			while (s.getTop() != '[') {
				if (s.getTop() == '(' || s.getTop() == '{')
					return false;
				else {
					Digit tmp(s.getTop());
					q.push_back(tmp);
					s.pop(c);
				}
			}
			s.pop(c);
		}

		else if (input[i] == '}') {
			if (i > 1 && input[i - 1] == '{') {
				return false;
			}

			while (s.getTop() != '{') {
				if (s.getTop() == '(' || s.getTop() == '[')
					return false;
				else {
					Digit tmp(s.getTop());
					q.push_back(tmp);
					s.pop(c);
				}
			}
			s.pop(c);
		}

		else if (isOperator(input[i])) {
			if (input[i] == '-' && i == 0 && isNumber(input[i+1]) && !minus) 
				minus = true;
			else {
				if (!s.isEmpty()) {
					while ((!s.isEmpty()) && (isOperator(s.getTop())) && (getPrecedence(s.getTop()) >= getPrecedence(input[i]))) {
						Digit tmp(s.getTop());
						q.push_back(tmp);
						s.pop(c);
					}
				}
				s.push(input[i]);
			}		
		}
			
	}	


	while (!s.isEmpty()) {
		Digit tmp(s.getTop());
		if (isNumber(tmp) || isOperator(tmp)) {
			q.push_back(tmp);
		}
		s.pop(c);
	}
	return true;
}

void calculate(Queue<Digit> & q, Stack<double> & s) {
	Digit tmp;
	bool crrct;
	//int count_num = 0;

	while (!(q.isEmpty())) {
		q.pop_front(tmp);
		if (isOperator(tmp)) {
			if (s.getSize() < 2) {
				cout << "BLAD" << endl;
				return;
			}
			crrct = operate(s, tmp.op_v);

			if (!crrct) {
				cout << "BLAD" << endl;
				return;
			}
		}
		else {
			s.push((double)tmp.num_v);
			//count_num++;
		}
	}

	//if (s.getSize() != 1 || count_num <=1 )
	if (s.getSize() != 1)
	{
		cout << "BLAD" << endl;
		return;
	}
	else {
			cout << s.getTop() << endl;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);

	unsigned int n;
	cin >> n;
	string garbage, input;

	getline(cin, garbage);

	while (n != 0) {
		Queue<Digit> q;
		Stack<double> s;
		getline(cin, input);
		if (correctNumBrackets(input)) {
			if (convert(input, q))
				calculate(q, s);
			else
				cout << "BLAD" << endl;
		}
		else
			cout << "BLAD" << endl;
		
		n--;
	}

	return 0;
}
