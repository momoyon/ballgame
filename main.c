#include <config.h>
#define ENGINE_IMPLEMENTATION
#include <engine.h>

#define COMMONLIB_REMOVE_PREFIX
#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>

int main() {

  log_info("WINDOW SIZE: %dx%d", g_width, g_height);

  return 0;
}
