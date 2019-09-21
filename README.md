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

  -Insert a new account named "Ni".
  
2. (i) n (sert) Ni Nj weight

  -Insert a transaction between Ni and Nj. The accounts Ni and Nj might have not been already inserted.
  
3. d (elete) Ni

  -Delete the account "Ni" as well as all its incoming / outgoing transactions.
  
4. (de) l (s) Ni Nj w

  -Delete the transaction between Ni and Nj by weight "w" . If there are multiple transactions with the same weight
  delete one of the existing ones. If no weight is specified, all existing edges between Ni and
  Nj are deleted.

5. m (odify) Ni Nj w nw

  -Change the weight "w" to the new "nw" value. If there are multiple edges with the same weight value
  change one of the existing ones.
  
6. r (eceiving) Ni

  -Print all incoming transactions.
  
7. c (irclefind) Ni

  -Find out if the node "Ni" is involved in simple cycles and print those cycles.
  
8. f (indcircles) Ni k

  -Find out if the node "Ni" is involved in circular dealings with others. However, the minimum amount that
  each edge must have is 'k" (minimum weight value).

9. t (raceflow) Ni Nj l

  -Find possible distributions of money starting at the node Ni and ending at the node Nj. "l" is the maximum length
  of the path(number of edges to be traversed).
  
10. e (xit)

  -Terminate the application.


Execution:

The application can be called in the following strict manner on the command line:

./mygraph -i inputfile -o outfile

where

• mygraph is the executable (can be created by the "makefile"),

• inputfile is the data entry file. In this, each line expresses an transactions between two accounts
and provides the amount of the transaction.

• outfile is the output file that records the status at the time your application exits.

Both of the above in-line parameters (and their corresponding flags) are optional. Flags can be displayed
in any order.

make makefile
./mygraph
i george
i john
i jack
d jack
n george john 10
n george john 20
l george john 10
