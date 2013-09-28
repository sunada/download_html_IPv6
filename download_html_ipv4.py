#!/usr/bin/python

from socket import *
import sys
import re

BUFSIZE = 10240

def parse(url):
    pattern1 = re.compile('.+?/')
    host = pattern1.findall(url)[0][:-1]
    pattern2 = re.compile('/.+$')
    try:
        file = pattern2.findall(url)[0]
    except:
        file = '/'
    #print host, file
    return (host, file)

def download(url):
    host, file = parse(url)
    print host, file

    ip = gethostbyname(host)
    print ip

    sock = socket(AF_INET, SOCK_STREAM)
    sock.connect((ip, 80))

    buf = "GET " + file + " HTTP/1.1\r\nHost: "+ host + "\r\n\r\n"
    print buf

    sock.send(buf)
    print "sended"

    html = sock.recv(BUFSIZE)
    print html
    html = sock.recv(BUFSIZE)
    print html


if __name__ == '__main__':
   url = sys.argv[1]

   download(url)
   #parse(url)

