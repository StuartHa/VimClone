#ifndef TEXT_H_
#define TEXT_H_

#include <vector>
#include <string>

class TextBuffer {
public:
  TextBuffer();
  void Insert(char ch);
  void Delete();
  void Left();
  void Up();
  void Down();
  void Right();
  void NewLine();

  void GetCursorPosition(int* cursor_line, int* cursor_pos);
  std::vector<std::string>& Text() { return line_buffer_; }
  std::string& CurrentLine() { return line_buffer_[cursor_line_]; }
  int GetLineLength(int line_num);
private:
  bool IsValidLine(int line_num);
  bool IsValidPosition(int line_num, int pos);

  std::vector<std::string> line_buffer_;
  int cursor_line_, cursor_pos_;
};

#endif /* TEXT_H_ */
