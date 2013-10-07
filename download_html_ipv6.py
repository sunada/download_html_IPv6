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
    #if url[-1] != '/':
    #    url += '/'

    host, file = parse(url)
    print host, file

    ip = getaddrinfo(host, None)[0][4][0]
    print ip

    sock = socket(AF_INET6, SOCK_STREAM)
    sock.connect((ip, 80))

    buf = "GET " + file + " HTTP/1.1\r\nHost: "+ host + "\r\n\r\n"
    print buf

    sock.send(buf)
    print "sended"

    html = sock.recv(BUFSIZE)
    print 'len(html): ', len(html)
    print html
    html = sock.recv(BUFSIZE)
    print
    print
    print 'second len(html): ', len(html)
    print html
    html = sock.recv(BUFSIZE)
    print 'third len(html): ', len(html)
    print html
    html = sock.recv(BUFSIZE)
    print 'forth len(html): ', len(html)
    print html

if __name__ == '__main__':
   url = sys.argv[1]

   download(url)
   #parse(url)

