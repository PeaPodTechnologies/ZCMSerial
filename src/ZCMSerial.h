#ifndef ZCMSERIAL_H_
#define ZCMSERIAL_H_

#define I2CIP_ZCM_BAUD_DEFAULT 115200

#define ZCM_INTCODE(i) ((zcm_return_codes)i)
#define ZCM_ERR_BREAK(errlev) if((errlev) != ZCM_EOK) { return (errlev); }

#include <zcm/zcm.h>

#define ZCM_CHANNEL_DEBUG "debug"
#define DEBUG_BREAKPOINT(str) ZCMSerial::Debug::_breakpoint(__LINE__, str, false);
#define DEBUG_BREAKPOINT(str, await) ZCMSerial::Debug::_breakpoint(__LINE__, str, await);

typedef zcm_return_codes zcm_errorlevel_t;

typedef struct {
  // controller ID
  // device list
  // 
} zcm_telemetry_event_t;

namespace ZCMSerial {
  private:
    // const zcm_key
  public:

    bool begin(uint32_t baud = I2CIP_ZCM_BAUD_DEFAULT);

    zcm_errorlevel_t publish(const char* channel, const uint8_t* buf, uint32_t buflen, bool await = false);
    
    zcm_errorlevel_t publish(const char* channel, const char* str, bool await = false);

    zcm_errorlevel_t subscribe(const char* channel, void (*cb)(const zcm_recv_buf_t *rbuf, const char *channel, void *usr));

    namespace Debug {
      void breakpoint(const char* message, bool await = false) {
        publish(ZCM_CHANNEL_DEBUG, message, await);
      }

      void _breakpoint(const unsigned long line, const char* message, bool await) {
        uint8_t len = strlen(message);
        char str[len] = { '\0' };

        sprintf(str, "%lu", line);

        len = strlen(str);
        strcpy(str+len, message)
        
        publish(ZCM_CHANNEL_DEBUG, str, await);
      }

    };

    namespace Telemetry {

    };
};

#endif