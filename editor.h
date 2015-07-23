#ifndef PARSER_H_
#define PARSER_H_

#include <ncurses.h>
#include <vector>
#include <string>
#include "text.h"

class Editor {
public:
  Editor(int num_rows, int num_cols);
  bool Input(char ch);
private:
  void UpdateCursor();
  void Insert(char ch);
  void InsertLine();
  void Delete();
  void Redraw();

  TextBuffer buffer_;
  enum class Mode {Insert, Command} mode_;
  const int num_rows_, num_cols_;
  static const int kEnter = 10;
  static const int kESC = 27;
  static const int kBACKSPACE = 127;
};

class EditorCoordinates {
public:
  EditorCoordinates(std::vector<std::string>& text,
                    int buffer_line, int buffer_pos,
                    int editor_cols): line_(0), pos_(0) {
    for (int i = 0; i <= buffer_line; i++) {
      line_ += 1 + text[i].length() / editor_cols;
    }
    // Adjust to be 0-based.
    line_--;
    pos_ = buffer_pos % editor_cols;
  }
  int line() { return line_; }
  int pos() { return pos_; }
private:
  int line_, pos_;
};

#endif /* PARSER_H_ */
