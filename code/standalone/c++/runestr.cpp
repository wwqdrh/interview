#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

class Rune {
private:
  char32_t value; // 存储 Unicode 码点
  uint8_t bytes;  // UTF-8 编码的字节数

public:
  // 从 UTF-8 字符串构造 Rune
  explicit Rune(std::string_view utf8_char) {
    if (utf8_char.empty()) {
      throw std::invalid_argument("Empty string");
    }

    uint8_t first_byte = static_cast<uint8_t>(utf8_char[0]);
    if ((first_byte & 0x80) == 0) {
      // ASCII
      value = first_byte;
      bytes = 1;
    } else if ((first_byte & 0xE0) == 0xC0) {
      // 2 bytes
      if (utf8_char.length() < 2)
        throw std::invalid_argument("Incomplete UTF-8 sequence");
      value = ((first_byte & 0x1F) << 6) |
              (static_cast<uint8_t>(utf8_char[1]) & 0x3F);
      bytes = 2;
    } else if ((first_byte & 0xF0) == 0xE0) {
      // 3 bytes
      if (utf8_char.length() < 3)
        throw std::invalid_argument("Incomplete UTF-8 sequence");
      value = ((first_byte & 0x0F) << 12) |
              ((static_cast<uint8_t>(utf8_char[1]) & 0x3F) << 6) |
              (static_cast<uint8_t>(utf8_char[2]) & 0x3F);
      bytes = 3;
    } else if ((first_byte & 0xF8) == 0xF0) {
      // 4 bytes
      if (utf8_char.length() < 4)
        throw std::invalid_argument("Incomplete UTF-8 sequence");
      value = ((first_byte & 0x07) << 18) |
              ((static_cast<uint8_t>(utf8_char[1]) & 0x3F) << 12) |
              ((static_cast<uint8_t>(utf8_char[2]) & 0x3F) << 6) |
              (static_cast<uint8_t>(utf8_char[3]) & 0x3F);
      bytes = 4;
    } else {
      throw std::invalid_argument("Invalid UTF-8 sequence");
    }
  }

  // 获取 Unicode 码点值
  char32_t code_point() const { return value; }

  // 获取 UTF-8 编码的字节数
  uint8_t size() const { return bytes; }

  // 转换回 UTF-8 字符串
  std::string to_string() const {
    std::string result;
    if (value <= 0x7F) {
      result.push_back(static_cast<char>(value));
    } else if (value <= 0x7FF) {
      result.push_back(static_cast<char>(0xC0 | (value >> 6)));
      result.push_back(static_cast<char>(0x80 | (value & 0x3F)));
    } else if (value <= 0xFFFF) {
      result.push_back(static_cast<char>(0xE0 | (value >> 12)));
      result.push_back(static_cast<char>(0x80 | ((value >> 6) & 0x3F)));
      result.push_back(static_cast<char>(0x80 | (value & 0x3F)));
    } else {
      result.push_back(static_cast<char>(0xF0 | (value >> 18)));
      result.push_back(static_cast<char>(0x80 | ((value >> 12) & 0x3F)));
      result.push_back(static_cast<char>(0x80 | ((value >> 6) & 0x3F)));
      result.push_back(static_cast<char>(0x80 | (value & 0x3F)));
    }
    return result;
  }

  // 比较运算符
  bool operator==(const Rune &other) const { return value == other.value; }
  bool operator!=(const Rune &other) const { return value != other.value; }
  bool operator<(const Rune &other) const { return value < other.value; }
};

// 工具函数：将 UTF-8 字符串转换为 Rune 数组
class RuneString {
public:
  static std::vector<Rune> from_string(const std::string &str) {
    std::vector<Rune> runes;
    size_t pos = 0;

    while (pos < str.length()) {
      size_t char_len = get_utf8_char_length(str[pos]);
      if (pos + char_len > str.length())
        break;

      runes.emplace_back(std::string_view(str.data() + pos, char_len));
      pos += char_len;
    }

    return runes;
  }

  // 获取一个字符的 UTF-8 编码长度
  static size_t get_utf8_char_length(char first_byte) {
    uint8_t byte = static_cast<uint8_t>(first_byte);
    if ((byte & 0x80) == 0)
      return 1;
    if ((byte & 0xE0) == 0xC0)
      return 2;
    if ((byte & 0xF0) == 0xE0)
      return 3;
    if ((byte & 0xF8) == 0xF0)
      return 4;
    return 1; // 处理无效的 UTF-8 字符
  }

  // 将 Rune 数组转换回字符串
  static std::string to_string(const std::vector<Rune> &runes) {
    std::string result;
    for (const auto &rune : runes) {
      result += rune.to_string();
    }
    return result;
  }
};

int main() {
  try {
    // 创建单个 Rune
    Rune chinese_char("你");
    std::cout << "码点值: " << chinese_char.code_point() << std::endl;
    std::cout << "UTF-8字节数: " << static_cast<int>(chinese_char.size())
              << std::endl;

    // 处理整个字符串
    std::string text = "你好，世界！";
    auto runes = RuneString::from_string(text);

    // 遍历每个字符
    for (const auto &rune : runes) {
      std::cout << "字符: " << rune.to_string()
                << " 码点: " << rune.code_point()
                << " 字节数: " << static_cast<int>(rune.size()) << std::endl;
    }

    // 修改字符串
    runes[1] = Rune("嗨"); // 将"好"替换为"嗨"
    std::string modified = RuneString::to_string(runes);
    std::cout << "修改后: " << modified << std::endl;

  } catch (const std::exception &e) {
    std::cerr << "错误: " << e.what() << std::endl;
  }

  return 0;
}