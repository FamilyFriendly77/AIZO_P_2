#include <string>
template <typename T> class Setting {
private:
  T value;
  std::string label;

public:
  Setting(std::string label) : label(label) {};
  Setting(std::string label, T v) : label(label), value(v) {};
  T getValue() { return value; };
  std::string getLabel() { return label; };
  void setSetting(T v) { value = v; }
};
