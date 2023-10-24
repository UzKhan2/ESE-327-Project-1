

def convert(string):
    li = list(string.split(" "))
    return li


class Node(object):
    data = None
    sup_count = 0

    def __init__(self, data):
        self.data = data
        self.sup_count = 1
        self.children = []

    def add_child(self, child):
        self.children.append(child)

    def inc_count(self):
        self.sup_count = self.sup_count + 1

    def set_count(self, value):
        self.sup_count = value

    def get_data(self):
        temp = self.data
        return temp

    def get_count(self):
        temp = self.sup_count
        return temp

    def get_children(self):
        temp = self.children
        return temp

    def print_children(self):
        print("Children: ", self.children)

    def print_count(self):
        print("Support Count: ", self.sup_count)

    def print_data(self):
        print("Data: ", self.data)


def traverse(root):
    if root is None:
        return
    print("Current Node: ", root.data)
    print("Count: ", root.sup_count)
    print("Children: ")
    for i in range(0, len(root.children)-1):
        print(root.children[i].data, "(", root.children[i].sup_count, ")")
    print("\n")
    for i, node in enumerate(root.children):
        traverse(node)


def init_tree(node, transaction, index):
    node.children.append(Node(transaction[index]))
    node = node.children[0]
    if index+1 >= len(transaction):
        return
    else:
        init_tree(node, transaction, index + 1)


def update_tree(node, transaction):

    if not transaction:
        return
    else:
        if transaction[0] == node.data:
            node.inc_count()
            transaction.pop(0)
            update_tree(node, transaction)
            return

        else:
            for i, child in enumerate(node.children):
                #print("Child data: ", child.data)
                if transaction[0] == child.data:
                    child.inc_count()
                    transaction.pop(0)
                    update_tree(node.children[i], transaction)
                    return
            node.children.append(Node(transaction[0]))
            transaction.pop(0)
            update_tree(node.children[len(node.children)-1], transaction)
            return


def partition(array, low, high, fq_pattern):
    # choose the rightmost element as pivot
    pivot = fq_pattern[array[high]]
    # pointer for greater element
    i = low - 1

    # traverse through all elements
    # compare each element with pivot
    for j in range(low, high):
        if fq_pattern[array[j]] >= pivot:
            # If element smaller than pivot is found
            # swap it with the greater element pointed by i
            i = i + 1

            # Swapping element at i with element at j
            (array[i], array[j]) = (array[j], array[i])

    # Swap the pivot element with the greater element specified by i
    (array[i + 1], array[high]) = (array[high], array[i + 1])

    # Return the position from where partition is done
    return i + 1


# function to perform quicksort
def quickSort(array, low, high, fq_pattern):
    if low < high:
        # Find pivot element such that
        # element smaller than pivot are on the left
        # element greater than pivot are on the right
        pi = partition(array, low, high, fq_pattern)

        # Recursive call on the left of pivot
        quickSort(array, low, pi - 1, fq_pattern)

        # Recursive call on the right of pivot
        quickSort(array, pi + 1, high, fq_pattern)


def read_dataset(f_name):
    with open(f_name, 'r') as file:
        dataset = []

        for line in file:
            line = line.strip()
            string = str(line)
            string = string.replace(',', ' ')
            li = convert(string)
            dataset.append(li)

    return dataset


def get_fq_pattern(dataset):
    fq_pattern = dict()
    for transaction in dataset:
        for data in transaction:
            if data not in fq_pattern.keys():
                fq_pattern[data] = 1
            else:
                fq_pattern[data] += 1

    fq_pattern = dict(sorted(fq_pattern.items(), key=lambda item: item[1], reverse=True))

    return fq_pattern


def filter_min(fq_pattern, min_sup):
    del_list = list()
    for key in fq_pattern:
        if fq_pattern[key] < min_sup:
            del_list.append(key)

    for key in del_list:
        del fq_pattern[key]

    return fq_pattern


def construct_tree(dataset, fq_pattern, min_sup):
    tree = Node(None)
    #tree.set_count(0)
    tree.set_count(None)

    for transaction in dataset:
        temp = []
        for element in transaction:
            if element in fq_pattern.keys():
                temp.append(element)
        quickSort(temp, 0, len(temp)-1, fq_pattern)

        if len(tree.children) == 0:
            init_tree(tree, temp, 0)
           # traverse(tree)
            continue

        else:
            update_tree(tree, temp)

    traverse(tree)
        # else:
        #     update_tree(tree, transaction)

def main():
    min_sup = 2
    f_name = input("Please enter a file name to scan:  ")
    dataset = read_dataset(f_name)
    fq_pattern = get_fq_pattern(dataset)
    fq_pattern = filter_min(fq_pattern, min_sup)
    print("Frequency Pattern: ", fq_pattern)
    construct_tree(dataset, fq_pattern, min_sup)


if __name__ == "__main__":
    main()
