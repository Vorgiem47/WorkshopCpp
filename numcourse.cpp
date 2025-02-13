
class ResourceHandler {
public:
    virtual ~ResourceHandler() = default;
    virtual bool open(const std::string& resourcename) = 0;
    virtual void close() = 0;
    virtual bool isOpen() const = 0;
    virtual void read() = 0;
    virtual void write(const std::string& data) = 0;
};