/*
 * WebServerPost.h
 *
 *  Created on: Sep 22, 2014
 *      Author: peter
 */

#ifndef WEBSERVERPOST_H_
#define WEBSERVERPOST_H_

void listenForEthernetClients();
void sendHeader(EthernetClient client, char *title);

void serverCmd(WebServer &server, WebServer::ConnectionType type, char *, bool);

#endif /* WEBSERVERPOST_H_ */
