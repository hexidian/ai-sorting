def get_matrix():
    matrix = []
    varbles = []
    more = True
    while more:
        equation = raw_input("give me the equation:\n").split()
        for i in range(len(equation)):
            try:
                equation[i] = int(equation[i])
            except:
                pass
        pm = ['+','-']
        for nomial in equation:
            if nomial =="=": break
            if nomial in pm:
                continue
            if nomial == str(nomial):
                 if not nomial in varbles: varbles.append(nomial)
        for i in range(len(equation)):
            if equation[i] == '-':
                equation[i+1] *= -1
        while ('-' in equation):
            equation.remove('-')
        while ('+' in equation):
            equation.remove('+')

        for i in varbles:
            if i in equation:
                equation.remove(i)

        matrix.append(equation)

        more = input("more equations? (1/0)")

    answers = []
    for row in range(len(matrix)):      #this set of loops will get the list of answers
        for column in range(len(matrix[row])):
            if matrix[row][column] == '=':
                answers.append([matrix[row][column+1]])
    for row in range(len(matrix)):      #this set of loops will take out the answers and equals signs
        matrix[row].pop(-1)
        matrix[row].pop(-1)
    return matrix,answers

def determinate(matrix):
    if len(matrix) == 1:
        return matrix[0][0]

    if len(matrix) == 2:
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0])#just the basic a*d - b*c

    cofactors = cofactor(matrix)

    det = 0
    for i in range(len(cofactors)):
        det += cofactors[0][i]*matrix[0][i]
    return det

def minors(matrix): #note, only works for more than 2x2
    minors = [i[:] for i in matrix]
    for row in range(len(matrix)):
        for column in range(len(matrix[row])):
            mini_mtrx = [i[:] for i in matrix]
            #print "about to start making a mini_mtrx out of",mini_mtrx
            mini_mtrx.pop(row)
            for i in range(len(mini_mtrx)):
                mini_mtrx[i].pop(column)
            #print "after changing the mini_mtrx, the matrix is",matrix
            #print "about to check determinate of a mini_mtrx which is",mini_mtrx
            minors[row][column] = determinate(mini_mtrx)
            #print "after changing the minors, the matrix is",matrix

    return minors

def cofactor(matrix):
    minor = minors(matrix)
    for row in range(len(minor)):
        for column in range(len(minor[0])):
            if not ((row + column)%2==0):             #if it's an odd spot (i.e. minus in the plus minus grid)
                minor[row][column] *= -1             #the negative of what it was

    return minor

def adjoint(matrix):
    cofactors = cofactor(matrix)
    adjnt = []

    for row in range(len(cofactors)):
        nrow = []
        for column in range(len(cofactors[row])):
            nrow.append(cofactors[column][row])
        #print "about to append adjnt with",nrow
        adjnt.append(nrow)
        #print "adjnt is",adjnt
    return adjnt

def matrix_mult(matrixa,matrixb):
    if len(matrixa[0]) != len(matrixb):
        print "incompatable matrix multiplication"
        return None

    product = []

    for prow in range(len(matrixa)):        #iterates through the rows that will be in the product
        newrow = []
        for pcolumn in range(len(matrixb[0])): #iterates through the columns that will be in the product
            spotsum = 0
            for spot in range(len(matrixb)):    #iterates through the spot in matrixa's row and matrixb's columbn
                spotsum += matrixa[prow][spot] * matrixb[spot][pcolumn]
            newrow.append(spotsum)
        product.append(newrow)

    return product

def matrix_mult_const(matrix,constant):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            matrix[i][j] *= constant

    return matrix
def solve(matrix,constants):
    #if len(matrix) != 2:
    print matrix
    adj = adjoint(matrix)
    inv = matrix_mult_const(adj, (1/float(determinate(matrix))) )
    print matrix_mult(inv,matrix),"\n"
    return matrix_mult(inv,constants)
def main():
    matrix,constants = get_matrix()
    '''
    print "your matrix is",matrix
    print "the minors are",minors(matrix)
    print "the cofactors are",cofactor(matrix)
    print "the adjoint is",adjoint(matrix)'''
    print solve(matrix,constants)

main()
