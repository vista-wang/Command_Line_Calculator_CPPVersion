#include <iostream>
#include <map>
#include <string>
#include <stdexcept>

using namespace std;
namespace vars{
	map<string, float> vars = {
		{"test", 114514}
	};
}

namespace func{
	//判断
	bool isnumber(const string& value, float& out)
	{
		//这一段try和catch是照着DeepSeek给的示例代码写的，什么意思去问DeepSeek
		try{
			size_t pos = 0;
			out = stof(value, &pos);
			while(pos < value.length() && isspace(value[pos])){
				++pos;
			}
			return pos == value.length();
		}catch(const exception&){
			return false;
		}
	}

	//输出
	int print(const string& out)
	{
		if(vars::vars.find(out) == vars::vars.end()){
			cout << "error 03: undefined variables" << endl;
			return 1;
		}
		cout << vars::vars[out] << endl;
		return 0;
	}

	//赋值
	int set(const float& num,const string& name)
	{
		vars::vars[name] = num;
		cout << name << " = " << num << endl;
		return 0;
	}

	//加
	int add(const float& num,const string& name)
	{
		vars::vars[name] += num;
		cout << name << " = " << vars::vars[name] << endl;
		return 0;
	}

	//减
	int sub(const float& num,const string& name)
	{
		vars::vars[name] -= num;
		cout << name << " = " << vars::vars[name] << endl;
		return 0;
	}

	//乘
	int mul(const float& num,const string& name)
	{
		vars::vars[name] *= num;
		cout << name << " = " << vars::vars[name] << endl;
		return 0;
	}

	//除
	int div(const float& num,const string& name)
	{
		vars::vars[name] /= num;
		cout << name << " = " << vars::vars[name] << endl;
		return 0;
	}

	//方
	int fang(const float& num,const string& name)
	{
		if (num < 0)
		{
			const float num2 = -num;
			float i = 0;
			while (i <= num2)
			{
				vars::vars[name] *= num2;
				i += 1;
			}
			vars::vars[name] = 1 / vars::vars[name];
		}else{
			float i = 0;
			while (i < num)
			{
				vars::vars[name] *= vars::vars[name];
				i += 1;
			}
		}
		cout << name << " = " << vars::vars[name] << endl;
		return 0;
	}

	//开方
	int srt(const float& num,const string& name)
	{
		int num2 = static_cast<int>(num);
		if (num2 < 0)
		{
			cout << "error 06: Negative index" << endl;
		}else if (vars::vars[name] < 0 && num2 % 2 == 0)
		{
			cout << "error 05: Unsupported digital domains" << endl;
		}else if (vars::vars[name] > 0 && num2 % 2 != 0)
		{
			num2 = -num2;
			vars::vars[name] = std::pow(vars::vars[name], 1.0/num2);
		}else{
			vars::vars[name] = std::pow(vars::vars[name], 1.0/num2);
		}
		return 0;
	}
}

int command_switch(const string& command,const string& a,const string& b)
{
	if(command == "print"){
		func::print(a);
		return 0;
	}
	float num = 0;
	if (not func::isnumber(a,num))
	{
		cout << "error 04: use non-real numbers to assign values" << endl;
		return 1;
	}
	if(a.empty()){
		cout << "error 02: first input is empty " << endl;
		return 1;
	}
	if(command == "set"){
		func::set(num, b);
		return 0;
	}
	if (command == "add")
	{
		func::add(num, b);
	}
	if (command == "sub")
	{
		func::sub(num, b);
	}
	if (command == "mul")
	{
		func::mul(num, b);
	}
	if (command == "div")
	{
		func::div(num, b);
	}
	if (command == "fang")
	{
		func::fang(num, b);
	}
	if (command == "srt")
	{
		func::srt(num, b);
	}
	cout << "error 01: incorrect command" <<endl;
	return 1;

}

int input_command(){
	string command, input_a, input_b;
	cout << "calculator>";
	cin >> command >> input_a >> input_b;
	command_switch(command, input_a, input_b);
	return 0;
}

[[noreturn]] int main(){
	string version = "InDev VERSION";
	cout << "Welcome to use the COMMAND LINE CALCULATOR (C++ remake version)" << version << "!" << endl;
	while(true){
		input_command();
	}
}

