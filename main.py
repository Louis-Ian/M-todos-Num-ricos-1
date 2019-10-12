import math

#Função dada pelo trabalho

def function(x, a1, a2):
	x=float(x)
	a1=float(a1)
	a2=float(a2)
	return a1*math.pow(x, 3) - 9*a2*x + 3

#Função derivada calculada a partir da função dada

def functionD(x, a1, a2):
	x=float(x)
	a1=float(a1)
	a2=float(a2)
	return 3*a1*math.pow(x, 2) - 9*a2

#Função para calcular a derivada de qualquer função a partir da definição de derivada:f'(x)==f(x+h)-f(x)/h', onde h é um valor proximo de zero

def derivative(f, x1, a1, a2):
	h=0.1e-10
	top=f(x1+h, a1, a2)-f(x1, a1, a2)
	bottom=h
	return top/bottom

#Funções que usam a função derivada pré-determinada functionD

def newton(x1, a1, a2, e1, e2):
	if abs(function(x1, a1, a2))<e1:
		return x
	while True:
		f1=function(x1, a1, a2)
		f2=functionD(x1, a1, a2)
		x2=x1-(f1/f2)
		if abs(function(x2, a1, a2))<e1 or abs(x2-x1)<e2:
			return x2
		else:
			x1=x2

def newtonFL(x1, a1, a2, e1, e2, l):
	if abs(function(x1, a1, a2))<e1:
		return x
	while True:
		f1=function(x1, a1, a2)
		f2=functionD(x1, a1, a2)
		if abs(functionD(x1, a1, a2))>l:
			fw=f2
		else:
			f2=fw
		x2=x1-(f1/f2)
		if abs(function(x2, a1, a2))<e1 or abs(x2-x1)<e2:
			return x2
		else:
			x1=x2

#Funções que usam a função generica derivate para calcular a derivada

def newton2(x1, a1, a2, e1, e2):
	if abs(function(x1, a1, a2))<e1:
		return x
	while True:
		f1=function(x1, a1, a2)
		f2=derivative(function, x1, a1, a2)
		x2=x1-(f1/f2)
		if abs(function(x2, a1, a2))<e1 or abs(x2-x1)<e2:
			return x2
		else:
			x1=x2

def newtonFL2(x1, a1, a2, e1, e2, l):
	if abs(function(x1, a1, a2))<e1:
		return x
	while True:
		f1=function(x1, a1, a2)
		f2=derivative(function, x1, a1, a2)
		if abs(f2)>l:
			fw=f2
		else:
			f2=fw
		x2=x1-(f1/f2)
		if abs(function(x2, a1, a2))<e1 or abs(x2-x1)<e2:
			return x2
		else:
			x1=x2

#Dados usado para calibrar o sistema, de acordo com o item d do trabalho

d0=-1.275
l=0.05
e1=0.05
e2=e1
a1=1
a2=1

#print(newton(d0, a1, a2, e1, e2))
print(newton2(d0, a1, a2, e1, e2))
#print(newtonFL(d0, a1, a2, e1, e2, l))
print(newtonFL2(d0, a1, a2, e1, e2, l))
