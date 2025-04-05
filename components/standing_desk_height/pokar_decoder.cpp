#include "pokar_decoder.h"

namespace esphome {
namespace standing_desk_height {

// decode binary 7 segment display data
int PokarDecoder::decode_7seg(uint8_t b) {
  // First bit is dot, ignore it
  switch (b & 0b01111111) {
  case 0b00111111: return 0;
  case 0b00000110: return 1;
  case 0b01011011: return 2;
  case 0b01001111: return 3;
  case 0b01100110: return 4;
  case 0b01101101: return 5;
  case 0b01111101: return 6;
  case 0b00000111: return 7;
  case 0b01111111: return 8;
  case 0b01101111: return 9;
  default: return -1;
  }
}

bool PokarDecoder::dot(uint8_t b) {
  return b & 0b10000000;
}

bool PokarDecoder::put(uint8_t b) {
  switch (state_) {
  case START:
    if (b == 0x5A) {
      state_ = HEIGHT1;
      return false;
    } else {
      state_ = START;
      return false;
    }
  case HEIGHT1:
    buf_[0] = b;
    state_ = HEIGHT2;
    return false;
  case HEIGHT2:
    buf_[1] = b;
    state_ = HEIGHT3;
    return false;
  case HEIGHT3:
    buf_[2] = b;
    state_ = AFTER_HEIGHT;
    return false;
  case AFTER_HEIGHT:
    if (b == 0x01) {
      state_ = CHECKSUM;
      return false;
    } else {
      state_ = START;
      return false;
    }
  case CHECKSUM:
    buf_[3] = b;
    state_ = START;
    return true;
  default:
    return false;
  }
  return false;
}

float PokarDecoder::decode() {
  // ignore checksum for now
  float total = 0;
  
  total += decode_7seg(buf_[0]) * 100;
  total += decode_7seg(buf_[1]) * 10;
  total += decode_7seg(buf_[2]);
  
  if (dot(buf_[1])) {
    total /= 10;
  }

  return total;
}

}
}
