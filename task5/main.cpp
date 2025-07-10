#include <format>
#include <iostream>
#include <string>

struct MyStruct {
  int id;
  std::string name;
  double score;
};

namespace std {
template <> struct formatter<MyStruct> {
  int precision = 2;
  bool no_id = false;

  constexpr auto parse(format_parse_context &ctx) {
    auto it = ctx.begin();
    auto end = ctx.end();

    int val = 0;
    bool found = false;
    if (*it == 'n') {
      ++it;
      no_id = true;
    }
    while (it != end && *it >= '0' && *it <= '9') {
      found = true;
      val = val * 10 + (*it - '0');
      ++it;
    }
    if (*it == 'n') {
      ++it;
      no_id = true;
    }
    if (found) {
      precision = val;
    }

    return it;
  }

  template <typename FormatContext>
  auto format(const MyStruct &ms, FormatContext &ctx) const {
    auto score_str = std::format("{:.{}f}", ms.score, precision);
    if (no_id) {
      return std::format_to(ctx.out(), "Name: {}, Score: {}", ms.name,
                            score_str);
    }
    return std::format_to(ctx.out(), "ID: {}, Name: {}, Score: {}", ms.id,
                          ms.name, score_str);
  }
};
} // namespace std

int main() {
  MyStruct obj{42, "Bob", 95.56789};

  std::cout << std::format("{}", obj) << '\n';
  std::cout << std::format("{:0}", obj) << '\n';
  std::cout << std::format("{:4}", obj) << '\n';
  std::cout << std::format("{:n}", obj) << '\n';
  std::cout << std::format("{:0n}", obj) << '\n';
  std::cout << std::format("{:n0}", obj) << '\n';
  std::cout << std::format("{:3n}", obj) << '\n';
}
