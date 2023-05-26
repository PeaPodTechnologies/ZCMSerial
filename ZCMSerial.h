#ifndef ZCMSERIAL_H_
#define ZCMSERIAL_H_

#define I2CIP_ZCM_BAUD_DEFAULT 115200

#define ZCM_INTCODE(i) ((zcm_return_codes)i)
#define ZCM_ERR_BREAK(errlev) if((errlev) != ZCM_EOK) { return (errlev); }

#include <zcm/zcm.h>

typedef zcm_return_codes zcm_errorlevel_t;

class ZCMSerial {
  private:
    // const zcm_key
  public:

    bool begin(uint32_t baud = I2CIP_ZCM_BAUD_DEFAULT);

    zcm_errorlevel_t publish(const char* channel, const uint8_t* buf, uint32_t buflen, bool await = false);
    
    zcm_errorlevel_t publish(const char* channel, const char* str, bool await = false);

    zcm_errorlevel_t subscribe(const char* channel, void (*cb)(const zcm_recv_buf_t *rbuf, const char *channel, void *usr))
};

#endif