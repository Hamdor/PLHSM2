// <-- HEADER
// Die möglichen Zustände
enum states {
  NO_CHANGE = -1,
  STOPPED,  // 0
  RUNNING,  // 1
};

// Die möglichen Eingangssignale
enum input {
  START, // 0
  STOP   // 1
};

// Ein Eintrag in der Tabelle
struct transition {
  states m_next;  // Nächster Zustand
  void (*m_fn) (void); // Funktionspointer für void name (void)
};

// Context Klasse
class conveyor {
  static void starten();
  static void stoppen();
  static void empty_func(); // Für leere Einträge in der Matrix
  // Transitionstabelle
  static transition trans[][2];
  // aktueller Zustand
  states m_state;
 public:
  void do_action(input in);
  conveyor() : m_state(STOPPED) { }
};

// <-- CPP
#include <iostream>

#define EMPTY_TRANS { NO_CHANGE, &conveyor::empty_func }

// Zugriff [Aktueller Zustand][Input]
transition conveyor::trans[][2] = {
  //-------------------------------+----------------------------------+-------+
  //          start                |           stop                   |Zustand|
  //------------------------------------------------------------------+-------+
  { { RUNNING, &conveyor::starten }, EMPTY_TRANS },                 //|stopped|
  { EMPTY_TRANS,                   { STOPPED, &conveyor::stoppen } }//|running|
  //------------------------------------------------------------------+-------+
};

#define TRANS_COUNT sizeof(trans) / sizeof(transition)

void conveyor::starten() {
  std::cout << "starten" << std::endl;
}

void conveyor::stoppen() {
  std::cout << "stoppen" << std::endl;
}

void conveyor::empty_func() {
  // Hier könnte eine Fehlerreaktion erfolgen
  std::cout << "no action" << std::endl;
}

void conveyor::do_action(input in) {
  int dim1 = static_cast<int>(this->m_state);
  int dim2 = static_cast<int>(in);
  trans[dim1][dim2].m_fn(); // funktion ausführen
  if (trans[dim1][dim2].m_next != NO_CHANGE) {
    // Übergang wird nur ausgeführt, wenn nächster Zustand
    this->m_state = trans[dim1][dim2].m_next;
  }
}

int main() {
  conveyor fsm;
  fsm.do_action(START);
  fsm.do_action(STOP);
  fsm.do_action(STOP); // no action
  return 0;
}
