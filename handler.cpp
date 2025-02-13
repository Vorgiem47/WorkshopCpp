#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

class ResourceHandler {
public:
    virtual ~ResourceHandler() = default;
    virtual bool open(const std::string& resourcename) = 0;
    virtual void close() = 0;
    virtual bool isOpen() const = 0;
    virtual void read() = 0;
    virtual void write(const std::string& data) = 0;
};

class FileHandler : public ResourceHandler {
private:
    std::fstream file;
    std::string filename;

public:
    bool open(const std::string& resourcename) override {
        filename = resourcename;
        file.open(filename, std::ios::in | std::ios::out | std::ios::app);
        return file.is_open();
    }

    void close() override {
        if (file.is_open()) file.close();
    }

    bool isOpen() const override {
        return file.is_open();
    }

    void read() override {
        if (!isOpen()) {
            std::cerr << "File is not open for reading\n";
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }
        file.clear();
        file.seekg(0, std::ios::beg);
    }

    void write(const std::string& data) override {
        if (!isOpen()) {
            std::cerr << "File is not open for writing\n";
            return;
        }
        file << data << std::endl;
    }
};

class NetworkHandler : public ResourceHandler {
private:
    bool connected = false;
    std::string endpoint;

public:
    bool open(const std::string& resourcename) override {
        endpoint = resourcename;
        connected = true;
        std::cout << "Connected to " << endpoint << '\n';
        return connected;
    }

    void close() override {
        if (connected) {
            std::cout << "Disconnected from " << endpoint << '\n';
            connected = false;
        }
    }

    bool isOpen() const override {
        return connected;
    }

    void read() override {
        if (!isOpen()) {
            std::cerr << "Network connection is not open\n";
            return;
        }
        std::cout << "Receiving data from " << endpoint << '\n';
    }

    void write(const std::string& data) override {
        if (!isOpen()) {
            std::cerr << "Network connection is not open\n";
            return;
        }
        std::cout << "Sending data to " << endpoint << ": " << data << '\n';
    }
};

class MemoryHandler : public ResourceHandler {
private:
    bool allocated = false;
    std::vector<char> memoryBuffer;

public:
    bool open(const std::string& resourcename) override {
        allocated = true;
        memoryBuffer.clear();
        std::cout << "Memory resource " << resourcename << " allocated\n";
        return allocated;
    }

    void close() override {
        if (allocated) {
            memoryBuffer.clear();
            allocated = false;
            std::cout << "Memory resource released\n";
        }
    }

    bool isOpen() const override {
        return allocated;
    }

    void read() override {
        if (!isOpen()) {
            std::cerr << "Memory resource is not allocated\n";
            return;
        }
        std::cout << "Memory contents: " << std::string(memoryBuffer.begin(), memoryBuffer.end()) << '\n';
    }

    void write(const std::string& data) override {
        if (!isOpen()) {
            std::cerr << "Memory resource is not allocated\n";
            return;
        }
        memoryBuffer.insert(memoryBuffer.end(), data.begin(), data.end());
        std::cout << "Data written to memory\n";
    }
};