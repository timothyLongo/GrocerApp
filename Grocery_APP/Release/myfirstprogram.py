import re
import string

# Items_Sold_Record.txt is the file downloaded from SNHU which lists every item purchased

# option 1 -- show list and frequency in PYTHON

def theList():
    # 1 - READ the file
    # opening a file this way automatically closes it without calling the close method
    with open('C:\\Users\\Timmy\\Documents\\ALL_CODING_PROJECTS\\z_MIXED\\C++_PY_GROCERY_APP\\Grocery_APP\\Items_Sold_Record.txt') as f:
        noDuplicatesList = [] # creates a blank list
        for line in f:
            if line.strip() not in noDuplicatesList: # if the line in the file is not in the list, add it
                noDuplicatesList.append(line.strip()) # adds it
            else:
                continue
    # this populates a list with ALL ITEMS - NO DUPLICATES

    # for element in noDuplicatesSet, check number of occurances in read file
    with open('C:\\Users\\Timmy\\Documents\\ALL_CODING_PROJECTS\\z_MIXED\\C++_PY_GROCERY_APP\\Grocery_APP\\Items_Sold_Record.txt') as f:
        WholeList = f.read().strip()
    
    for i in range(0, len(noDuplicatesList)):
        print("{:<12}".format(noDuplicatesList[i]), "{:>6}".format(WholeList.count(noDuplicatesList[i])))
        # python has a built-in count function! makes this easy!
        # for element in noDuplicatesList, print element
        # then print the count of the element from the WholeList


# option 2 - display frequency of item

def returnFreq(itemName):
    # 1 - READ the file
    # opening a file this way automatically closes it without calling the close method
    with open('C:\\Users\\Timmy\\Documents\\ALL_CODING_PROJECTS\\z_MIXED\\C++_PY_GROCERY_APP\\Grocery_APP\\Items_Sold_Record.txt') as f:
        noDuplicatesList = [] # creates a blank list
        for line in f:
            if line.strip() not in noDuplicatesList:
                noDuplicatesList.append(line.strip())
            else:
                continue
    if itemName in noDuplicatesList: # if user enetered item is in the list
        with open('C:\\Users\\Timmy\\Documents\\ALL_CODING_PROJECTS\\z_MIXED\\C++_PY_GROCERY_APP\\Grocery_APP\\Items_Sold_Record.txt') as f:
            WholeList = f.read().strip()
            freq = WholeList.count(noDuplicatesList[noDuplicatesList.index(itemName)])
            # freq is a count how many times that item's index appears in the whole list
    else:
        return 0 # if it doesn't exist, returns freq value of zero
    return freq


# option 3 - read the file, then write the item + freq file to frequency.dat


def writeTheFile():

    # 1 - READ the file
    # opening a file this way automatically closes it without calling the close method
    with open('C:\\Users\\Timmy\\Documents\\ALL_CODING_PROJECTS\\z_MIXED\\C++_PY_GROCERY_APP\\Grocery_APP\\Items_Sold_Record.txt') as f:
        noDuplicatesList = [] # creates a blank list
        for line in f:
            if line.strip() not in noDuplicatesList:
                noDuplicatesList.append(line.strip())
            else:
                continue
    # this populates a list with ALL ITEMS - NO DUPLICATES

    # for element in noDuplicatesSet, check number of occurances in read file
    with open('C:\\Users\\Timmy\\Documents\\ALL_CODING_PROJECTS\\z_MIXED\\C++_PY_GROCERY_APP\\Grocery_APP\\Items_Sold_Record.txt') as f:
        WholeList = f.read().strip()

    with open('C:\\Users\\Timmy\\Documents\\frequency.dat', "x") as f:
        for i in range(0, len(noDuplicatesList)):
            f.write(noDuplicatesList[i] + " " + str(WholeList.count(noDuplicatesList[i])) + "\n")