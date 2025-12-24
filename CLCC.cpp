#include <iostream>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <cctype>

namespace vars {
    std::unordered_map<std::string, double> vars = {
        {"test", 114514.0}
    };
}

namespace func {
    // 判断字符串是否为数字并输出其值
    bool isnumber(const std::string& value, double& out) {
        try {
            size_t pos = 0;
            out = std::stod(value, &pos);
            while (pos < value.length() && std::isspace(static_cast<unsigned char>(value[pos]))) {
                ++pos;
            }
            return pos == value.length();
        } catch (const std::exception&) {
            return false;
        }
    }

    // 输出变量
    int print(const std::string& name) {
        auto it = vars::vars.find(name);
        if (it == vars::vars.end()) {
            std::cout << "error 03: undefined variables" << std::endl;
            return 1;
        }
        std::cout << it->second << std::endl;
        return 0;
    }

    // 赋值（可以创建新变量）
    int set(const double& num, const std::string& name) {
        vars::vars[name] = num;
        std::cout << name << " = " << num << std::endl;
        return 0;
    }

    // 加/减/乘/除（操作必须在已定义变量上进行）
    int add(const double& num, const std::string& name) {
        auto it = vars::vars.find(name);
        if (it == vars::vars.end()) {
            std::cout << "error 03: undefined variables" << std::endl;
            return 1;
        }
        it->second += num;
        std::cout << name << " = " << it->second << std::endl;
        return 0;
    }

    int sub(const double& num, const std::string& name) {
        auto it = vars::vars.find(name);
        if (it == vars::vars.end()) {
            std::cout << "error 03: undefined variables" << std::endl;
            return 1;
        }
        it->second -= num;
        std::cout << name << " = " << it->second << std::endl;
        return 0;
    }

    int mul(const double& num, const std::string& name) {
        auto it = vars::vars.find(name);
        if (it == vars::vars.end()) {
            std::cout << "error 03: undefined variables" << std::endl;
            return 1;
        }
        it->second *= num;
        std::cout << name << " = " << it->second << std::endl;
        return 0;
    }

    int div(const double& num, const std::string& name) {
        if (num == 0.0) {
            std::cout << "error 07: division by zero" << std::endl;
            return 1;
        }
        auto it = vars::vars.find(name);
        if (it == vars::vars.end()) {
            std::cout << "error 03: undefined variables" << std::endl;
            return 1;
        }
        it->second /= num;
        std::cout << name << " = " << it->second << std::endl;
        return 0;
    }

    // 幂运算：将变量的值提升到 num 次幂
    int fang(const double& num, const std::string& name) {
        auto it = vars::vars.find(name);
        if (it == vars::vars.end()) {
            std::cout << "error 03: undefined variables" << std::endl;
            return 1;
        }
        double base = it->second;
        // 如果底数为负数且指数不是整数，则不支持
        double intpart;
        if (base < 0.0 && std::modf(num, &intpart) != 0.0) {
            std::cout << "error 05: Unsupported digital domains" << std::endl;
            return 1;
        }
        it->second = std::pow(base, num);
        if (std::isnan(it->second) || std::isinf(it->second)) {
            std::cout << "error 08: numeric result out of range" << std::endl;
            return 1;
        }
        std::cout << name << " = " << it->second << std::endl;
        return 0;
    }

    // 开方：计算变量的 n 次方根（只接受正整数 n）
    int srt(const double& num, const std::string& name) {
        auto it = vars::vars.find(name);
        if (it == vars::vars.end()) {
            std::cout << "error 03: undefined variables" << std::endl;
            return 1;
        }
        double intpart;
        if (std::modf(num, &intpart) != 0.0) {
            std::cout << "error 09: root index must be an integer" << std::endl;
            return 1;
        }
        int n = static_cast<int>(num);
        if (n <= 0) {
            std::cout << "error 06: Negative or zero index" << std::endl;
            return 1;
        }
        double value = it->second;
        if (value < 0.0 && n % 2 == 0) {
            std::cout << "error 05: Unsupported digital domains" << std::endl;
            return 1;
        }
        it->second = std::pow(value, 1.0 / n);
        if (std::isnan(it->second) || std::isinf(it->second)) {
            std::cout << "error 08: numeric result out of range" << std::endl;
            return 1;
        }
        std::cout << name << " = " << it->second << std::endl;
        return 0;
    }
}

int command_switch(const std::string& command, const std::string& a, const std::string& b) {
    if (command == "print") {
        return func::print(a);
    }

    if (a.empty()) {
        std::cout << "error 02: first input is empty " << std::endl;
        return 1;
    }

    double num = 0.0;
    if (!func::isnumber(a, num)) {
        // 如果 a 不是数字，则尝试把它当成已定义的变量名
        auto it = vars::vars.find(a);
        if (it == vars::vars.end()) {
            std::cout << "error 04: use non-real numbers to assign values" << std::endl;
            return 1;
        }
        num = it->second; // 修复：正确把变量的值赋给 num，而不是把字符串覆盖
    }

    if (command == "set") {
        return func::set(num, b);
    }
    if (command == "add") {
        return func::add(num, b);
    }
    if (command == "sub") {
        return func::sub(num, b);
    }
    if (command == "mul") {
        return func::mul(num, b);
    }
    if (command == "div") {
        return func::div(num, b);
    }
    if (command == "fang") {
        return func::fang(num, b);
    }
    if (command == "srt") {
        return func::srt(num, b);
    }
    std::cout << "error 01: incorrect command" << std::endl;
    return 1;
}

int input_command() {
    std::string line;
    std::cout << "calculator <<< ";
    if (!std::getline(std::cin, line)) {
        return 1; // EOF or error
    }
    std::istringstream iss(line);
    std::string command, input_a, input_b;
    iss >> command >> input_a >> input_b;
    if (command.empty()) {
        return 0; // ignore empty lines
    }
    command_switch(command, input_a, input_b);
    return 0;
}

int main() {
    const std::string version = "Alpha 0.1.2";
    std::cout << "Welcome to use the COMMAND LINE CALCULATOR (C++ remake version) " << version << "!" << std::endl;
    while (true) {
        if (input_command() != 0) {
            break; // exit on EOF or read error
        }
    }
    return 0;
}
