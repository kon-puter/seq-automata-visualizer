#include <algorithm>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

typedef int state;

std::string int_to_bin_str(int a) {
  std::ostringstream out;
  size_t count = 0;
  while (a > 0) {
    out << (a & 1);
    a >>= 1;
    count++;
  }

  if (count == 0) {
    out << '0';
  }

  std::string bin_a = out.str();
  std::reverse(bin_a.begin(), bin_a.end());
  return bin_a;
}
struct StateChange {
  state from;
  state to;
  bool in;
  bool out;

  void print(const std::string_view sep, std::ostream &o = std::cout) const {
    o << int_to_bin_str(from) << sep << in << sep << int_to_bin_str(to) << sep
      << out << '\n';
  }
};

bool digit_to_logical_val(const char digit) {
  if (digit != '1' && digit != '0') {
    // TODO: handle bad input here
  }
  bool val = digit == '1';
  return val;
}

void print_table(const std::vector<StateChange> &edges,
                 std::ostream &out = std::cout) {
  for (const auto &e : edges) {
    e.print(";", out);
  }
  out.flush();
}

void gen_uml(const std::vector<StateChange> &edges,
             std::ostream &out = std::cout) {
  out << "@startuml\n"
         "hide empty description"
         "\n"
         "[*] --> State0\n";

  for (const auto &e : edges) {
    out << "State" << e.from << " --> " << "State" << e.to << " : " << e.in
        << "/" << e.out << '\n';
  }

  out << "@enduml\n";
  out.flush();
}

int main(int argc, char **argv) {
  using namespace std;
  string seq;
  cin >> seq;

  int state_num = seq.length();
  bool first_val = digit_to_logical_val(seq[0]);
  vector<StateChange> edges(state_num * 2);
  size_t edge_count = 0;
  for (int i = 0; i < state_num; i++) {
    bool val = digit_to_logical_val(seq[i]);
    edges[edge_count] = {i, (i + 1) % state_num, val,
                         (i == state_num - 1 ? true : false)};
    edge_count++;
    edges[edge_count] = {i, (first_val == !val) ? 1 : 0, !val, 0};
    edge_count++;
  }

  // print_table(edges);
  gen_uml(edges);
  return 0;
}
