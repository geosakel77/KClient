//
// Created by george on 16/11/2017.
//

#ifndef KCLIENT_KCLIENT_H
#define KCLIENT_KCLIENT_H

#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "FHE-SI.h"
#include "Serialization.h"
#include "clientfhesiutils.h"
#include "unistd.h"
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

class KClientV1 {

private:
    string u_serverIP;
    int u_serverPort;
    int u_serverSocket=-1;
    string t_serverIP;
    int t_serverPort;
    int t_serverSocket=-1;
    bool verbose;

    unsigned client_p;
    unsigned client_g;
    unsigned client_logQ;
    unsigned dim; // dimension of the data
    FHEcontext *client_context;
    FHESISecKey *fhesiSecKey;
    FHESIPubKey *fhesiPubKey;
    KeySwitchSI *keySwitchSI;
    FHESISecKey *fhesiSecKeyT;
    KeySwitchSI *keySwitchSIT;
    ifstream pkCToStream();
    ifstream ksCToStream();
    ifstream ksTToStream();
    ifstream skTToStream();
    ifstream contextToStream();
    ifstream encryptedDataToStream(const Ciphertext &);
    vector<vector<uint32_t>> loadedataToInt;
    vector<vector<ZZ_pX>> loadeddata;
    vector<ZZ_p> labels;
    map<uint32_t ,vector<ZZ_pX> > encrypted_data_hash_table;
    map<uint32_t ,vector<uint32_t>> unencrypted_data_hash_table;
    map<uint32_t ,unsigned> results;
    map<uint32_t ,uint32_t > identifiers;
    void connectToUServer();
    void connectToTServer();
    void createStruct();

public:
    KClientV1(unsigned, unsigned, unsigned,const string &,const string&,unsigned ,const string &, unsigned,bool verbose=true);
    bool sendMessage(string, int socket);
    bool sendStream(ifstream, int);
    string receiveMessage(const int &,int buffersize=64);
    void log(int,string);
    void sendEncryptionParamToTServer();
    void sendEncryptionParamToUServer();
    void sendEncryptedDataToUServer();
    void sendUnEncryptedDataToTServer();
    void receiveResult();
};


#endif //KCLIENT_KCLIENT_H
