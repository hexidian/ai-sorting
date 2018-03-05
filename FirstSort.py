import random
import time
import math

def Bsort(start):#Big Sort

    lnt = len(start)
    top = max(start)
    bot = min(start)

    #after a lot of testing I found out that the optimal group size is a function of the input length
    #the original "magic number" was that at 20,000 a group size of 500 works best
    #if you increase the input length by a factor, then you should increase the group size by
    #the square root of the increase factor

    scale_factor = math.sqrt(float(lnt)/20000.0)

    groups = int(lnt/(500*scale_factor))

    #I am now going to make a list of lists,
    #where each list in the larger list is about 1/5 of the total thing to sort
    #this will mean that it will be okay to sort the small groups...
    #with a fairly innefficient algorithm

    #this is going to be fairly fast (I hope), but the disadvantage is that it has a small chance of
    #not being fast at all

    #I might as well add that I just learned some basic x86 assembly and I am thanking the lord I don't
    #have to do lists of lists in assembly

    subs = []

    for grop in range(0,groups):
        group = float(grop)
        subd = []
        for i in start:
            if (i>=(top*(group/groups))) and (i<(top*((group+1)/groups))):
                subd.append(i)
        subs.append(subd)

    #now we sort each of these small lists

    for i in range(len(subs)):
        subs[i] = Ssort(subs[i])

    #now we just need to put the lists together

    output = []
    for i in subs:
        output.extend(i)

    return output


def Ssort(piece):#just makes an outpust list which is filled in from the input, this time ordered
    output = []
    while len(piece)>0:
        i = min(piece)
        output.append(i)
        piece.remove(i)
    return output
def main():
    slist = []#my starting list
    numb_range = input("the elements will be from 0 to what number?")
    for i in range(input("how many elements should be in the list?")):
        slist.append(random.randint(0,numb_range))
    #now the list is ready
    start_time = time.time()
    result = Bsort(slist)
    speed = time.time()- start_time
    print "I sorted it in",speed,"seconds.\nthe result is being exported:\n",#result
    #the result is commented out because it takes forever to print
    export = open('output.txt','w')
    export.write(str(result))
    export.close

main()
