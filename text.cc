#include "text.h"
#include <iostream>
#include <iterator>
#include <vector>

using std::iterator;
using std::string;
using std::vector;

TextBuffer::TextBuffer(): cursor_line_(0), cursor_pos_(0) {
  line_buffer_.push_back("");
}

void TextBuffer::Insert(char ch) {
  string& line = line_buffer_[cursor_line_];
  line.insert(cursor_pos_, 1, ch);
  cursor_pos_++;
}

void TextBuffer::Delete() {
  string& line = line_buffer_[cursor_line_];
  if (cursor_pos_ > 0) {
    line.erase(cursor_pos_ - 1, 1);
    cursor_pos_--;
  }
}

void TextBuffer::Left() {
  if (cursor_pos_ > 0) {
    cursor_pos_--;
  }
}

void TextBuffer::Up() {
  if (cursor_line_ > 0) {
    cursor_line_--;
  }
}

void TextBuffer::Down() {
  if (cursor_line_ < line_buffer_.size() - 1) {
    cursor_line_++;
  }
}

void TextBuffer::Right() {
  if (cursor_pos_ < line_buffer_[cursor_line_].size()) {
    cursor_pos_++;
  }
}

void TextBuffer::NewLine() {
  vector<string>::iterator it = line_buffer_.begin();
  line_buffer_.insert(it + cursor_line_ + 1, "");
  cursor_line_++;
  cursor_pos_ = 0;
}

void TextBuffer::GetCursorPosition(int* cursor_line, int* cursor_pos) {
    *cursor_line = cursor_line_;
    *cursor_pos = cursor_pos_;
  }

int TextBuffer::GetLineLength(int line_num) {
  if (line_num < 0 || line_num >= line_buffer_.size()) {
    return -1;
  }
  return line_buffer_[line_num].size();
}

bool TextBuffer::IsValidLine(int line_num) {
  return line_num >= 0 && line_num < line_buffer_.size();
}

bool TextBuffer::IsValidPosition(int line_num, int pos) {
  if (!IsValidLine(line_num)) {
    return false;
  }

  return pos >= 0 && pos <= line_buffer_[line_num].size();
}
