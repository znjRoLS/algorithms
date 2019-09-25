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
  assert (data.size() == BLOCK_SIZE / 8);
  state_side_size_ = sqrt(BLOCK_SIZE / STATE_CELL_SIZE);
  assert(state_side_size_ * state_side_size_ == BLOCK_SIZE / STATE_CELL_SIZE);
  state_matrix_ = new uint8_t *[state_side_size_];
  for (int ii = 0; ii < state_side_size_; ii++) state_matrix_[ii] = new uint8_t[state_side_size_];

  if (STATE_CELL_SIZE == 8) {
    for (int ii = 0; ii < data.size(); ii++) {
      state_matrix_[ii % state_side_size_][ii / state_side_size_] = data[ii];
    }
  }
}

AES::State::~State() {
  for (int ii = 0; ii < state_side_size_; ii++) delete[] state_matrix_[ii];
  delete[] state_matrix_;
}

void AES::State::XOR(State &other) {
  assert(state_side_size_ == other.state_side_size_);

  for (int ii = 0; ii < state_side_size_; ii++) {
    for (int jj = 0; jj < state_side_size_; jj++) {
      state_matrix_[ii][jj] ^= other.state_matrix_[ii][jj];
    }
  }
}

AES::AES() {

}

void AES::SetSBox(const uint8_t s_box[256]) {
  for (uint16_t i = 0; i < 256u; i++) {
    m_s_box_[i] = s_box[i];
    m_s_box_inv_[s_box[i]] = i;
  }
}

void AES::SetType(Type type) {
  m_aes_type_ = type;
}

string AES::Encrypt(string data, string key) {
  vector<State> round_keys = ExpandKey(key);
  m_current_state_ = std::make_shared<AES::State>(data);

  AddRoundKey(m_current_state_, round_keys[0]);

  return "";
}

//TODO iterator?
vector<AES::State> AES::ExpandKey(string key) {
  vector<State> keys;
  State original_key(key);

  keys.push_back(original_key);

  for (int ii = 1; ii < NUM_ROUNDS[m_aes_type_]; ii++) {
    uint8_t *column = new uint8_t[original_key.state_side_size_];
    for (int jj = 0; jj < original_key.state_side_size_; jj++) {
      column[jj] = original_key.state_matrix_[jj][original_key.state_side_size_ - 1];
    }

  }

  return {};
}

void AES::AddRoundKey(std::shared_ptr<State> state, State &key) {
  state->XOR(key);
}

void AES::SubstituteBytes(State &state) {
  for (int ii = 0; ii < state.state_side_size_; ii++) {
    for (int jj = 0; jj < state.state_side_size_; jj++) {
      state.state_matrix_[ii][jj] = m_s_box_[state.state_matrix_[ii][jj]];
    }
  }
}

void AES::ShiftRows(State &state) {
  for (int ii = 1; ii < state.state_side_size_; ii++) {
    int processed = 0;
    int cnt = 0;
    while (processed < state.state_side_size_) {
      uint8_t state_temp = state.state_matrix_[ii][cnt];
      for (int jj = cnt; jj < state.state_side_size_; jj = (jj + ii) % state.state_side_size_) {

        state.state_matrix_[ii][jj] = state.state_matrix_[ii][(jj + ii) % state.state_side_size_];
        processed++;

        if ((jj + ii) % state.state_side_size_ == cnt) {
          state.state_matrix_[ii][jj] = state_temp;
          break;
        }
      }
      cnt++;
    }
  }
}

void AES::MixColumns(State &state) {
  auto *new_column = new uint8_t[state.state_side_size_];
  for (int ii = 0; ii < state.state_side_size_; ii++) {
    for (int jj = 0; jj < state.state_side_size_; jj++) {
      uint8_t val = 0;
      for (int kk = 0; kk < state.state_side_size_; kk++) {
        val ^= state.state_matrix_[kk][ii] * state.state_matrix_[jj][kk];
      }
      new_column[jj] = val;
    }
    for (int jj = 0; jj < state.state_side_size_; jj++) {
      state.state_matrix_[jj][ii] = new_column[jj];
    }
  }
  delete[] new_column;
}