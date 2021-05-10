e, p, q = 35, 23, 53   #49,21  #101,23  #131,53 
n = int(p) * int(q)
message = 50
msg_decrypted = 1

for i in range (e):                
    msg_decrypted = (msg_decrypted * message) % n

print(msg_decrypted)
