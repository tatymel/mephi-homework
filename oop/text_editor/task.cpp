#include "task.h"
#include "logged_command_wrapper.h"

/* Курсор влево */
class MoveCursorLeftCommand : public ICommand {
public:
    MoveCursorLeftCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(buffer[cursorPosition - 1] != '\n')
            --cursorPosition;
        else
            cursorPosition -= 2;

        if(editor.HasSelection())
            editor.UnselectText();
    }

    void AcceptVisitor(CommandVisitor& visitor) override{}
};

/* Курсор вправо */
class MoveCursorRightCommand : public ICommand {
};

/* Курсор вверх */
class MoveCursorUpCommand : public ICommand {
public:
    MoveCursorUpCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        int kol_n = 0;
        size_t kol_elem = 0;
        while(kol_n < 2 && cursorPosition > 0){
            if(buffer[cursorPosition] == '\n')
                ++kol_n;
            if(kol_n == 0)
                ++kol_elem;
            --cursorPosition;
        }
        if(cursorPosition != 0){
            cursorPosition += kol_elem;
        }

        if(editor.HasSelection())
            editor.UnselectText();
    }

    void AcceptVisitor(CommandVisitor& visitor) override{}
};

/* Курсор вниз */
class MoveCursorDownCommand : public ICommand {
};

/* Выделить текст */
class SelectTextCommand : public ICommand {
public:
    SelectTextCommand(size_t selectionSize) : selectionSize_(std::move(selectionSize)) {};

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        editor.SelectText(cursorPosition, selectionSize_);
    }
    void AcceptVisitor(CommandVisitor& visitor) override{}
private:
    size_t selectionSize_;
};

/* Ввести текст */
class InsertTextCommand : public ICommand {
public:
    InsertTextCommand(std::string text) : insertText_(std::move(text)){};

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(editor.HasSelection()){

        }else{
            buffer = buffer.substr(0, cursorPosition) + insertText_ + buffer.substr(cursorPosition, buffer.size() - cursorPosition);
            cursorPosition += insertText_.size();
        }

    }

    void AcceptVisitor(CommandVisitor& visitor) override{}

private:
    std::string insertText_;
};

/* Удалить текст */
class DeleteTextCommand : public ICommand {
public:
    void Apply(){}
};

/* Скопировать текст */
class CopyTextCommand : public ICommand {
public:
    CopyTextCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        std::pair<size_t, size_t> pa = editor.GetSelection();
        clipboard = buffer.substr(pa.first, pa.second - pa.first);

        if(editor.HasSelection())
            editor.UnselectText();
    }

    void AcceptVisitor(CommandVisitor& visitor) override{}

};

/* Вставить скопированный текст */
class PasteTextCommand : public ICommand {
public:
    PasteTextCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if(editor.HasSelection()){
            std::pair<size_t, size_t> pa = editor.GetSelection();
            buffer = buffer.substr(0, pa.first) + clipboard + buffer.substr(pa.second, buffer.size());
            editor.UnselectText();
        }else{
            buffer = buffer.substr(0, cursorPosition) + clipboard + buffer.substr(cursorPosition, buffer.size() - cursorPosition);
            cursorPosition += clipboard.size();
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override{}
};

/* Привести выделенный текст в ВЕРХНИЙ регистр */
class UppercaseTextCommand : public ICommand {
};

/* Привести выделенный текст в нижний регистр */
class LowercaseTextCommand : public ICommand {
};

/* Перенести курсор в конец строки */
class MoveToEndCommand : public ICommand {
public:
    MoveToEndCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        size_t buf_size = buffer.size();
        while(buffer[cursorPosition] != '\n' && cursorPosition < buf_size)
            ++cursorPosition;

        if(editor.HasSelection())
            editor.UnselectText();
    }

    void AcceptVisitor(CommandVisitor& visitor) override{}
};

/* Перенести курсор в начало строки */
class MoveToStartCommand : public ICommand {
};

/* Удалить часть строки, начиная от позиции курсора до первого пробела или конца строки */
class DeleteWordCommand : public ICommand {
};

/* Макрос */
class MacroCommand : public ICommand {
};

CommandBuilder::CommandBuilder() = default;

CommandBuilder& CommandBuilder::WithType(Type type){
    type_ = type;
    return *this;
}

CommandBuilder& CommandBuilder::Text(std::string text){
    text_ = std::move(text);
    return *this;
}
CommandBuilder& CommandBuilder::SelectionSize(size_t selectionSize){
    selectionSize_ = selectionSize;
    return *this;
}
CommandPtr CommandBuilder::build() {
    CommandPtr new_command;
    switch(type_){
        case CommandBuilder::Type::InsertText :
            new_command = std::make_shared<InsertTextCommand>(InsertTextCommand(text_));
            return new_command;
        case CommandBuilder::Type::MoveCursorLeft :
            new_command = std::make_shared<MoveCursorLeftCommand>(MoveCursorLeftCommand());
            return new_command;
        case Type::MoveCursorRight:
            break;
        case Type::MoveCursorUp:
            new_command = std::make_shared<MoveCursorUpCommand>(MoveCursorUpCommand());
            return new_command;
        case Type::MoveCursorDown:
            break;
        case Type::SelectText:
            new_command = std::make_shared<SelectTextCommand>(SelectTextCommand(selectionSize_));
            return new_command;
        case Type::DeleteText:
            break;
        case Type::CopyText:
            new_command = std::make_shared<CopyTextCommand>(CopyTextCommand());
            return new_command;
        case Type::PasteText:
            new_command = std::make_shared<PasteTextCommand>(PasteTextCommand());
            return new_command;
        case Type::UppercaseText:
            break;
        case Type::LowercaseText:
            break;
        case Type::MoveToEnd:
            new_command = std::make_shared<MoveToEndCommand>(MoveToEndCommand());
            return new_command;
        case Type::MoveToStart:
            break;
        case Type::DeleteWord:
            break;
        case Type::Macro:
            break;
    }

}

