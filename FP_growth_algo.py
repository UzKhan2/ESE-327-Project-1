def convert(string):
    li = list(string.split(" "))
    return li


class ConditionPattern:
    pattern = []
    count = 0

    def __init__(self, count):
        self.pattern = []
        self.count = 0

    def set_count(self, cnt):
        self.count = cnt

    def update_pattern(self, str_list):
        self.pattern.append(str_list)

    def print_pattern(self):
        print("Pattern: ")
        for str_list in self.pattern:
            print(str_list)

    def get_pattern(self):
        temp = self.pattern
        return temp

    def get_count(self):
        temp = self.count
        return temp


class Node(object):
    data = None
    sup_count = 0
    children = []
    parent = []

    def __init__(self, data, count):
        self.data = data
        self.sup_count = count
        self.children = []
        self.parent = []

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

    def inc_count_value(self, value):
        self.sup_count = self.sup_count + value

    def get_parent(self):
        temp = self.parent[0]
        return temp

    def get_children(self):
        temp = self.children
        return temp

    def print_children(self):
        for item in self.children:
            print("Data = %s   Count = %d" % (item.get_data(), item.get_count()))

    def print_count(self):
        print("Support Count: ", self.sup_count)

    def print_data(self):
        print("Data: ", self.data)

    def print_node(self):
        print("Data: ", self.data, "   [Count=", self.sup_count, "]")

    def set_parent(self, prev):
        self.parent.append(prev)

    def print_parent(self):
        print("Parent Node: ")
        if len(self.parent):
            print("Data: ", self.parent[0].get_data(), "   [Count=", self.parent[0].get_count(), "]")
        else:
            print("No parent node")


class Header:
    pointer = ""
    pointerList = []

    def __init__(self, ptr):
        self.pointer = ptr
        self.pointerList = []

    def add_pointer(self, ptr):
        self.pointerList.append(ptr)

    def print_list(self):
        if self.pointerList:
            print("Pointer Info: ")
            for element in self.pointerList:
                element.print_node()
        else:
            print("List is empty")

    def set_pointer(self, ptr):
        self.pointer = ptr

    def get_pointer(self):
        temp = self.pointer
        return temp

    def get_list(self):
        temp = self.pointerList
        return temp


def print_tree(root):
    if root is None:
        return
    print("Node: ", root.data)
    print("Count: ", root.sup_count)
    print(root.print_parent())
    print("Children nodes: ")
    if not root.children:
        print("No children node")
    else:
        root.print_children()
        # for i in range(0, len(root.children)-1):
        #     print(root.children[i].get_data(), "[count=", root.children[i].get_count(), "]")

    print(" ")
    for i, node in enumerate(root.children):
        print_tree(node)


def init_tree(node, transaction, index):

    #print("Parent: ", node.parent[0].get_data())
    node.children.append(Node(transaction[index], 1))
    temp = node
    node = node.children[0]
    node.set_parent(temp)
   # print("Node's parent: ", node.parent[0].data)
    if index+1 >= len(transaction):
        return
    else:
        init_tree(node, transaction, index + 1)


def update_tree(node, transaction):

    if not transaction:
        return
    else:
        # if transaction[0] == node.data:
        #     node.inc_count()
        #     transaction.pop(0)
        #     #update_tree(node, transaction)
        #     if not transaction:
        #         return
        for i, child in enumerate(node.children):
            #print("Child data: ", child.data)
            if transaction[0] == child.data:
                node.children[i].inc_count()
                transaction.pop(0)
                update_tree(node.children[i], transaction)
                return
        node.children.append(Node(transaction[0], 1))
        node.children[-1].parent.append(node)
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
    tree = Node(None, 0)
    tree.set_count(None)

    for transaction in dataset:
        temp = []
        for element in transaction:
            if element in fq_pattern.keys():
                temp.append(element)
        quickSort(temp, 0, len(temp)-1, fq_pattern)

        if len(tree.children) == 0:
            init_tree(tree, temp, 0)
            continue

        else:
            update_tree(tree, temp)
    return tree


def getHeader(tree, fq_pattern):

    header_table = dict()

    for key in reversed(fq_pattern.keys()):
        header_table[key] = Header(key)

    queue = [tree]
    while queue:
        curr = queue[0]
        queue.pop(0)
        if curr.get_data() in header_table:
            temp_header = header_table[curr.get_data()]
            temp_header.pointer = curr.get_data()
            temp_header.pointerList.append(curr)
            header_table[curr.get_data()] = temp_header
        for child in curr.children:
            queue.append(child)

    # for element in header_table.values():
    #     print("Pointer: ", element.get_pointer())
    #     for item in element.get_list():
    #         item.print_parent()
    #     print()

    return header_table


def extract_path(header):
    li = []

    for pointer in header.pointerList:
        condition_pattern = ConditionPattern(0)
        curr = pointer
        condition_pattern.set_count(curr.get_count())
        while curr.parent[0]:
            if not curr.parent[0].data:
                break
            condition_pattern.pattern.append(curr.get_parent().get_data())
            curr = curr.get_parent()
        if condition_pattern.pattern:
            condition_pattern.pattern.reverse()
            li.append(condition_pattern)

    for element in li:
        print("Pattern: ", element.pattern, "  Count: ", element.get_count())

    return li

# def find_common_pattern(data_path):
#     common_sublist = []
#     for pattern in data_path:
#


def update_cond_fp_tree(node, pattern_list):
    if not pattern_list.pattern:
        return
    else:
        for i, child in enumerate(node.children):
            #print("Child data: ", child.data)
            if pattern_list.pattern[0] == child.data:
                node.children[i].inc_count_value(pattern_list.count)
                pattern_list.pattern.pop(0)
                update_tree(node.children[i], pattern_list.pattern)
                return
        node.children.append(Node(pattern_list.pattern[0], pattern_list.count))
        node.children[-1].parent.append(node)
        pattern_list.pattern.pop(0)
        update_tree(node.children[len(node.children)-1], pattern_list.pattern)
        return


def filter_tree(tree, sup):
    if tree is None:
        return

    if tree.get_count() < sup:
        del tree
        return

    for i, node in enumerate(tree.children):
        filter_tree(node, sup)


def condition_fp_tree(pattern_base):
    tree = Node(None, 0)
    for pattern_list in pattern_base:
        update_cond_fp_tree(tree, pattern_list)
        filter_tree(tree, 2)
    return tree


def generate_combinations(elements, key):
    all_combinations = []

    for length in range(1, len(elements) + 1):
        for i in range(len(elements)):
            if i + length <= len(elements):
                combination = elements[i:i+length] + [key]
                all_combinations.append(combination)

    return all_combinations


def generate_pattern(header_table):
    key_list = header_table.keys()
    result = dict()
    node_list = []
    queue = []
    for key in key_list:
        pointers = header_table[key]
        data_path = extract_path(pointers)
        tree = condition_fp_tree(data_path)
        #print_tree(tree)
        node_list.append(tree)
        while node_list:
            curr = node_list[0]
            removed = node_list.pop(0)
            queue.append(removed.get_data())
           # print("Removed: ", removed.get_data())
        # print("Queue: ", queue)
        all_combination = generate_combinations(queue, key)
        result[key] = all_combination

    return data_path


def main():
    header_table = dict()
    min_sup = 2
    f_name = "agaricus-lepiota.data"  # input("Please enter a file name to scan:  ")
    output_f = "output.txt"
    output_file = open("output.txt", 'w')
    dataset = read_dataset(f_name)
    fq_pattern = get_fq_pattern(dataset)
    fq_pattern = filter_min(fq_pattern, min_sup)
    print("Frequency Pattern: ", fq_pattern)
    tree = construct_tree(dataset, fq_pattern, min_sup)
    header_table = getHeader(tree, fq_pattern)
    result = generate_pattern(header_table)
    # for i, element in enumerate(result):
    #     print("Path: ", element.pattern, "  Count: ", element.get_count())
    #     output_file.writelines(element.pattern)
    # output_file.close()


if __name__ == "__main__":
    main()
