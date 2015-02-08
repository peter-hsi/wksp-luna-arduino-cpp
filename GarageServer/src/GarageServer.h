/*
 * GarageServer.h
 *
 *  Created on: Sep 22, 2014
 *      Author: Peter Hsi
 */

#ifndef GARAGESERVER_H_
#define GARAGESERVER_H_

void listenForEthernetClients();
void sendHeader(EthernetClient client, char *title);

void serverCmd(WebServer &server, WebServer::ConnectionType type, char *, bool);

#endif /* GARAGESERVER_H_ */
