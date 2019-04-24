#include "DebugMacros.h"
#include <ThingSpeak.h>
void SendDataThingSpeak(int *xt, int *it, unsigned long mych,
                        const char *mykey) {
  ThingSpeak.setField(1, xt[0]);
  ThingSpeak.setField(2, it[0]);
  ThingSpeak.setField(3, xt[1]);
  ThingSpeak.setField(4, it[1]);
  ThingSpeak.setField(5, xt[2]);
  ThingSpeak.setField(6, it[2]);

  ThingSpeak.setStatus("OK");
  int x = ThingSpeak.writeFields(mych, mykey);
  if (x == 200)
    DPRINTLN("Update OK");
  else
    DPRINTLN("Update error. Code " + String(x));
}
