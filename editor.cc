#include "editor.h"

using std::string;
using std::vector;

Editor::Editor(int num_rows, int num_cols) :
    num_rows_(num_rows), num_cols_(num_cols),
    mode_(Mode::Command) { }

bool Editor::Input(char ch) {
  switch (mode_) {
  case Mode::Insert:
    switch (ch) {
    case kESC:
      mode_ = Mode::Command;
      break;
    case kBACKSPACE:
      Delete();
      break;
    case kEnter:
      buffer_.NewLine();
      Redraw();
      break;
    default:
      buffer_.Insert(ch);
      Redraw();
      break;
    }
    break;
  case Mode::Command:
    switch (ch) {
    case 'i':
      mode_ = Mode::Insert;
      break;
    case 'h':
      buffer_.Left();
      break;
    case 'j':
      buffer_.Down();
      break;
    case 'k':
      buffer_.Up();
      break;
    case 'l':
      buffer_.Right();
      break;
    case 'q':
      // Signal quit.
      return false;
    }
  }

  UpdateCursor();
  return true;
}

void Editor::Insert(char ch) {
  string& line = buffer_.CurrentLine();
  // ncurses doesn't support insert operations. Need to rewrite line.
  // Get coordinates of start of line
  int text_line, text_pos;
  buffer_.GetCursorPosition(&text_line, &text_pos);
  EditorCoordinates editor_coords(buffer_.Text(), text_line, 0, num_cols_);
  move(editor_coords.line(), editor_coords.pos());

  for (char ch : line) {
    addch(' ');
  }
  // Now go through and set erase the line.

  buffer_.Insert(ch);
  line = buffer_.CurrentLine();
  move(editor_coords.line(), editor_coords.pos());
  for (char ch : line) {
    addch(ch);
  }

  refresh();
}

void Editor::Redraw() {
  vector<string>& text = buffer_.Text();
  for (int i = 0; i < text.size(); i++) {
    EditorCoordinates editor_coords(buffer_.Text(), i, 0, num_cols_);
    move(editor_coords.line(), editor_coords.pos());

    // Clear line
    for (int j = 0; j < num_cols_; j++) {
      addch(' ');
    }

    move(editor_coords.line(), editor_coords.pos());
    for (char ch : text[i]) {
      addch(ch);
    }
  }
  refresh();
}

void Editor::Delete() {
  buffer_.Delete();
  UpdateCursor();
  delch();
  refresh();
}

void Editor::UpdateCursor() {
  int buffer_line, buffer_pos;
  buffer_.GetCursorPosition(&buffer_line, &buffer_pos);
  EditorCoordinates editor_coords(buffer_.Text(), buffer_line, buffer_pos, num_cols_);
  move(editor_coords.line(), editor_coords.pos());
  refresh();
}
