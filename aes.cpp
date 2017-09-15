//
// Created by rols on 3/27/17.
//

#include "aes.h"
#include <unordered_map>
#include <cassert>
#include <cmath>

using namespace std;


static unordered_map<AES::Type, int> NUM_ROUNDS = {
        {AES::AES_128, 10},
        {AES::AES_192, 12},
        {AES::AES_256, 14}
};



AES::State::State(std::string data) {
    assert (data.size() == BLOCK_SIZE/8);
    stateSideSize = sqrt(BLOCK_SIZE/STATE_CELL_SIZE);
    assert(stateSideSize*stateSideSize == BLOCK_SIZE/STATE_CELL_SIZE);
    stateMatrix = new uint8_t*[stateSideSize];
    for(int ii = 0; ii < stateSideSize; ii++) stateMatrix[ii] = new uint8_t[stateSideSize];

    if (STATE_CELL_SIZE == 8) {
        for(int ii = 0; ii < data.size(); ii ++) {
            stateMatrix[ii%stateSideSize][ii/stateSideSize] = data[ii];
        }
    }
}

AES::State::~State() {
    for(int ii = 0; ii < stateSideSize; ii++) delete [] stateMatrix[ii];
    delete [] stateMatrix;
}

void AES::State::XOR(State& other) {
    assert(stateSideSize == other.stateSideSize);

    for(int ii = 0 ; ii < stateSideSize; ii ++) {
        for(int jj = 0; jj < stateSideSize; jj++) {
            stateMatrix[ii][jj] ^= other.stateMatrix[ii][jj];
        }
    }
}

AES::AES() {

}

void AES::SetSBox(uint8_t sBox[256]) {
    for(uint8_t i = 0 ; i < 256; i ++) {
        m_sBox[i] = sBox[i];
        m_sBoxInv[sBox[i]] = i;
    }
}

void AES::SetType(Type type) {
    m_aesType = type;
}

string AES::Encrypt(string data, string key) {
    vector<State> roundKeys = ExpandKey(key);
    m_currentState = InitState(data);

    AddRoundKey(state, roundKeys[0]);

}

//TODO iterator?
vector<State> AES::ExpandKey(string key) {
    vector<State> keys;
    State originalKey(key);

    keys.push_back(originalKey);

    for (int ii = 1; ii < NUM_ROUNDS[m_aesType]; ii++) {
        uint8_t *column = new uint8_t[originalKey.stateSideSize];
        for(int jj = 0; jj < originalKey.stateSideSize; jj ++) {
            column[jj] = originalKey.stateMatrix[jj][originalKey.stateSideSize-1];
        }

    }
}

State& AES::InitState(string data) {
    return State(data);
}

void AES::AddRoundKey(State& state, State& key) {
    state.XOR(key);
}

void AES::SubstituteBytes(State &state) {
    for(int ii = 0 ; ii < state.stateSideSize; ii ++) {
        for (int jj = 0; jj < state.stateSideSize; jj++) {
            state.stateMatrix[ii][jj] = m_sBox[state.stateMatrix[ii][jj]];
        }
    }
}

void AES::ShiftRows(State &state) {
    for(int ii = 1; ii < state.stateSideSize; ii++) {
        int processed = 0;
        int cnt = 0;
        while(processed < state.stateSideSize) {
            uint8_t stateTemp = state.stateMatrix[ii][cnt];
            for(int jj = cnt; jj < state.stateSideSize; jj = (jj+ii)%state.stateSideSize) {

                state.stateMatrix[ii][jj] = state.stateMatrix[ii][(jj+ii)%state.stateSideSize];
                processed ++;

                if ((jj+ii)%state.stateSideSize == cnt) {
                    state.stateMatrix[ii][jj] = stateTemp;
                    break;
                }
            }
            cnt++;
        }
    }
}

void AES::MixColumns(State &state) {
    uint8_t *newColumn = new uint8_t[state.stateSideSize];
    for(int ii = 0; ii < state.stateSideSize; ii++) {
        for(int jj = 0; jj < state.stateSideSize; jj++) {
            uint8_t val = 0;
            for (int kk = 0; kk < state.stateSideSize; kk ++) {
                val ^= state.stateMatrix[kk][ii] * state.stateMatrix[jj][kk];
            }
            newColumn[jj] = val;
        }
        for (int jj = 0; jj < state.stateSideSize; jj++) {
            state.stateMatrix[jj][ii] = newColumn[jj];
        }
    }
    delete [] newColumn;
}