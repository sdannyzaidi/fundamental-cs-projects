'''
This module defines the behaviour of client
'''
import sys
import getopt
import socket
import random
from threading import Thread
import os
import util
import queue


class Client:
    '''
    This is the main Client Class. 
    '''

    def __init__(self, username, dest, port, window_size):
        self.server_addr = dest
        self.server_port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.settimeout(None)
        self.sock.bind(('', random.randint(10000, 40000)))
        self.name = username
        self.window = window_size
        self.message_handler = {
            'data': self.handle_data,
            'end': self.handle_end,
            'ack' : self.handle_ack,
            'start': self.handle_start
        }
        #self.chunk
        self.sendStart
        self.sendEnd
        self.sendJoin
        self.msg_pkt_s = ""
        self.queue = queue.Queue()
        self.ack = queue.Queue()
        self.seq = queue.Queue()
        self.r_seq = random.randint(1000,10000)
        self.check = self.r_seq

    def sendStart(self, seqno):
        pkt_s = util.make_packet("start",seqno)
        self.send(pkt_s)

    def sendJoin(self,seqno):
        pkt = util.make_message("JOIN", 1, message=self.name)
        pkt_s = util.make_packet("data",seqno, pkt)
        self.queue.put(pkt_s)
        self.seq.put(seqno)

    def sendEnd(self, seqno):
        pkt_s = util.make_packet("end",seqno)
        self.queue.put(pkt_s)
        self.seq.put(seqno)

    def handle_start(self,seqno,data):
        ack_seqno = int(seqno) + 1
        ack_pac = util.make_packet("ack",ack_seqno)
        self.send(ack_pac)

    def handle_end(self,seqno,data):
        ack_seqno = int(seqno) + 1
        ack_pac = util.make_packet("ack",ack_seqno)
        self.send(ack_pac)

    def handle_ack(self,seqno,data):
        intSeqno = int(seqno)
        self.ack.put(intSeqno)
        try:
            x = self.ack.get(True,0.5)
            self.check += 1
            count = 0
            if intSeqno >= self.check:
                if not (self.queue.empty()):
                    self.msg_pkt_s = self.queue.get()
                    self.send(self.msg_pkt_s)
                else:
                    return
        except:
            if (count < util.NUM_OF_RETRANSMISSIONS):
                self.send(self.msg_pkt_s)
                count += 1
            else:
                return

    def start(self):
        '''
        Main Loop is here
        Waits for userinput and then process it
        '''
        self.sendStart(self.r_seq)
        joinCheck = self.r_seq + 1
        self.sendJoin(joinCheck)
        joinCheck += 1
        self.sendEnd(joinCheck)

        while True:
            user_input = input()
            pkt = self.parse_input(user_input)
            if pkt is not None:
                msg_type = 'data'
                seqno = self.check
                self.sendStart(seqno)
                seqno += 1
                pkt_s = util.make_packet(msg_type, seqno, pkt)
                self.queue.put(pkt_s)
                self.seq.put(seqno)
                seqno += 1
                self.sendEnd(seqno)

    def receive_handler(self):
        '''
        Waits for message from server and forward the message to proper handler
        '''
        while True:
            msg = self.receive()
            if util.validate_checksum(msg.decode()):
                msg_type, seqno, data, _ = util.parse_packet(
                    msg.decode())
                self.message_handler.get(
                    msg_type, self.handle_other)(seqno, data)
                print("Print message from server",msg)
            else:
                # drop the packet if Checksum failed
                pass

    def receive(self, timeout=None):
        '''
        Waits to receive a message from socket and returns the message (if any)
        '''
        self.sock.settimeout(timeout)
        try:
            return self.sock.recv(4096)
        except socket.timeout:
            return None

    def handle_other(self, seqno, data):
        '''
        Drop the message if it has an unknown type
        '''
        raise NotImplementedError

    def handle_data(self, seqno, data):
        '''
        This function handles the message according to its type
        '''
        ack_seqno = int(seqno) + 1
        ack_pac = util.make_packet("ack",ack_seqno)
        self.send(ack_pac)

        _data = data.split(" ", 2)

        if _data[0] == "FORWARD_MESSAGE":
            _data = data.split(" ", 4)
            print("msg: %s: %s" % (_data[3], _data[4]))
        elif _data[0] == "RESPONSE_USERS_LIST":
            _data = data.split(" ", 3)
            print("list: %s" % _data[3])
        elif _data[0] == "ERR_UNKNOWN_MESSAGE":
            print("disconnected: server received an unknown command")
            os._exit(1)
        elif _data[0] == "ERR_SERVER_FULL":
            print("disconnected: server full")
            os._exit(1)
        elif _data[0] == "ERR_USERNAME_UNAVAILABLE":
            print("disconnected: username not available")
            os._exit(1)
        if _data[0] == "FORWARD_FILE":
            _data = data.split(" ", 5)
            print("file: %s: %s" % (_data[3], _data[4]))
            with open(self.name + "_" + _data[4], "w") as file_ptr:
                file_ptr.write(_data[5])
        else:
            # Just drop the packet
            pass

    def send(self, message, address=None):
        '''
        This methos will send the message to the provided address or the server
        '''
        if address is None:
            address = (self.server_addr, self.server_port)
        self.sock.sendto(message.encode(), address)

    def parse_input(self, input_data):
        '''
        This functions parses useriput and returns a packet to send to server (if required)
        '''
        data = input_data.split()
        if data[0] == "quit" and len(data) == 1:
            pkt = util.make_message("DISCONNECT", 1, message=self.name)
            pkt_with_header = util.make_packet("data", 0, pkt)
            self.send(pkt_with_header)
            print("quitting")
            sys.exit()
        elif data[0] == "list" and len(data) == 1:
            return util.make_message("REQUEST_USERS_LIST", 2)
        elif data[0] == "help" and len(data) == 1:
            helper()
        elif data[0] == "msg" and (int(data[1]) <= (len(data) - 3)):
            msg = " ".join(data[1:])
            return util.make_message("SEND_MESSAGE", 4, message=msg)
        elif data[0] == "file" and (int(data[1]) <= (len(data) - 3)):
            filename = data[-1]
            file_content = ""
            with open(filename) as file_ptr:
                file_content = file_ptr.read()
            msg = " ".join(data[1:])
            msg += " " + file_content
            return util.make_message("SEND_FILE", 4, message=msg)
        else:
            print("incorrect userinput format")
        return None


# Do not change this part of code
if __name__ == "__main__":
    def helper():
        '''
        This function is just for the sake of our Client module completion
        '''
        print("Client")
        print("-u username | --user=username The username of Client")
        print("-p PORT | --port=PORT The server port, defaults to 15000")
        print("-a ADDRESS | --address=ADDRESS The server ip or hostname, defaults to localhost")
        print("-w WINDOW_SIZE | --window=WINDOW_SIZE The window_size, defaults to 3")
        print("-h | --help Print this help")
    try:
        OPTS, ARGS = getopt.getopt(sys.argv[1:],
                                   "u:p:a:w", ["user=", "port=", "address=", "window="])
    except getopt.error:
        helper()
        exit(1)

    PORT = 15000
    DEST = "localhost"
    USER_NAME = None
    WINDOW_SIZE = 3
    for o, a in OPTS:
        if o in ("-u", "--user="):
            USER_NAME = a
        elif o in ("-p", "--port="):
            PORT = int(a)
        elif o in ("-a", "--address="):
            DEST = a
        elif o in ("-w", "--window="):
            WINDOW_SIZE = a

    if USER_NAME is None:
        print("Missing Username.")
        helper()
        exit(1)

    S = Client(USER_NAME, DEST, PORT, WINDOW_SIZE)
    try:
        # Start receiving Messages
        T = Thread(target=S.receive_handler)
        T.daemon = True
        T.start()
        # Start Client
        S.start()
    except (KeyboardInterrupt, SystemExit):
        sys.exit()
