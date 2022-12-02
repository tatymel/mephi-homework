#include "task.h"
#include "logged_command_wrapper.h"

/* Курсор влево */
class MoveCursorLeftCommand : public ICommand {
public:
    MoveCursorLeftCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(cursorPosition != 0)
            --cursorPosition;
        if(buffer[cursorPosition] == '\n')
            --cursorPosition;
        if(editor.HasSelection())
            editor.UnselectText();
    }

    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveCursorLeftCommand(*this);
    }
};

/* Курсор вправо */
class MoveCursorRightCommand : public ICommand {
public:
    MoveCursorRightCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(cursorPosition < buffer.size() - 1)
            ++cursorPosition;
        if(buffer[cursorPosition] == '\n')
            ++cursorPosition;
        if(editor.HasSelection())
            editor.UnselectText();
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveCursorRightCommand(*this);
    }
};

/* Курсор вверх */
class MoveCursorUpCommand : public ICommand {
public:
    MoveCursorUpCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        /*if(cursorPosition == buffer.size()){
            cursorPosition = 0;
        }else {
            int kol_n = 0;
            size_t kol_elem = 0;
            if(buffer[cursorPosition] == '\n')
                --kol_n;
            while (kol_n < 2 && cursorPosition > 0) {
                if (buffer[cursorPosition] == '\n')
                    ++kol_n;
                if (kol_n == 0)
                    ++kol_elem;
                --cursorPosition;
            }
            if(kol_n == 0){
                cursorPosition += kol_elem;
            }else {
                if (kol_n == 2) {
                    cursorPosition += 2;
                }
                if (kol_elem != 0)
                    cursorPosition += kol_elem - 1;
            }
        }*/
        if(buffer[cursorPosition] == '\n' && cursorPosition > 0)
            --cursorPosition;

        size_t n1 = buffer.rfind('\n', cursorPosition);
        size_t n2 = n1;
        if(n1 != std::string::npos)
            n2 = buffer.rfind('\n', n1-1);
        if(n2 == std::string::npos && n1 != n2)
            cursorPosition -= (n1 + 1);
        else if(n2 != std::string::npos)
            cursorPosition = n2 + (cursorPosition - n1) + 1;

        if (editor.HasSelection())
            editor.UnselectText();
    }

    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveCursorUpCommand(*this);
    }
};

/* Курсор вниз */
class MoveCursorDownCommand : public ICommand {
public:
    MoveCursorDownCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        size_t n = buffer.find('\n', cursorPosition);

        if(n != std::string::npos){
            cursorPosition += n + 1;
        }

        if(cursorPosition > buffer.size())
            cursorPosition = buffer.size() - 1;

        if (editor.HasSelection())
            editor.UnselectText();
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveCursorDownCommand(*this);
    }
};

/* Выделить текст */
class SelectTextCommand : public ICommand {
public:
    SelectTextCommand(size_t selectionSize) : selectionSize_(selectionSize) {};

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        editor.SelectText(cursorPosition, cursorPosition + selectionSize_);
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitSelectCommand(*this);
    }
private:
    size_t selectionSize_;
};


/* Ввести текст */
class InsertTextCommand : public ICommand {
public:
    InsertTextCommand(std::string text) : insertText_(std::move(text)){};

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(editor.HasSelection()){
            std::pair<size_t, size_t> pa = editor.GetSelection();
            buffer.erase(pa.first, pa.second);
            buffer.insert(pa.first, insertText_);
            editor.UnselectText();
        }else{
            buffer = buffer.substr(0, cursorPosition) + insertText_ + buffer.substr(cursorPosition, buffer.size() - cursorPosition);
            cursorPosition += insertText_.size();
        }

    }

    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitInsertTextCommand(*this);
    }

private:
    std::string insertText_;
};

/* Удалить текст */
class DeleteTextCommand : public ICommand {
public:
    DeleteTextCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if(!clipboard.empty()){
            size_t n = buffer.find(clipboard);
            if(n != std::string::npos)
                buffer.erase(n, clipboard.size());
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitDeleteTextCommand(*this);
    }
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

    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitCopyTextCommand(*this);
    }

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
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitPasteTextCommand(*this);
    }
};

/* Привести выделенный текст в ВЕРХНИЙ регистр */
class UppercaseTextCommand : public ICommand {
public:
    UppercaseTextCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if(editor.HasSelection()){
            std::pair<size_t, size_t> pa = editor.GetSelection();
            for(size_t i = pa.first; i < pa.second; ++i){
                if(buffer[i] > 96 && buffer[i] < 123)
                    buffer[i] -= 32;
            }
        }
        editor.UnselectText();
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitUppercaseTextCommand(*this);
    }
};

/* Привести выделенный текст в нижний регистр */
class LowercaseTextCommand : public ICommand {
public:
    LowercaseTextCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if(editor.HasSelection()){
            std::pair<size_t, size_t> pa = editor.GetSelection();
            for(size_t i = pa.first; i < pa.second; ++i){
                if(buffer[i] > 64 && buffer[i] < 91)
                    buffer[i] += 32;
            }
            editor.UnselectText();
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitLowercaseTextCommand(*this);
    }
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

    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveToEndCommand(*this);
    }
};

/* Перенести курсор в начало строки */
class MoveToStartCommand : public ICommand {
public:
    MoveToStartCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if(buffer[cursorPosition] == '\n' && cursorPosition > 0)
            --cursorPosition;
        while(buffer[cursorPosition] != '\n' && cursorPosition > 0)
            --cursorPosition;
        if(buffer[cursorPosition] == '\n')
            ++cursorPosition;
        if(editor.HasSelection())
            editor.UnselectText();
    }

    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveToStartCommand(*this);
    }
};

/* Удалить часть строки, начиная от позиции курсора до первого пробела или конца строки */
class DeleteWordCommand : public ICommand {
public:
    DeleteWordCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        size_t end = cursorPosition;
        while(buffer[end] != ' ' && buffer[end] != '\n'){
            ++end;
        }
        --end;
        buffer.erase(cursorPosition, end - cursorPosition + 1);
    }

    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitDeleteWordCommand(*this);
    }
};

/* Макрос */
class MacroCommand : public ICommand {
public:
    MacroCommand(std::list<CommandPtr> subcommands) : subcommands_(std::move(subcommands)){};

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        for (const CommandPtr &commandPtr: subcommands_)
            commandPtr->Apply(buffer, cursorPosition, clipboard, editor);

    }

    void AcceptVisitor(CommandVisitor& visitor) override{
        for (const CommandPtr &commandPtr: subcommands_)
            commandPtr->AcceptVisitor(visitor);
    }

private:
    std::list<CommandPtr> subcommands_;
};

CommandBuilder::CommandBuilder() = default;

CommandBuilder& CommandBuilder::WithType(Type type){
    type_ = type;
    logStreamPtr_ = nullptr;
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

CommandBuilder& CommandBuilder::AddSubcommand(CommandPtr subcommand){
    subcommands_.emplace_back(std::move(subcommand));
    return *this;
}

CommandBuilder& CommandBuilder::LogTo(std::ostream& logStream){
    logStreamPtr_ = &logStream;
    return *this;
}

////CommandLoggerVisitor
CommandLoggerVisitor::CommandLoggerVisitor(std::ostream &logStream) : logStream_(logStream){};

void CommandLoggerVisitor::VisitInsertTextCommand(InsertTextCommand& command){
    logStream_ << "i";
}

void CommandLoggerVisitor::VisitMoveCursorUpCommand(MoveCursorUpCommand &command) {
    logStream_ << "k";
}

void CommandLoggerVisitor::VisitMoveToStartCommand(MoveToStartCommand &command) {
    logStream_ << "0";
}

void CommandLoggerVisitor::VisitMoveCursorDownCommand(MoveCursorDownCommand &command) {
    logStream_ << "j";
}

void CommandLoggerVisitor::VisitMoveToEndCommand(MoveToEndCommand &command) {
    logStream_ << "$";
}

void CommandLoggerVisitor::VisitSelectCommand(SelectTextCommand &command) {
    logStream_ << "v";
}

void CommandLoggerVisitor::VisitCopyTextCommand(CopyTextCommand &command) {
    logStream_ << "y";
}

void CommandLoggerVisitor::VisitDeleteWordCommand(DeleteWordCommand &command) {
    logStream_ << "dE";
}

void CommandLoggerVisitor::VisitPasteTextCommand(PasteTextCommand &command) {
    logStream_ << "p";
}

void CommandLoggerVisitor::VisitMoveCursorLeftCommand(MoveCursorLeftCommand &command) {
    logStream_ << "h";
}

void CommandLoggerVisitor::VisitMoveCursorRightCommand(MoveCursorRightCommand &command) {
    logStream_ << "l";
}

void CommandLoggerVisitor::VisitDeleteTextCommand(DeleteTextCommand &command) {
    logStream_ << "d";
}

void CommandLoggerVisitor::VisitUppercaseTextCommand(UppercaseTextCommand &command) {
    logStream_ << "U";
}

void CommandLoggerVisitor::VisitLowercaseTextCommand(LowercaseTextCommand &command) {
    logStream_ << "u";
}


CommandPtr CommandBuilder::build() {
    CommandPtr new_command;
    //CommandLoggerVisitor commandLoggerVisitor(*logStreamPtr_);
    switch(type_){
        case CommandBuilder::Type::InsertText :
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_, std::make_shared<InsertTextCommand>(InsertTextCommand(text_))));
            new_command = std::make_shared<InsertTextCommand>(InsertTextCommand(text_));
            break;
        case CommandBuilder::Type::MoveCursorLeft :
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_, std::make_shared<MoveCursorLeftCommand>(MoveCursorLeftCommand())));
            new_command = std::make_shared<MoveCursorLeftCommand>(MoveCursorLeftCommand());
            //return new_command;
            break;
        case Type::MoveCursorRight:
            new_command = std::make_shared<MoveCursorRightCommand>(MoveCursorRightCommand());
            break;
        case Type::MoveCursorUp:
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_, std::make_shared<MoveCursorUpCommand>(MoveCursorUpCommand())));
            new_command = std::make_shared<MoveCursorUpCommand>(MoveCursorUpCommand());
            //return new_command;
            break;
        case Type::MoveCursorDown:
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_,std::make_shared<MoveCursorDownCommand>(MoveCursorDownCommand())));
            new_command = std::make_shared<MoveCursorDownCommand>(MoveCursorDownCommand());
            break;
        case Type::SelectText:
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_,std::make_shared<SelectTextCommand>(SelectTextCommand(selectionSize_))));

            new_command = std::make_shared<SelectTextCommand>(SelectTextCommand(selectionSize_));
            //return new_command;
            break;
        case Type::DeleteText:
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_,std::make_shared<DeleteTextCommand>(DeleteTextCommand())));
            //return loggedCommandWrapper;
            new_command = std::make_shared<DeleteTextCommand>(DeleteTextCommand());
            break;
        case Type::CopyText:
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_,std::make_shared<CopyTextCommand>(CopyTextCommand())));
            new_command = std::make_shared<CopyTextCommand>(CopyTextCommand());
            //return new_command;
            break;
        case Type::PasteText:
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_,std::make_shared<PasteTextCommand>(PasteTextCommand())));
            new_command = std::make_shared<PasteTextCommand>(PasteTextCommand());
            //return new_command;
            break;
        case Type::UppercaseText:
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_,std::make_shared<UppercaseTextCommand>(UppercaseTextCommand())));
            //return loggedCommandWrapper;
            new_command = std::make_shared<UppercaseTextCommand>(UppercaseTextCommand());
            break;
        case Type::LowercaseText:
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_,std::make_shared<LowercaseTextCommand>(LowercaseTextCommand())));
            //return loggedCommandWrapper;
            new_command = std::make_shared<LowercaseTextCommand>(LowercaseTextCommand());
            break;
        case Type::MoveToEnd:
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_,std::make_shared<MoveToEndCommand>(MoveToEndCommand())));
            new_command = std::make_shared<MoveToEndCommand>(MoveToEndCommand());
            //return new_command;
            break;
        case Type::MoveToStart:
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_,std::make_shared<MoveToStartCommand>(MoveToStartCommand())));
            new_command = std::make_shared<MoveToStartCommand>(MoveToStartCommand());
            //return new_command;
            break;
        case Type::DeleteWord:
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_,std::make_shared<DeleteWordCommand>(DeleteWordCommand())));
            new_command = std::make_shared<DeleteWordCommand>(DeleteWordCommand());
            //return new_command;
            break;
        case Type::Macro:
            //loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_,std::make_shared<MacroCommand>(MacroCommand(subcommands_))));
            new_command = std::make_shared<MacroCommand>(MacroCommand(subcommands_));
            //return new_command;
            break;
    }

    if(logStreamPtr_ != nullptr) {
        CommandPtr loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(
                LoggedCommandWrapper(*logStreamPtr_, new_command));
        return loggedCommandWrapper;
    }else{
        return new_command;
    }
    /*if(logStreamPtr_ != nullptr) {
        CommandPtr loggedCommandWrapper = std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*logStreamPtr_, new_command));
        return loggedCommandWrapper;
    }else {
        return new_command;*/
}

