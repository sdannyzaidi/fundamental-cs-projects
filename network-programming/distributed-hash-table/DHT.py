import socket 
import threading
import os
import time
import hashlib


class Node:
	def __init__(self, host, port):
		self.stop = False
		self.host = host
		self.port = port
		self.M = 16
		self.N = 2**self.M
		self.key = self.hasher(host+str(port))
		# You will need to kill this thread when leaving, to do so just set self.stop = True
		threading.Thread(target = self.listener).start()
		self.files = []
		self.backUpFiles = []
		if not os.path.exists(host+"_"+str(port)):
			os.mkdir(host+"_"+str(port))
		'''
		------------------------------------------------------------------------------------
		DO NOT EDIT ANYTHING ABOVE THIS LINE
		'''
		# Set value of the following variables appropriately to pass Intialization test
		self.successor = self.host, self.port
		self.predecessor = self.host, self.port
		self.list1 = []
		# additional state variables



	def hasher(self, key):
		'''
		DO NOT EDIT THIS FUNCTION.
		You can use this function as follow:
			For a node: self.hasher(node.host+str(node.port))
			For a file: self.hasher(file)
		'''
		return int(hashlib.md5(key.encode()).hexdigest(), 16) % self.N

	def handleConnection(self, client, addr):
		'''
		 Function to handle each inbound connection, called as a thread from the listener.
		'''
		message = client.recv(1024).decode("utf-8")
		if "lookupNode" in message:
			commad,data = message.split(" ",1)
			data1 = data.split(" ")
			lookNode = (data1[0],int(data1[1]))
			myAddr = (self.host, self.port)
			reply = self.lookup(myAddr,lookNode)
			reply = reply[0] + ' ' + str(reply[1])
			client.send(reply.encode("utf-8"))
		elif "checkFile" in message:
			commad,data = message.split(" ",1)
			myAddr = (self.host, self.port)
			reply = self.lookup(myAddr,data)
			reply = reply[0] + ' ' + str(reply[1])
			client.send(reply.encode("utf-8"))
		elif "lookupSuccessor" in message:
			commad,data = message.split(" ",1)
			data1 = data.split(" ")
			lookNode = (data1[0],int(data1[1]))
			myAddr = (self.host, self.port)
			yourSuccessor = self.lookup(myAddr, lookNode)
			myTuple = "yourSucessor" + " " + yourSuccessor[0] + " " + str(yourSuccessor[1])
			client.send(myTuple.encode("utf-8"))
		elif "yourPredecessor" in message:
			commad,data = message.split(" ",1)
			data1 = data.split(" ")
			newPredecessor = (data1[0], int(data1[1]))
			prevpredecessor = self.predecessor
			self.predecessor = newPredecessor
			myTuple = "myprevpred" + " " + prevpredecessor[0] + " " + str(prevpredecessor[1])
			client.send(myTuple.encode("utf-8"))
		elif "changeSucessor" in message:
			commad,data = message.split(" ",1)
			data1 = data.split(" ")
			newSucessor = (data1[0], int(data1[1]))
			self.successor = newSucessor
			yourPredecessor = (self.host,self.port)
			myTuple = "changePred" + " " + yourPredecessor[0] + " " + str(yourPredecessor[1])
			client.send(myTuple.encode("utf-8"))
		elif "PutFile" in message:
			command,data = message.split(" ",1)
			fileName = self.host + '_' + str(self.port) + '/' +  data
			self.recieveFile(client,fileName)
			self.files.append(data)
		elif "searchFile" in message:
			command, data = message.split(" ",1)
			counter = 0
			for x in range(len(self.files)):
				if self.files[x] == data:
					client.send("fileExists".encode("utf-8"))
					counter += 1
				else:
					continue
			if counter == 0:
				client.send("fileDoesnotExist".encode("utf-8"))
		elif "getFile" in message:
			command,data = message.split(" ",1)
			fileName = self.host + '_' + str(self.port) + '/' + data
			time.sleep(0.5)
			self.sendFile(client,fileName)
		elif "sendYourFiles" in message:
			myTuple = ""
			for x in range(len(self.files)):
				myTuple += " " + self.files[x]
			myTuple = "myFiles" + myTuple
			client.send(myTuple.encode("utf-8"))
		elif "rehashFiles" in message:
			command,data = message.split(" ",1)
			fileName = self.host + '_' + str(self.port) + '/' + data
			time.sleep(0.5)
			self.sendFile(client,fileName)
			deleter = ""
			for x in range(len(self.files)):
				if self.files[x] == data:
					deleter = self.files[x]
				else:
					continue
			self.files.remove(deleter)
			os.remove(fileName)
		elif "leaveaFiles" in message:
			command, data = message.split(" ",1)
			fileName = self.host + '_' + str(self.port) + '/' +  data
			self.recieveFile(client,fileName)
			self.files.append(data)
		elif "iamleavingpred" in message:
			command, data = message.split(" ",1)
			data = data.split(" ")
			mySuccessor = (data[0], int(data[1]))
			self.successor = mySuccessor
		elif "iamleavingsucess" in message:
			command, data = message.split(" ",1)
			data = data.split(" ")
			mypredcessor = (data[0], int(data[1]))
			self.predecessor = mypredcessor
		client.close()

	def listener(self):
		'''
		We have already created a listener for you, any connection made by other nodes will be accepted here.
		For every inbound connection we spin a new thread in the form of handleConnection function. You do not need
		to edit this function. If needed you can edit signature of handleConnection function, but nothing more.
		'''
		listener = socket.socket()
		listener.bind((self.host, self.port))
		listener.listen(10)
		while not self.stop:
			client, addr = listener.accept()
			threading.Thread(target = self.handleConnection, args = (client, addr)).start()
		print ("Shutting down node:", self.host, self.port)
		try:
			listener.shutdown(2)
			listener.close()
		except:
			listener.close()

	def lookup(self, myAddr, lookNode):
		if isinstance(lookNode, tuple):
			key = self.hasher(lookNode[0] + str(lookNode[1]))
			myHash = self.hasher(myAddr[0] + str(myAddr[1]))
			successorHash = self.hasher(self.successor[0] + str(self.successor[1]))
			predecessorHash = self.hasher(self.predecessor[0] + str(self.predecessor[1]))
			if myHash == successorHash: # First node case
				return self.successor
			elif (myHash < key <= successorHash): # normal case
				return self.successor
			elif (myHash > successorHash) and ((key > myHash) or (key <= successorHash)): # last node case
				return self.successor
			else:
				soc = socket.socket()
				soc.connect(self.successor)
				myTuple = "lookupNode" + " " + lookNode[0] + " " + str(lookNode[1])
				soc.send(myTuple.encode("utf-8"))
				message = soc.recv(1024).decode("utf-8")
				soc.close()
				message = message.split(' ')
				message = (message[0], int(message[1]))
				return message
		else:
			key = self.hasher(lookNode)
			myHash = self.hasher(myAddr[0] + str(myAddr[1]))
			successorHash = self.hasher(self.successor[0] + str(self.successor[1]))
			predecessorHash = self.hasher(self.predecessor[0] + str(self.predecessor[1]))
			if myHash == successorHash: # First node case
				return self.successor
			elif (myHash < key <= successorHash): # normal case
				return self.successor
			elif (myHash > successorHash) and ((key > myHash) or (key <= successorHash)): # last node case
				return self.successor
			else:
				soc = socket.socket()
				soc.connect(self.successor)
				myTuple = "checkFile" + " " + lookNode
				soc.send(myTuple.encode("utf-8"))
				message = soc.recv(1024).decode("utf-8")
				soc.close()
				message = message.split(' ')
				message = (message[0], int(message[1]))
				return message

	def join(self, joiningAddr):
		'''
		This function handles the logic of a node joining. This function should do a lot of things such as:
		Update successor, predecessor, getting files, back up files. SEE MANUAL FOR DETAILS.
		'''
		if isinstance(joiningAddr, tuple):
			soc = socket.socket()
			soc.connect(joiningAddr)
			myTuple = "lookupSuccessor" + " " + self.host + " " + str(self.port)
			soc.send(myTuple.encode("utf-8"))
			message = soc.recv(1024).decode("utf-8")
			soc.close()
			commad,data = message.split(" ",1)
			data1 = data.split(" ")
			if "yourSucessor" in message:
				mySuccessor = (data1[0], int(data1[1]))
				myAddr = (self.host, self.port)
				self.successor = mySuccessor
				myTuple = "yourPredecessor" + " " + myAddr[0] + " " + str(myAddr[1])
				soc = socket.socket()
				soc.connect(mySuccessor)
				soc.send(myTuple.encode("utf-8"))
				message = soc.recv(1024).decode("utf-8")
				soc.close()
				commad,data = message.split(" ",1)
				data1 = data.split(" ")
				if "myprevpred" in message:
					myprevpred = (data1[0], int(data1[1]))
					myAddr = (self.host, self.port)
					myTuple = "changeSucessor" + " " + myAddr[0] + " " + str(myAddr[1])
					soc = socket.socket()
					soc.connect(myprevpred)
					soc.send(myTuple.encode("utf-8"))
					message = soc.recv(1024).decode("utf-8")
					soc.close()
					commad,data = message.split(" ",1)
					data1 = data.split(" ")
					if "changePred" in message:
						myPred = (data1[0], int(data1[1]))
						self.predecessor = myPred
			soc = socket.socket()
			soc.connect(mySuccessor)
			soc.send("sendYourFiles".encode("utf-8"))
			message = soc.recv(1024).decode("utf-8")
			soc.close()
			if "myFiles" in message:
				command = message.split(" ")
				if len(command) == 1:
					return
				else:
					command,data = message.split(" ",1)
					data = data.split(" ")
					for fileName in data:
						myAddr = (self.host,self.port)
						destNode = self.lookup(myAddr,fileName)
						if destNode == myAddr:
							self.files.append(fileName)
							soc = socket.socket()
							soc.connect(mySuccessor)
							myTuple = "rehashFiles" + " " + fileName
							soc.send(myTuple.encode("utf-8"))
							fileName = destNode[0] + '_' + str(destNode[1]) + '/' + fileName
							self.recieveFile(soc,fileName)
							soc.close()
		else:
			return

	def put(self, fileName):
		'''
		This function should first find node responsible for the file given by fileName, then send the file over the socket to that node
		Responsible node should then replicate the file on appropriate node. SEE MANUAL FOR DETAILS. Responsible node should save the files
		in directory given by host_port e.g. "localhost_20007/file.py".
		'''
		if fileName == '':
			return
		else:
			myAddr = (self.host,self.port)
			destNode = self.lookup(myAddr,fileName)
			soc = socket.socket()
			soc.connect(destNode)
			packet = "PutFile" + ' ' + fileName
			soc.send(packet.encode("utf-8"))
			time.sleep(0.5)
			self.sendFile(soc,fileName)
			soc.close()
		
	def get(self, fileName):
		'''
		This function finds node responsible for file given by fileName, gets the file from responsible node, saves it in current directory
		i.e. "./file.py" and returns the name of file. If the file is not present on the network, return None.
		'''
		if fileName == '':
			return None
		else:
			myAddr = (self.host,self.port)
			destNode = self.lookup(myAddr,fileName)
			soc = socket.socket()
			soc.connect(destNode)
			myTuple = "searchFile" + ' ' + fileName
			soc.send(myTuple.encode("utf-8"))
			message = soc.recv(1024).decode("utf-8")
			soc.close()
			if "fileExists" in message:
				soc = socket.socket()
				soc.connect(destNode)
				packet = "getFile" + ' ' + fileName
				soc.send(packet.encode("utf-8"))
				self.recieveFile(soc,fileName)
				soc.close()
				return fileName
			elif "fileDoesnotExist" in message:
				return None

	def leave(self):
		'''
		When called leave, a node should gracefully leave the network i.e. it should update its predecessor that it is leaving
		it should send its share of file to the new responsible node, close all the threads and leave. You can close listener thread
		by setting self.stop flag to True
		'''
		for x in range(len(self.files)):
			myTuple = "leaveaFiles" + " " +self.files[x]
			soc = socket.socket()
			soc.connect(self.successor)
			soc.send(myTuple.encode("utf-8"))
			time.sleep(0.5)
			fileName = self.host + '_' + str(self.port) + '/' + self.files[x]
			self.sendFile(soc,fileName)
			os.remove(fileName)
			soc.close()
		self.files.clear()
		mySuccessor = self.successor
		mypredcessor = self.predecessor
		myTuple = "iamleavingpred" + " " + mySuccessor[0] + " " + str(mySuccessor[1])
		soc = socket.socket()
		soc.connect(mypredcessor)
		soc.send(myTuple.encode("utf-8"))
		soc.close()
		self.predecessor = (self.host,self.port)
		myTuple = "iamleavingsucess" + " " + mypredcessor[0] + " " + str(mypredcessor[1])
		soc = socket.socket()
		soc.connect(mySuccessor)
		soc.send(myTuple.encode("utf-8"))
		soc.close()
		self.successor = (self.host,self.port)
		self.stop = True

	def sendFile(self, soc, fileName):
		''' 
		Utility function to send a file over a socket Arguments:	soc => a socket object
		fileName => file's name including its path e.g. NetCen/PA3/file.py
		'''
		fileSize = os.path.getsize(fileName)
		soc.send(str(fileSize).encode('utf-8'))
		soc.recv(1024).decode('utf-8')
		with open(fileName, "rb") as file:
			contentChunk = file.read(1024)
			while contentChunk!="".encode('utf-8'):
				soc.send(contentChunk)
				contentChunk = file.read(1024)

	def recieveFile(self, soc, fileName):
		'''
		Utility function to recieve a file over a socket
			Arguments:	soc => a socket object
						fileName => file's name including its path e.g. NetCen/PA3/file.py
		'''
		fileSize = int(soc.recv(1024).decode('utf-8'))
		soc.send("ok".encode('utf-8'))
		contentRecieved = 0
		file = open(fileName, "wb")
		while contentRecieved < fileSize:
			contentChunk = soc.recv(1024)
			contentRecieved += len(contentChunk)
			file.write(contentChunk)
		file.close()

	def kill(self):
		# DO NOT EDIT THIS, used for code testing
		self.stop = True