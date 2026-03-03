cod=int(input("Digite o código do seu produto: "))
preco=float(input("Digite o preço do seu produto: "))
if cod==1:
    print ("Sul")
if cod==2:  
    print("Norte")
if cod==3:
    print("Leste")
if cod==4:
    print("Oeste")
if cod== 5 or cod==6:
    print("Nordeste")
if cod== 7 or cod==8 or cod==9:
    print("Sudeste")   
if cod>=10 and cod<=20:
    print("Centro-Oeste")
print("O preço do seu produto é de",preco)