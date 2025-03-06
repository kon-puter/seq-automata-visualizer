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



std::vector<StateChange> encode_seq(const std::string &seq, state zero_id,
                                    state one_id, int start, bool prefix = false) {
  int state_num = seq.length();
  std::vector<StateChange> edges;
  bool first_val = digit_to_logical_val(seq[0]);
  for (int i = 0; i < state_num; i++) {
    bool val = digit_to_logical_val(seq[i]);
    if (!prefix  || i != state_num - 1) {
      edges.push_back(
          {i, (i + 1 + start), val, (i == state_num -1 ? true : false)});
    }
    edges.push_back({i, (first_val == !val) ? one_id : zero_id, !val, 0});
  }
  return edges;
}

std::string get_prefix(const std::string &a, const std::string &b) {
  size_t prefix_size = 0;
  while (a[prefix_size] == b[prefix_size]) {
    prefix_size++;
  }

  return a.substr(0, prefix_size);
}

int main(int argc, char **argv) {
  using namespace std;
  string seq1, seq2;
  cin >> seq1 >> seq2;

  string prefix = get_prefix(seq1, seq2);

  auto transitions = encode_seq(prefix, 0, 1, 0, true);
  state branch_state = prefix.length() - 1;
  auto u1_transitions =
      encode_seq(seq1.substr(prefix.length() - 1), 0, 1, prefix.length() - 1);
  auto u2_transitions =
      encode_seq(seq2.substr(prefix.length() - 1), 0, 1, seq1.length() - 1);
  transitions.insert(transitions.end(), u1_transitions.begin(),
                     u1_transitions.end());
  transitions.insert(transitions.end(), u2_transitions.begin(),
                     u2_transitions.end());
  // print_table(edges);
  gen_uml(transitions);
  return 0;
}
