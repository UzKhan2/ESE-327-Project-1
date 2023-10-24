# ESE-327-Project-1

Implement the Frequent Pattern Growth Algorithm for mining frequent  item sets:                                                                      

- The algorithm implements a tree system to store the frequent data sets in order
- Have an array containing pointers linking all like data sets
- Minimize run time
 
 <br /> Program inputs:

- Data Values (CSV)
- Data Names

# Frequent Pattern Growth Algorithm

<br /> Data Preprocessing:

Convert the dataset into a transactional format. This means representing it as a collection of sets, where each set contains items that occur together in a transaction.

<br /> 1) First Pass - Counting Support:

Scan the dataset to count the support (frequency of occurrence) of each item.

<br /> 2) Sort Items by Support:

Sort the items in descending order of support. This helps in building the FP-tree efficiently.

<br /> 3) Build the FP-Tree:

Start with an empty FP-tree. For each transaction in the dataset: Sort the items in the transaction according to their support. Add the sorted transaction to the FP-tree. If a path with the same items already exists in the tree, increment the count of the existing path.

<br /> 4) Build the Header Table:

Create a header table to keep track of the first occurrence of each item in the FP-tree. This table will be used for efficient navigation and linking of nodes.

<br /> 5) Mine Frequent Itemsets:

For each item in the header table (starting with the least frequent), do the following: Generate conditional pattern bases: For each occurrence of the item in the FP-tree, traverse the tree upwards (following parent links) to collect the prefix path. Build a conditional FP-tree from the prefix paths. Recursively mine the conditional FP-tree.

<br /> 6) Combine Results:

Combine the frequent itemsets obtained from each recursion to get the final set of frequent itemsets. Repeat for All Items: Repeat step 5 for all items in the header table.

<br /> 7) Return Frequent Itemsets:

The final step is to collect and return all the frequent itemsets.
