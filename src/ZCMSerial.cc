#include <ZCMSerial.h>

#include <zcm/zcm.h>
#include <zcm/transport/third-party/embedded/arduino/transport_arduino_serial.h>

#include <Arduino.h>

class ZCMSerial {
  private:
    zcm_t zcm;
  public:

    bool begin(uint32_t baud) {
      zcm_trans_t *zcm_serial = zcm_trans_arduino_serial_create(baud, timestamp_now, NULL);
      if(!zcm_serial) return false;
      return (zcm_init_trans(&zcm, zcm_serial) == 0);
    }

    zcm_errorlevel_t publish(const char* channel, const uint8_t* buf, uint32_t buflen, bool await = false) {
      zcm_errorlevel_t errlev = ZCM_INTCODE(zcm_publish(&zcm, channel, buf, buflen));
      ZCM_ERR_BREAK(errlev);

      if(await) {
        zcm_flush(&zcm);
        errlev = ZCM_INTCODE(zcm.err);
      }

      return errlev;
    }

    /**
     * Publish a UTF-8 string.
    */
    zcm_errorlevel_t publish(const char* channel, const char* str, bool await = false) {
      return publish(channel, (const uint8_t*)str, strlen(str), await);
    }

    /**
     * Subscribe a callback to a channel.
     * @param channel string to match (can be RegEx!)
     * @param cb subscription event buffer handler callback
     * @param args
    */
    zcm_errorlevel_t subscribe(const char* channel, void (*cb)(const zcm_recv_buf_t *rbuf, const char *channel, void *usr), void* args = NULL) {
      zcm_sub_t* sub = zcm_subscribe(&zcm, channel, cb, args);
      return (sub == NULL ? ZCM_EINVALID : ZCM_EOK);
    }
};

uint64_t timestamp_now(void* usr) {
  return micros();
}