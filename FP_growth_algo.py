

# read wine dataset from the file "wine.data"
def convert(string):
    li = list(string.split(" "))
    return li


def read_daatset(fname):
    with open(fname, 'r') as file:
        dataset = []

        for line in file:
            line = line.strip()
            string = str(line)
            string = string.replace(',', ' ')
            li = convert(string)
            dataset.append(li)

    print(dataset)
    return dataset


def getL1(dataset):
    L1=dict()
    for transction in dataset:
        for data in transction:
            if data not in L1.keys():
                L1[data] = 1
            else:
                L1[data] += 1

    L1 = dict(sorted(L1.items(), key=lambda item: item[1]))

    print(L1)
    return L1


def main():
    fileName = input("Please enter a file name to scan:  ")
    dataset = read_daatset(fileName)
    getL1(dataset)


if __name__ == "__main__":
    main()