# BankTransactions
Implementation of a directed multi-graph structure that illustrates money transfers between different banks accounts.
The graph provides a mechanism that can help track traffic money and in clarifying poly / triangular transfers.

Application features:

1.Dynamic directed multi-graph structure. There are no restrictions on the size of the graph (ie number
of vertices/edges available). Each (directed) edge has a weight that essentially indicates
the total amount of transaction between two nodes.

2.Searching of graph circles, finding of money flow and printing its structure in a user-understandable way.

3.Ability to add or delete accounts and transactions during the execution of the application and adjust
the values of (existing) edges.


Application Interface:

Once the program is called, the user can interact with the help of the command prompt through
the following commands:
1. i (nsert) Ni
  insert a new account named "Ni".
2. (i) n (sert) Ni Nj weight
  insert a transaction between Ni and Nj. The accounts Ni and Nj might have not been already inserted.
3. d (elete) Ni
  delete the account "Ni" as well as all its incoming / outgoing transactions.
4. (de) l (s) Ni Nj w
  delete the transaction between Ni and Nj by weight "w" . If there are multiple transactions with the same weight
delete one of the existing ones. If no weight is specified, all existing edges between Ni and
Nj are deleted.
5. m (odify) Ni Nj w nw
  change the weight "w" to the new "nw" value. If there are multiple edges with the same weight value
  change one of the existing ones.
6. r (eceiving) Ni
  print all incoming transactions.
7. c (irclefind) Ni
  find out if the node "Ni" is involved in simple cycles and print those cycles.
  
8. f (indcircles) Ni k
  find out if the node "Ni" is involved in circular dealings with others. However, the minimum amount that
each edge must have is 'k" (minimum weight value).
9. t (raceflow) Ni Nj l
  find possible distributions of money starting at the node Ni and ending at the node Nj. "l" is the maximum length
  of the path(number of edges to be traversed).
10. e (xit)
  terminate the application.
  
  eg. 
  i george
  i john
  i jack
  d jack
  n george john 10
  n george john 20
  l george john 10
