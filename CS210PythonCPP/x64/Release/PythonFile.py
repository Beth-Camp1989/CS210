import re
import string
from collections import Counter #import to count word frequency in file

    #removed PrintSomething function due to not being used 
    #Removed PrintMe function due to not being used


def readItems():
    # function will read file, count total amount, output to console
    itemsToRead = open("items.txt")
    items = itemsToRead.read().split()

    uniqueItem = sorted(set(items))

    print("ITEMS        QUANTITY PURCHASED")
    print("_______________________________")
    totalInventory = 0
    for word in uniqueItem:
        x = word.ljust(18," ")
        print(x,"\t",items.count(word))
        totalInventory += items.count(word)
    print("Total Items Sold Today: ", len(items))
        

    itemsToRead.close() #closes file

def TotalProductAmount(userString):
    itemsToRead = open("items.txt") #opens txt file
    items = itemsToRead.read().split() #creates an object to hold each line info    
    uniqueItem =  sorted(set(items)) #sorts items into alphabetical order
    itemsToRead.close() #closes itemsToRead

    total = 0
    totalInventory = 0 # counts times loop iterates
    totInvCount = 0 #holds total inventory

    for word in uniqueItem: #gets total amount of items
        totInvCount +=1

    for word in uniqueItem: #finds the element that is requested by user string
        tempString = word
        totalInventory +=1
        if (tempString == userString):
            total = items.count(word)
            
    return total

def readAndWriteFile():
    itemsToRead = open("items.txt")
    data = open("frequency.dat","w") #opens frequency.dat and makes it writeable 
    items = itemsToRead.read().split() #creates an object to hold line info
    uniqueItem=sorted(set(items))

    for word in uniqueItem:
        data.write(word)
        data.write(" ")
        data.write(str(items.count(word)))
        data.write("\n")

    data.close() #closes file for writing

    histogram_data = open("frequency.dat", "r") # opens file for reading
    productData = histogram_data.readlines()

    #temps for nested loops
    tempFreq = 0
    tempItem= ""

    for line in productData: #reference is Teiga_artzee github
        tempInt = 0
        
        tempString = line.split() #splits item name and count
        for word in tempString:
            tempInt +=1
            if(tempInt ==1):
                tempItem = word #for item
                print(tempItem, end = " ")
            if (tempInt == 2):
                tempFreq = int(word) #item count
        
        for i in range(tempFreq):
            print("*", end = " ") 
        print()
    print("Total Items Sold Today: ", len(items)) ##prints total Items sold. 
        

def ExitProgram():
    print("Exiting Program")
    exit()

