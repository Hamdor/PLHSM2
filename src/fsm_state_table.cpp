// <-- HEADER
// Die möglichen Zustände
enum states {
  STOPPED,
  RUNNING,
};

// Die möglichen Eingangssignale
enum input {
  START,
  STOP
};

// Ein Eintrag in der Tabelle
struct transition {
  states m_state; // Aktueller Zustand
  input  m_input; // Aktueller Input
  states m_next;  // Nächster Zustand
  void (*m_fn) (void); // Funktionspointer für void name (void)
};

// Context Klasse
class conveyor {
  static void starten();
  static void stoppen();
  // Transitionstabelle
  static transition trans[];
  // aktueller Zustand
  states m_state;
 public:
  void do_action(input in);
  conveyor() : m_state(STOPPED) { }
};

// <-- CPP
#include <iostream>

transition conveyor::trans[] = {
  { STOPPED, START, RUNNING, &conveyor::starten },
  { RUNNING, STOP,  STOPPED, &conveyor::stoppen }
};

#define TRANS_COUNT sizeof(trans) / sizeof(transition)

void conveyor::starten() {
  std::cout << "starten" << std::endl;
}

void conveyor::stoppen() {
  std::cout << "stoppen" << std::endl;
}

void conveyor::do_action(input in) {
  // Über tabelle iterieren und passenden Eintrag wählen
  for (int i = 0; i < TRANS_COUNT; ++i) {
    if (trans[i].m_state == this->m_state &&
        trans[i].m_input == in) {
      // Eintrag gefunden
      trans[i].m_fn(); // funktion aus Tabelle ausführen
      this->m_state = trans[i].m_next; // Zustandswechsel
      return;
    }
  }
  std::cout << "no action" << std::endl;
}

int main() {
  conveyor fsm;
  fsm.do_action(START);
  fsm.do_action(STOP);
  fsm.do_action(STOP); // no action
  return 0;
}
