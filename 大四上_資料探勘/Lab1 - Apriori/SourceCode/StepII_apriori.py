"""
Description     : Simple Python implementation of the Apriori Algorithm
Modified from:  https://github.com/asaini/Apriori
Usage:
    $python apriori.py -f DATASET.csv -s minSupport

    $python apriori.py -f DATASET.csv -s 0.15
"""

import sys
import time

from itertools import chain, combinations
from collections import defaultdict
from optparse import OptionParser

def subsets(arr):
    """ Returns non empty subsets of arr"""
    return chain(*[combinations(arr, i + 1) for i, a in enumerate(arr)])

def returnItemsWithMinSupport(itemSet, transactionList, minSupport, freqSet):
    """calculates the support for items in the itemSet and returns a subset
    of the itemSet each of whose elements satisfies the minimum support"""
    _itemSet = set()
    localSet = defaultdict(int)
    
    for item in itemSet:
        for transaction in transactionList:
            if item.issubset(transaction):
                freqSet[item] += 1
                localSet[item] += 1

    for item, count in localSet.items():
        support = float(count) / len(transactionList)

        if support >= minSupport:
            _itemSet.add(item)

    return _itemSet

# 得到itemset的組合
def joinSet(itemSet, length):
    """Join a set with itself and returns the n-element itemsets"""
    return set(
        [i.union(j) for i in itemSet for j in itemSet if len(i.union(j)) == length]
    )

def getItemSetTransactionList(data_iterator):
    transactionList = list()
    itemSet = set()
    for record in data_iterator:
        transaction = frozenset(record)
        transactionList.append(transaction)
        for item in transaction:
            itemSet.add(frozenset([item]))  # Generate 1-itemSets
            
    return itemSet, transactionList

def runApriori(data_iter, minSupport,task):
    def getSupport(item):
        """local function which Returns the support of an item"""
        return float(freqSet[item]) / len(transactionList)

    """
    run the apriori algorithm. data_iter is a record iterator
    Return both:
     - items (tuple, support)
    """

    """Modify: initial support and statistics"""
    itemSupportDict = {}
    toStatistics = []
    itemSet, transactionList = getItemSetTransactionList(data_iter)
    freqSet = defaultdict(int)
    largeSet = dict()
    closed = []
    
    # Global dictionary which stores (key=n-itemSets,value=support)
    # which satisfy minSupport
    oneCSet= returnItemsWithMinSupport(itemSet, transactionList, minSupport, freqSet)
    currentLSet = oneCSet

    """Modify: save 1st statistics data"""
    k = 1
    toStatistics.append([k, len(itemSet), len(oneCSet)])
    total = len(oneCSet)
    k += 1

    """Modify: save the 1st support"""
    for item in currentLSet:
        itemSupportDict[item] = getSupport(item)

    if(task==1):
        while currentLSet != set([]):
            largeSet[k - 1] = currentLSet
            currentLSet = joinSet(currentLSet, k)
            currentCSet= returnItemsWithMinSupport(
                currentLSet, transactionList, minSupport, freqSet
            )
            for C_item in currentCSet:
                itemSupportDict[C_item] = getSupport(C_item)
            
            """Modify: save the statistics"""
            toStatistics.append([k, len(currentLSet), len(currentCSet)])
            total+=len(currentCSet)
            currentLSet = currentCSet
            k = k + 1
    else:
        while currentLSet != set([]):
            """Modify: closed"""
            closed_tmp = currentLSet.copy()

            largeSet[k - 1] = currentLSet
            currentLSet = joinSet(currentLSet, k)
            currentCSet= returnItemsWithMinSupport(
                currentLSet, transactionList, minSupport, freqSet
            )
            
            """Modify: check whether it is closed and save"""
            for C_item in currentCSet:
                itemSupportDict[C_item] = getSupport(C_item)
                to_remove = set()
                for L_item in closed_tmp:
                    if(L_item.issubset(C_item) and itemSupportDict[L_item] ==itemSupportDict[C_item]):
                        to_remove.add(L_item)
                closed_tmp -= to_remove
            for item in closed_tmp:
                closed.append((tuple(item), itemSupportDict[item]))
            currentLSet = currentCSet
            k = k + 1
           
    toRetItems = []
    for key, value in largeSet.items():
        toRetItems.extend([(tuple(item), itemSupportDict[item]) for item in value])
    return toRetItems, toStatistics, total, closed







def printResults(items):
    """prints the generated itemsets sorted by support """
    for item, support in sorted(items, key=lambda x: x[1]):
        print("item: %s , %.3f" % (str(item), support))
  

def to_str_results(items):
    """prints the generated itemsets sorted by support"""
    i = []
    for item, support in sorted(items, key=lambda x: x[1]):
        x = "item: %s , %.3f" % (str(item), support)
        i.append(x)
    return i

"""Modify: read.data file"""
def dataFromFile(fname):
    """Function which reads from the file and yields a generator"""
    with open(fname, "r") as file_iter:
        for line in file_iter:
            line = line.strip().rstrip(",") 
            """Modify: to fit the input data 移除前面的 SID TID NITEMS """
            trans = line.split(" ")[3:]
            record = frozenset(trans)
            yield record

"""Modify: save task1 file"""
def saveResultToFileTask1(items,total,statistics, output_file1,output_file2):
    """save the generated itemsets sorted by support to txt """
    with open(output_file1, "w") as file:
        for item, support in sorted(items, key=lambda x: x[1], reverse=True):
            file.write("%.1f \t{%s}\n" % (support * 100, ", ".join(item)))
    with open(output_file2, 'w') as file:
        file.write(str(total) + '\n')
        for sublist in statistics:
            file.write('\t'.join(map(str, sublist)) + '\n')

"""Modify: save task2 file"""
def saveResultToFileTask2(closed,output_file3):
    """save the generated itemsets sorted by support to txt """
    with open(output_file3, "w") as file:
        file.write(str(len(closed)) + '\n')
        for item, support in sorted(closed, key=lambda x: x[1], reverse=True):
            file.write("%.1f \t{%s}\n" % (support * 100, ", ".join(item)))

if __name__ == "__main__":
    start_time = time.time() 
    optparser = OptionParser()
    optparser.add_option(
        "-f", "--inputFile", dest="input", help="filename containing csv", default=None
    )
    optparser.add_option(
        "-s",
        "--minSupport",
        dest="minS",
        help="minimum support value",
        default=0.1,
        type="float",
    )

    optparser.add_option(
        "-t","--task", 
        dest="task", 
        help="Task number (1 or 2)", 
        type="int", 
        default=1
    )
    
    (options, args) = optparser.parse_args()

    inFile = None
    if options.input is None:
        inFile = sys.stdin
    elif options.input is not None:
        inFile = dataFromFile(options.input)
    else:
        print("No dataset filename specified, system with exit\n")
        sys.exit("System will exit")

    minSupport = options.minS
    task = options.task
    input_filename = options.input.split("/")[-1].split(".")[0] 
    output_file1 = f"../OutputFile/step2_task{task:1d}_{input_filename}_{options.minS:.{str(options.minS)[::-1].find('.')}f}_result1.txt"
    output_file2 = f"../OutputFile/step2_task{task:1d}_{input_filename}_{options.minS:.{str(options.minS)[::-1].find('.')}f}_result2.txt"
    output_file3 = f"../OutputFile/step2_task{task:1d}_{input_filename}_{options.minS:.{str(options.minS)[::-1].find('.')}f}_result1.txt"
    items, statistics, total, closed = runApriori(inFile, minSupport,task) 
    #printResults(items)
    if(task==1):
        saveResultToFileTask1(items,total,statistics, output_file1,output_file2) 
    else:
        saveResultToFileTask2(closed, output_file3)
    end_time = time.time()  
    total_elapsed_time = end_time - start_time
    print(f"Execution time w/  write file: {total_elapsed_time:.2f} seconds")
    with open("../OutputFile/time.txt", "a") as time_file:
        time_file.write(f"{total_elapsed_time:.2f}\tstep2\ttask{task:1d}\t{input_filename}\t{options.minS:.{str(options.minS)[::-1].find('.')}f}\n")
