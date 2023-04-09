#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

class IOperation {
public:
    IOperation(std::vector<std::string>* data_, const bool signal_) : data(data_), ending_signal(signal_) {}

    virtual void ProcessLine() = 0;

    virtual void SetNextOperation(std::shared_ptr<IOperation> object) = 0;

    void HandleEndOfInput();

    std::vector<std::string>* data;
    std::shared_ptr<IOperation> next;
    std::shared_ptr<IOperation> prev;
    bool ending_signal;
};

class CatOperation : public IOperation {
public:
    CatOperation(const std::string& fname, std::vector<std::string>* res, const bool signal_) : IOperation(res, signal_) {
        file.open(fname);
        if (!file.is_open()) {
            std::cerr << "File " << fname << " not found" << std::endl;
        }
    }

    ~CatOperation() {
        file.close();
    }

    void ProcessLine() override;
    void SetNextOperation(std::shared_ptr<IOperation> object) override;

private:
    std::ifstream file;
};

class EchoOperation : public IOperation {
public:
    EchoOperation(const std::string& data_, std::vector<std::string>* res, const bool signal_) : IOperation(res, signal_), string(data_) {}

    void ProcessLine() override;
    void SetNextOperation(std::shared_ptr<IOperation> object) override;

private:
    std::string string;
};

class GrepOperation : public IOperation {
public:
    GrepOperation(const std::string& substr_, std::vector<std::string>* res, const bool signal_) : IOperation(res, signal_), substr(substr_) {}

    void ProcessLine() override;
    void SetNextOperation(std::shared_ptr<IOperation> object) override;

private:
    std::string substr;
};


template<typename T>
class List {
public:
    List() : head(nullptr), tail(nullptr) {}
    ~List() {}

    void push_back(T object);

    bool is_empty() const {
        return tail == nullptr;
    }

private:
    T head;
    T tail;
};

void parsing(List<std::shared_ptr<IOperation>> list, std::vector<std::string>* result, char *argument);
