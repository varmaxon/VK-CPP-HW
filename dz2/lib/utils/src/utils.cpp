#include "utils.hpp"

void IOperation::HandleEndOfInput() {
    if (ending_signal) {
        for (size_t i = 0; i < data->size(); ++i) {
            std::cout << data->at(i) << std::endl;
        }
    }
}

void CatOperation::ProcessLine() {
    file.seekg(0);
    std::string line, text;
    while (std::getline(file, line)) {
        text += line;
    }
    data->push_back(text);
}

void CatOperation::SetNextOperation(std::shared_ptr<IOperation> object) {
    data = object->data;
    ProcessLine();
    HandleEndOfInput();
}

void EchoOperation::ProcessLine() {
    data->clear();
    data->push_back(string);
}

void EchoOperation::SetNextOperation(std::shared_ptr<IOperation> object) {
    data = object->data;
    ProcessLine();
    HandleEndOfInput();
}

void GrepOperation::ProcessLine() {
    std::vector<std::string> tmp_data = *data;
    data->clear();
    for (size_t i = 0; i < tmp_data.size(); ++i) {
        if (tmp_data.at(i).find(substr) != std::string::npos) {
            data->push_back(tmp_data.at(i));
        }
    }
}

void GrepOperation::SetNextOperation(std::shared_ptr<IOperation> object) {
    data = object->data;
    ProcessLine();
    HandleEndOfInput();
}

template<typename T>
void List<T>::push_back(T object) {
    if (is_empty()) {
        head = object;
        tail = object;
        tail->SetNextOperation(tail);
        return;
    }
    object->prev = tail;
    tail->next = object;
    tail = object;
    
    tail->SetNextOperation(tail->prev);
}

void parsing(List<std::shared_ptr<IOperation>> list, std::shared_ptr<std::vector<std::string>> result, std::string argument) {
    std::string str = "", operation;
    std::string commands(argument);
    commands += " ";
    bool flag = true, ending_signal = false;
    unsigned int index = 0;

    while (index < commands.size()) {
        if (commands.at(index) != '|' && index != commands.size() - 1) {
            if (flag && commands.at(index) == ' ') {
                operation = str;
                flag = false;
                str = "";
            }
            else if (commands.at(index) != ' ') {
                str += commands.at(index);
            }
        }
        else {
            if (index == commands.size() - 1) {
                ending_signal = true;
            }

            std::shared_ptr<IOperation> ptr;
            if (operation == "cat") {
                ptr = std::make_shared<CatOperation>(str, result, ending_signal);
            }
            else if (operation == "echo") {
                ptr = std::make_shared<EchoOperation>(str, result, ending_signal);
            }
            else if (operation == "grep") {
                ptr = std::make_shared<GrepOperation>(str, result, ending_signal);
            }
            else {
                std::cerr << "Not found operation" << std::endl;
                return;
            }

            list.push_back(ptr);

            str = "";
            operation = "";
            flag = true;
            index++;
        }
        index++;
    }
}
