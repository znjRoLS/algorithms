//
// Created by rols on 3/27/17.
//
#pragma once

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

  void SetSBox(const uint8_t s_box[256]);
//    void SetSBox(uint8_t sBox[16][16]);
  void SetType(Type type);

  string Encrypt(string data, string key);
//    string Decrypt(string data, string key);
 private:

  class State {
   public:
    //TODO
    explicit State(string data);
//        explicit State(vector<vector<uint8_t>> data);
    ~State();

    void XOR(State &other);
//        void SubstituteBytes(uint8_t *sBox);

    uint8_t **state_matrix_;
    int state_side_size_;

  };

  std::shared_ptr<State> m_current_state_ = nullptr;
  Type m_aes_type_;
  uint8_t m_s_box_[STATE_CELL_SIZE * STATE_CELL_SIZE];
  uint8_t m_s_box_inv_[STATE_CELL_SIZE * STATE_CELL_SIZE];

  vector<State> ExpandKey(string key);
//  State &InitState(string data);

  void AddRoundKey(std::shared_ptr<State> data, State &key);
  void SubstituteBytes(State &state);
  void ShiftRows(State &state);
  void MixColumns(State &state);

};

//string aes_encrypt(string plaintext, string key);
//string aes_decrypt(string plaintext, string key);
