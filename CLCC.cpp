#include <iostream>
#include <string>
#include <map>

//这里引用的头文件你问DeepSeek是干嘛的，DS示例代码里加的
#include <stdexcept>

using namespace std;
namespace vars{
	map<string, float> vars = {
		{"test", 114514}
	};
}

namespace func{
	int print(const string& out){
		if(vars::vars.find(out) == vars::vars.end()){
			cout << "error 03: undefined variables" << endl;
			return 1;
		}
		cout << vars::vars[out] << endl;
		return 0;
	}
	bool isnumber(const string& value, float& out){
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
	int set(const string& value,const string& name)
	{
		float num = 0;
		if(isnumber(value,num)){
			vars::vars[name] = num;
			cout << name << " = " << num << endl;
		}else{
			cout << "error 04: use non-real numbers to assign values" << endl;
			return 1;
		}
		return 0;
	}
}

int command_switch(const string& command,const string& a,const string& b)
{
	if(a.empty()){
		cout << "error 02: first input is empty " << endl;
		return 1;
	}
	if(command == "print"){
		func::print(a);
		return 0;
	}
	if(command == "set"){
		func::set(a, b);
		return 0;
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
	string version = "INDEV VERSION";
	cout << "Welcome to use the COMMAND LINE CALCULATOR (C++ remake version)" << version << "!" << endl;
	while(true){
		input_command();
	}
}

