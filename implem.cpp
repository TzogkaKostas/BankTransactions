#include "classes.h"
#include <fstream>
//----EDGE FUNCTIONS
string edge::get_str_edge() {
	vertex *v1,*v2;
	v1 = get_source();
	v2 = get_destination();
	return "|" + v1->get_name() + "|"
		+"->"+to_string(get_weight())+"->"+"|"+v2->get_name()+"|"; //returns the edge as a string(e.g. a->2->b)
}

string edge::get_str_dest() {
	vertex *v1,*v2;
	v1 = get_source();
	v2 = get_destination();
	return 
	"->"+to_string(get_weight())+"->"+"|"+v2->get_name()+"|";////return a string like this 2->b
}
void edge::set_weight(int w) {
	weight = w;
	return;
}

void edge::set_direction(bool b) {
	direction = b;
}

//----EDGE_LIST FUNCTIONS
void edge_list::insert(vertex *v1,vertex *v2,int w,bool b) {
	node_edge *temp = new node_edge(v1,v2,w);
	temp->myedge.set_direction(b);
	temp->next = head;
	head = temp;
	size++;
	return;
}

int edge_list::delete_enode(string s,string d,int w) {
	struct node_edge *cur,*prev;
	string s1,s2;
	int n;
	if (head == NULL) return -1;
	cur = head;
	s1 = cur->myedge.get_source()->get_name();
	s2 = cur->myedge.get_destination()->get_name();
	n = cur->myedge.get_weight();
	if (s1 == s && s2 == d && n == w) { //in case we delete the first node.
		head = head->next;
		delete cur;
		size--;
		return 0;

	}
	while (cur != NULL) {
		s1 = cur->myedge.get_source()->get_name();
		s2 = cur->myedge.get_destination()->get_name();
		n = cur->myedge.get_weight();
		if ( s1 == s && s2 == d && n == w) {
			prev->next = cur->next;
			delete cur;
			size--;
			return 0;
		}
		else {
			prev = cur;
			cur = cur->next;
		}
	}
	return -1;
}
						//prints all edges
void edge_list::print_list() {
	struct node_edge *temp;
	temp = head;
	while(temp != NULL) {
		cout<<"\t"<<temp->get_str_edge()<<endl;
		temp = temp->next;
	}
	return;
}
						//prints internal edges
int edge_list::print_in_list(string s) {
	struct node_edge *temp;
	string s1;
	temp = head;
	int count = 0;
	while(temp != NULL) {
		s1 = temp->myedge.get_source()->get_name();
		if (s1 != s) {
			if (count == 0) {
				cout <<"Rec-edges ";
			}
			cout<<temp->get_str_edge()<<endl;
			count++;
		}
		temp = temp->next;
	}
	return count;
}
						//prints external edges
void edge_list::print_out_list(string s) { 
	struct node_edge *temp;
	string s1;
	temp = head;

	while(temp != NULL) {
		s1 = temp->myedge.get_source()->get_name();
		if (s1 == s) {
			cout<<"\t"<<temp->get_str_edge()<<endl;
		}
		temp = temp->next;
	}
	return;
}
						//deletes whole list(called by destructor)
void edge_list::delete_list() {
	struct node_edge *temp;
	while(head != NULL) {
		temp = head;
		head = head->next;
		delete temp;
	}
	return; 
}
		//deletes edges pointing to "s" vertex.
void edge_list::delete_edges_to_dest(string s) {
	struct node_edge *temp;	
	vertex *v1,*v2;
	string s1,s2;
	int w;
	temp = head;
	while(temp != NULL) { //for each edge, we find the destination vertex
		v1 = temp->myedge.get_source(); //and we call delete_edge function
		s1 = v1->get_name();			// to delete those edges there too.
		v2 = temp->myedge.get_destination();
		s2 = v2->get_name();
		w = temp->myedge.get_weight();
		if (s1 == s2) {//if we have an edge with the same src and dst vertex
			temp = temp->next; //we do nothing
			continue;
		}
		if (s1 == s) { //if s1==s edge is internal edge
			v2->delete_edge(s1,s2,w); //so v2 is destination vertex
		}
		else {	//if s1!=s (s2==s) edge is external
			v1->delete_edge(s1,s2,w); //so v1 is destination vertex
		}
		temp = temp->next;
	}
	return;
}

edge* edge_list::find_edge(string s,string d,int w) {
	struct node_edge *temp;
	string s1,s2;
	int n;
	temp = head;
	while (temp != NULL) {
		s1 = temp->myedge.get_source()->get_name();
		s2 = temp->myedge.get_destination()->get_name();
		n = temp->myedge.get_weight();
		if (s1 == s && s2 == d && n == w) {
			return temp->get_edge();
		}
		temp = temp->next;
		
	}
	return NULL;
}
		//deletes all edges beetween and vertex
int edge_list::delete_edges(string s,string d) {
	struct node_edge *cur,*prev;
	string s1,s2;
	int n;
	if (head == NULL) return -1;
	cur = head;
	prev = head;
	s1 = cur->myedge.get_source()->get_name();
	s2 = cur->myedge.get_destination()->get_name();
	while (cur != NULL && s1 == s && s2 == d) { //in case we delete first node.
		head = head->next;
		delete cur;
		cur = head;
		if (cur == NULL) break;
		s1 = cur->myedge.get_source()->get_name();
		s2 = cur->myedge.get_destination()->get_name();
		size--;
	}

	while (cur != NULL) {
		if ( s1 == s && s2 == d) {
			prev->next = cur->next;
			delete cur;
			cur = prev->next;
			size--;
		}
		else {
			prev = cur;
			cur = cur->next;
		}
		if (cur == NULL) break;
		s1 = cur->myedge.get_source()->get_name();
		s2 = cur->myedge.get_destination()->get_name();
	}
	return 0;
}
		//prints the graph to file 
void edge_list::print_list_file(string s,ofstream *my_file) {
	struct node_edge *temp;
	string s1;
	temp = head;

	while(temp != NULL) {
		s1 = temp->myedge.get_source()->get_name();
		if (s1 == s) {
			*my_file<<"\t"+temp->get_str_dest()<<endl;
			//cout<<"\t"<<temp->get_str_dest()<<endl;
		}
		temp = temp->next;
	}
	return;
}

//----VERTEX FUNCTIONS
void vertex::insert_edge(vertex *v1,vertex *v2,int w,bool b) {
	edges_list.insert(v1,v2,w,b);
	return;
}

int vertex::delete_edge(string s,string d,int w) {
	return edges_list.delete_enode(s,d,w);
}

void vertex::print_edges() {
	edges_list.print_list();
	return;
}

int vertex::print_in_edges(string s) {
	return edges_list.print_in_list(s);
}

void vertex::print_out_edges(string s) {
	edges_list.print_out_list(s);
	return;
}

void vertex::print_edges_file(string s,ofstream *my_file) {
	edges_list.print_list_file(s,my_file);
	return;
}

void vertex::delete_edges_to_dest(string s) {
	edges_list.delete_edges_to_dest(s);
	return;
}

int vertex::modify_weight(string s,string d,int w,int nw) {
	edge *temp;
	temp = edges_list.find_edge(s,d,w);
	if (temp == NULL) {
		return -1;
	}
	temp->set_weight(nw);
	return 0;
}

void vertex::delete_edges(string s,string d) {
	edges_list.delete_edges(s,d);
	return;
}

//----VERTEX_LIST FUNCTIONS
vertex* vertex_list::insert(string x) {
	node_vertex *temp = new node_vertex(x);
	temp->next=head;
	head=temp;
	size++;
	return &temp->myvertex;
}
	//inserts a node to the list ,whose memory is already allocated
void vertex_list::insert_by_address(node_vertex* n_v) {
	n_v->next = head;
	head = n_v;
	size++;
	return;
}

vertex* vertex_list::find_vertex(string s) {
	struct node_vertex *temp;
	temp = head;
	while (temp != NULL) {
		if ( temp->get_vertex_name() == s) {
			return temp->get_vertex();
		}
		temp = temp->next;
	}
	return NULL;
}

int vertex_list::delete_vnode(string s) {
	struct node_vertex *cur,*prev;
	cur = head;
	if (head == NULL) return -1; //empty list
	if (head->get_vertex_name() == s) { //in case we delete the first node.
		head = head->next;
	//VERTICES WITH EDGES POINTING TO THIS VERTEX MUST DELETE THOSES EDGES FIRST
		cur->myvertex.delete_edges_to_dest(s);
		delete cur;
		return 0;

	}
	while (cur != NULL) {
		if (cur->get_vertex_name() == s) {
			prev->next = cur->next;
	//VERTICES WITH EDGES POINTING TO THIS VERTEX MUST DELETE THOSES EDGES FIRST
			cur->myvertex.delete_edges_to_dest(s);
			delete cur;
			return 0;
		}
		else {
			prev = cur;
			cur = cur->next;
		}
	}
	return -1;
}

void vertex_list::print_list() {
	struct node_vertex *temp;
	temp=head;
	while(temp!=NULL) {
		cout<<temp->get_vertex_name()<<" ";
		temp=temp->next; 
	}
	return;
}

void vertex_list::delete_list() {
	struct node_vertex *temp;
	while(head!=NULL) {
		temp=head;
		head=head->next;
		delete temp;
	}
	return;
}

vertex* vertex_list::get_first_vertex() {
	if (head == NULL) {
		return NULL;
	}
	else {
		return head->get_vertex();
	}
}


//----GRAPH FUNCTIONS
void graph::print_graph() {
	string name;
	struct node_vertex *temp;
	vertex_list* temp_table;
	temp_table = myhash_table.get_h_table();
	for (int i = 0 ; i < myhash_table.get_h_size(); i++) {
		temp = temp_table[i].get_head();
		while (temp != NULL) {
			cout<<"|"<<temp->get_vertex_name()<<"|"<<endl;
			temp->get_vertex()->print_out_edges(temp->get_vertex_name());
			temp=temp->next; 
		}
	}
	return;
}

void graph::print_vertices() {
	myhash_table.hash_print();
	return;
}

vertex* graph::insert_vertex(string x) {
	vertex *v;
	if ( find_vertex(x) != NULL ) {
		return NULL;
	}
	v = myhash_table.hash_insert(x);
	return v;
}

void graph::insert_edge(string s,string d,int w) {
	vertex *v1;
	vertex *v2;
	numEdges++;
	v1 = find_vertex(s);
	if (v1 == NULL) {
		v1 = insert_vertex(s);
	}

	if (s == d) { //in case we have an edge with the same source and destination.
		v1->insert_edge(v1,v1,w,true);
		return;
	}

	v2 = find_vertex(d);
	if (v2 == NULL) {
		v2 = insert_vertex(d);
	}
	v1->insert_edge(v1,v2,w,true);
	v2->insert_edge(v1,v2,w,false);
	return;
}

int graph::delete_vertex(string s) {
	return myhash_table.hash_delete(s);
	
}

int graph::delete_edge(string s,string d,int w) {
	vertex *v1,*v2;
	v1 = find_vertex(s);
	if (v1 == NULL) {
		return -1;
	}
	v2 = find_vertex(d);
	if (v2 == NULL) {
		return -2;
	}
	if (w > 0) {
		if (s == d) {
			if ( v1->delete_edge(s,d,w) == -1 ) {
				return -3;
			}
		}
		else {
			if ( v1->delete_edge(s,d,w) == -1 ) {
				return -3;
			}
			if ( v2->delete_edge(s,d,w) == -1 ) {
				return -3;
			}
		}
	}
	else {
		v1->delete_edges(s,d);
		v2->delete_edges(s,d);
	}
	return 0 ;
}

int graph::modify(string s,string d,int w,int nw) {
	vertex *v1,*v2;
	v1 = find_vertex(s);
	if (v1 == NULL) {
		return -1; 
	}
	v2 = find_vertex(d);
	if (v2 == NULL) {
		return -2;
	}
	if (s == d) {
		if (v1->modify_weight(s,d,w,nw) == -1) {
			return -3;
		}
	}
	else {
		if (v1->modify_weight(s,d,w,nw) == -1) {
			return -3;
		}
		if (v2->modify_weight(s,d,w,nw) == -1) {
			return -3;
		}
	}
	return 0;
}

int graph::receiving(string s) {
	vertex *v;
	v = find_vertex(s);
	if (v == NULL) {
		return -1;
	}
	return v->print_in_edges(s);
	
}

vertex* graph::find_vertex(string s) {
	return myhash_table.hash_find(s);
}

int graph::circle_find(string s) {
	vertex *v;
	int res = 0;
	v = find_vertex(s);
	if (v == NULL) {
		return -1;
	}
	stack mystack(get_numEdges());
	simple_cycles(&mystack,v,s,&res);
	return res;
}

int graph::find_circles(string s,int min_w) {
	vertex *v = find_vertex(s);
	int res = 0;
	if (v == NULL) {
		return -1;
	}
	stack mystack2(get_numEdges());
	cycles(&mystack2,v,s,min_w,&res);
	return res;
}

int graph::traceflow(string s,string d,int l) {
	vertex *v1,*v2;
	int res = 0;
	v1 = find_vertex(s);
	if (v1 == NULL) {
		return -1;
	}
	v2 = find_vertex(d);
	if (v2 == NULL) {
		return -2;
	}
	stack mystack(get_numVertices());	
	paths(&mystack,v1,d,l,&res);
	return res;
}
			//res(result) is used in order to know that at least a path was found.
void graph::simple_cycles(stack *stack_ptr,vertex *v,string goal,int *res) {
	string str,name;
	node_edge *temp;
	vertex *w;
	temp = v->get_edge_list()->get_head(); //we get the first edge
	while(temp != NULL) {
		if (temp->myedge.is_outer() == false) { //we only check external edges
			temp=temp->next;
			continue; //otherwise we continue to the next edge
		}
		w = temp->myedge.get_destination();
		str = temp->myedge.get_destination()->get_name();
		if (stack_ptr->is_vertex_there(w) == true && str!=goal) {
			temp = temp->next;
			continue;
		}
		if (str == goal) {
			if (*res == 0) {
				cout <<"Cir-found "; 
			}
			(*res)++;
			stack_ptr->push(temp); //in case we find and an edge pointing to the goal vertex
			stack_ptr->print();		//we push it to the stack in order to print the path
			cout<<"|"<<goal<<"|"<<endl;
			stack_ptr->pop(); //and we pop that edge again
			temp = temp->next;
			continue;
		}
		if (stack_ptr->is_vertex_there(w) == false) {
			stack_ptr->push(temp); //in case we didnt find the edge pointing to the "goal" vertex 
			simple_cycles(stack_ptr,w,goal,res);//we continue the searching
		}
		temp = temp->next;
	}
	stack_ptr->pop();
	return;
}

void graph::cycles(stack *stack_ptr,vertex *v,string goal,int min_w,int *res) {
	string str,name;
	node_edge *temp;
	vertex *w;
	int weight;
	name = v->get_name();
	temp = v->get_edge_list()->get_head();

	while(temp != NULL) {
		if (temp->myedge.is_outer() == false) {
			temp=temp->next;
			continue;
		}
		w = temp->myedge.get_destination();
		str = w->get_name();
		weight = temp->myedge.get_weight();
		if (weight < min_w) {
			temp = temp->next;
			continue;
		}
		if (str == goal && stack_ptr->is_there(temp) == false) {
			if (*res == 0) {
				cout <<"Cir-found ";
			}
			(*res)++;
			stack_ptr->push(temp);
			stack_ptr->print();
			cout<<"|"<<goal<<"|"<<endl;
			cycles(stack_ptr,w,goal,min_w,res);
			temp = temp->next;
			continue;
		}
		if (stack_ptr->is_there(temp) == true) {
			temp = temp->next;
			continue;
		}
		else {
			stack_ptr->push(temp);
			cycles(stack_ptr,w,goal,min_w,res);
		}
		temp = temp->next;
	}
	stack_ptr->pop();
	return;
}

void graph::paths(stack *stack_ptr,vertex *v,string goal,int l,int *res) {
	string str,name;
	node_edge *temp;
	vertex *w;
	int weight;
	if (l == 0) {
		stack_ptr->pop();
		return;
	}
	name = v->get_name();
	temp = v->get_edge_list()->get_head();
	
	while(temp != NULL) {
		if (temp->myedge.is_outer() == false) {
			temp=temp->next;
			continue;
		}
		w = temp->myedge.get_destination();
		str = w->get_name();
		weight = temp->myedge.get_weight();
		if (str == goal ) {
			if (*res == 0) {
				cout <<"Tra-found ";
			}
			(*res)++;
			stack_ptr->push(temp);
			stack_ptr->print();
			cout<<"|"<<goal<<"|"<<endl;
			paths(stack_ptr,w,goal,l-1,res);
			temp = temp->next;
			continue;
		
		}
		if (stack_ptr->is_there(temp) == true) {
			temp = temp->next;
			continue;
		}
		else {
			stack_ptr->push(temp);
			paths(stack_ptr,w,goal,l-1,res);
		}
		temp = temp->next;
	}
	stack_ptr->pop();
	return ;
}

void graph::print_to_file(ofstream *my_file) {
	string name;
	struct node_vertex *temp;
	vertex_list* temp_table;
	temp_table = myhash_table.get_h_table();
	for (int i = 0 ; i < myhash_table.get_h_size(); i++) {
		temp = temp_table[i].get_head();
		while (temp != NULL) {
			*my_file <<"|"<<temp->get_vertex_name()<<"|"<<endl;
			//cout <<"|"<<temp->get_vertex_name()<<"|"<<endl;
			temp->get_vertex()->print_edges_file(temp->get_vertex_name(),my_file);
			temp=temp->next; 
		}
	}
	return;
}


//----stack functions
stack::stack(int stack_size) {
	top = 0;
	edge_array = new node_edge*[stack_size];
}

stack::~stack() {
	delete[] edge_array;
}

void stack::push(node_edge *ne_ptr) {
	edge_array[top++] = ne_ptr;
	return;
}

node_edge* stack::pop() {
	return edge_array[--top];
}

void stack::print() {
	edge *e;
	for (int i=0; i<top; i++) {
		e = edge_array[i]->get_edge();
		cout<<"|" + e->get_source()->get_name() + "|->"
			<<e->get_weight()<<"->";
	}
}

bool stack::is_there(node_edge *ne_ptr) {
	for (int i=0; i<top; i++) {
		if (edge_array[i] == ne_ptr) return true;
	}
	return false;
}
	//returns true if an edge ,which is pointing to "v" exists in the stack
bool stack::is_vertex_there(vertex *v) {
	for (int i=0; i<top; i++) {
		if (edge_array[i]->myedge.get_destination() == v) {
			return true;
		}
	}
	return false;
}


///// HASH TABLE
hash_table::hash_table(int initial_size) {
	threshold = 0.8;
	tablesize = initial_size;
	maxVertices = int (threshold * tablesize);
	numVertices = 0;
	table = new vertex_list[tablesize];
}

hash_table::~hash_table() {
	delete[] table;
}

int hash_table::hash_function(string key) {
	unsigned long int hash = 5381;
	for(int i = 0; i <= key.length()-1; i++ )
		//hash += key[i];
		hash = (hash << 5) + hash  + key[i];
	return hash % tablesize;
}

vertex* hash_table::hash_find(string key) {
	vertex* v;
	int hash = hash_function(key);
	v = table[hash].find_vertex(key);
	return v;
}

vertex* hash_table::hash_insert(string key) {
	vertex *v=NULL;
	int hash = hash_function(key);
	if (hash_find(key) != NULL) {
		return v;
	}
	v = table[hash].insert(key);
	numVertices++;
	if (numVertices >= maxVertices) {
		hash_resize();
	}
	return v;
}

int hash_table::hash_delete(string key) {
	int hash = hash_function(key);
	if (table[hash].delete_vnode(key) == -1) {
		return -1;
	}
	numVertices--;
	return 0;
}

void hash_table::hash_resize() {
	int new_hash;
	vertex *v;
	node_vertex *temp;
	node_vertex **temp_head;
	vertex_list *prev_table = table;//we keep the a ptr to previous table
	int prev_table_size = tablesize;//and previous table size
	tablesize *= 2; 
	maxVertices = (int) (tablesize * threshold); //
	string key;
	table = new vertex_list[tablesize]; //we create a new table
	for (int i = 0 ; i < prev_table_size; i++) { //for each list of previous table
		temp = prev_table[i].get_head(); //we get the first node of the list and the the address of the head of
		temp_head = prev_table[i].get_head_ptr(); //the list because we may need to change its value
		while (temp != NULL ) {
			key = temp->get_vertex_name(); //we get the name of the vertex
			new_hash = hash_function(key); //we find its hash value
			prev_table[i].set_head(temp->next);//we make the the head ,which we got before,point to the next node
			temp_head = prev_table[i].get_head_ptr(); //and we get it the head again

			table[new_hash].insert_by_address(temp);//we put it to the new table()
			temp = prev_table[i].get_head(); //and we get the first node of list again
		}
	}
	delete[] prev_table;
}

void hash_table::hash_print() {
	for(int i = 0; i < tablesize; i++) {
		cout <<"table["<<i<<"] : ";
		table[i].print_list();
		cout <<endl;
	}
	return;
}