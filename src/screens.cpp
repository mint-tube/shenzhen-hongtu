#include "common.hpp"

void resize_screen() {
  if (ignore_size) return;

  mlog::debug("Entering the resize screen");
  mbox::term term = mbox::term::instance();
  term.clear();



  while (true) {

    mbox::event ev = term.poll_event();
    switch (ev.type) {
      case EventType::KEY:

        break;

      case EventType::RESIZE:
        if (ev.width == WIDTH && ev.height == HEIGHT) return;
        break;

      default:
        continue;
    }
  }
}

void emulator_screen() {

}