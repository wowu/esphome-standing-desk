#include "decoder_variant.h"

namespace esphome {
namespace standing_desk_height {

const LogString *decoder_variant_to_string(DecoderVariant variant) {
  switch (variant) {
    case DECODER_VARIANT_JARVIS:
      return LOG_STR("jarvis");
    case DECODER_VARIANT_UPLIFT:
      return LOG_STR("uplift");
    case DECODER_VARIANT_OMNIDESK:
      return LOG_STR("omnidesk");
    case DECODER_VARIANT_POKAR:
      return LOG_STR("pokar");
    default:
      return LOG_STR("unknown");
  }
}

}
}
