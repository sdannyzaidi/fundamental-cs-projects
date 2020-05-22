'''
This module defines the behaviour of server
'''
import sys
import getopt
import socket
import util
import queue
import random
from threading import Thread
import time

class Server:
    '''
    This is the main Server Class. You will to write Server code inside this class.
    '''

    def __init__(self, dest, port, window_size):
        self.server_addr = dest
        self.server_port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.settimeout(None)
        self.sock.bind((self.server_addr, self.server_port))
        self.window = window_size
        self.connections = {}
        self.packet_handler = {
            'start': self.handle_start,
            'data': self.handle_data,
            'end': self.handle_end,
            'ack': self.handle_ack
        }
        self.message_handler = {
            'JOIN': self.handle_msg_join,
            'DISCONNECT': self.handle_msg_disconnect,
            'REQUEST_USERS_LIST': self.handle_msg_list,
            'SEND_MESSAGE': self.handle_msg_msg,
            'SEND_FILE': self.handle_msg_file
        }
        # self.chunk
        self.sendStart
        self.sendEnd
        self.msg_pkt_s = ""
        self.queue = queue.Queue()
        self.ack = queue.Queue()
        self.seq = queue.Queue()
        self.r_seq = random.randint(1000,10000)
        self.check = self.r_seq

    def start(self):
        '''
        Main loop.
        Receive a Message from a Client and process it
        '''
        while True:
            try:
                message, address = self.receive()
                # self.send(message,address)
                msg_type, seqno, data, _ = util.parse_packet(message.decode())

                if util.validate_checksum(message.decode()):
                    if "data" in msg_type:
                        intSeqno = int(seqno) + 1
                        ack_pac = util.make_packet("ack",intSeqno)
                        self.send(ack_pac,address)
                    self.packet_handler.get(msg_type, self.handle_other)(seqno, data, address)
                    print("Message from Client: ", message)
                    
                
            except (KeyboardInterrupt, SystemExit):
                exit()

    def send(self, message, address):
        '''
        Sends the given message to the provided address
        '''
        self.sock.sendto(message.encode(), address)

    def get_address(self, username):
        '''
        Helper function to find address of a user
        '''
        for i, j in self.connections:
            if self.connections[(i, j)] == username:
                return (i, j)
        return None

    def receive(self):
        '''
        Receives message and returns. (Blocking)
        '''
        return self.sock.recvfrom(4096)
    # def chunk(self,str,size)
    
    def sendStart(self, seqno,address):
        pkt_s = util.make_packet("start",seqno)
        self.send(pkt_s,address)
        # self.queue.put(pkt_s)
        # self.seq.put(seqno)

    def sendEnd(self, seqno):
        pkt_s = util.make_packet("end",seqno)
        self.queue.put(pkt_s)
        self.seq.put(seqno)


    def handle_start(self, seqno, data, address):
        '''
        Handles Start Message
        '''
        ack_seqno = int(seqno) + 1
        ack_pac = util.make_packet("ack",ack_seqno)
        self.send(ack_pac,address)

    def handle_data(self, seqno, data, address):
        '''
        Forwards the message to proper handler (according to its type)
        '''
        _data = data.split(" ", 2)
        self.message_handler.get(_data[0], self.handle_msg_other)(seqno, data, address)
        # intSeqno = int(seqno) + 1
        # ack_pac = util.make_packet("ack",intSeqno)
        # self.send(ack_pac,address)

    def handle_ack(self, seqno, data, address):
        '''
        Handles ACK Message
        '''
        intSeqno = int(seqno)
        self.ack.put(intSeqno)
        try:
            x = self.ack.get(True,0.5)
            self.check += 1
            count = 0
            if intSeqno >= self.check:
                if not (self.queue.empty()):
                    self.msg_pkt_s = self.queue.get()
                    self.send(self.msg_pkt_s,address)
                else:
                    return
        except:
            if (count < util.NUM_OF_RETRANSMISSIONS):
                self.send(self.msg_pkt_s,address)
                count += 1
            else:
                return
        
    def handle_end(self, seqno, data, address):
        '''
        Handle END Message
        '''
        ack_seqno = int(seqno) + 1
        ack_pac = util.make_packet("ack",ack_seqno)
        self.send(ack_pac,address)

    def handle_other(self, seqno, data, address):
        '''
        Handles Message of Unknown type header
        '''
        raise NotImplementedError

    def handle_msg_disconnect(self, seqno, data, address):
        '''
        Handles Message of type DISCONNECT
        '''
        _data = data.split(" ", 2)
        if address in self.connections:
            username = self.connections[address]
            del self.connections[address]
            print("disconnected: %s" % username)

    def handle_msg_join(self, seqno, data, address):
        '''
        Handles Message of Type JOIN
        '''
        intSeqno = int(seqno) + 1
        _data = data.split(" ", 2)
        username = _data[2]
        if username in self.connections.values():
            # send ERR_USERNAME_UNAVAILABLE
            #send ack
            pkt = util.make_message("ERR_USERNAME_UNAVAILABLE", 2)
            pkt_with_header = util.make_packet("data", 0, pkt)
            self.send(pkt_with_header, address)
            print("disconnected: username not available")

        elif len(self.connections) >= util.MAX_NUM_CLIENTS:
            # send ERR_SERVER_FULL
            #send ack
            pkt = util.make_message("ERR_SERVER_FULL", 2)
            pkt_with_header = util.make_packet("data", 0, pkt)
            self.send(pkt_with_header, address)
            print("disconnected: server full")

        else:
            self.connections[address] = username
            print("join: %s" % username)
            # ack_pac = util.make_packet("ack",intSeqno)
            # self.send(ack_pac,address)

    def handle_msg_list(self, seqno, data, address):
        '''
        Handles Message of Type REQUEST_USERS_LIST
        '''
        #intSeqno = int(seqno) + 1
        _data = data.split(" ", 2)
        if address in self.connections:
            username = self.connections[address]
            # ack_pac = util.make_packet("ack",intSeqno)
            # self.send(ack_pac,address)
            # send RESPONSE_USERS_LIST
            check = self.check
            self.sendStart(check,address)
            check += 1
            msg = "%d %s" % (len(self.connections)," ".join(sorted(self.connections.values())))
            pkt = util.make_message("RESPONSE_USERS_LIST", 3, message=msg)
            pkt_s = util.make_packet("data", check, pkt)
            self.queue.put(pkt_s)
            self.seq.put(check)
            check += 1
            self.sendEnd(check)
            print("request_users_list: %s" % username)

    def handle_msg_msg(self, _, data, address):
        '''
        Handles Message of Type SEND_MESSAGE
        '''
        _data = data.split(" ", 2)
        if address in self.connections:
            _data = data.split(" ", 3)
            num_receipients = int(_data[2])
            msg = data.split(" ", num_receipients + 3)[-1]
            username = self.connections[address]

            print("msg: %s" % username)

            receipients = data.split(
                " ", num_receipients + 3)[3:3 + num_receipients]
            # removing duplicates
            receipients = list(dict.fromkeys(receipients))

            for receiver in receipients:
                if receiver in self.connections.values():
                    address_recv = self.get_address(receiver)
                    # send FORWARD_MESSAGE
                    msg_to_send = "%d %s %s" % (1, username, msg)
                    pkt = util.make_message("FORWARD_MESSAGE", 4, message=msg_to_send)
                    check = self.check
                    self.sendStart(check,address_recv)
                    check += 1
                    pkt_s = util.make_packet("data", check, pkt)
                    self.queue.put(pkt_s)
                    self.seq.put(check)
                    check += 1
                    self.sendEnd(check)
                    
                else:
                    print("msg: %s to non-existent user %s" %
                          (username, receiver))

    def handle_msg_file(self, _, data, address):
        '''
        Handles Message of SEND_FILE type
        '''
        if address in self.connections:
            _data = data.split(" ", 3)
            num_receipients = int(_data[2])
            msg = data.split(" ", num_receipients + 3)[-1]
            username = self.connections[address]

            print("file: %s" % username)

            receipients = data.split(
                " ", num_receipients + 3)[3:3 + num_receipients]
            # removing duplicates
            receipients = list(dict.fromkeys(receipients))

            for receiver in receipients:
                if receiver in self.connections.values():
                    address_recv = self.get_address(receiver)
                    # send FORWARD_MESSAGE
                    msg_to_send = "%d %s %s" % (1, username, msg)
                    pkt = util.make_message("FORWARD_FILE", 4, message=msg_to_send)
                    check = self.check
                    self.sendStart(check,address_recv)
                    check += 1
                    pkt_s = util.make_packet("data", check, pkt)
                    self.queue.put(pkt_s)
                    self.seq.put(check)
                    check += 1
                    self.sendEnd(check)
                else:
                    print("file: %s to non-existent user %s" %
                          (username, receiver))

    def handle_msg_other(self, seqno, data, address):
        '''
        Handles Message of Unknown Type
        '''
        raise NotImplementedError


# Do not change this part of code
if __name__ == "__main__":
    def helper():
        '''
        This function is just for the sake of our module completion
        '''
        print("Server")
        print("-p PORT | --port=PORT The server port, defaults to 15000")
        print("-a ADDRESS | --address=ADDRESS The server ip or hostname, defaults to localhost")
        print("-w WINDOW | --window=WINDOW The window size, default is 3")
        print("-h | --help Print this help")

    try:
        OPTS, ARGS = getopt.getopt(sys.argv[1:],
                                   "p:a:w", ["port=", "address=", "window="])
    except getopt.GetoptError:
        helper()
        exit()

    PORT = 15000
    DEST = "localhost"
    WINDOW = 3

    for o, a in OPTS:
        if o in ("-p", "--port="):
            PORT = int(a)
        elif o in ("-a", "--address="):
            DEST = a
        elif o in ("-w", "--window="):
            WINDOW = a

    SERVER = Server(DEST, PORT, WINDOW)
    try:
        SERVER.start()
    except (KeyboardInterrupt, SystemExit):
        exit()
