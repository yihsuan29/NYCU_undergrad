import sys
import time
from optparse import OptionParser

"""Modify: global var to save the frequent itemsets"""
frequent_itemsets = []

def eclat(prefix, items):
    # for each item in the list
    while items:
        # create Equivalence Class itids
        i, itids = items.pop()
        isupp = len(itids)        
        # check if the item support >= minimum support threshold 
        if isupp >= minsup:
            # if so, the item is a frequent itemset.
            frequent_itemset = sorted(prefix + [i])
            frequent_itemsets.append((frequent_itemset, isupp))
            # find more frequent itemsets that contain the current item.
            # by combining current item and other items in the EC. 
            suffix = [] 
            for j, ojtids in items:
                jtids = itids & ojtids
                if len(jtids) >= minsup:
                    suffix.append((j, jtids))
            # Recursively call eclat() on the transactions of the EC
            # EC: the remaining transactions after removing the current item.
            eclat(prefix + [i], sorted(suffix, key=lambda item: len(item[1]), reverse=True))


def printResults(items):
    """prints the generated itemsets sorted by support """
    for item, support in sorted(items, key=lambda x: x[1]):
        print("item: %s , %.3f" % (str(item), support))
  
"""Modify: save task1 file"""
def saveResultToFileTask1(items, output_file1,trans):
    """save the generated itemsets sorted by support to txt """
    with open(output_file1, "w") as file:
        for item, support in sorted(items, key=lambda x: x[1], reverse=True):
            file.write("%.1f \t{%s}\n" % (support*100/trans, ", ".join(item)))


if __name__ == "__main__":
    start_time = time.time() 
    """Modify: Add command options"""
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

    (options, args) = optparser.parse_args()
    trans = 0
    inFile = None
    if options.input is None:
        inFile = sys.stdin
    elif options.input is not None:
        """Modify: read .data file
                   get the # of transactions"""
        data = {}
        f = open(options.input, 'r')
        for row in f:
            trans += 1
            for item in row.split()[3:]:
                if item not in data:
                    data[item] = set()
                data[item].add(trans)
        f.close()

    else:
        print("No dataset filename specified, system with exit\n")
        sys.exit("System will exit")
    
    """Modify: input minS ratio """
    minsup = options.minS * trans

    """Modify: write result to file"""
    input_filename = options.input.split("/")[-1].split(".")[0] 
    output_file1 = f"../OutputFile/step3_task1_{input_filename}_{options.minS:.{str(options.minS)[::-1].find('.')}f}_result1.txt"
    
    eclat([], sorted(data.items(), key=lambda item: len(item[1]), reverse=True))
    saveResultToFileTask1(frequent_itemsets, output_file1,trans) 

    end_time = time.time()  
    total_elapsed_time = end_time - start_time
    print(f"Execution time w/  write file: {total_elapsed_time:.2f} seconds")
    with open("../OutputFile/time.txt", "a") as time_file:
        time_file.write(f"{total_elapsed_time:.2f}\tstep3\ttask1\t{input_filename}\t{options.minS:.{str(options.minS)[::-1].find('.')}f}\n")
