#include<iostream>

using namespace std;

int valtab[127]; //used for integer values of variables

class Node {
	friend class Tree;
	friend ostream& operator<<(ostream&, const Tree&);
public:
	Node() { cout << "node constructor" << endl; use = 1; }
	virtual ~Node() { cout << "node destructor" << endl; }
	virtual void print(ostream&) = 0;
	virtual int eval() = 0;

protected:
	int use;//reference count -GC
};

class Tree {
	friend class Node;
	friend ostream& operator<<(ostream&, const Tree&);
public:
	Tree(int);//constant
	Tree(char);//variable
	Tree(char, Tree);//unary operator
	Tree(char, Tree, Tree);//binary operator
	Tree(const Tree& t) { cout << "tree copy constructor" << endl; p = t.p; ++p->use; }
	~Tree() { cout << "tree destructor" << endl; if (--p->use == 0) delete p; }
	void operator=(const Tree& t);
	int eval() { return p->eval(); }
protected:
	Node* p;
};

class LeafNode : public Node {
	friend class Tree;
	void print(ostream&) = 0;
	virtual int eval() = 0;
};

class IntNode :public LeafNode {//leaf node with a constant int value
	friend class Tree;
public:
	void print(ostream& o) { o << n; }
	IntNode(int k) :n(k) { cout << "constant leaf node constructor" << endl; }
	int eval() { return n; }
protected:
	int n;
};

class IdNode :public LeafNode {//leaf node that corresponds to a variable
	friend class Tree;
public:
	int eval() { return valtab[name]; }
	void print(ostream& o) { o << name; }
	IdNode(char id) :name(id) { cout << "identifier node constructor" << endl; }
protected:
	char name;
};

class UnaryNode :public Node {
	friend class Tree;
public:
	UnaryNode(char a, Tree b) :op(a), opnd(b) { cout << "node with unray operator constructor" << endl; }
	void print(ostream& o) { o << "(" << op << opnd << ")"; }
	int eval();
protected:
	char op;
	Tree opnd;
};

int UnaryNode::eval() {
	switch (op) {
	case'-': return(-opnd.eval());
	case'+': return(+opnd.eval());
	default: cerr << "no operand\n" << endl;
	}
	return 0;
}

class BinaryNode : public LeafNode {
	friend class Tree;
public:
	BinaryNode(char a, Tree b, Tree c) :op(a), left(b), right(c) { cout << "node with binary operator constructor" << endl; }
	void print(ostream& o) { o << "(" << left << op << right << ")"; }
	int eval();
protected:
	char op;
	Tree left, right;
};

int BinaryNode::eval() {
	switch (op) {
	case'-': return(left.eval() - right.eval());
	case'+': return(left.eval() + right.eval());
	case'*': return(left.eval() * right.eval());
	default: cerr << "no operand\n" << endl;
	}
	return 0;
}

void Tree:: operator=(const Tree& t){
	cout << "tree copy assignement" << endl;
	++t.p->use;
	if (--p->use == 0)
		delete p;
	p = t.p;
}

Tree::Tree(int n) {
	cout << "tree with integer constant node constructor" << endl;
	p = new IntNode(n); 
}

Tree::Tree(char id) {
	cout << "tree with identifier node constructor" << endl;
	p = new IdNode(id);
 }

Tree::Tree(char op, Tree t) {
	cout << "tree with unary node constructor" << endl;
	p = new UnaryNode(op, t);
}

Tree::Tree(char op, Tree left, Tree right) {
	cout << "tree with binary node constructor" << endl;
	p = new BinaryNode(op, left, right);
}

ostream& operator<<(ostream& o, const Tree& t) {
	t.p->print(o);
	return o;
}

int main() {
	valtab['A'] = 3; valtab['B'] = 4;
	cout << "A = 3,  B = 4" << endl;
	Tree t1 = Tree('*', Tree('-', 5), Tree('+', 'A', 4));
	Tree t2 = Tree('+', Tree('-', 'A', 1), Tree('+', t1, 'B'));
	cout << "t1 = " << t1 << " ;  t2 = " << t2 << endl;
	cout << "t1:" << t1.eval() << "  t2:" << t2.eval() << endl;
	return 0;
}
