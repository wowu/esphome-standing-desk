#pragma once

#include <stdint.h>
#include "decoder.h"

namespace esphome {
namespace standing_desk_height {

class PokarDecoder : public Decoder {
  private:
    // decode binary 7 segment display data
    int decode_7seg(uint8_t b) { }
    bool dot(uint8_t b) { }

  protected:
    enum state_t {
      START,  // waiting for 0x5A
      HEIGHT1,  // waiting for first height arg
      HEIGHT2,  // waiting for second height arg
      HEIGHT3,  // waiting for third height arg
      AFTER_HEIGHT,  // waiting for 0x01
      CHECKSUM,  // waiting for checksum
    } state_ = START;
    uint8_t buf_[4];

  public:
    PokarDecoder() { }
    ~PokarDecoder() { }

    bool put(uint8_t b);
    float decode();
};

}
}
