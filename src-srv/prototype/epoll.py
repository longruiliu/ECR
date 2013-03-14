import socket, select, thread

SERVER_PORT = 0x1024
SERVER_DOMAIN = '0.0.0.0'
BACKLOG = 1024
TIME_INTERVAL = 0.5

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((SERVER_DOMAIN, SERVER_PORT))
    server.listen(BACKLOG)
    server.setblocking(0)

    epoll = select.epoll()
    epoll.register(server.fileno(), select.EPOLLIN)

    try:
        connections = {}
        while 1:
            events = epoll.poll(TIME_INTERVAL)
            for fileno, event in events:
                if fileno == server.fileno():
                    newsock, addr = server.accept()
                    newsock.setblocking(0)
                    epoll.register(newsock.fileno(), select.EPOLLIN)
                    connections[newsock.fileno()] = (newsock, addr)
                elif event & select.EPOLLIN:
                    
