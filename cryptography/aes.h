//
// Created by rols on 3/27/17.
//

#ifndef HELMET_AES_H
#define HELMET_AES_H

#include <iostream>
#include <vector>


#define BLOCK_SIZE 128
#define STATE_CELL_SIZE 8
#define AES_TYPE AES_128

using namespace std;

class AES {

public:
    AES();

    enum Type { AES_128, AES_192, AES_256 };

    void SetSBox(uint8_t sBox[256]);
    void SetSBox(uint8_t sBox[16][16]);
    void SetType(Type type);


    string Encrypt(string data, string key);
    string Decrypt(string data, string key);
private:

    class State {
    public:
        //TODO
        State(string data);
        State(vector<vector<uint8_t>> data);
        ~State();

        void XOR(State& other);
        void SubstituteBytes(uint8_t *sBox);

        uint8_t **stateMatrix;
        int stateSideSize;

    };

    State m_currentState;
    Type m_aesType;
    uint8_t m_sBox[STATE_CELL_SIZE*STATE_CELL_SIZE];
    uint8_t m_sBoxInv[STATE_CELL_SIZE*STATE_CELL_SIZE];

    vector<State> ExpandKey(string key);
    State& InitState(string data);

    void AddRoundKey(State& data, State& key);
    void SubstituteBytes(State& state);
    void ShiftRows(State& state);
    void MixColumns(State& state);

};

string aes_encrypt(string plaintext, string key);
string aes_decrypt(string plaintext, string key);

#endif //HELMET_AES_H
