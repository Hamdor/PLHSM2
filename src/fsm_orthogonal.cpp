// <-- HEADER
#include <iostream>
#include <vector>

class state {
 public:
  virtual ~state() { }
  virtual void height() { std::cout << "super::height()" << std::endl; }
  virtual void del() { std::cout << "super::del()" << std::endl; }
};

class einlauf : public state {
 public:
  void height();
};

class messung : public state {
  void del();
};

class token { // Kontext Klasse
  state* m_state;
 public:
  token() : m_state(new einlauf) { }
  ~token() { delete m_state; }
  void entry();
  void height();
  void del();
};

class token_summary {
  std::vector<token*> m_tokens;
 public:
  void entry();
  void height();
  void del();
};

// <-- CPP

void token::height() {
  m_state->height();
}

void token::del() {
  m_state->del();
}

void einlauf::height() {
  new (this) messung;
  std::cout << "Token in höhenmessung" << std::endl;
}

void messung::del() {
  std::cout << "Token verlässt Band" << std::endl;
}

void token_summary::entry() {
  m_tokens.push_back(new token());
  std::cout << "Neuer Token auf Band" << std::endl;
}

void token_summary::height() {
  for(size_t i = 0; i < m_tokens.size(); ++i) {
    m_tokens[i]->height();
  }
}

void token_summary::del() {
  for(size_t i = 0; i < m_tokens.size(); ++i) {
    m_tokens[i]->del();
  }
  token* ptr = m_tokens.front();
  m_tokens.erase(m_tokens.begin());
  delete ptr;
}

int main() {
  token_summary sum;
  sum.entry();  // erste token
  sum.height(); // token wandert in die höhenmessung
  sum.entry();  // zweite token
  sum.del();    // erste token verlässt band
  sum.height(); // zweite token in höhenmessung
  sum.del();    // zweite token verlässt band
}
