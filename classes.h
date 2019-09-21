#include <iostream>

using namespace std;

class vertex;
class stack;
class stack2;

class edge {
public:
	edge(vertex* s,vertex* d,int w) : src(s),dest(d),weight(w){}
	int get_weight() {return weight;}
	vertex* get_source() {return src;}
	vertex* get_destination() {return dest;}
	string get_str_edge();
	string get_str_dest();
	void set_weight(int);
	void set_direction(bool);
	bool is_outer() {return direction;}
private:
	vertex *src;
	vertex *dest;
	int weight;
	bool direction;  //true == outer edge,false == inner
};

struct node_edge {
	edge myedge;
	node_edge *next;
	node_edge(vertex* s,vertex* d,int w) : myedge(s,d,w) {}
	string get_str_edge() {return myedge.get_str_edge();}
	string get_str_dest() {return myedge.get_str_dest();}
	edge* get_edge() {return &myedge;}
};

class edge_list {
public:
	edge_list():head(NULL),size(0) {}
	~edge_list() {delete_list();}

	void insert(vertex*,vertex*,int,bool);
	int delete_enode(string,string,int);
	void print_list();
	int print_in_list(string);
	void print_out_list(string);
	void delete_list();
	void delete_edges_to_dest(string);
	edge* find_edge(string,string,int);
	int delete_edges(string,string);
	void print_list_file(string,ofstream*);

	node_edge* get_head() {return head;}
private:
	node_edge *head;
	int size;
};



class vertex {
public:
	vertex(string x) : name(x){}

	void insert_edge(vertex*,vertex*,int,bool);
	int delete_edge(string,string,int);
	void print_edges();
	int print_in_edges(string);
	void print_out_edges(string);
	void delete_edges_to_dest(string);
	int modify_weight(string,string,int,int);
	void delete_edges(string,string);
	string get_name() {return name;}
	edge_list* get_edge_list() {return &edges_list;}
	void print_edges_file(string,ofstream*);
private:
	string name;
	edge_list edges_list;
};

struct node_vertex {
	vertex myvertex;
	node_vertex *next;
	node_vertex(string x) : next(NULL),myvertex(x)
	{}

	string get_vertex_name() {return myvertex.get_name();}
	vertex* get_vertex() {return &myvertex;}
}; 

class vertex_list {
public:
	vertex_list() : head(NULL),size(0) {}
	~vertex_list() {delete_list();}


	vertex* insert(string);
	void insert_by_address(node_vertex*);
	vertex* find_vertex(string);
	node_vertex* get_head() {return head;}
	node_vertex** get_head_ptr() {return &head;}
	int delete_vnode(string);

	void print_list();
	void delete_list();
	int get_size() {return size;}
	vertex* get_first_vertex();
	void set_head(node_vertex* n_v) {head = n_v;}

private:
	node_vertex *head;
	int size;
};

class hash_table{
public:
	hash_table(int);
	~hash_table();

	int hash_function(string);
	vertex* hash_insert(string);
	int hash_delete(string);
	vertex* hash_find(string);
	void hash_resize();
	void hash_print();
	int get_h_size() {return tablesize;}
	int get_h_numVertices() {return numVertices;}
	vertex_list* get_h_table() {return table;}
private:
	double threshold;
	int maxVertices;	//max size of table before resize
	int tablesize; //the size of the array
	int numVertices;	//the current table size
	vertex_list *table;
};

class graph {
public:
	graph(int h_t_size) :numEdges(0),myhash_table(h_t_size){}

	vertex* find_vertex(string);
	void print_vertices();
	void print_graph();
	vertex* insert_vertex(string);
	int delete_vertex(string);
	void insert_edge(string,string,int);
	int delete_edge(string,string,int);
	int modify(string,string,int,int);
	int receiving(string);
	int circle_find(string);
	int find_circles(string,int);
	void print_to_file(ofstream*);
	int traceflow(string,string,int);

	int get_numVertices() {return myhash_table.get_h_numVertices();}
	int get_tablesize() {return myhash_table.get_h_size();}
	int get_numEdges() {return numEdges;}
private:
	hash_table myhash_table;
	int numEdges;
	void simple_cycles(stack*,vertex*,string,int*);
	void cycles(stack*,vertex*,string,int,int*);
	void paths(stack*,vertex*,string,int,int*);
	
};

class stack {
public:
	stack(int);
	~stack();

	void push(node_edge*);
	node_edge* pop();
	int get_top() {return top;}
	void print();
	bool is_there(node_edge*);
	bool is_vertex_there(vertex*);
	
private:
	node_edge **edge_array;
	int top;
};