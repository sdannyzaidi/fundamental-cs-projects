import sys
from collections import defaultdict
from router import Router
from packet import Packet
from json import dumps, loads
from dijkstar import Graph, find_path


class LSrouter(Router):
    """Link state routing protocol implementation."""

    def __init__(self, addr, heartbeatTime):
        """TODO: add your own class fields and initialization code here"""
        Router.__init__(self, addr)  # initialize superclass - don't remove
        self.heartbeatTime = heartbeatTime
        self.last_time = 0
        self.LSalgorithm = Graph(undirected=True)
        self.neighbourData = []
        self.rouTable = {}
        self.lsStorage = {}
        self.seqno = 0
        self.numInfinity = 16
        
    def handlePacket(self, port, packet):
        """TODO: process incoming packet"""
        if packet.isTraceroute():
            # Hints: this is a normal data packet
            # if the forwarding table contains packet.dstAddr
            if packet.dstAddr in self.rouTable:
                hop = self.rouTable[packet.dstAddr][1]
                for node in self.neighbourData:
                    if hop == node[1]:
                        self.send(node[0], packet)
                        break
                    else:
                        continue
        
        else:
            data, start, newSeqno = loads(packet.content)
            newData = loads(data)
            if start in self.lsStorage:
                prevSeqno = self.lsStorage[start][0]
                if prevSeqno < newSeqno:
                    self.lsStorage[start] = [newSeqno,newData]
                    for node in self.neighbourData:
                        if node[0] == port:
                            continue
                        else:
                            self.send(node[0], packet)
            else:
                self.lsStorage[start] = [newSeqno,newData]
            
            for a in range(len(newData)):
                for b in range(len(self.neighbourData)):
                    sender = newData[a]
                    reciever = self.neighbourData[b]
                    if sender[1] == reciever[1]:
                        continue
                    else:
                        self.LSalgorithm.add_edge(start, sender[1], sender[2])
            
            for destination in self.LSalgorithm:
                try:
                    destPath = find_path(self.LSalgorithm, self.addr, destination)
                    hop = destPath.nodes[1]
                    leastCost = destPath.total_cost
                except:
                    if destination != self.addr:
                        hop = None
                        leastCost = self.numInfinity

                    else:
                        hop = None
                        leastCost = self.numInfinity
                self.rouTable[destination] = [leastCost, hop]

    def handleNewLink(self, port, endpoint, cost):
        """TODO: handle new link"""
        # Hints:
        # update the forwarding table
        infoList = [port,endpoint,cost,self.addr]
        self.neighbourData.append(infoList)
        self.LSalgorithm.add_edge(self.addr, endpoint, cost)
        for flooding in range(len(self.neighbourData)):
            pac = Packet(Packet.ROUTING, self.addr, self.neighbourData[flooding][1])
            pac.content = dumps((dumps(self.neighbourData),self.addr, self.seqno))
            self.send(self.neighbourData[flooding][0], pac)
        self.seqno += 1
        
        for destination in self.LSalgorithm:
            try:
                destPath = find_path(self.LSalgorithm, self.addr, destination)
                hop = destPath.nodes[1]
                leastCost = destPath.total_cost
            except:
                if destination != self.addr:
                    hop = None
                    leastCost = self.numInfinity
                else:
                    hop = destination
                    leastCost = 0
            self.rouTable[destination] = [leastCost, hop]

    def handleRemoveLink(self, port):
        # Hints:
        # update the forwarding table
        # broadcast the new link state of this router to all neighbors
        for node in self.neighbourData:
            if node[0] == port:
                node[2] = self.numInfinity
                self.LSalgorithm.remove_edge(self.addr, node[1])
                self.LSalgorithm.add_edge(self.addr, node[1], self.numInfinity)
                break
            else:
                continue

        for node in self.neighbourData:
            pac = Packet(Packet.ROUTING, self.addr, node[1])
            pac.content = dumps((dumps(self.neighbourData),self.addr, self.seqno))
            self.send(node[0], pac)
        self.seqno += 1
        for destination in self.LSalgorithm:
            try:
                destPath = find_path(self.LSalgorithm, self.addr, destination)
                hop = destPath.nodes[1]
                leastCost = destPath.total_cost
            except:
                if destination != self.addr:
                    hop = None
                    leastCost = self.numInfinity
                else:
                    hop = destination
                    leastCost = 0
            self.rouTable[destination] = [leastCost, hop]

    def handleTime(self, timeMillisecs):
        """TODO: handle current time"""
        if timeMillisecs - self.last_time >= self.heartbeatTime:
            self.last_time = timeMillisecs
            # Hints:
            # broadcast the link state of this router to all neighbors
            for node in self.neighbourData:
                pac = Packet(Packet.ROUTING, self.addr, node[1])
                pac.content = dumps((dumps(self.neighbourData),self.addr, self.seqno))
                self.send(node[0], pac)
                self.seqno += 1

    def debugString(self):
        """TODO: generate a string for debugging in network visualizer"""
        return ""