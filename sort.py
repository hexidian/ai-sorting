import math
import FirstSort

#I will be using Timsort for the subgroups instead of mergesort. So this ends up being a hybrid algorithm of 3 different types.

class sortalg:

    def __init__(self,groupFunc):

        self.groupFunc = groupFunc

    def fsort(self,data):
            lnt = len(data)
            top = max(data)
            bot = min(data)

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
                subdTop = ((group+1)/groups)
                subdBot = (group/groups)
                for i in data:
                    val = self.groupFunc(i)
                    if (val>=subdBot) and (val<subdTop):
                        subd.append(i)
                subs.append(subd)

            #now we sort each of these small lists using the built-in Timsort

            for i in subs:
                subs.sort()

            #now we just need to put the lists together

            output = []
            for i in subs:
                output.extend(i)

            return output
