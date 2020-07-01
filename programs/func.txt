# Program to compute the GCD

# Funcion que calcula el maximo comun divisor
def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

x = input("Introduzca un numero: ")
y = input("Introduzca otro numero: ")
z = gcd(x, y)
print "El maximo comun divisor es ", z