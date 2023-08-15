import re
import string


# The following three functions were included in the Python Starter Code and were used to troubleshoot the integration
# of Python and C++
def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

# END troubleshooting functions

# Takes in a file name as a parameter. Opens and reads the file into a list and then counts the number of times each item occurs.
# Prints each unique item with the number of times it was purchased that day, according to the user's file.
def ListAllItemsQuantity(v):
    print("\n")

    groceryList = []
    groceryItemCount = {}

    try:
        myFile = open(v, "r")
    except IOError:
        print("Error: File does not exist.")

    line = ((myFile.readline()).strip()).lower()

    # This while loop continues to read the file as long as another line exists.
    while line:
        # Adds every item to the grocery list.
        groceryList.append(line)
        line = ((myFile.readline()).strip()).lower()

    myFile.close()

    # If the item isn't already in the groceryItemCount dictionary, then it is added as a key with a value of 1. If the item is
    # already in the groceryItemCount dictionary, then its value is incremented by 1.
    for x in groceryList:
        if not x in groceryItemCount:
            groceryItemCount[x] = 1
        else:
            groceryItemCount[x] += 1

    # Iterates through the groceryItemCount dictionary and prints the number of times each unique item was purchased.
    for key, value in groceryItemCount.items():
        print(key + ": " + str(value))

# Takes in a file name as a parameter. Opens and reads the file into a list and then searches that list for the number of 
# occurrences of a specific item. Finally, displays to the user the amount of times that item was purchased.
def SpecificItemCount(v):
    print("\n")

    specificItem = (input("Which specific item did you want to know how many of which were purchased throughout the day? ")).lower()
    print("\n")

    groceryList = []
    specificItemCount = 0

    try:
        myFile = open(v, "r")
    except IOError:
        print("Error: File does not exist.")

    line = ((myFile.readline()).strip()).lower()

    # This while loop continues to read the file as long as another line exists.
    while line:
        # Adds every item to the grocery list.
        groceryList.append(line)
        line = ((myFile.readline()).strip()).lower()

    myFile.close()

    # Iterates through the whole groceryList and counts the number of times the specificItem is seen.
    for x in groceryList:
        if x == specificItem:
            specificItemCount += 1

    print("Number of " + specificItem + " purchased: " + str(specificItemCount))

# Takes in a file name as a parameter. Opens and reads the file into a list and then counts the number of times each item occurs.
# Prints each unique item with the number of times it was purchased that day, according to the user's file. Also prints a 
# text-based histogram representing the amount of times each item was purchased that day.
def DisplayQuantityHistogram(v):
    print("\n")

    groceryList = []
    groceryItemCount = {}

    try:
        myFile = open(v, "r")
    except IOError:
        print("Error: File does not exist.")

    line = ((myFile.readline()).strip()).lower()

    # This while loop continues to read the file as long as another line exists.
    while line:
        # Adds every item to the grocery list.
        groceryList.append(line)
        line = ((myFile.readline()).strip()).lower()

    myFile.close()

    # If the item isn't already in the groceryItemCount dictionary, then it is added as a key with a value of 1. If the item is
    # already in the groceryItemCount dictionary, then its value is incremented by 1.
    for x in groceryList:
        if not x in groceryItemCount:
            groceryItemCount[x] = 1
        else:
            groceryItemCount[x] += 1

    print("Grocery Purchases of the Day:\n")

    # Iterates through the groceryItemCount dictionary and prints the number of times each unique item was purchased. Also prints
    # a text-based histogram of the amount of times each item was purchased.
    for key, value in groceryItemCount.items():
        myGroceryString = key + ": " + str(value)
        myHistogramSymbol = '*'

        print(f'{myGroceryString:<20}' + (myHistogramSymbol * value))