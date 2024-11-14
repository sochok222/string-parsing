#include<cctype>
#include<iostream>
#include<stack>
#include<string>


// this is recursion function to calculate given string

std::pair<int, std::string> calculate(std::string str) 
{
	std::stack<int> stk;
	std::string buffer;
	char lastOperator = '+';
	int num = 0;

	while (!str.empty())
	{
		char el = str[0];
		str.erase(0, 1);

		if (std::isdigit(el) || (el == '-' && (buffer.empty() || buffer == "-")))
		{
			buffer += el;
		}
		else if (!std::isdigit(el))
		{
			if (el == '(' && buffer == "-")
			{
				auto [newValue, newStr] = calculate(str); // recursion begins at this point when we met '(', and return value inside "()"
				stk.push(-newValue);
				str = newStr;
				buffer.clear();
			}
			else if (el == '(')
			{
				auto [newValue, newStr] = calculate(str);
				if (lastOperator == '*')
				{
					int prevValue = stk.top();
					stk.pop();
					stk.push(prevValue * newValue);
				}
				else if (lastOperator == '/')
				{
					int prevValue = stk.top();
					stk.pop();
					stk.push(prevValue / newValue);
				}
				else {
					stk.push(newValue);
				}
				str = newStr;
				buffer.clear();
			}
			else
			{
				if (!buffer.empty())
				{
					if (lastOperator == '+')
					{
						stk.push(std::stoi(buffer));
					}
					else if (lastOperator == '-')
					{
						stk.push(-std::stoi(buffer));
					}
					else if (lastOperator == '*')
					{
						int top = stk.top();
						stk.pop();
						stk.push(std::stoi(buffer) / top);
					}
					else if (lastOperator == '/')
					{
						int top = stk.top();
						stk.pop();
						stk.push(std::stoi(buffer) / top);
					}
					buffer.clear();
				}
				lastOperator = el;
			}
			if (el == ')')
			{
				break;
			}
		}
	}
	int res = 0;
	while (!stk.empty())
	{
		res += stk.top();
		stk.pop();
	}

	return { res, str };
}

int main()
{
	std::string str = "10*(-2+(3))"; // my program can't calculate correctly string like: 10-(-2) 
	int result = calculate(str).first;

	std::cout << "Result: " << result << std::endl;

	return 0;
}